use std::fs::File;
use std::io::{Write, Read};
use std::thread;

use hermit::Isle;
use hermit::error::*;
use hermit::socket::Socket;

use std::os::unix::net::UnixStream;

pub struct Multi {
    num: u8,
    socket: Option<Socket>
}

impl Multi {
    pub fn new(num: u8, path: &str, mem_size: u64, num_cpus: u32) -> Result<Multi> {
        let cpu_path = format!("/sys/hermit/isle{}/path", num);
        let bin_path= format!("/sys/hermit/isle{}/cpus", num);
        debug!("Mem size: {}", mem_size);

        // request a new isle, enforce close
        {
            let mut path_file = File::create(&bin_path)
                .map_err(|_| Error::InvalidFile(bin_path.clone()))?;

            let mut cpus_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;
            
            let cpus = num_cpus.to_string();

            path_file.write_all(path.as_bytes())
                .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;
            
            cpus_file.write_all(cpus.as_bytes())
                .map_err(|_| Error::InvalidFile(bin_path))?;
        }

        // check the result
        let mut path_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;

        let mut result = String::new();
        
        path_file.read_to_string(&mut result)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;
        
        if result.parse::<i32>().map_err(|_| Error::InvalidFile(cpu_path))? == -1 {
            return Err(Error::MultiIsleFailed);
        }

        Ok(Multi { num: num, socket: Some(Socket::new(18766)) })
    }
}

impl Isle for Multi {
    fn num(&self) -> u8 {
        self.num
    }

    fn log_file(&self) -> Option<String> {
        Some(format!("/sys/hermit/isle{}/log", self.num))
    }

    fn log_path(&self) -> Option<String> {
        Some("/sys/hermit/".into())
    }

    fn cpu_path(&self) -> Option<String> {
        Some(format!("/sys/hermit/isle{}/cpus", self.num))
    }

    fn run(&mut self) -> Result<()> {
        let mut socket = self.socket.take().ok_or(Error::InternalError)?;
        socket.connect()?;

        thread::spawn(move || {
            
            socket.run();
        });

        Ok(())
    }

    fn output(&self) -> Result<String> {
        Ok("".into())
    }
    fn stop(&mut self) -> Result<i32> {
        debug!("Stop the HermitIsle");
       
        let cpu_path = match self.cpu_path() {
            Some(f) => f,
            None => return Ok(0)
        };

        let mut cpus_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;

        cpus_file.write("-1".as_bytes())
            .map_err(|_| Error::InvalidFile(cpu_path));
    
        Ok(0)
    }

    fn is_running(&mut self) -> Result<bool> {
        Ok(true)
    }

    fn add_endpoint(&mut self, _: UnixStream) -> Result<()> {
        Ok(())
    }
}
