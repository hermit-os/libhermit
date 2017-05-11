use std::fs::File;
use std::env;
use std::io::{Write, Read};

use error::*;

use hermit_env;
use dedicate::socket::Socket;

pub struct Multi {
    num: u8,
    socket: Socket
}

impl Multi {
    pub fn new(num: u8, path: &str) -> Result<Multi> {
        let cpu_path = format!("/sys/hermit/isle{}/path", num);
        let bin_path= format!("/sys/hermit/isle{}/cpus", num);

        // request a new isle, enforce close
        {
            let mut path_file = File::create(&bin_path)
                .map_err(|_| Error::InvalidFile(bin_path.clone()))?;

            let mut cpus_file = File::create(&cpu_path)
            .map_err(|_| Error::InvalidFile(cpu_path.clone()))?;
            
            let cpus = hermit_env::num_cpus();

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

        Ok(Multi { num: num, socket: Socket::new_multi(num) })
    }

    pub fn get_num(&self) -> u8 {
        self.num
    }

    pub fn run(&self) {
        self.socket.connect().run();
    }
}
