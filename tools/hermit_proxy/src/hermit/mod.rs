pub mod error;
mod utils;
pub mod qemu;
pub mod multi;
mod proto;
mod socket;
pub mod uhyve;

use std::fs::File;
use std::path::Path;
use std::io::{Write, Read, BufReader, BufRead};
use inotify::{Inotify, watch_mask};
use std::env;
use std::os::unix::net::UnixStream;
use std::sync::Arc;
use std::sync::Mutex;

use hermit::qemu::QEmu;
use hermit::multi::Multi;
use hermit::uhyve::uhyve::Uhyve;

use hermit::error::*;

#[derive(Deserialize, Serialize, Debug, Clone)]
pub struct IsleParameterQEmu {
    binary: String,
    use_kvm: bool,
    monitor: bool,
    capture_net:bool,
    port: u16,
    should_debug: bool,
    app_port: u16
}

#[derive(Deserialize, Serialize, Debug, Clone)]
pub enum IsleParameter {
    QEmu {
        mem_size: u64,
        num_cpus: u32,
        additional: IsleParameterQEmu
    },
    UHyve {
        mem_size: u64,
        num_cpus: u32
    },
    Multi {
        mem_size: u64,
        num_cpus: u32
    }
}

impl IsleParameter {
    pub fn from_env() -> IsleParameter {
        let isle_kind = env::var("HERMIT_ISLE").unwrap_or("qemu".into());
        let mem_size: u64 = env::var("HERMIT_MEM").map(|x| utils::parse_mem(&x).unwrap_or(512*1024*1024)).unwrap_or(512*1024*1024);
        let num_cpus: u32 = env::var("HERMIT_CPUS").map(|x| x.parse().unwrap_or(1)).unwrap_or(1);

        match isle_kind.as_str() {
            "multi" | "MULTI" | "Multi" => {
                IsleParameter::Multi {
                    mem_size: mem_size,
                    num_cpus: num_cpus
                }
            },
            "uhyve" | "UHyve" | "UHYVE" => {
                IsleParameter::UHyve {
                    mem_size: mem_size,
                    num_cpus: num_cpus
                }
            },
            _ => {
                let binary = env::var("HERMIT_BINARY").unwrap_or("qemu-system-x86_64".into());
                let kvm = env::var("HERMIT_KVM").map(|x| x.parse().unwrap_or(true)).unwrap_or(true);
                let monitor = env::var("HERMIT_MONITOR").map(|x| x.parse().unwrap_or(false)).unwrap_or(false);
                let capture_net = env::var("HERMIT_CAPTURE_NET").map(|x| x.parse().unwrap_or(false)).unwrap_or(false);
                let port = env::var("HERMIT_PORT").map(|x| x.parse().unwrap_or(18766)).unwrap_or(18766);
                let app_port = env::var("HERMIT_APP_PORT").map(|x| x.parse().unwrap_or(0)).unwrap_or(0);
                let debug = env::var("HERMIT_DEBUG").map(|x| x.parse().unwrap_or(false)).unwrap_or(false);

                IsleParameter::QEmu {
                    mem_size: mem_size,
                    num_cpus: num_cpus,
                    additional: IsleParameterQEmu {
                        binary: binary,
                        use_kvm: kvm,
                        monitor: monitor,
                        capture_net: capture_net,
                        port:port,
                        app_port: app_port,
                        should_debug: debug
                    }
                }
            }
        }
    }
}

pub trait Isle {
    fn num(&self) -> u8;
    fn log_file(&self) -> Option<String>;
    fn log_path(&self) -> Option<String>;
    fn cpu_path(&self) -> Option<String>;

    fn output(&self) -> Result<String>;

    fn stop(&mut self) -> Result<i32>;
    fn run(&mut self) -> Result<()>;

    fn is_running(&mut self) -> Result<bool>;

    fn add_endpoint(&mut self, stream: UnixStream) -> Result<()>;

    fn is_available(&self) -> Result<bool> {
        let log = match self.log_file() {
            Some(f) => f,
            None => return Ok(false)
        };

        // open the log file
        let mut file = File::open(log)
            .map_err(|x| Error::InvalidFile(format!("{:?}",x)))?;

        let mut reader = BufReader::new(file);
       
        for line in reader.lines() {
            if line.unwrap().contains("TCP server is listening.") {
                debug!("Found key token, continue");
                return Ok(true);
            }
        }

        Ok(false)
    }

    fn wait_until_available(&self) -> Result<()> {
        debug!("Wait for the HermitIsle to be available");

        let mut ino = Inotify::init().unwrap();

        // watch on the log path
        let log_path = match self.log_path() {
            Some(f) => f,
            None => return Ok(())
        };

        ino.add_watch(Path::new(&log_path), watch_mask::MODIFY | watch_mask::CREATE).unwrap();

        let mut buffer = [0; 1024];
        loop {
            if let Some(_) = ino.read_events(&mut buffer).unwrap().next() {
                if self.is_available()? {
                    return Ok(());
                }
            }

            /*
            if let IsleKind::QEMU(ref mut obj) = *self {
                let (stdout,stderr) = obj.output();
                
                if stderr != "" {
                    return Err(Error::QEmu((stdout, stderr)));
                }

                if stdout != "" {
                    debug!("stdout: {}", stdout);
                }
            }*/
        }
    }

}
