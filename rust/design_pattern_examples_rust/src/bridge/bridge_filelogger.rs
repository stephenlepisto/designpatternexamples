//! Contains the FileLogger implementation.

use std::fs::File;
use std::io::Write;

use std::boxed::Box;
use super::bridge_ilogger_trait::ILogger;
use super::bridge_loghelper::loghelper_formatlogline;

/// Represents a logger that writes logging to a file.
pub struct FileLogger {
    filename: String,
    file: File,
}

impl FileLogger {
    /// Create an instance of a file logger, which writes to a file.  The file
    /// is always overwritten each time the bridge example is run.
    ///
    /// # Parameters
    /// - filename
    ///
    ///   Name of the log file to output to.
    ///
    /// # Returns
    ///   An instance of an ILogger object.
    pub fn new(filename: &str) -> Box<dyn ILogger> {
        Box::new(FileLogger {
            filename: filename.to_string(),
            file: File::create(filename).unwrap(),
        })
    }
}

impl ILogger for FileLogger {
    fn write_line(&mut self, loglevel:&str, message: &str) {
        let output = loghelper_formatlogline(loglevel, message);
        match self.file.write_all(output.as_bytes()) {
            Ok(_) => { },
            Err(ioerror) => {
                eprintln!("Failed to write to file \"{}\": Error = {:#?}", self.filename, ioerror);
            }
        }
    }
}
