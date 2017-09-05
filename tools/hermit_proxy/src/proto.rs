use std::os::unix::net::UnixStream;
use bincode::{serialize, deserialize, Infinite};
use hermit::IsleParameter;
use hermit::error::Result;
use daemon::Log;
use std::io::{Write, Read};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum Action {
    CreateIsle(String, IsleParameter),
    StopIsle(u32),
    RemoveIsle(u32),
    Connect(u32),
    Log(Option<u32>),
    List,
    KillDaemon
}

impl Action {
    pub fn send(&self, mut socket: &UnixStream) -> ActionResult {
        let encoded = serialize(self, Infinite).unwrap();

        socket.write(&encoded).unwrap();

        let mut tmp = vec![0; 1024];
        let mut buf = Vec::new();

        loop {
            match socket.read(&mut tmp) {
                Ok(0) => break,
                Ok(nread) => buf.extend_from_slice(&tmp[0..nread]),
                Err(_) => {
                    if buf.len() > 0 {
                        break;
                    }
                }
            }
        }

        if buf.len() == 0 {
            if let Action::KillDaemon = *self {
                return ActionResult::KillDaemon(Ok(()));
            } else {
                panic!("The result was empty!");
            }
        }

        deserialize(&buf).unwrap()
    }
}

#[derive(Serialize, Deserialize, Debug)]
pub enum ActionResult {
    CreateIsle(Result<u32>),
    StopIsle(Result<i32>),
    RemoveIsle(Result<i32>),
    Connect(Result<()>),
    Log(Vec<Log>),
    IsleLog(Result<String>),
    List(Vec<(Result<bool>, IsleParameter)>),
    KillDaemon(Result<()>),
    Output(String),
    OutputErr(String)
}


