use std::io::{Read, Seek, Cursor};
use std::mem;
use byteorder::{ReadBytesExt, WriteBytesExt,LittleEndian,BigEndian};
use std::ffi::CString;

const PACKET_LENGTH: &'static [u64] = &[1,3,1,1,2,3];

#[derive(Debug)]
pub enum PartialPacket {
    Exit { arg: i32 },
    Write { fd: i32, len: u64 },
    Open { len: i64 },
    Close { fd: i32 },
    Read { fd: i32, len: u64 },
    LSeek { fd: i32, offset: i64, whence: i32 }
}

impl PartialPacket {
    pub fn from_buf(id: i32, buf: &mut Cursor<Vec<u8>>) -> PartialPacket {
        match id {
            0 => PartialPacket::Exit { 
                arg: buf.read_i32::<LittleEndian>().unwrap() 
            },
            1 => PartialPacket::Write {
                fd: buf.read_i32::<LittleEndian>().unwrap(),
                len: buf.read_u64::<LittleEndian>().unwrap()
            },
            2 => PartialPacket::Open {
                len: buf.read_i64::<LittleEndian>().unwrap()
            },
            3 => PartialPacket::Close {
                fd: buf.read_i32::<LittleEndian>().unwrap()
            },
            4 => PartialPacket::Read {
                fd: buf.read_i32::<LittleEndian>().unwrap(),
                len: buf.read_u64::<LittleEndian>().unwrap()
            },
            5 => PartialPacket::LSeek {
                fd: buf.read_i32::<LittleEndian>().unwrap(),
                offset: buf.read_i64::<LittleEndian>().unwrap(),
                whence: buf.read_i32::<LittleEndian>().unwrap()
            },
            _ => panic!("")
        }
    }

    pub fn additional_size(&self) -> usize {
        match *self {
            PartialPacket::Write { fd, len } => len as usize,
            PartialPacket::Open { len } => len as usize + 8,
            _ => 0
        }
    }
}

#[derive(Debug)]
pub enum Packet {
    Exit { arg: i32 },
    Write { fd: i32, buf: Vec<u8> },
    Open { name: CString, flags: i32, mode: i32 },
    Close { fd: i32 },
    Read { fd: i32, len: u64 },
    LSeek { fd: i32, whence: i32, offset: i64 }
}

impl Packet {
    pub fn from_buf(obj: &PartialPacket, buf: &mut Cursor<Vec<u8>>) -> Packet {

        //println!("{:?}", *obj);


        match *obj {
            PartialPacket::Write { fd, len } => {
                debug!("Read write packet with length {}", len);
                let mut content = vec![0; len as usize];
                buf.read(&mut content);

                Packet::Write { fd: fd, buf: content }
            },
            PartialPacket::Open { len } => {
                let mut name_buf = vec![0; len as usize];
                buf.read(&mut name_buf);
                name_buf.pop();

                let c_str = CString::new(name_buf).unwrap();

                Packet::Open { 
                    name: c_str, 
                    flags: buf.read_i32::<LittleEndian>().unwrap(), 
                    mode: buf.read_i32::<LittleEndian>().unwrap() 
                }
            },
            PartialPacket::Exit { arg } => Packet::Exit { arg },
            PartialPacket::Close { fd } => Packet::Close { fd },
            PartialPacket::Read { fd, len } => Packet::Read { fd, len },
            PartialPacket::LSeek { fd, whence, offset } => Packet::LSeek { fd, whence, offset }
        }
    }
}

#[derive(Debug)]
pub enum State {
    Id,
    Type { id: i32, len: u64 },
    Partial(PartialPacket),
    Finished(Packet)
}

impl State {
    pub fn read_in(self, buf: &mut Cursor<Vec<u8>>) -> State {
        let length = buf.get_ref().len() - buf.position() as usize;
        
        match self {
            State::Id if length < mem::size_of::<isize>() => {
                State::Id
            },
            State::Id => {
                let id = buf.read_i32::<LittleEndian>().unwrap();
                State::Type { 
                    id: id, 
                    len: match id as usize {
                        x @ 0...5 => PACKET_LENGTH[x],
                        _ => panic!("")
                    }
                }
            },
            State::Type { id, len } => {
                if length >= (len as usize) * mem::size_of::<i32>() {
                    let par_packet = State::Partial(PartialPacket::from_buf(id, buf));
                    debug!("Partial packet {:?} pos {}", par_packet, buf.position());

                    par_packet
                } else {
                    self
                }
            },
            State::Partial(ref packet) if length >= packet.additional_size()  => {
                    State::Finished(Packet::from_buf(packet, buf))
            },
            _ => { self }
        }
    }
}
