use libc::{write, read, lseek, exit, open, close, c_int, c_void, c_char};
use super::kvm_header::{kvm_run, KVM_EXIT_IO, KVM_EXIT_HLT, KVM_EXIT_MMIO,KVM_EXIT_FAIL_ENTRY, KVM_EXIT_INTERNAL_ERROR, KVM_EXIT_SHUTDOWN }; 
use std::ffi::CStr;
use bincode::{serialize, Infinite};
use std::slice;

use super::{Error, Result};
use hermit::socket::Console;
use daemon::ActionResult;

const PORT_WRITE: u16 = 0x499;
const PORT_OPEN: u16 = 0x500;
const PORT_CLOSE: u16 = 0x501;
const PORT_READ: u16 = 0x502;
const PORT_EXIT: u16 = 0x503;
const PORT_LSEEK: u16 = 0x504;

#[repr(packed)]
pub struct Write {
    fd: i32,
    buf: isize,
    length: isize
}

#[repr(packed)]
pub struct Open {
    name: isize,
    flags: i32,
    mode: i32,
    ret: i32
}

#[repr(packed)]
pub struct Close {
    fd: i32,
    ret: i32
}

#[repr(packed)]
pub struct Read {
    fd: i32,
    buf: isize,
    len: usize,
    ret: isize
}

#[repr(packed)]
pub struct LSeek {
    fd: i32,
    whence: i32,
    offset: i64,
}

#[derive(Debug)]
pub enum Syscall {
    Write(*mut Write),
    Open(*mut Open),
    Close(*mut Close),
    Read(*mut Read),
    LSeek(*mut LSeek),
    Exit(*mut i32),
    Other(*const kvm_run)
}

#[derive(Debug)]
pub enum Return {
    Continue,
    Exit(i32)
}

impl Syscall {
    pub fn from_mem(mem: *const u8, guest_mem: *const u8) -> Syscall {
        unsafe {
            let ref run = *(mem as *const kvm_run);

            debug!("Exit reason {}", run.exit_reason);

            if run.exit_reason != KVM_EXIT_IO {
                return Syscall::Other(mem as *const kvm_run);
            }


            let offset = *((mem.offset(run.__bindgen_anon_1.io.data_offset as isize) as *const isize));
            
            match run.__bindgen_anon_1.io.port {
                PORT_WRITE => { Syscall::Write(guest_mem.offset(offset) as *mut Write) },
                PORT_READ  => { Syscall::Read (guest_mem.offset(offset) as *mut Read)  },
                PORT_CLOSE => { Syscall::Close(guest_mem.offset(offset) as *mut Close) },
                PORT_OPEN  => { Syscall::Open (guest_mem.offset(offset) as *mut Open ) },
                PORT_LSEEK => { Syscall::LSeek(guest_mem.offset(offset) as *mut LSeek) },
                PORT_EXIT  => { Syscall::Exit( guest_mem.offset(offset) as *mut i32) },
                _ => { panic!("KVM: unhandled KVM_EXIT_IO at port 0x{}, direction {}", run.__bindgen_anon_1.io.port, run.__bindgen_anon_1.io.direction); }
            }
        }

    }

    pub unsafe fn run(&self, guest_mem: *mut u8, console: Console) -> Result<Return> {
        match *self {
            Syscall::Write(obj) => {
                use std::io::Write;

                if (*obj).fd != 1 && (*obj).fd != 2 {
                    (*obj).length = write((*obj).fd, guest_mem.offset((*obj).buf) as *const c_void, (*obj).length as usize);
                } else {
                    let tmp = slice::from_raw_parts(guest_mem.offset((*obj).buf) as *const u8, (*obj).length as usize);
                    let content = String::from_utf8_unchecked(tmp.into());

                    let ret = match (*obj).fd {
                        1 => ActionResult::Output(content),
                        2 => ActionResult::OutputErr(content),
                        _ => unreachable!()
                    };

                    let buf: Vec<u8> = serialize(&ret, Infinite).unwrap();
                    
                    console.lock().unwrap().retain(|mut x| x.write(&buf).is_ok());
                }
            },
            Syscall::Read(obj) => {
                (*obj).ret = read((*obj).fd, guest_mem.offset((*obj).buf) as *mut c_void, (*obj).len);
            },
            Syscall::Exit(obj) => {
                return Ok(Return::Exit(*(guest_mem.offset((*obj) as isize)) as i32));
            },
            Syscall::Open(obj) => {
                (*obj).ret = open(guest_mem.offset((*obj).name) as *const i8, (*obj).flags, (*obj).mode);
            },
            Syscall::Close(obj) => {
                if (*obj).ret == 2 {
                    (*obj).ret = close((*obj).fd);
                }
            },
            Syscall::LSeek(obj) => {
                (*obj).offset = lseek((*obj).fd, (*obj).offset as i64, (*obj).whence);
            },
            Syscall::Other(id) => { 
                let err = match (*id).exit_reason {
                    KVM_EXIT_HLT => format!("Guest has halted the CPU, this is considered as a normal exit."),
                    KVM_EXIT_MMIO => panic!("KVM: unhandled KVM_EXIT_MMIO at 0x{}", (*id).__bindgen_anon_1.mmio.phys_addr ),
                    KVM_EXIT_FAIL_ENTRY => panic!("KVM: entry failure: hw_entry_failure_reason=0x{}", (*id).__bindgen_anon_1.fail_entry.hardware_entry_failure_reason),
                    KVM_EXIT_INTERNAL_ERROR => panic!("KVM: internal error exit: suberror = 0x{}", (*id).__bindgen_anon_1.internal.suberror),
                    KVM_EXIT_SHUTDOWN => format!("KVM: receive shutdown command"),
                    _ => {
                        panic!("KVM: unhandled exit: exit_reason = 0x{}", (*id).exit_reason)
                    }  
                };

                return Err(Error::Protocol(err));
            }
        }

        return Ok(Return::Continue);
    }
}
