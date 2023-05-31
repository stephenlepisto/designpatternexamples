//! Contains the ConsoleLogger implementation.

use std::boxed::Box;
use super::bridge_ilogger_trait::ILogger;
use super::bridge_loghelper::loghelper_formatlogline;

/// Represents a logger that writes logging to the standard output.
pub struct ConsoleLogger { }

impl ConsoleLogger {
    /// Create an instance of a console logger, which writes to the standard
    /// output.
    ///
    /// # Returns
    ///   An instance of an ILogger object.
    pub fn new() -> Box<dyn ILogger> {
        Box::new(ConsoleLogger{})
    }
}

impl ILogger for ConsoleLogger {
    fn write_line(&mut self, loglevel:&str, message: &str) {
        let output = loghelper_formatlogline(loglevel, message);
        print!("{output}");
    }
}
