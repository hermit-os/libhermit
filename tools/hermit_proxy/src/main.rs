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
use std::env;

use hermit::error;

extern fn exit(_:i32) {
    panic!("Aborting ..");
}

fn main() {
    // register a signal
    let sig_action = signal::SigAction::new(signal::SigHandler::Handler(exit), signal::SaFlags::empty(), signal::SigSet::empty());
    unsafe {
        signal::sigaction(signal::SIGINT, &sig_action).unwrap();
        signal::sigaction(signal::SIGTERM, &sig_action).unwrap();
    }

    let matches = clap_app!(HermitProxy => 
        (version: "0.0.1")
        (author: "Lorenz Schmidt <bytesnake@mailbox.org>")
        (about: "Allows you to start and manage HermitCore isles")
        (@subcommand run => 
            (about: "Executes an HermitCore application")
            (@arg file: +required "The binary to be executed")
            (@arg isle: --isle +takes_value "Choose the hypervisor [uhyve/qemu/multi]")
            (@arg debug: -d --debug "Enables debugging information")
            (@arg cpus: --num_cpus +takes_value "Sets the number of cpus")
            (@arg mem_size: --mem_size +takes_value "Sets the memory size")
            (@arg qemu_binary: --qemu_binary +takes_value "Overrides the default qemu binary")
            (@arg port: --port +takes_value "Overrides the default port [qemu only]")
            (@arg app_port: --app_port +takes_value "Overrides the default app port [qemu only]")
        )
    ).get_matches();

    // create the isle, wait to be available and start it
    if let Some(matches) = matches.subcommand_matches("run") {
        if let Some(isle) = matches.value_of("isle") {
            env::set_var("HERMIT_ISLE", isle);
        }

        if matches.is_present("debug") {
            env::set_var("RUST_LOG", "trace");
            env::set_var("HERMIT_VERBOSE", "1");
        }

        if let Some(num_cpus) = matches.value_of("cpus") {
            env::set_var("HERMIT_CPUS",num_cpus);
        }

        if let Some(mem_size) = matches.value_of("mem_size") {
            env::set_var("HERMIT_MEM", mem_size);
        }

        if let Some(qemu_binary) = matches.value_of("qemu_binary") {
            env::set_var("HERMIT_QEMU", qemu_binary);
        }

        if let Some(port) = matches.value_of("port") {
            env::set_var("HERMIT_PORT",port);
        }

        if let Some(app_port) = matches.value_of("app_port") {
            env::set_var("HERMIT_APP_PORT",app_port);
        }

        env_logger::init().unwrap();
        
        hermit::new_isle(&matches.value_of("file").unwrap())
            .and_then(|mut isle| { 
                isle.wait_until_available()?;
                isle.run()?;

                Ok(())
            }).unwrap();
    }
}
