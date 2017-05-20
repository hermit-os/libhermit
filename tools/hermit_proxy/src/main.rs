#![feature(untagged_unions)]
#![allow(dead_code)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]

#[macro_use]
extern crate log;
extern crate env_logger;

#[macro_use]
extern crate clap;

extern crate libc;
extern crate memmap;
extern crate elf;
extern crate errno;
extern crate inotify;
extern crate byteorder;

#[macro_use]
extern crate nix;

mod hermit;

use nix::sys::signal;
use std::{env, process};
use hermit::error;

extern fn exit(_:i32) {
    panic!("Aborting ..");
}

fn main() {
    env_logger::init().unwrap();
    
    // register a signal
    let sig_action = signal::SigAction::new(signal::SigHandler::Handler(exit), signal::SaFlags::empty(), signal::SigSet::empty());
    unsafe {
        signal::sigaction(signal::SIGINT, &sig_action).unwrap();
        signal::sigaction(signal::SIGTERM, &sig_action).unwrap();
    }

/*    let matches = clap_app!(proxy => 
        (version: "0.0.1")
        (author: "Lorenz Schmidt <bytesnake@mailbox.org>")
        (about: "Allows you to start and manage HermitCore isles")
        (@arg debug: -d ... "Sets the level of debugging information")
    ).get_matches();
*/

    // create the isle, wait to be available and start it
    env::args().skip(1).next().ok_or(error::Error::MissingBinary)
        .and_then(|path| hermit::new_isle(&path))
        .and_then(|mut isle| { 
            isle.wait_until_available()?;
            isle.run()?;

            Ok(())
        }).unwrap();
}
