//! By calling create_vm KVM returns a fd, this file wraps all relevant functions belonging to the
//! VM layer

use libc;
use std::ptr;
use std::fs::File;
use std::io::{Read, Cursor};
use memmap::{Mmap, Protection};
use elf;
use elf::types::{ELFCLASS64, OSABI, PT_LOAD};
use std::ffi::CStr;

use hermit::utils;
use hermit::uhyve;
use super::kvm_header::{kvm_userspace_memory_region, KVM_CAP_SYNC_MMU, KVM_32BIT_GAP_START, KVM_32BIT_GAP_SIZE};
use super::{Result, Error, NameIOCTL};
use super::vcpu::VirtualCPU;

//use byteorder::ByteOrder;
// guest offset?
//pub const GUEST_OFFSET = 0;

pub struct VirtualMachine {
    kvm_fd: libc::c_int,
    vm_fd: libc::c_int,
    mem: Mmap,
    elf_header: Option<elf::types::FileHeader>,
    klog: Option<*const i8>,
    mboot: Option<*mut u8>,
    vcpus: Vec<VirtualCPU>
}

impl VirtualMachine {
    pub fn new(kvm_fd: libc::c_int, fd: libc::c_int, size: usize) -> Result<VirtualMachine> {
        debug!("New virtual machine with memory size {}", size);

        // create a new memory region to map the memory of our guest
        let mut mem;
        if size < KVM_32BIT_GAP_START {
            mem = Mmap::anonymous(size, Protection::ReadWrite)
                .map_err(|_| Error::NotEnoughMemory)?;
        } else {
            mem = Mmap::anonymous(size + KVM_32BIT_GAP_START, Protection::ReadWrite)
                .map_err(|_| Error::NotEnoughMemory)?;
            
            unsafe { libc::mprotect((mem.mut_ptr() as *mut libc::c_void).offset(KVM_32BIT_GAP_START as isize), KVM_32BIT_GAP_START, libc::PROT_NONE); }
        }
        
        Ok(VirtualMachine { kvm_fd: kvm_fd, vm_fd: fd, mem: mem, elf_header: None, klog: None, vcpus: Vec::new(), mboot: None })
    }

    /// Loads a kernel from path and initialite mem and elf_entry
    pub fn load_kernel(&mut self, path: &str) -> Result<()> {
        debug!("Load kernel from {}", path);

        // open the file in read only
        let file = Mmap::open_path(path, Protection::Read)
            .map_err(|_| Error::InvalidFile(path.into()))?;

        // parse the header with ELF module
        let file_efi = {
            let mut data = unsafe { Cursor::new(file.as_slice()) };
            
            elf::File::open_stream(&mut data)
                .map_err(|_| Error::InvalidFile(path.into()))
        }?;

        if file_efi.ehdr.class != ELFCLASS64 ||  file_efi.ehdr.osabi != OSABI(0x42) {
            return Err(Error::InvalidFile(path.into()));
        }

        self.elf_header = Some(file_efi.ehdr);

        // acquire the slices of the user memory and kernel file
        let vm_mem_length = self.mem.len() as u64;
        let vm_mem = unsafe { self.mem.as_mut_slice() };
        let kernel_file  = unsafe { file.as_slice() };

        for header in file_efi.phdrs {
            if header.progtype != PT_LOAD {
                continue;
            }

            let vm_start = header.paddr as usize;
            let vm_end   = vm_start + header.filesz as usize;

            let kernel_start = header.offset as usize;
            let kernel_end   = kernel_start + header.filesz as usize;

            debug!("Load segment with start addr {} and size {} to {}", header.paddr, header.filesz, header.offset);

            vm_mem[vm_start..vm_end].copy_from_slice(&kernel_file[kernel_start..kernel_end]);
            
            unsafe {
                libc::memset(vm_mem.as_mut_ptr().offset(vm_end as isize) as *mut libc::c_void, 0x00, (header.memsz - header.filesz) as usize);
            }

            let ptr = vm_mem[vm_start..vm_end].as_mut_ptr();
           
            unsafe {
                *(ptr.offset(0x08) as *mut u64) = header.paddr;   // physical start addr
                *(ptr.offset(0x10) as *mut u64) = vm_mem_length;  // physical size limit
                *(ptr.offset(0x18) as *mut u32) = utils::cpufreq()? / 1000; // CPU frequency
                *(ptr.offset(0x24) as *mut u32) = 1;              // number of used CPUs
                *(ptr.offset(0x30) as *mut u32) = 0;              // apicid (?)
                *(ptr.offset(0x38) as *mut u64) = header.memsz;  // 
                *(ptr.offset(0x60) as *mut u32) = 1;              // NUMA nodes
                *(ptr.offset(0x94) as *mut u32) = 1;              // announce uhyve
            
                self.klog = Some(vm_mem.as_ptr().offset(header.paddr as isize + 0x5000) as *const i8);
                self.mboot = Some(vm_mem.as_mut_ptr().offset(header.paddr as isize) as *mut u8);
            }
        }

        debug!("Kernel loaded");

        Ok(())
    }

