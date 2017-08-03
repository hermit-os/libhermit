use std::{result, fmt};
use nix;
use errno::errno;

pub type Result<T> = result::Result<T, Error>;

#[derive(Deserialize, Serialize, Clone)]
pub enum Error {
    InternalError,
    NotEnoughMemory,
    InvalidFile(String),
    IOCTL(NameIOCTL),
    KernelNotLoaded,
    MissingFrequency,
    MultiIsleFailed,
    CannotCreateTmpFile(usize),
    QEmu((String, String)),
    MissingBinary,
    Protocol(String),
    ParseMemory,
    WrongIsleNumber
}

impl fmt::Debug for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            Error::InternalError => write!(f, "An internal error has occurred, please report."),
            Error::NotEnoughMemory => write!(f, "The host system has not enough memory, please check your memory usage."),
            Error::InvalidFile(ref file) => write!(f, "The file {} was not found or is invalid.", file),
            Error::IOCTL(ref name) => {
                let e = errno();

                write!(f, "The IOCTL command {:?} has failed: {}", name, e)
            },
            Error::KernelNotLoaded => write!(f, "Please load the kernel before your start the virtual machine."),
            Error::MissingFrequency => write!(f, "Couldn't get the CPU frequency from you system. (is /proc/cpuinfo missing?)"),
            Error::MultiIsleFailed => write!(f, "The Multi isle was selected on a system without supported, please load the kernel driver."),
            Error::CannotCreateTmpFile(_) => write!(f, "Couldn't create a tmp file in /tmp."),
            Error::QEmu((_, ref stderr)) => write!(f, "The qemu binary has encountered an error: {}", stderr),
            Error::MissingBinary => write!(f, "Please specify a binary."),
            Error::Protocol(ref err) => write!(f, "{}", err),
            Error::ParseMemory => write!(f, "Couldn't parse the guest memory size from the environment"),
            Error::WrongIsleNumber => write!(f, "Unknown isle number")
        }
    }
}

#[derive(Serialize, Deserialize,Debug,Clone)]
pub enum NameIOCTL {
    GetVersion,
    CreateVM,
    GetMsrIndexList,
    CheckExtension,
    GetVCPUMMAPSize,
    GetSupportedCpuID,
    SetCpuID2,
    CreateVcpu,
    SetMemoryAlias,
    SetNRMMUPages,
    GetNRMMUPages,
    SetMemoryRegion,
    SetUserMemoryRegion,
    CreateIRQChip,
    Run,
    GetRegs,
    SetRegs,
    GetSRegs,
    SetSRegs,
    SetTssIdentity,
    SetTssAddr,
    SetMPState
}
