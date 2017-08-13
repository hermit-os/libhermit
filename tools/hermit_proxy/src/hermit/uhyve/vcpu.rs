use libc;
use libc::c_void;
use std::{mem, ptr};
use std::fs::File;
use std::os::unix::io::{FromRawFd, RawFd};
use std::intrinsics::{volatile_load,volatile_store};
use std::thread;
use std::thread::current;
use std::ptr::Unique;
use std::sync::Arc;
use std::thread::JoinHandle;
use std::sync::atomic::{AtomicBool, Ordering};

use memmap::{Mmap, Protection};
use errno::errno;

use hermit::uhyve;
use super::kvm_header::{kvm_sregs, kvm_regs, kvm_segment, kvm_cpuid2,kvm_cpuid2_header, KVM_MP_STATE_RUNNABLE, kvm_mp_state};
use super::{Result, Error, NameIOCTL};
use super::gdt;
use super::proto;
use hermit::socket::Console;

pub const GUEST_OFFSET: usize = 0x0;
pub const CPUID_FUNC_PERFMON: usize = 0x0A;
pub const GUEST_PAGE_SIZE: usize = 0x200000;

// TODO configuration missing
pub const GUEST_SIZE: usize = 0x20000000;

pub const BOOT_GDT:  usize = 0x1000;
pub const BOOT_INFO: usize = 0x2000;
pub const BOOT_PML4: usize = 0x10000;
pub const BOOT_PDPTE:usize = 0x11000;
pub const BOOT_PDE:  usize = 0x12000;

/// Basic CPU control in CR0
pub const X86_CR0_PE: u64 = (1 << 0);
pub const X86_CR0_PG: u64 = (1 << 31);

/// Intel long mode page directory/table entries
pub const X86_CR4_PAE: u64 = (1u64 << 5);

/// Intel long mode page directory/table entries
pub const X86_PDPT_P:  u64 = (1 << 0);
pub const X86_PDPT_RW: u64 = (1 << 1);
pub const X86_PDPT_PS: u64 = (1 << 7);

pub enum ExitCode {
    Cause(Result<i32>),
    Innocent
}

pub struct SharedState {
    run_mem: Mmap,
    mboot:*mut u8,
    guest_mem: *mut u8,
    running_state: Arc<AtomicBool>,
    console: Console
}

pub struct VirtualCPU {
    id: u32,
    kvm_fd: RawFd,
    vm_fd: RawFd,
    vcpu_fd: RawFd,
    state: Arc<SharedState>
}

impl VirtualCPU {
    pub fn new(kvm_fd: RawFd, vm_fd: RawFd, id: u32, entry: u64, mem: &mut Mmap, mboot: *mut u8, running_state: Arc<AtomicBool>, console: Console) -> Result<VirtualCPU> {
        
        // create a new VCPU and save the file descriptor
        let fd = VirtualCPU::create_vcpu(vm_fd, id as u32)?;

        debug!("New virtual CPU with id {} and FD {}", id, fd);

        let file = unsafe { File::from_raw_fd(fd) };

        let run_mem = unsafe {
            Mmap::open_with_offset(&file, Protection::ReadWrite, 0, VirtualCPU::get_mmap_size(kvm_fd)?)
                .map_err(|x| panic!("{:?}", x) )//Error::InvalidFile)
        }?;
      
        // forget the file, we don't want to close the file descriptor
        mem::forget(file);

        let state = SharedState {
            run_mem: run_mem,
            mboot: mboot,
            guest_mem: mem.mut_ptr(),
            running_state: running_state,
            console: console
        };

        let cpu = VirtualCPU {
            kvm_fd: kvm_fd, 
            vm_fd: vm_fd, 
            vcpu_fd: fd, 
            id: id, 
            state: Arc::new(state)
        };

        debug!("Set the CPUID");
        
        cpu.setup_cpuid()?;
       
        debug!("Set MP state");

        cpu.set_mp_state(kvm_mp_state { mp_state: KVM_MP_STATE_RUNNABLE })?;

        debug!("Initialize the register of {} with start address {:?}", id, entry);

        let mut regs = kvm_regs::empty();
        regs.rip = entry;
        regs.rflags = 0x2;
        cpu.set_regs(regs)?;
        
        Ok(cpu)
    }

