use std::env;
use std::fs::File;
use std::path::Path;
use std::io::{Write, Read, BufReader, BufRead};
use inotify::INotify;
use inotify::ffi::{IN_MODIFY, IN_CREATE};

use hermit_env;
use dedicate::qemu::QEmu;
use dedicate::multi::Multi;
use uhyve::Uhyve;
use uhyve::vm::VirtualMachine;
use error::*;

pub enum IsleKind {
    QEMU(QEmu),
    UHYVE((Uhyve, VirtualMachine)),
    MULTI(Multi)
}

impl IsleKind {
    pub fn new(path: &str) -> Result<IsleKind> {
        let isle = hermit_env::isle_kind();

        debug!("Create a new {} isle", isle);

        let isle = match isle.as_str() {
            "qemu"=>IsleKind::QEMU(QEmu::new(path)?),
            "uhyve" => {
                let uhyve = Uhyve::new();
                let mut vm = uhyve.create_vm(0x20000000)?;
                vm.load_kernel(path)?;
                vm.init()?;

                IsleKind::UHYVE((uhyve, vm))
            },
            s => IsleKind::MULTI(Multi::new(s.parse::<u8>().unwrap_or(0), path)?)
        };

        Ok(isle)
    }

    fn get_num(&self) -> u8 {
        match *self {
            IsleKind::QEMU(_) => 0,
            IsleKind::UHYVE(_) => 0,
            IsleKind::MULTI(ref s) => s.get_num()
        }
    }

    pub fn is_available(&self) -> Result<bool> {
        let mut file = match *self {
            IsleKind::QEMU(ref q) => File::open(q.tmp_path()),
            _ => File::open(format!("/sys/hermit/isle{}/log", self.get_num()))
        };

        let mut file = file.map_err(|x| Error::InvalidFile(format!("{:?}",x)))?;
        let mut reader = BufReader::new(file);

        //let mut result = String::new();
        //file.read_to_string(&mut result).map_err(|_| Error::InvalidFile)?;

        for line in reader.lines() {
            if line.unwrap().contains("TCP server is listening.") {
                debug!("Found key token, continue");
                return Ok(true);
            }
        }

        Ok(false)

        //debug!("HERMIT - isle log contains: {}", result);

        //Ok(result == "TCP server is listening.")
    }

    pub fn wait_available(&self) -> Result<()> {
        debug!("HERMIT - wait to be available");

        let mut ino = INotify::init().unwrap();

        match *self {
            IsleKind::QEMU(_) => ino.add_watch(Path::new("/tmp"), IN_MODIFY | IN_CREATE).unwrap(),
            IsleKind::MULTI(_) => ino.add_watch(Path::new("/sys/hermit"), IN_MODIFY | IN_CREATE).unwrap(),
            IsleKind::UHYVE(_) => return Ok(())
        };

        loop {
            let events = ino.wait_for_events().unwrap();

            if self.is_available()? {
                return Ok(());
            }
        }
    }

    pub fn stop(&self) -> Result<()> {
        let cpu_path = format!("/sys/hermit/isle{}/cpus", self.get_num());

        let mut cpus_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;

        cpus_file.write("-1".as_bytes())
            .map_err(|_| Error::InvalidFile(cpu_path));
    
        Ok(())
    }

    pub fn run(mut self) -> Result<()> {
        match self {
            IsleKind::UHYVE((_, mut vm)) => vm.run()?,
            IsleKind::QEMU(qemu) => qemu.run(),
            IsleKind::MULTI(multi) => multi.run()
        }

        Ok(())
    }
}
