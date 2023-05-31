//! Contains the loghelper_formatlogline() function for formatting a complete
//! line to be written to a log.

use time::OffsetDateTime;
use time::macros::format_description;

/// The string with which to format a timestamp for logging.
const DATE_FORMAT_STR: &[time::format_description::FormatItem<'static>] = format_description!(version = 2, "[month]/[day]/[year]  [hour repr:12]:[minute]:[second] [period]");

/// Return a regular time stamp of the current time in local time.
fn _gettimestamp() -> String {
    let local_time = OffsetDateTime::now_local().unwrap();
    local_time.format(&DATE_FORMAT_STR).unwrap()
}

/// Format a line for logging, including time stamp.
///
/// # Parameters
/// - loglevel
///
///   Level of logging ("TRACE", "INFO", "ERROR")
/// - message
///
///   Message to log
///
/// # Returns
///   A string containing the formatted log line.
pub fn loghelper_formatlogline(loglevel: &str, message: &str) -> String {
    let timestamp = _gettimestamp();
    format!("{timestamp} [{loglevel:<5}] {message}\n")
}
