use std::os::unix::net::{UnixStream, UnixListener};
use std::path::Path;
use std::thread;
use std::process;
use std::result;
use nix::unistd::{fork, ForkResult};
use nix::sys::signal;
use hermit::Isle;
use std::io::Write;
use std::io::Read;
use std::time::Duration;
use bincode::{serialize, deserialize, Infinite};
use std::fs;
use hermit::IsleParameter;
use hermit::qemu::QEmu;
use hermit::multi::Multi;
use hermit::uhyve::Uhyve;
use proto::{Action, ActionResult};
use hermit::error::{Result,Error};
use chrono::{DateTime, Local};
use logger::{LocalLogger, LOGS};

const DAEMON_PATH: &'static str = "/tmp/hermit_daemon";

/// Represent a connection to the daemon over an unix socket. The important function here is to
/// connect to the daemon and in case it doesn't run, start the daemon in background.
pub struct Connection {
    pub socket: UnixStream
}

impl Connection {
    pub fn connect() -> Connection {
        // if the path to the unix socket doesn't exit, we assume that the daemon is not running,
        // therefore a new one is started
        if !Path::new(DAEMON_PATH).exists() {
            match fork() {
                Ok(ForkResult::Child) => {
                    daemon_handler();

                    process::exit(0);
                },
                _ => panic!("Couldn't fork the deamon process!")
            }
        }

        // wait for the daemon to start
        loop {
            if let Ok(socket) = UnixStream::connect(DAEMON_PATH) {
                socket.set_nonblocking(true).unwrap();

                return Connection { socket: socket };
            }

            thread::sleep(Duration::from_millis(100));
        }
    }

    /// Wait for an output packet and print it to the console
    pub fn output(&mut self) {
        let mut buf = vec![0; 1024];
        loop {
            if let Ok(_) = self.socket.read(&mut buf) {
                let obj = deserialize(&buf).unwrap();

                // if this is a output result, then print it
                if let ActionResult::Output(out) = obj {
                    print!("{}", out);
                } else if let ActionResult::OutputErr(out) = obj {
                    print!("{}", out);
                }
            }
        }
    }

    pub fn send(&self, action: Action) -> ActionResult {
        action.send(&self.socket)
    }
}

/// Different kinds of logs are possible. These are from the daemon.
#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum LogCoverage {
    All,
    Communication,
    Intern
}

/// A log entry with a time stamp and a message
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Log {
    pub time: DateTime<Local>,
    pub level: LogCoverage,
    pub text: String
}

/// This structure contains the state of the daemon. The daemon controls different isles with
/// different start parameters.
struct State {
    isles: Vec<Box<Isle>>,
    specs: Vec<IsleParameter>
}

impl State {
    // create a new empty state
    pub fn new() -> State {
        State { isles: Vec::new(), specs: Vec::new() }
    }

    // create a new isle, which starts the application at the path with the parameters specs. The
    // returning integer is the isle id.
    pub fn create_isle(&mut self, path: String, specs: IsleParameter) -> Result<u32> {
        // register the new specifications
        self.specs.push(specs.clone());

        // create a new isle and put it in a box and reduce the object to its trait.
        let mut isle: Box<Isle> = match specs {
            IsleParameter::QEmu { mem_size, num_cpus, additional} => Box::new(QEmu::new(&path, mem_size, num_cpus, additional)?),
            IsleParameter::UHyve{ mem_size, num_cpus } => Box::new(Uhyve::new(&path, mem_size, num_cpus)?),
            IsleParameter::Multi{ mem_size, num_cpus } => Box::new(Multi::new(0, &path, mem_size, num_cpus)?)
        };

        // start the isle
        isle.run()?;

        // register the new isle
        self.isles.push(isle);

        // acquire a new isle id
        Ok(self.isles.len() as u32 -1)
    }
        
    // combine information about the isle and its running state to a single tuple
    pub fn list(&mut self) -> Vec<(Result<bool>, IsleParameter)> {
        self.specs.iter().zip(self.isles.iter_mut()).map(|(x,y)| (y.is_running(), x.clone())).collect()
    }

    // get all log entries up to this point
    pub fn log(&self) -> Vec<Log> {
        let mut logs = Vec::new();
        LOGS.with(|f| {
            logs = (*f.read().unwrap()).to_vec();
        });

        logs
    }

