use std::os::unix::net::{UnixStream, UnixListener};
use std::path::Path;
use std::result;
use std::thread;
use std::process;
use log;
use log::{LogMetadata, LogRecord, SetLoggerError, LogLevel, LogLevelFilter};
use nix::unistd::{fork, ForkResult};
use hermit::Isle;
use std::sync::RwLock;
use std::io::Write;
use std::io::Read;
use bincode::{serialize, deserialize, Infinite};
use std::fs;
use hermit::IsleParameter;
use hermit::qemu::QEmu;
use hermit::multi::Multi;
use hermit::uhyve::Uhyve;
use hermit::error::{Result,Error};
use chrono::{DateTime,Local};

thread_local!{
    static LOGS: RwLock<Vec<Log>> = RwLock::new(Vec::new());
}

struct LocalLogger;

impl log::Log for LocalLogger {
    fn enabled(&self, metadata: &LogMetadata) -> bool {
        true
    }

    fn log(&self, record: &LogRecord) {

        LOGS.with(|f| {
            let mut writable = f.write().unwrap();

            writable.push(Log { time: Local::now(), level: LogCoverage::Intern, text: format!("{}", record.args()) });
        });

    }
}

impl LocalLogger {
    pub fn init() -> result::Result<(), SetLoggerError> {
        log::set_logger(|max_level| {
            max_level.set(LogLevelFilter::Trace);
            Box::new(LocalLogger)
        })
    }
}

pub struct Connection {
    pub socket: UnixStream
}

impl Connection {
    pub fn connect() -> Connection {
        if !Path::new("/tmp/hermit_daemon").exists() {
            match fork() {
                Ok(ForkResult::Child) => {
                    daemon_handler();

                    process::exit(0);
                },
                _ => {}
            }
        }

        loop {
            if let Ok(socket) = UnixStream::connect("/tmp/hermit_daemon") {
                return Connection { socket: socket };
            }
        }
    }

    pub fn send(&mut self,action: Action) -> ActionResult {
        let encoded = serialize(&action, Infinite).unwrap();

        self.socket.write(&encoded).unwrap();

        let mut buf = Vec::new();

        if let Err(err) = self.socket.read_to_end(&mut buf) {
            if let Action::KillDaemon = action {
                return ActionResult::KillDaemon(Ok(()));
            }

            panic!("The daemon seem to be crashed!");
        }

        if buf.len() == 0 {
            if let Action::KillDaemon = action {
                return ActionResult::KillDaemon(Ok(()));
            } else {
                panic!("he result was empty!");
            }
        }

        deserialize(&buf).unwrap()
    }
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum Action {
    CreateIsle(String, IsleParameter),
    StopIsle(u32),
    RemoveIsle(u32),
    Log(Option<u32>),
    List,
    KillDaemon
}

#[derive(Serialize, Deserialize, Debug)]
pub enum ActionResult {
    CreateIsle(Result<u32>),
    StopIsle(Result<i32>),
    RemoveIsle(Result<i32>),
    Log(Vec<Log>),
    IsleLog(Result<String>),
    List(Vec<(Result<bool>, IsleParameter)>),
    KillDaemon(Result<()>)
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum LogCoverage {
    All,
    Communication,
    Intern
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Log {
    pub time: DateTime<Local>,
    pub level: LogCoverage,
    pub text: String
}

struct State {
    isles: Vec<Box<Isle>>,
    specs: Vec<IsleParameter>
}

impl State {
    pub fn new() -> State {
        State { isles: Vec::new(), specs: Vec::new() }
    }

    pub fn create_isle(&mut self, path: String, specs: IsleParameter) -> Result<u32> {
        self.specs.push(specs.clone());

        let mut isle: Box<Isle> = match specs {
            IsleParameter::QEmu { mem_size, num_cpus, additional} => Box::new(QEmu::new(&path, mem_size, num_cpus, additional)?),
            IsleParameter::UHyve{ mem_size, num_cpus } => Box::new(Uhyve::new(&path, mem_size, num_cpus)?),
            IsleParameter::Multi{ mem_size, num_cpus } => Box::new(Multi::new(0, &path, mem_size, num_cpus)?)
        };

        isle.run()?;

        self.isles.push(isle);

        Ok(self.isles.len() as u32 -1)
    }

    pub fn list(&mut self) -> Vec<(Result<bool>, IsleParameter)> {
        self.specs.iter().zip(self.isles.iter_mut()).map(|(x,y)| (y.is_running(), x.clone())).collect()
    }

    pub fn log(&self) -> Vec<Log> {
        let mut logs = Vec::new();
        LOGS.with(|f| {
            logs = (*f.read().unwrap()).to_vec();
        });

        logs
    }

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

        if self.isles[id as usize].is_running()? {
            self.isles[id as usize].stop()?;
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
}

pub fn daemon_handler() {
    let mut state = State::new();
    let mut buf = vec![0; 256];

    LocalLogger::init();

    let listener = UnixListener::bind("/tmp/hermit_daemon").unwrap();
    //for stream in listener.incoming() {
    //    match stream {
    //        Ok(mut stream) => {
    'outer: loop { match listener.accept() {
        Ok((mut stream, addr)) => {
//            loop {
                    if let Ok(nread) = stream.read(&mut buf) {
                        if nread > 0 {
                            let action:Action  = deserialize(&buf).unwrap();
                            
                            state.add_log(action.clone());

                            let ret = match action {
                                Action::KillDaemon => {
                                    fs::remove_file("/tmp/hermit_daemon").unwrap();
                                    break 'outer;
                                },
                                Action::CreateIsle(path, specs) => ActionResult::CreateIsle(state.create_isle(path,specs)),
                                Action::List => ActionResult::List(state.list()),
                                Action::Log(id) => {
                                    match id {
                                        Some(id) => ActionResult::IsleLog(state.log_isle(id)),
                                        None => ActionResult::Log(state.log())
                                    }
                                },
                                Action::StopIsle(id) => ActionResult::StopIsle(state.stop_isle(id)),
                                Action::RemoveIsle(id) => ActionResult::RemoveIsle(state.remove_isle(id)),
                                _ => { panic!(""); }
                            };

                            let buf: Vec<u8> = serialize(&ret, Infinite).unwrap();
                            stream.write(&buf);
                        }
                    } else {

                    }
  //              }
            },
            Err(err) => {
                println!("ERR: {:?}", err);
            }
        }
    }
}
