//! Contains the check_for_key() function that polls for keyboard input and
//! returns true if a key was pressed.

//-----------------------------------------------------------------------------

use std::time::Duration;

use crossterm::event::{poll, read, Event};

//-----------------------------------------------------------------------------


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
