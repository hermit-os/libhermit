use std::os::unix::net::{UnixStream, UnixListener};
use std::path::Path;
use std::thread;
use nix::unistd::{fork, ForkResult};
use hermit::Isle;
use std::io::Write;
use std::io::Read;
use bincode::{serialize, deserialize, Infinite};
use std::fs;
use hermit::IsleParameter;
use hermit::qemu::QEmu;
use hermit::multi::Multi;
use hermit::uhyve::Uhyve;
use hermit::error::Result;
use chrono::{DateTime,Local};

pub struct Connection {
    pub socket: UnixStream
}

impl Connection {
    pub fn connect() -> Connection {
        if !Path::new("/tmp/hermit_daemon").exists() {
            match fork() {
                Ok(ForkResult::Child) => daemon_handler(),
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

        self.socket.read_to_end(&mut buf).unwrap();

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
pub struct Log {
    pub time: DateTime<Local>,
    pub action: Action
}

struct State {
    isles: Vec<Box<Isle>>,
    specs: Vec<IsleParameter>,
    logs: Vec<Log>
}

impl State {
    pub fn new() -> State {
        State { isles: Vec::new(), logs: Vec::new(), specs: Vec::new() }
    }

    pub fn create_isle(&mut self, path: String, specs: IsleParameter) -> Result<u32> {
        self.specs.push(specs.clone());

        let mut isle: Box<Isle> = match specs {
            IsleParameter::QEmu { mem_size, num_cpus, additional} => Box::new(QEmu::new(&path, mem_size, num_cpus, additional)?),
            IsleParameter::UHyve{ mem_size, num_cpus } => Box::new(Uhyve::new(&path, mem_size, num_cpus)?),
            IsleParameter::Multi{ mem_size, num_cpus } => Box::new(Multi::new(0, &path, mem_size, num_cpus)?)
        };

        isle.wait_until_available()?;
        isle.run()?;

        self.isles.push(isle);

        Ok(self.isles.len() as u32 -1)
    }

    pub fn list(&mut self) -> Vec<(Result<bool>, IsleParameter)> {
        self.specs.iter().zip(self.isles.iter_mut()).map(|(x,y)| (y.is_running(), x.clone())).collect()
    }

    pub fn log(&self) -> Vec<Log> {
        self.logs.clone()
    }

    pub fn add_log(&mut self, action: Action) {
        self.logs.push(Log { time: Local::now(), action: action });
    }

    pub fn stop_isle(&mut self, id: u32) -> Result<i32> {
        self.isles[id as usize].stop()
    }

    pub fn remove_isle(&mut self, id: u32) -> Result<i32> {
        if self.isles[id as usize].is_running()? {
            self.isles[id as usize].stop()?;
        }

        self.isles.remove(id as usize);
        self.specs.remove(id as usize);

        Ok(0)
    }
}

pub fn daemon_handler() {
    let mut state = State::new();
    let mut buf = vec![0; 256];

    let listener = UnixListener::bind("/tmp/hermit_daemon").unwrap();
    //for stream in listener.incoming() {
    //    match stream {
    //        Ok(mut stream) => {
    loop { match listener.accept() {
        Ok((mut stream, addr)) => {
//            loop {
                    if let Ok(nread) = stream.read(&mut buf) {
                        if nread > 0 {
                            let action:Action  = deserialize(&buf).unwrap();
                            
                            state.add_log(action.clone());

                            let ret = match action {
                                Action::KillDaemon => {
                                    fs::remove_file("/tmp/hermit_daemon").unwrap();
                                    break;
                                },
                                Action::CreateIsle(path, specs) => ActionResult::CreateIsle(state.create_isle(path,specs)),
                                Action::List => ActionResult::List(state.list()),
                                Action::Log(id) => {
                                    match id {
                                        Some(id) => ActionResult::IsleLog(state.isles[id as usize].output()),
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
