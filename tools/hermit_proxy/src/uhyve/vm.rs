//! By calling create_vm KVM returns a fd, this file wraps all relevant functions belonging to the
//! VM layer

use libc;
use std::ptr;
use std::fs::File;
use std::io::{Read, Cursor};
use memmap::{Mmap, Protection};
use elf;
use elf::types::{ELFCLASS64, OSABI, PT_LOAD};

use utils;
use uhyve;
use uhyve::kvm_header::{kvm_userspace_memory_region };
use uhyve::{Result, Error};
use uhyve::vcpu::VirtualCPU;

//use byteorder::ByteOrder;
// guest offset?
//pub const GUEST_OFFSET = 0;

pub struct VirtualMachine {
    kvm_fd: libc::c_int,
    vm_fd: libc::c_int,
    mem: Mmap,
    elf_entry: Option<u64>,
    vcpus: Vec<VirtualCPU>,
    size: usize
}

impl VirtualMachine {
    pub fn new(kvm_fd: libc::c_int, fd: libc::c_int, size: usize) -> Result<VirtualMachine> {
        debug!("UHYVE - New virtual machine with memory size {}", size);

        // create a new memory region to map the memory of our guest
        Mmap::anonymous(size, Protection::ReadWrite)
            .map_err(|_| Error::NotEnoughMemory)
            .map(|mem| VirtualMachine { kvm_fd: kvm_fd, vm_fd: fd, mem: mem, elf_entry: None, vcpus: Vec::new(), size: size })
    }

    /// Loads a kernel from path and initialite mem and elf_entry
    pub fn load_kernel(&mut self, path: &str) -> Result<()> {
        debug!("UHYVE - Load kernel from {}", path);
        
        // open the file in read only
        let file = Mmap::open_path(path, Protection::Read).map_err(|_| Error::InvalidFile)?;

        // parse the header with ELF module
        let file_efi = {
            let mut data = unsafe { Cursor::new(file.as_slice()) };
            
            elf::File::open_stream(&mut data).map_err(|_| Error::InvalidFile)
        }?;

        if file_efi.ehdr.class != ELFCLASS64 ||  file_efi.ehdr.osabi != OSABI(0x42) {
            return Err(Error::InvalidFile);
        }

        self.elf_entry = Some(file_efi.ehdr.entry);

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

            let ptr = vm_mem[vm_start..vm_end].as_mut_ptr();
           
            unsafe {
                *(ptr.offset(0x08) as *mut u64) = header.paddr;   // physical start addr
                *(ptr.offset(0x10) as *mut u64) = vm_mem_length;  // physical size limit
                *(ptr.offset(0x18) as *mut u32) = utils::cpufreq()?; // CPU frequency
                *(ptr.offset(0x24) as *mut u32) = 1;              // number of used CPUs
                *(ptr.offset(0x30) as *mut u32) = 0;              // apicid (?)
                *(ptr.offset(0x38) as *mut u64) = header.filesz;  // 
                *(ptr.offset(0x60) as *mut u32) = 1;              // NUMA nodes
                *(ptr.offset(0x94) as *mut u32) = 1;              // announce uhyve
            }
        }

        debug!("Kernel loaded");

        Ok(())
    }

    /// Initialize the virtual machine
    pub fn init(&mut self) -> Result<()> {
        let start_ptr = unsafe { self.mem.as_slice().as_ptr() as u64 };
        let kvm_region = kvm_userspace_memory_region {
            slot: 0, guest_phys_addr: 0, flags: 0, memory_size: self.mem.len() as u64, userspace_addr: start_ptr
        };

        self.set_user_memory_region(kvm_region)?;
        self.create_irqchip()?;
        let vcpu = self.create_vcpu(0)?;

        self.vcpus.push(vcpu);

        Ok(())
    }

    pub fn set_user_memory_region(&self, mut region: kvm_userspace_memory_region) -> Result<()> {
        unsafe {
            uhyve::ioctl::set_user_memory_region(self.vm_fd, (&mut region) as *mut kvm_userspace_memory_region)
                .map_err(|x| Error::FailedIOCTL(x)).map(|_| ())
        }
    }

    pub fn create_irqchip(&self) -> Result<()> {
        unsafe {
            uhyve::ioctl::create_irqchip(self.vm_fd, ptr::null_mut())
                .map_err(|x| Error::FailedIOCTL(x)).map(|_| ())
        }
    }

    pub fn create_vcpu(&mut self, id: u8) -> Result<VirtualCPU> {
        let entry = self.elf_entry.ok_or(Error::KernelNotLoaded)?;

        let cpu = VirtualCPU::new(self.kvm_fd, self.vm_fd, id, entry, &mut self.mem)?;

        Ok(cpu)
    }

    pub fn run(&mut self) -> Result<()> {
        let mut guest_mem = unsafe { self.mem.as_mut_slice() };
        
        for vcpu in &self.vcpus {
            vcpu.run(&mut guest_mem)?;
        }

        Ok(())
    }
}
