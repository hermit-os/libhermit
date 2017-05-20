use std::env;
use std::process::{Stdio, Child, Command};
use libc;
use std::fs::File;
use std::io::Read;
use std::process::{ChildStdout, ChildStderr};

use hermit::Isle;
use hermit::utils;
use hermit::error::*;
use hermit::hermit_env;
use hermit::socket::Socket;

const PIDNAME: &'static str = "/tmp/hpid-XXXXXX";
const TMPNAME: &'static str = "/tmp/hermit-XXXXXX";

#[derive(Debug)]
pub struct QEmu {
    socket: Socket,
    child: Child,
    stdout: ChildStdout,
    stderr: ChildStderr,
    tmp_file: String,
    pid_file: String,
}

impl QEmu {
    pub fn new(path: &str) -> Result<QEmu> {
        let tmpf = utils::create_tmp_file(TMPNAME)?;
        let pidf = utils::create_tmp_file(PIDNAME)?;

        let mut child = QEmu::start_with(path, &tmpf, &pidf)?.spawn().expect("Couldn't find qemu binary!");
        let stdout = child.stdout.take().unwrap();
        let stderr = child.stderr.take().unwrap();

        Ok(QEmu {
            socket: Socket::new_qemu(),
            child: child,
            stdout: stdout,
            stderr: stderr,
            tmp_file: tmpf,
            pid_file: pidf
        })
    }
    
    pub fn start_with(path: &str, tmp_file: &str, pid_file: &str) -> Result<Command> {
        let hostfwd = format!("user,hostfwd=tcp:127.0.0.1:{}-:{}", hermit_env::port(), hermit_env::port());
        let monitor_str = format!("telnet:127.0.0.1:{},server,nowait", (hermit_env::port().parse::<u32>().unwrap()+1).to_string());
        let chardev = format!("file,id=gnc0,path={}",&tmp_file);
        let freq = format!("\"-freq{} -proxy\"",(utils::cpufreq().unwrap()/1000).to_string());
        let cpus = hermit_env::num_cpus();
        let mem_size = hermit_env::mem_size();

        let exe = env::current_exe().unwrap();
        let name = exe.to_str().unwrap();
        let exe_path  = name.split("/").take(name.matches('/').count()).collect::<Vec<&str>>().join("/");

        let exe = format!("{}/ldhermit.elf", exe_path);

        let mut port_str;

        let mut args: Vec<&str> = vec![
            "-daemonize",
            "-display", "none",
            "-smp", &cpus,
            "-m", &mem_size,
            "-pidfile", pid_file,
            "-net", "nic,model=rtl8139",
            "-net", &hostfwd,
            "-chardev", &chardev,
            "-device", "pci-serial,chardev=gnc0",
            "-kernel", &exe,
            "-initrd", path,
            "-append", &freq];

        let app_port = hermit_env::app_port();
        if app_port != "" {
            port_str = format!("{},hostfwd=tcp::{}-:{}", hostfwd,app_port, app_port);
            args[12] = &port_str;
        }

        if hermit_env::use_kvm() != "0" {
            args.push("-machine");
            args.push("accel=kvm");
            args.push("-cpu");
            args.push("host");
        }

        if hermit_env::monitor() != "0" {
            args.push("-monitor");
            args.push(&monitor_str);
        }

        if hermit_env::should_debug() != "0" {
            args.push("-s");
        }

        if hermit_env::capture_net() != "0" {
            args.push("-net");
            args.push("dump");
        }

        if hermit_env::verbose() != "0" {
            println!("{:#?}", args);
        }

        debug!("Execute {} with args {:#?}", hermit_env::qemu_binary(), args);

        let mut cmd = Command::new(hermit_env::qemu_binary());

        cmd.args(args).stdout(Stdio::piped()).stderr(Stdio::piped());


        Ok(cmd)
    }

    pub fn output(&mut self) -> (String, String) {
        let mut stderr = String::new();
        let mut stdout = String::new();

        self.stdout.read_to_string(&mut stdout);
        self.stderr.read_to_string(&mut stderr);

        (stdout, stderr)
    }
}

impl Isle for QEmu {
    fn num(&self) -> u8 { 0 }
    fn log_file(&self) -> Option<String> {
        Some(self.tmp_file.clone())
    }
    fn log_path(&self) -> Option<String> {
        Some("/tmp".into())
    }
    fn cpu_path(&self) -> Option<String> {
        None 
    }

    fn run(&mut self) -> Result<()> {
        self.socket.connect().run();

        Ok(())
    }
}

impl Drop for QEmu {
    fn drop(&mut self) {
        let mut id_str = String::new();
        let mut file = File::open(&self.pid_file).unwrap();
        file.read_to_string(&mut id_str);
        id_str.pop();

        let id = id_str.parse::<i32>().unwrap();

        if id >= 0 {
            unsafe { libc::kill(id, libc::SIGINT); }
        }

        utils::delete_tmp_file(&self.pid_file);
        utils::delete_tmp_file(&self.tmp_file);
    }
}
