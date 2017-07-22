use std::net::TcpStream;
use std::env;
use std::mem::transmute;
use std::io::{Write, Read, Cursor};
use std::ffi::CString;
use std::ffi::CStr;
use std::process;
use byteorder::{ReadBytesExt, WriteBytesExt, LittleEndian};
use std::sync::Arc;
use std::sync::Mutex;
use std::os::unix::net::UnixStream;
use bincode::{serialize, Infinite};

use hermit::proto;
use hermit::proto::Packet;
use hermit::error::{Error, Result};

use daemon::ActionResult;

use libc;

const HERMIT_MAGIC: u32 = 0x7E317;

pub type Console = Arc<Mutex<Vec<Arc<Mutex<UnixStream>>>>>;

#[derive(Debug)]
pub struct Socket {
    stream: Option<TcpStream>, 
    console: Console
}

impl Socket {
    pub fn new() -> Socket {
        Socket { stream: None, console: Arc::new(Mutex::new(Vec::new())) }
    }

    pub fn connect(&mut self) -> Result<()> {
        // prepare the initializing struct
        let length: usize = 4 + env::args().skip(2).map(|x| 4+x.len()).sum::<usize>() + 
                            4 + env::vars().map(|(x,y)| 5 + x.len()+ y.len()).sum::<usize>();

        let mut buf = Cursor::new(vec![0u8;length]);

        // initialize the connection with the magic number
        buf.write_u32::<LittleEndian>(HERMIT_MAGIC);
        // send all arguments (skip first)
        buf.write_u32::<LittleEndian>(env::args().count() as u32 - 2);
        for key in env::args().skip(2) {
            buf.write_u32::<LittleEndian>(key.len() as u32);
            buf.write(key.as_bytes());
        }

        // send the environment
        buf.write_u32::<LittleEndian>(env::vars().count() as u32);
        for (val,key) in env::vars() {
            let tmp = format!("{}={}", val, key);
            buf.write_u32::<LittleEndian>(tmp.len() as u32);
            buf.write(tmp.as_bytes());
        }

        let mut stream;
        loop {
            match TcpStream::connect(("127.0.0.1", 0x494E)) {
                Ok(mut s) => { 
                    match s.write(buf.get_ref()) {
                        Ok(_) => { stream = s; break; },
                        Err(_) => {}
                    }
                },

                Err(_) => {}
            }
        }

        self.stream = Some(stream);

        debug!("Connected to {}", self.stream()?.peer_addr().unwrap());
        debug!("Transmitted environment and arguments with length {}", length);

        Ok(())
    }

    pub fn console(&self) -> Console {
        self.console.clone()
    }

    pub fn stream(&self) -> Result<&TcpStream> {
        self.stream.as_ref().ok_or(Error::InternalError)
    }

    pub fn run(&mut self) -> Result<()> {
        debug!("Initializing protocol state machine");
        let mut state = proto::State::Id;
        let mut stream = self.stream()?;

        let mut cur = Cursor::new(vec![]);
        let mut buf = [0u8; 4096];
        'main: loop {
            debug!("Attempt read");
            let nread =  stream.read(&mut buf).unwrap();

            let old_position = cur.position();
            let end = cur.get_ref().len() as u64;

            cur.set_position(end);
            cur.write(&buf[0..nread]);
            cur.set_position(old_position);

            debug!("Got message with {} bytes: {:?}", nread, &buf[0 .. nread]);

            let mut old_position = cur.position();

            loop {
                state = state.read_in(&mut cur);
                
                if let proto::State::Finished(packet) = state {
                    unsafe {
                    match packet {
                        Packet::Exit { arg } => break 'main,
                        Packet::Write { fd, buf } => {
                            let buf_ret: [u8;8] = transmute(libc::write(fd as i32, buf.as_ptr() as *const libc::c_void, buf.len()).to_le());
                            
                            if fd == 1 {
                                let ret = ActionResult::Output(String::from_utf8_unchecked(buf));
                                let buf: Vec<u8> = serialize(&ret, Infinite).unwrap();
                                
                                for stream in self.console.lock().unwrap().iter_mut() {
                                    stream.lock().unwrap().write(&buf).unwrap();
                                }
                                //stdout.push_str(&String::from_utf8_unchecked(buf));
                            } else if fd == 2 {
                                let ret = ActionResult::OutputErr(String::from_utf8_unchecked(buf));
                                let buf: Vec<u8> = serialize(&ret, Infinite).unwrap();

                                for stream in self.console.lock().unwrap().iter_mut() {
                                    stream.lock().unwrap().write(&buf).unwrap();
                                }
                                //stderr.push_str(&String::from_utf8_unchecked(buf));
                            } else {
                                stream.write(&buf_ret);
                            }
                        },
                        Packet::Open { name, mode, flags } => {
                            let buf: [u8; 4] = transmute(libc::open(name.as_ptr(), flags as i32, mode as i32).to_le());
                            debug!("got {:?}", buf);
                            
                            let written = stream.write(&buf).unwrap();
                                
                            debug!("Written {}", written);
                        },
                        Packet::Close { fd } => {
                            let buf: [u8; 4] = transmute(libc::close(fd as i32).to_le());
                            stream.write(&buf);
                        },
                        Packet::Read { fd, len } => {
                            let mut tmp: Vec<u8> = vec![0; len as usize];
                            let got = libc::read(fd as i32, tmp.as_mut_ptr() as *mut libc::c_void, len as usize);
                            let buf: [u8; 8] = transmute(got.to_le());

                            debug!("Read size {:?}", buf);

                            stream.write(&buf);

                            if got > 0 {
                                stream.write(&tmp[..]);
                            }
                        },
                        Packet::LSeek { fd, offset, whence } => {
                            let buf: [u8; 8] = transmute(libc::lseek(fd as i32, offset, whence as i32).to_le());
                            stream.write(&buf);
                        }
                    };
                    }
                
                    state = proto::State::Id;
                }

                if cur.position() == old_position {
                    break;
                } else {
                    old_position = cur.position();
                }
            }
        }
        Ok(())
    }
}
