//! Contains the LoggerType enumeration and the create_logger() factory function
//! for instantiating specific kinds of loggers that implement the ILogger
//! trait.

use crate::bridge::bridge_ilogger_trait::ILogger;
use super::bridge_nulllogger::NullLogger;
use super::bridge_consolelogger::ConsoleLogger;
use super::bridge_filelogger::FileLogger;


pub enum LoggerType {
    /// Log to nowhere, that is, throw out all logging.  No additional parameters.
    ToNull = 0,

    /// Log to a file.  One additional parameter: the name of the file to log to.
    ToFile = 1,

    /// Log to the console.  No additional parameters.
    ToConsole = 2,

}

/// Factor function that takes a LoggerTypes value to create a new Logger instance.
///
/// # Parameters
/// - logger_type
///
///   A value from the LoggerTypes enumeration specifying the type of logger
///   object to create.
/// - filename
///
///   If creating a LoggerType::ToFile, then `filename` specifies the path and
///   name of the file to write to.  Otherwise, this parameter is ignored (just
///   pass an empty string).
///
/// # Returns
/// Returns an object represented by the ILogger trait.
pub fn create_logger(logger_type: LoggerType, filename: &str) -> Box<dyn ILogger> {
    match logger_type {
        LoggerType::ToNull => NullLogger::new(),
        LoggerType::ToConsole => ConsoleLogger::new(),
        LoggerType::ToFile => FileLogger::new(&filename),
    }
}