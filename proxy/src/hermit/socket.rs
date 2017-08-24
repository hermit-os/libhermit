use std::net::TcpStream;
use std::{env, slice};
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

pub type Console = Arc<Mutex<Vec<UnixStream>>>;

#[derive(Debug)]
pub struct Socket {
    stream: Option<TcpStream>, 
    port: u16,
    console: Console
}

impl Socket {
    pub fn new(port: u16) -> Socket {
        Socket { stream: None, port: port, console: Arc::new(Mutex::new(Vec::new())) }
    }

    pub fn connect(&mut self) -> Result<()> {
        // prepare the initializing struct
        let length: usize = 4 + 4 + env::args().skip(2).map(|x| 4+x.len()+1).sum::<usize>() +
                            4 + env::vars().map(|(x,y)| 5 + x.len()+ y.len()).sum::<usize>();

        let mut buf = Cursor::new(vec![0u8;length]);

        // initialize the connection with the magic number
        buf.write_u32::<LittleEndian>(HERMIT_MAGIC);
        // send all arguments (skip first)
        buf.write_u32::<LittleEndian>(env::args().count() as u32 - 2);
        for key in env::args().skip(2) {
            buf.write_u32::<LittleEndian>(key.len() as u32 + 1);
            buf.write(key.as_bytes());
            buf.write_u8(b'\0');
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
            match TcpStream::connect(("127.0.0.1", self.port)) {
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
                            let mut buf_ret: [u8; 8];
                            if fd != 1 && fd != 2 {
                                buf_ret = transmute(libc::write(fd, buf.as_ptr() as *const libc::c_void, buf.len()).to_le());
                            } else {
                                let res = match fd {
                                    1 => ActionResult::Output(String::from_utf8_unchecked(buf)),
                                    2 => ActionResult::OutputErr(String::from_utf8_unchecked(buf)),
                                    _ => unreachable!()
                                };

                                let buf: Vec<u8> = serialize(&res, Infinite).unwrap();

                                // try to send the new console log to each endpoint and retain only
                                // the successfully ones.
                                self.console.lock().unwrap().retain(|mut x| x.write(&buf).is_ok());

                                buf_ret = transmute(buf.len());
                            }

                            stream.write(&buf_ret);
                        },
                        Packet::Open { name, mode, flags } => {
                            let mut buf: [u8; 4] = transmute(libc::open(name.as_ptr(), flags as i32, mode as i32).to_le());
                            let written = stream.write(&buf).unwrap();
                                
                        },
                        Packet::Close { fd } => {
                            let buf: [u8; 4] = transmute(libc::close(fd).to_le());
                            stream.write(&buf);
                        },
                        Packet::Read { fd, len } => {
                            let mut tmp: Vec<u8> = vec![0; len as usize];
                            let got = libc::read(fd, tmp.as_mut_ptr() as *mut libc::c_void, len as usize);
                            let buf: [u8; 8] = transmute(got.to_le());

                            stream.write(&buf);

                            if got > 0 {
                                stream.write(&tmp[..]);
                            }
                        },
                        Packet::LSeek { fd, offset, whence } => {
                            let buf: [u8; 8] = transmute(libc::lseek(fd, offset, whence as i32).to_le());
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
