pub mod error;
mod utils;
mod hermit_env;
mod qemu;
mod multi;
mod proto;
mod socket;
mod uhyve;

use std::fs::File;
use std::path::Path;
use std::io::{Write, Read, BufReader, BufRead};
use inotify::{Inotify, watch_mask};

use hermit::qemu::QEmu;
use hermit::multi::Multi;
use hermit::uhyve::uhyve::Uhyve;

use hermit::error::*;

pub fn new_isle(path: &str) -> Result<Box<Isle>> {
    let isle = hermit_env::isle_kind();
    
    debug!("Create a new {} isle", isle);
    
    match isle.as_str() {
        "qemu"=> Ok(Box::new(QEmu::new(path)?)),
        "uhyve" => Ok(Box::new(Uhyve::new(path)?)),
        s => Ok(Box::new(Multi::new(s.parse::<u8>().unwrap_or(0), path)?))
    }
}

pub trait Isle {
    fn num(&self) -> u8;
    fn log_file(&self) -> Option<String>;
    fn log_path(&self) -> Option<String>;
    fn cpu_path(&self) -> Option<String>;

    fn run(&mut self) -> Result<()>;

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

    fn stop(&self) -> Result<()> {
        debug!("Stop the HermitIsle");
       
        let cpu_path = match self.cpu_path() {
            Some(f) => f,
            None => return Ok(())
        };

        let mut cpus_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;

        cpus_file.write("-1".as_bytes())
            .map_err(|_| Error::InvalidFile(cpu_path));
    
        Ok(())
    }
}
