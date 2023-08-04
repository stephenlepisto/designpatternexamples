//! Contains functions fo dealing with input echo to standard out
//! (is_input_echo_disabled(), enable_input_echo(), disable_input_echo()) as
//! well as a function for determining if a key is pressed (check_for_key()).

//-----------------------------------------------------------------------------

use std::time::Duration;
use std::sync::Mutex;

use crossterm::{
    terminal,
    event::{poll, read, Event},
};

//-----------------------------------------------------------------------------

/// Global field indicating whether input echo has been disabled.
static INPUT_ECHO_DISABLED: Mutex<bool> = Mutex::new(false);

/// Determine if we have disabled input echo.
///
/// # Returns
/// Returns true if we have disabled input echo with disable_input_echo();
/// otherwise, returns false.
pub fn is_input_echo_disabled() -> bool {
    let echo_disabled = INPUT_ECHO_DISABLED.lock().unwrap();
    *echo_disabled
}

/// Enable input echo.  This is the normal state of standard input, where all
/// input in standard input is echoed to standard output.
pub fn enable_input_echo() {
    if is_input_echo_disabled() {
        terminal::disable_raw_mode().unwrap();
        *INPUT_ECHO_DISABLED.lock().unwrap() = true;
    }
}

/// Disable input echo.  Once disabled, all input from standard input is NOT
/// echoed to standard output and is otherwise invisible.  The input is still
/// there, just not visible in standard output.
pub fn disable_input_echo() {
    if !is_input_echo_disabled() {
        terminal::enable_raw_mode().unwrap();
        *INPUT_ECHO_DISABLED.lock().unwrap() = false;
    }
}

/// Determine if a key has been pressed on the keyboard.
///
/// # Returns
/// Returns true if a key was pressed; otherwise, returns false.
pub fn check_for_key() -> bool {
    let mut key_pressed = false;
    if let Ok(event_ready) = poll(Duration::from_millis(0)) {
        if event_ready {
            if let Ok(Event::Key(_k)) = read() {
                key_pressed = true;
            }
        }
    }
    key_pressed
}