    /// Initialize the virtual machine
    pub fn init(&mut self) -> Result<()> {
        let mut identity_base: u64 = 0xfffbc000;
        if let Ok(true) = self.check_extension(KVM_CAP_SYNC_MMU) {
            identity_base = 0xfeffc000;

            self.set_tss_identity(identity_base)?;
        }
        
        self.set_tss_addr(identity_base+0x1000)?;

        let start_ptr = unsafe { self.mem.as_slice().as_ptr() as u64 };
        let mut kvm_region = kvm_userspace_memory_region {
            slot: 0, guest_phys_addr: 0, flags: 0, memory_size: self.mem_size() as u64, userspace_addr: start_ptr
        };

        if self.mem_size() <= KVM_32BIT_GAP_START {
            self.set_user_memory_region(kvm_region)?;
        } else {
            kvm_region.memory_size = KVM_32BIT_GAP_START as u64;
            self.set_user_memory_region(kvm_region)?;

            kvm_region.slot = 1;
            kvm_region.guest_phys_addr = (KVM_32BIT_GAP_START+KVM_32BIT_GAP_SIZE) as u64;
            kvm_region.memory_size = (self.mem_size() - KVM_32BIT_GAP_SIZE - KVM_32BIT_GAP_START) as u64;
            self.set_user_memory_region(kvm_region)?;
        }

        self.create_irqchip()?;

        self.create_vcpu(0)
    }

    pub fn set_user_memory_region(&self, mut region: kvm_userspace_memory_region) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_user_memory_region(self.vm_fd, (&mut region) as *mut kvm_userspace_memory_region)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetUserMemoryRegion)).map(|_| ())
        }
    }

    pub fn create_irqchip(&self) -> Result<()> {
        unsafe {
            uhyve::ioctl::create_irqchip(self.vm_fd, ptr::null_mut())
                .map_err(|x| Error::IOCTL(NameIOCTL::CreateIRQChip)).map(|_| ())
        }
    }

    pub fn check_extension(&self, mut extension: u32) -> Result<bool> {
        unsafe {
            uhyve::ioctl::check_extension(self.vm_fd, (&mut extension) as *mut u32 as *mut u8)
                .map_err(|x| Error::IOCTL(NameIOCTL::CheckExtension)).map(|x| x == 1)
        }
    }

    pub fn set_tss_identity(&self, identity_base: u64) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_identity_map_addr(self.kvm_fd, (&identity_base) as *const u64)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetTssIdentity)).map(|_| ())
        }
    }

    pub fn set_tss_addr(&self, mut identity_base: u64) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_tss_addr(self.vm_fd, identity_base as *mut u8)
                .map_err(|x| Error::IOCTL(NameIOCTL::SetTssAddr)).map(|_| ())
        }
    }

    pub fn create_vcpu(&mut self, id: u8) -> Result<()> {
        let entry = self.elf_header.ok_or(Error::KernelNotLoaded)?.entry;

        let cpu = VirtualCPU::new(self.kvm_fd, self.vm_fd, id, entry, &mut self.mem, self.mboot.unwrap())?;

        let id = id as usize;

        /*
        let len = self.vcpus.len();
        if len < id+1 {
            debug!("Reserve one!");
            self.vcpus.reserve(id - len + 1);
        }

        self.vcpus[id] = cpu;
*/
        self.vcpus.insert(id, cpu);

        Ok(())
    }

    pub fn output(&self) -> Result<String> {
        let paddr = self.klog.ok_or(Error::KernelNotLoaded)?;
        let c_str = unsafe { CStr::from_ptr(paddr).to_str().map_err(|_| Error::KernelNotLoaded)? };
        
        Ok(c_str.into())
    }

    pub fn run(&mut self) -> Result<()> {
        let mut guest_mem = unsafe { self.mem.as_mut_slice() };
        
        loop {
            if let Some(vcpu)  = self.vcpus.pop() {
                vcpu.run()?;
            } else {
                break;
            }
        }

        Ok(())
    }

    pub fn mem_size(&self) -> usize {
        self.mem.len()
    }
}

impl Drop for VirtualMachine {
    fn drop(&mut self) {
        if let Ok(output) = self.output() {
            debug!("{}", output);
        }
    }
}