    pub fn create_vcpu(fd: RawFd, mut id: u32) -> Result<RawFd> {
        unsafe { 
            uhyve::ioctl::create_vcpu(fd, id as *mut u8)
                .map_err(|_| Error::IOCTL(NameIOCTL::CreateVcpu))
        }
    }   

    pub fn get_sregs(&self) -> Result<kvm_sregs> {
        let mut sregs = kvm_sregs::empty();
        unsafe {
            uhyve::ioctl::get_sregs(self.vcpu_fd, (&mut sregs) as *mut kvm_sregs)
                .map_err(|x| Error::IOCTL(NameIOCTL::GetSRegs))?;
        }

        Ok(sregs)
    }

    pub fn set_sregs(&self, mut sregs: kvm_sregs) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_sregs(self.vcpu_fd, (&mut sregs) as *mut kvm_sregs)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetSRegs))?;
        }

        Ok(())
    }

    pub fn set_regs(&self, mut regs: kvm_regs) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_regs(self.vcpu_fd, (&mut regs) as *mut kvm_regs)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetSRegs))?;
        }

        Ok(())
    }

    pub fn get_supported_cpuid(&self) -> Result<kvm_cpuid2> {
        let mut cpuid = kvm_cpuid2::empty();

        unsafe {
            uhyve::ioctl::get_supported_cpuid(self.kvm_fd, (&mut cpuid.header) as *mut kvm_cpuid2_header)
                .map_err(|x| Error::IOCTL(NameIOCTL::GetSupportedCpuID))?;
        }

        Ok(cpuid)
    }

    pub fn set_cpuid2(&self, mut cpuid: kvm_cpuid2) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_cpuid2(self.vcpu_fd, (&mut cpuid.header) as *mut kvm_cpuid2_header)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetCpuID2))?;
        }

        Ok(())
    }
   
    pub fn get_mmap_size(vcpu_fd: RawFd) -> Result<usize> {
        unsafe {
            uhyve::ioctl::get_vcpu_mmap_size(vcpu_fd, ptr::null_mut())
                .map_err(|x| Error::IOCTL(NameIOCTL::GetVCPUMMAPSize)).map(|x| { x as usize})
        }
    }
    
    pub fn set_mp_state(&self, mp_state: kvm_mp_state) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_mp_state(self.vcpu_fd, (&mp_state) as *const kvm_mp_state)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetMPState)).map(|_| ())
        }
    }

    pub fn single_run(fd: RawFd, state: &Arc<SharedState>) -> Result<proto::Return> {
        let ret = unsafe {
            uhyve::ioctl::run(fd, ptr::null_mut())
                .map_err(|x| Error::IOCTL(NameIOCTL::Run))
        }?;

        debug!("Single Run CPU {}", fd);

        if ret == -1 {
            match errno().0 {
                libc::EINTR => { return Ok(proto::Return::Continue); },
                libc::EFAULT => {
                    // TODO
                    panic!("translation fault!");
                },
                _ => {
                    panic!("KVM: ioctl KVM_RUN in vcpu_loop failed");
                }
            }
        }

        unsafe {
            let a = proto::Syscall::from_mem(state.run_mem.ptr(), state.guest_mem).run(state.guest_mem, state.console.clone());
        
            a
        }
    }

    pub fn run(&self) -> JoinHandle<ExitCode> {
        debug!("Run CPU {}", self.id);

        let state = self.state.clone();
        let id = self.id;
        let fd = self.vcpu_fd;

        let child = thread::spawn(move || { 
            unsafe {
                while volatile_load(state.mboot.offset(0x20)) < id as u8 {
                    thread::yield_now();
                }

                volatile_store(state.mboot.offset(0x30), id as u8);
            }

            while state.running_state.load(Ordering::Relaxed) {
                match VirtualCPU::single_run(fd, &state) {
                    Ok(proto::Return::Exit(code)) => {
                        state.running_state.store(false, Ordering::Relaxed);

                        return ExitCode::Cause(Ok(code));
                    },
                    Err(err) => {
                        state.running_state.store(false, Ordering::Relaxed);
                        
                        return ExitCode::Cause(Err(err));
                    },
                    _ => {}
                }
            }

            ExitCode::Innocent
        });
    
        child
    }
    
    pub fn init_sregs(&self) -> Result<kvm_sregs> {
        let mut sregs = self.get_sregs()?;

        debug!("Setup GDT");
        self.setup_system_gdt(&mut sregs, 0)?;
        debug!("Setup the page table");
        self.setup_system_page_table(&mut sregs)?;
        debug!("Set the system to 64bit");
        self.setup_system_64bit(&mut sregs)?;

        Ok(sregs)
    }

    pub fn setup_system_gdt(&self, sregs: &mut kvm_sregs, offset: u64) -> Result<()> {
        let (mut data_seg, mut code_seg) = (kvm_segment::empty(), kvm_segment::empty());               
        
        // create the GDT entries
        let gdt_null = gdt::Entry::new(0, 0, 0);
        let gdt_code = gdt::Entry::new(0xA09B, 0, 0xFFFFF);
        let gdt_data = gdt::Entry::new(0xC093, 0, 0xFFFFF);

        // apply the new GDTs to our guest memory
        unsafe {
            let ptr = self.state.guest_mem.offset(offset as isize) as *mut u64;
            
            *(ptr.offset(gdt::BOOT_NULL)) = gdt_null.as_u64();
            *(ptr.offset(gdt::BOOT_CODE)) = gdt_code.as_u64();
            *(ptr.offset(gdt::BOOT_DATA)) = gdt_data.as_u64();
        }

        gdt_code.apply_to_kvm(gdt::BOOT_CODE, &mut code_seg);
        gdt_data.apply_to_kvm(gdt::BOOT_DATA, &mut data_seg);

        sregs.gdt.base = offset;
        sregs.gdt.limit = ((mem::size_of::<u64>() * gdt::BOOT_MAX) - 1) as u16;
        sregs.cs = code_seg;
        sregs.ds = data_seg;
        sregs.es = data_seg;
        sregs.fs = data_seg;
        sregs.gs = data_seg;
        sregs.ss = data_seg;

        Ok(())
    }
    pub fn setup_system_page_table(&self, sregs: &mut kvm_sregs) -> Result<()> {
        unsafe {
            let pml4 = self.state.guest_mem.offset(BOOT_PML4 as isize) as *mut u64;
            let pdpte = self.state.guest_mem.offset(BOOT_PDPTE as isize) as *mut u64;
            let pde = self.state.guest_mem.offset(BOOT_PDE as isize) as *mut u64;
            
            libc::memset(pml4 as *mut c_void, 0x00, 4096);
            libc::memset(pdpte as *mut c_void, 0x00, 4096);
            libc::memset(pde as *mut c_void, 0x00, 4096);
            
            *pml4 = (BOOT_PDPTE as u64) | (X86_PDPT_P | X86_PDPT_RW);
            *pdpte = (BOOT_PDE as u64) | (X86_PDPT_P | X86_PDPT_RW);
           
            for i in 0..(GUEST_SIZE/GUEST_PAGE_SIZE) {
                *(pde.offset(i as isize)) = (i*GUEST_PAGE_SIZE) as u64 | (X86_PDPT_P | X86_PDPT_RW | X86_PDPT_PS);
            }
        }

        sregs.cr3 = BOOT_PML4 as u64;
        sregs.cr4 |= X86_CR4_PAE;
        sregs.cr0 |= X86_CR0_PG;

        Ok(())
    }

    pub fn setup_system_64bit(&self, sregs: &mut kvm_sregs) -> Result<()> {
        sregs.cr0 |= X86_CR0_PE;
        sregs.efer |= 1 << 8;

        Ok(())
    }

    pub fn setup_cpuid(&self) -> Result<()> {
        let mut kvm_cpuid = self.get_supported_cpuid()?;

        for entry in kvm_cpuid.data.iter_mut() {
            match entry.function {
                1 => {
                    entry.ecx |= 1u32 << 31; // propagate that we are running on a hypervisor
                    //entry.ecx = entry.ecx & !(1 << 21);
                    entry.edx |= 1u32 << 5; // enable msr support
                },
                0x0A => {
                    // disable it
                    entry.eax = 0x00;
                },
                _ => {}
            }
        }

        self.set_cpuid2(kvm_cpuid)?;

        Ok(())
    }
}

unsafe impl Sync for SharedState { }
unsafe impl Send for SharedState {}
