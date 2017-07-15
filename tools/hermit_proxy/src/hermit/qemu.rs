use std::env;
use std::process::{Stdio, Child, Command};
use libc;
use std::fs::File;
use std::io::Read;
use std::process::{ChildStdout, ChildStderr};
use std::thread;
use std::os::unix::net::UnixStream;
use std::io::Write;

use hermit::{Isle, IsleParameterQEmu};
use hermit::utils;
use hermit::error::*;
use hermit::socket::Socket;

const PIDNAME: &'static str = "/tmp/hpid-XXXXXX";
const TMPNAME: &'static str = "/tmp/hermit-XXXXXX";

#[derive(Debug)]
pub struct QEmu {
    socket: Option<Socket>,
    child: Child,
    stdout: ChildStdout,
    stderr: ChildStderr,
    tmp_file: String,
    pid_file: String,
}

impl QEmu {
    pub fn new(path: &str, mem_size: u64, num_cpus: u32, additional: IsleParameterQEmu) -> Result<QEmu> {
        let tmpf = utils::create_tmp_file(TMPNAME)?;
        let pidf = utils::create_tmp_file(PIDNAME)?;

        let mut child = QEmu::start_with(path, mem_size, num_cpus, additional, &tmpf, &pidf)?.spawn().expect("Couldn't find qemu binary!");
        let stdout = child.stdout.take().unwrap();
        let stderr = child.stderr.take().unwrap();
        println!("{}", pidf);

        Ok(QEmu {
            socket: Some(Socket::new_qemu()),
            child: child,
            stdout: stdout,
            stderr: stderr,
            tmp_file: tmpf,
            pid_file: pidf,
        })
    }
    
    pub fn start_with(path: &str, mem_size: u64, num_cpus: u32, add: IsleParameterQEmu, tmp_file: &str, pid_file: &str) -> Result<Command> {
        let hostfwd = format!("user,hostfwd=tcp:127.0.0.1:{}-:{}", add.port, add.port);
        //let monitor_str = format!("telnet:127.0.0.1:{},server,nowait", add.port+1);
        let monitor_str = format!("unix:{}_monitor,server,nowait", pid_file);
        let chardev = format!("file,id=gnc0,path={}",&tmp_file);
        let freq = format!("\"-freq{} -proxy\"",(utils::cpufreq().unwrap()/1000).to_string());
        let num_cpus = num_cpus.to_string();
        let mem_size = format!("{}B", mem_size);

        let exe = env::current_exe().unwrap();
        let name = exe.to_str().unwrap();
        let exe_path  = name.split("/").take(name.matches('/').count()).collect::<Vec<&str>>().join("/");

        let exe = format!("{}/ldhermit.elf", exe_path);

        let mut port_str;

        let mut args: Vec<&str> = vec![
            "-daemonize",
            "-display", "none",
            "-smp", &num_cpus,
            "-m", &mem_size,
            "-pidfile", pid_file,
            "-net", "nic,model=rtl8139",
            "-net", &hostfwd,
            "-chardev", &chardev,
            "-device", "pci-serial,chardev=gnc0",
            "-kernel", &exe,
            "-initrd", path,
            "-append", &freq];

        let app_port = add.app_port;
        if app_port != 0 {
            port_str = format!("{},hostfwd=tcp::{}-:{}", hostfwd,app_port, app_port);
            args[12] = &port_str;
        }

        if add.use_kvm {
            args.push("-machine");
            args.push("accel=kvm");
            args.push("-cpu");
            args.push("host");
        }

        args.push("-monitor");
        args.push(&monitor_str);

        if add.should_debug {
            args.push("-s");
        }

        if add.capture_net {
            args.push("-net");
            args.push("dump");
        }

        debug!("Execute {} with {}", add.binary, args.join(" "));

        let mut cmd = Command::new(add.binary);

        cmd.args(args).stdout(Stdio::piped()).stderr(Stdio::piped());

        Ok(cmd)
    }

    pub fn qemu_log(&mut self) -> (String, String) {
        let mut stderr = String::new();
        let mut stdout = String::new();

        self.stdout.read_to_string(&mut stdout);
        self.stderr.read_to_string(&mut stderr);

        (stdout, stderr)
    }

    pub fn send_cmd(&self, cmd: &str) -> Result<String> {
        let file = format!("{}_monitor", self.pid_file);

        let mut control = UnixStream::connect(&file)
            .map_err(|_| Error::InvalidFile(file.clone()))?;
        
        control.write_all(cmd.as_bytes())
            .map_err(|_| Error::InvalidFile(file))?;

        let mut buf = String::new();

        control.read_to_string(&mut buf);

        Ok(buf)
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
        let socket = self.socket.take();

        thread::spawn(|| {
            socket.unwrap().connect().run();
        });

        Ok(())
    }

    fn output(&self) -> Result<String> {
        /*if let &Socket::Connected { ref stdout, ref stderr, .. } = &self.socket.unwrap() {
            Ok(stdout.clone())
        } else {
            Err(Error::InternalError)
        }*/

        Err(Error::InternalError)
    }

    fn stop(&mut self) -> Result<i32> {
        self.send_cmd("system_powerdown")?;

        Ok(0)
    }

    fn is_running(&mut self) -> Result<bool> {
        let state = self.send_cmd("info status")?;

        Ok(state == "running")
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