    // add a new log entry
    pub fn add_log(&mut self, action: Action) {
        LOGS.with(|f| {
            let mut writable = f.write().unwrap();

            writable.push(Log { time: Local::now(), level: LogCoverage::Communication, text: format!("{:?}",action) });
        });
    }

    pub fn stop_isle(&mut self, id: u32) -> Result<i32> {
        self.exist_isle(id)?;

        self.isles[id as usize].stop()
    }

    pub fn remove_isle(&mut self, id: u32) -> Result<i32> {
        self.exist_isle(id)?;

        if let Ok(true) = self.isles[id as usize].is_running() {
            self.isles[id as usize].stop();
        }

        self.isles.remove(id as usize);
        self.specs.remove(id as usize);

        Ok(0)
    }

    fn log_isle(&self, id: u32) -> Result<String> {
        self.exist_isle(id)?;

        self.isles[id as usize].output()
    }

    fn exist_isle(&self, id: u32) -> Result<()> {
        if self.isles.len() > id as usize {
            Ok(())
        } else {
            Err(Error::WrongIsleNumber)
        }
    }

    fn add_endpoint(&mut self, id: u32, stream: UnixStream) -> Result<()> {
        self.exist_isle(id)?;

        self.isles[id as usize].add_endpoint(stream)
    }
}

//lazy_static!{
//    ref stopFlag: AtomicBool = AtomicBool::new(false);
//}

extern fn exit_daemon_handler(_: i32) {
    println!("Interrupted!");

    let path = Path::new(DAEMON_PATH);
    if path.exists() {
        fs::remove_file(path).unwrap();
    }

    //stopFlag.store(true, Ordering::Relaxed);
}

enum DaemonError {
    CloseConnection
}

fn daemon_state_loop(state: &mut State, buf: &[u8], mut stream: UnixStream) -> result::Result<UnixStream, DaemonError> {
    let action:Action  = deserialize(&buf).unwrap();
    
    state.add_log(action.clone());

    let ret = match action {
        Action::KillDaemon => {
            fs::remove_file(DAEMON_PATH).unwrap();

            let buf: Vec<u8> = serialize(&ActionResult::KillDaemon(Ok(())), Infinite).unwrap();
            stream.write(&buf);

            process::exit(0);
        },
        Action::CreateIsle(path, specs) => {
            let id = state.create_isle(path,specs);
            let buf: Vec<u8> = serialize(&ActionResult::CreateIsle(id.clone()), Infinite).unwrap();
            stream.write(&buf);

            if let Ok(id) = id {
                state.add_endpoint(id, stream);
            }

            return Err(DaemonError::CloseConnection);
        },
        Action::List => ActionResult::List(state.list()),
        Action::Connect(id) => {
            let buf: Vec<u8> = serialize(&ActionResult::Connect(state.exist_isle(id)), Infinite).unwrap();
            stream.write(&buf);
            
            state.add_endpoint(id, stream);

            return Err(DaemonError::CloseConnection);
        },
        Action::Log(id) => {
            match id {
                Some(id) => ActionResult::IsleLog(state.log_isle(id)),
                None => ActionResult::Log(state.log())
            }
        },
        Action::StopIsle(id) => ActionResult::StopIsle(state.stop_isle(id)),
        Action::RemoveIsle(id) => ActionResult::RemoveIsle(state.remove_isle(id))
    };

    let buf = serialize(&ret, Infinite).unwrap();

    stream.write(&buf);

    Ok(stream)
}

pub fn daemon_handler() {
    let mut state = State::new();
    let mut buf = vec![0; 256];

    // set up the logger
    LocalLogger::init();

    // catch a SIGINT
    let sig_action = signal::SigAction::new(signal::SigHandler::Handler(exit_daemon_handler), signal::SaFlags::empty(), signal::SigSet::empty());
    unsafe { signal::sigaction(signal::SIGINT, &sig_action); }

    let listener = UnixListener::bind(DAEMON_PATH).unwrap();
    for stream in listener.incoming() {
        match stream {
            Ok(mut stream) => {
                    loop {
                        let nread = stream.read(&mut buf);

                        if let Ok(nread) = nread {
                            if nread > 0 {
                                stream = match daemon_state_loop(&mut state, &buf, stream) {
                                    Err(CloseConnection) => break,
                                    Ok(s) => s
                                };
                            } else {
                                break;
                            }
                        } else {
                            break;
                        }
                    }
        },
        Err(err) => { println!("ERR: {:?}", err); }
    }}
}
