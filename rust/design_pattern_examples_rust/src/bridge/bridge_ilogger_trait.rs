//! Contains the ILogger trait that loggers can implement.
//!
//! The ILogger interface acts as a bridge between the application and the
//! specific logging functionality implemented in this example of the bridge
//! pattern.


/// Represents the ability to send logging messages to some kind of output,
/// which is dictated by the required implementation of ILogger::write_line().
pub trait ILogger {
    /// Send a formatted line to the logger.  Must be implemented by any struct
    /// implementing the ILogger trait.
    ///
    /// # Parameters
    /// - loglevel
    ///
    ///   Level of logging ("TRACE", "INFO", "ERROR")
    /// - message
    ///
    ///   Message to log
    fn write_line(&mut self, loglevel: &str, message: &str);

    /// Log trace messages to the configured output.  A newline will always be
    /// added to the message when writing to the log.  Default behavior is to
    /// send the message to ILogger::write_line().
    ///
    /// # Parameters
    /// - message
    ///
    ///   The message to write to the log.
    fn log_trace(&mut self, message: &str) {
        self.write_line("TRACE", message);
    }

    /// Log information messages to the configured output.  A newline will
    /// always be added to the message when writing to the log.  Default
    /// behavior is to send the message to ILogger::write_line().
    ///
    /// # Parameters
    /// - message
    ///
    ///   The message to write to the log.
    fn log_info(&mut self, message: &str) {
        self.write_line("INFO", message);
    }

    /// Log error messages to the configured output.  A newline will always be
    /// added to the message when writing to the log.  Default behavior is to
    /// send the message to ILogger::write_line().
    ///
    /// # Parameters
    /// - message
    ///
    ///   The message to write to the log.
    fn log_error(&mut self, message: &str) {
        self.write_line("ERROR", message);
    }
}
