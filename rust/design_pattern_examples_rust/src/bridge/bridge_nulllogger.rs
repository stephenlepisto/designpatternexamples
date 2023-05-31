//! Contains the NullLogger implementation.

use std::boxed::Box;
use super::bridge_ilogger_trait::ILogger;

/// Represents a logger that throws away anything sent its way.
pub struct NullLogger {}

impl NullLogger {
    /// Create an instance of a null logger, a logger that doesn't do anything.
    ///
    /// # Returns
    ///   An instance of an ILogger object.
    pub fn new() -> Box<dyn ILogger> {
        Box::new(NullLogger{})
    }
}
impl ILogger for NullLogger {
    fn write_line(&mut self, _loglevel:&str, _message: &str) {
        // do nothing
    }
}
