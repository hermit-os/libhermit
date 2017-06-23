#![feature(untagged_unions)]
#![feature(core_intrinsics)]
#![feature(unique)]
#![allow(dead_code)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]

#[macro_use]
extern crate log;
extern crate env_logger;

#[macro_use]
extern crate clap;

#[macro_use]
extern crate serde_derive;
extern crate bincode;

extern crate libc;
extern crate memmap;
extern crate elf;
extern crate errno;
extern crate inotify;
extern crate byteorder;
extern crate chrono;

#[macro_use]
extern crate nix;

mod hermit;
mod daemon;

use nix::sys::signal;
use std::env;

use hermit::{IsleParameter, error};
use daemon::{Action, ActionResult};
use std::net::Shutdown;
use chrono::DateTime;

extern fn exit(_:i32) {
    panic!("Aborting ..");
}

fn main() {
    // register a signal
    /*let sig_action = signal::SigAction::new(signal::SigHandler::Handler(exit), signal::SaFlags::empty(), signal::SigSet::empty());
    unsafe {
        signal::sigaction(signal::SIGINT, &sig_action).unwrap();
        signal::sigaction(signal::SIGTERM, &sig_action).unwrap();
    }*/

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
        (@subcommand list =>
            (about: "Lists all Hermit isles")
        )
        (@subcommand kill_daemon => 
            (about: "Stops the daemon and deletes the unix socket")
        )
        (@subcommand stop => 
            (about: "Stops an Hermit isle")
            (@arg name: +required "The corresponding name")
        )
        (@subcommand log =>
            (about: "Acquire logging information")
            (@arg name: "Focus on a single instance")
        )
        (@subcommand remove => 
            (about: "Remove a Isle")
            (@arg name: "The number or name of the Isle")
        )
    ).get_matches();

    let mut daemon = daemon::Connection::connect();

    // list all isles
    if let Some(_) = matches.subcommand_matches("list") {
        let isles = daemon.send(Action::List);   

        if let ActionResult::List(isles) = isles {
            println!("{0: <10} | {1: <10} | {2: <10} | {3: <10}", "number", "state", "CPUs", "memory size");
            
            let mut id = 0;
            for (running, infos) in isles.into_iter() {
                let (cpus, mem_size) = match infos {
                    IsleParameter::QEmu { mem_size, num_cpus, .. } => (num_cpus, mem_size),
                    IsleParameter::Multi { mem_size, num_cpus } => (num_cpus, mem_size),
                    IsleParameter::UHyve { mem_size, num_cpus } => (num_cpus, mem_size)
                };

                let state = match running {
                    Ok(true) => "running",
                    Ok(false) => "stopped",
                    Err(_) => "error"
                };

                println!("{0: <10} | {1: <10} | {2: <10} | {3: <10}", id, state, cpus, mem_size);

                id += 1;
            }
        }
    }

    if let Some(_) = matches.subcommand_matches("kill_daemon") {
        daemon.send(Action::KillDaemon);
    }

    if let Some(matches) = matches.subcommand_matches("log") {
        let id = matches.value_of("name").and_then(|x| x.parse::<u32>().ok());
        let res = daemon.send(Action::Log(id));

        if let ActionResult::Log(logs) = res { 
            let mut i = 0;
            println!("{0: <10} | {1: <10} | {2: <10}", "number", "time", "action");
            for log in logs {
                println!("{0: <10} | {1: <10} | {2: <10?}", i, log.time.to_string(), log.action);
                i += 1;
            }
        } else if let ActionResult::IsleLog(content) = res {
            match content {
                Ok(log) => {
                    println!("Output of isle {}", id.unwrap());
                    println!("{}", log);
                },
                Err(_) => println!("An error occured!")
            }
                
        }
    }

    if let Some(matches) = matches.subcommand_matches("stop") {
        match matches.value_of("name").unwrap().parse::<u32>() {
            Ok(id) => {
                let res = daemon.send(Action::StopIsle(id));

                println!("Isle {} exited with code {:?}", id, res);
            },
            Err(_) => {
                println!("Invalid number!");
            }
        }
    }

    if let Some(matches) = matches.subcommand_matches("remove") {
        match matches.value_of("name").unwrap().parse::<u32>() {
            Ok(id) => {
                let res = daemon.send(Action::RemoveIsle(id));

            },
            Err(_) => {
                println!("Invalid number!");
            }
        }
    }

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
        let res = daemon.send(Action::CreateIsle(
                matches.value_of("file").unwrap().into(), 
                IsleParameter::from_env()
        )); 

        println!("Created Isle with number: {:?}", res);

//        hermit::new_isle(&matches.value_of("file").unwrap())
//            .and_then(|mut isle| { 
//                isle.wait_until_available()?;
//                isle.run()?;
//
//                Ok(())
//            }).unwrap();
    }
}
