use std::env;
use super::utils;

pub fn isle_kind() -> String {
    env::var("HERMIT_ISLE").unwrap_or("qemu".into())
}

pub fn qemu_binary() -> String {
    env::var("HERMIT_QEMU").unwrap_or("qemu-system-x86_64".into())
}

pub fn num_cpus() -> String {
    env::var("HERMIT_CPUS").unwrap_or("1".into())
}

pub fn num_cpus_parsed() -> u32 {
    env::var("HERMIT_CPUS").map(|x| x.parse().unwrap_or(1)).unwrap_or(1)
}

pub fn mem_size() -> String {
    env::var("HERMIT_MEM").unwrap_or("2G".into())
}

pub fn mem_size_parsed() -> usize {
    env::var("HERMIT_MEM").map(|x| utils::parse_mem(&x).unwrap_or(512*1024*1024)).unwrap_or(512*1024*1024)
}

pub fn use_kvm() -> String {
    env::var("HERMIT_KVM").unwrap_or("1".into())
}

pub fn monitor() -> String {
    env::var("HERMIT_MONITOR").unwrap_or("0".into())
}

pub fn should_debug() -> String {
    env::var("HERMIT_DEBUG").unwrap_or("0".into())
}

pub fn capture_net() -> String {
    env::var("HERMIT_CAPTURE_NET").unwrap_or("0".into())
}

pub fn verbose() -> String {
    env::var("HERMIT_VERBOSE").unwrap_or("0".into())
}

pub fn port() -> String {
    env::var("HERMIT_PORT").unwrap_or("18766".into())
}

pub fn app_port() -> String {
    env::var("HERMIT_APP_PORT").unwrap_or("".into())
}

