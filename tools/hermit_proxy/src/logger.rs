use log;
use log::{LogMetadata, LogRecord, SetLoggerError, LogLevelFilter};
use std::sync::RwLock;
use daemon::{Log, LogCoverage};
use chrono::Local;

thread_local!{
    pub static LOGS: RwLock<Vec<Log>> = RwLock::new(Vec::new());
}

pub struct LocalLogger;

impl log::Log for LocalLogger {
    fn enabled(&self, _: &LogMetadata) -> bool {
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
    pub fn init() -> Result<(), SetLoggerError> {
        log::set_logger(|max_level| {
            max_level.set(LogLevelFilter::Trace);
            Box::new(LocalLogger)
        })
    }
}
