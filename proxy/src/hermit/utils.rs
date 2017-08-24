use std::fs::File;
use std::os::unix::io::FromRawFd;
use std::ffi::CString;
use std::io::Read;

use hermit::error::*;

use libc;

/// Returns the CPU frequency
pub fn cpufreq() -> Result<u32> {
    let mut content = String::new();
   
    // If the file cpuinfo_max_freq exists, parse the content and return the frequency
    if let Ok(mut file) = File::open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq") {
        file.read_to_string(&mut content).unwrap();
        return content.trim().parse::<u32>().map_err(|_| Error::MissingFrequency);
    } 
    // otherwise use the more acurate cpuinfo file and search for the right line
    else if let Ok(mut file) = File::open("/proc/cpuinfo") {
        file.read_to_string(&mut content).expect("Couldnt read!");
    
        for line in content.lines() {
            if line.starts_with("cpu MHz") {
                return line.split(':').skip(1).next().unwrap().trim().parse::<f32>().map_err(|_| Error::MissingFrequency).map(|x| x as u32);
            }
        }
    }

    // ups shouldn't happened ..
    Err(Error::MissingFrequency)
}

pub fn parse_mem(mem: &str) -> Result<u64> {
    let (num, postfix): (String, String) = mem.chars().partition(|&x| x.is_numeric());
    let num = num.parse::<u64>().map_err(|_| Error::ParseMemory)?;

    let factor = match postfix.as_str() {
        "E" | "e" => 1 << 60,
        "P" | "p" => 1 << 50,
        "T" | "t" => 1 << 40,
        "G" | "g" => 1 << 30,
        "M" | "m" => 1 << 20,
        "K" | "k" => 1 << 10,
        _ => return Err(Error::ParseMemory)
    };
   
    Ok(num*factor)
}

/// Creates a temporary file /tmp/<name>-XXXX, the X will be replaced by an arbitrary sequence
pub fn create_tmp_file(name: &str) -> Result<String> {
    unsafe {
        let c_str = CString::new(name).unwrap();
        let raw = c_str.into_raw();
        let res = libc::mkstemp(raw);

        if res < 0 {
            return Err(Error::CannotCreateTmpFile(res as usize));
        }

        let new_name = CString::from_raw(raw).into_string().unwrap();
        
        debug!("Created tmp file with name {}", new_name);
        
        Ok(new_name)
    }
}

/// Deletes a temporary file 
pub fn delete_tmp_file(name: &str) -> Result<()> {
    unsafe {
        let c_str = CString::new(name).unwrap();
        let res = libc::unlink(c_str.into_raw());

        debug!("Deleted tmp file {}", name);

        if res < 0 {
            return Err(Error::InvalidFile(name.into()));
        } else {
            return Ok(());
        }
    }
}
