use libc::{write, read, lseek, exit, open, close, c_int, c_void};
use uhyve::kvm_header::{kvm_run, KVM_EXIT_IO, KVM_EXIT_HLT, KVM_EXIT_MMIO,KVM_EXIT_FAIL_ENTRY, KVM_EXIT_INTERNAL_ERROR, KVM_EXIT_SHUTDOWN }; 

const PORT_WRITE: u16 = 0x499;
const PORT_OPEN: u16 = 0x500;
const PORT_CLOSE: u16 = 0x501;
const PORT_READ: u16 = 0x502;
const PORT_EXIT: u16 = 0x503;
const PORT_LSEEK: u16 = 0x504;

pub struct Write {
    fd: c_int,
    buf: *const u8,
    length: usize
}

pub struct Open {
    name: *const u8,
    flags: c_int,
    mode: c_int,
    ret: c_int
}

pub struct Close {
    fd: c_int,
    ret: c_int
}

pub struct Read {
    fd: c_int,
    buf: *mut u8,
    len: usize,
    ret: isize
}

pub struct LSeek {
    fd: c_int,
    offset: usize,
    whence: c_int
}

pub enum Syscall {
    Write(*mut Write),
    Open(*mut Open),
    Close(*mut Close),
    Read(*mut Read),
    LSeek(*mut LSeek),
    Exit(*mut isize),
    Other(*const kvm_run)
}

impl Syscall {
    pub fn from_mem(mem: &[u8], guest_mem: &[u8]) -> Syscall {
        unsafe {
            let ref run = *(mem.as_ptr() as *const kvm_run);

            if run.exit_reason != KVM_EXIT_IO {
                return Syscall::Other(mem.as_ptr() as *const kvm_run);
            }

            let offset = mem.as_ptr().offset(run.__bindgen_anon_1.io.data_offset as isize) as isize;
        
            match run.__bindgen_anon_1.io.port {
                PORT_WRITE => { Syscall::Write(guest_mem.as_ptr().offset(offset) as *mut Write) },
                PORT_READ  => { Syscall::Read (guest_mem.as_ptr().offset(offset) as *mut Read)  },
                PORT_CLOSE => { Syscall::Close(guest_mem.as_ptr().offset(offset) as *mut Close) },
                PORT_OPEN  => { Syscall::Open (guest_mem.as_ptr().offset(offset) as *mut Open ) },
                PORT_LSEEK => { Syscall::LSeek(guest_mem.as_ptr().offset(offset) as *mut LSeek) },
                PORT_EXIT  => { Syscall::Exit( guest_mem.as_ptr().offset(offset) as *mut isize) },
                _ => { panic!("KVM: unhandled KVM_EXIT_IO at port 0x{}, direction {}", run.__bindgen_anon_1.io.port, run.__bindgen_anon_1.io.direction); }
            }
        }

    }

    pub unsafe fn run(&self, guest_mem: *mut u8) {
        match *self {
            Syscall::Write(obj) => {
                //let Write { fd, buf, length } = *write;
                (*obj).length = write((*obj).fd, guest_mem.offset((*obj).buf as isize) as *const c_void, (*obj).length) as usize;
            },
            Syscall::Read(obj) => {
                (*obj).ret = read((*obj).fd, guest_mem.offset((*obj).buf as isize) as *mut c_void, (*obj).len) as isize;
            },
            Syscall::Exit(obj) => {
                exit(*((guest_mem as *mut i32).offset((*obj) as isize)));
            },
            Syscall::Open(obj) => {
                (*obj).ret = open((guest_mem as *const i8).offset((*obj).name as isize), (*obj).flags, (*obj).mode);
            },
            Syscall::Close(obj) => {
                if (*obj).ret == 2 {
                    (*obj).ret = close((*obj).fd);
                }
            },
            Syscall::LSeek(obj) => {
                (*obj).offset = lseek((*obj).fd, (*obj).offset as i64, (*obj).whence) as usize;
            },
            Syscall::Other(id) => { match (*id).exit_reason {
                KVM_EXIT_HLT => panic!("Guest has halted the CPU, this is considered as a normal exit."),
                KVM_EXIT_MMIO =>panic!("KVM: unhandled KVM_EXIT_MMIO at 0x{}", (*id).__bindgen_anon_1.mmio.phys_addr ),
                KVM_EXIT_FAIL_ENTRY => panic!("KVM: entry failure: hw_entry_failure_reason=0x{}", (*id).__bindgen_anon_1.fail_entry.hardware_entry_failure_reason),
                KVM_EXIT_INTERNAL_ERROR => panic!("KVM: internal error exit: suberror = 0x{}", (*id).__bindgen_anon_1.internal.suberror),
                KVM_EXIT_SHUTDOWN => panic!("KVM: receive shutdown command"),
                _ => {
                    panic!("KVM: unhandled exit: exit_reason = 0x{}", (*id).exit_reason);
                }  
            }}
        }
    }
}
