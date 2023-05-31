//! The Bridge design pattern example module
//!
//! In this example, the Bridge pattern is used to allow a program to offer
//! multiple ways to perform logging without changing how the logging is used
//! throughout the program.
//!
//! Take note of how the calls into the logger are the same regardless of the
//! logger used.
//!
//! Accessed through the bridge_exercise() function.

pub mod bridge_ilogger_trait;
pub mod bridge_logger;
pub mod bridge_nulllogger;
pub mod bridge_filelogger;
pub mod bridge_consolelogger;
pub mod bridge_loghelper;

use bridge_ilogger_trait::ILogger;
use bridge_logger::{create_logger, LoggerType};

//-----------------------------------------------------------------------------

/// Helper function to show an example of writing to a logger.
/// 
/// This is called for all types of loggers, showing how the ILogger interface
/// hides the details of the underlying implementation.
///
/// # Parameters
/// - logger
///
///   A struct that implements the ILogger trait to which to log to.
/// - logger_type
///
///   The type of the underlying logging implementation.
fn _bridge_exercise_demonstrate_logging(logger: &mut Box<dyn ILogger>, logger_type: &str) {
    let mut message = format!("Starting log to {logger_type} example");

    logger.log_trace(&message);
    logger.log_info("An example of an informational line");
    logger.log_error("An example of an error log entry");

    message = format!("Done with log to {logger_type} example");
    logger.log_trace(&message);
}


//-----------------------------------------------------------------------------


/// Example of using the "Bridge" _pattern.
/// 
/// In this example, the Bridge pattern is used to allow a program to offer
/// multiple ways to perform logging without changing how the logging is
/// used throughout the program.
///
/// In this exercise, note how the calls into the logger are the
/// same regardless of the logger used.
pub fn bridge_exercise() -> Result<(), String> {
    println!("");
    println!("Bridge Exercise");

    {
        let mut logger = create_logger(LoggerType::ToFile, "bridge.log");
        println!("  Example of writing to a log file...");
        _bridge_exercise_demonstrate_logging(&mut logger, "file");
    }

    {
        let mut logger = create_logger(LoggerType::ToConsole, "");
        println!("  Example of writing to the console...");
        _bridge_exercise_demonstrate_logging(&mut logger, "console");
    }

    {
        let mut logger = create_logger(LoggerType::ToNull, "");
        println!("  Example of writing to a Null object (no output)...");
        _bridge_exercise_demonstrate_logging(&mut logger, "null");
    }

    println!("  Done.");

    Ok(())
}
