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
        // request a new isle, enforce close
        {
            let mut path_file = File::create(format!("/sys/hermit/isle{}/path", num)).map_err(|_| Error::InvalidFile)?;
            let mut cpus_file = File::create(format!("/sys/hermit/isle{}/cpus", num)).map_err(|_| Error::InvalidFile)?;
            
            let cpus = hermit_env::num_cpus();

            path_file.write_all(path.as_bytes()).map_err(|_| Error::InvalidFile)?;
            cpus_file.write_all(cpus.as_bytes()).map_err(|_| Error::InvalidFile)?;
        }

        // check the result
        let mut path_file = File::create(format!("/sys/hermit/isle{}/cpus", num)).map_err(|_| Error::InvalidFile)?;
        let mut result = String::new();
        
        path_file.read_to_string(&mut result).map_err(|_| Error::InvalidFile)?;
        
        if result.parse::<i32>().map_err(|_| Error::InvalidFile)? == -1 {
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
