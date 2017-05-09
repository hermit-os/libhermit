use std::result;
use nix;

pub type Result<T> = result::Result<T, Error>;

#[derive(Debug)]
pub enum Error {
    InternalError,
    NotEnoughMemory,
    InvalidFile,
    FailedIOCTL(nix::Error),
    KernelNotLoaded,
    MissingFrequency,
    MultiIsleFailed,
    CannotCreateTmpFile(usize),
    QEmu((String, String))

}
