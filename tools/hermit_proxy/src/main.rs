#![feature(untagged_unions)]
#![feature(core_intrinsics)]
#![allow(dead_code)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]

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

#[macro_use]
extern crate log;

mod hermit;
mod daemon;
mod proto;
mod logger;

use std::{env, fs};

use hermit::IsleParameter;
use proto::{Action, ActionResult};

fn main() {
    // create the structure of the application
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
        (@subcommand start_daemon => 
            (about: "Starts the daemon in foreground")
        )
        (@subcommand kill_daemon => 
            (about: "Stops the daemon and deletes the unix socket")
        )
        (@subcommand stop => 
            (about: "Stops an Hermit isle")
            (@arg name: +required "The corresponding name")
        )
        (@subcommand connect =>
            (about: "Connects to an hermit isle")
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

    // start the daemon in foreground
    if let Some(_) = matches.subcommand_matches("start_daemon") {
        daemon::daemon_handler();

        return;
    }

    // connect to the daemon and (if not running) start the daemon in background
    let mut daemon = daemon::Connection::connect();

    // list all isles
    if let Some(_) = matches.subcommand_matches("list") {
        let isles = daemon.send(Action::List);   

        // if everything worked as expected, list all isles
        if let ActionResult::List(isles) = isles {
            println!("{0: <10} | {1: <10} | {2: <10} | {3: <10}", "number", "state", "CPUs", "memory size");
            
            let mut id = 0;
            for (running, infos) in isles.into_iter() {
                // obtain information about the memory size and number of CPUs
                let (cpus, mem_size) = match infos {
                    IsleParameter::QEmu { mem_size, num_cpus, .. } => (num_cpus, mem_size),
                    IsleParameter::Multi { mem_size, num_cpus } => (num_cpus, mem_size),
                    IsleParameter::UHyve { mem_size, num_cpus } => (num_cpus, mem_size)
                };

                // running state
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

    // send an action to kill the daemon
    if let Some(_) = matches.subcommand_matches("kill_daemon") {
        daemon.send(Action::KillDaemon);
    }

    // print either the daemon log or logs about a single isle
    if let Some(matches) = matches.subcommand_matches("log") {
        // parse the ID to an integer
        let id = matches.value_of("name")
            .and_then(|x| x.parse::<u32>().ok());

        let res = daemon.send(Action::Log(id));

        if let ActionResult::Log(logs) = res { 
            let mut i = 0;

            // print the header
            println!("{0: <10} | {1: <10} | {2: <10}", "number", "time", "action");
            
            // and each line of log
            for log in logs {
                println!("{0: <10} | {1: <10} | {2: <10?}", i, log.time.format("%H:%M:%S"), log.text);
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

    // stop the execution of an isle
    if let Some(matches) = matches.subcommand_matches("stop") {
        // parse the id as an integer
        let id = matches.value_of("name")
            .and_then(|x| x.parse::<u32>().ok());

        match id {
            Some(id) => {
                let res = daemon.send(Action::StopIsle(id));

                println!("Isle {} exited with code {:?}", id, res);
            },
            None => {
                println!("Invalid number!");
            }
        }
    }

    // remove the isle from the list
    if let Some(matches) = matches.subcommand_matches("remove") {
        // parse the id as an integer
        let id = matches.value_of("name")
            .and_then(|x| x.parse::<u32>().ok());

        match id {
            Some(id) => {
                let res = daemon.send(Action::RemoveIsle(id));

                if let ActionResult::RemoveIsle(Ok(_)) = res {
                    println!("Isle {} was successfully removed", id);
                } else if let ActionResult::RemoveIsle(Err(err)) = res {
                    println!("Remove failed: {:?}", err);
                }
            },
            None => {
                println!("Invalid number!");
            }
        }
    }

    // connect to console of an isle
    if let Some(matches) = matches.subcommand_matches("connect") {
        // parse the id as an integer
        let id = matches.value_of("name")
            .and_then(|x| x.parse::<u32>().ok());

        match id {
            Some(id) => {
                let res = daemon.send(Action::Connect(id));

                if let ActionResult::Connect(Ok(())) = res {
                    daemon.output();
                } else {
                    println!("Invalid number!");
                }
            },
            None => {
                println!("Invalid number!");
            }
        }
    }

    // create the isle, wait to be available and start it
    if let Some(matches) = matches.subcommand_matches("run") {
        // copy some parameters to the environment
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

        let relative_path: String = matches.value_of("file").unwrap().into();
        let path = fs::canonicalize(relative_path).unwrap();

        // start a new isle
        let res = daemon.send(Action::CreateIsle(
                path.to_str().unwrap().into(),
                IsleParameter::from_env()
        )); 

        // connect to the console of the isle
        if let ActionResult::CreateIsle(_) = res {
            daemon.output();
        }

        println!("Created Isle with number: {:?}", res);
    }
}

