#![feature(untagged_unions)]
#![allow(dead_code)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]

#[macro_use]
extern crate log;
extern crate env_logger;

extern crate libc;
extern crate memmap;
extern crate elf;
extern crate errno;
extern crate inotify;
extern crate byteorder;

#[macro_use]
extern crate nix;

mod error;
mod utils;
mod hermit;
mod uhyve;
mod hermit_env;
mod qemu;
mod multi;
mod proto;
mod socket;

use nix::sys::signal;
use std::{env, process};

extern fn exit(_:i32) {
    panic!("Aborting ..");
}

fn main() {
    env_logger::init().unwrap();
    
    let sig_action = signal::SigAction::new(signal::SigHandler::Handler(exit), signal::SaFlags::empty(), signal::SigSet::empty());
    unsafe {
        signal::sigaction(signal::SIGINT, &sig_action).unwrap();
        signal::sigaction(signal::SIGTERM, &sig_action).unwrap();
    }

    if let Some(path) = env::args().skip(1).next() {
        let isle = hermit::IsleKind::new(&path).unwrap();

        isle.wait_available();

        isle.run();
    }
}
