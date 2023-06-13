//! Contains KeyInput struct that implements the check_for_key() method in an
//! input context.

//-----------------------------------------------------------------------------

use winconsole::input::{self, InputContext, InputEvent};

//-----------------------------------------------------------------------------

/// Represents keyboard input.
pub struct KeyInput {
    context: InputContext,
}

impl KeyInput {
    /// Constructor.
    pub fn new() -> KeyInput {
        let mut local_context = input::start().unwrap();
        local_context.flush();
        KeyInput {
            context: local_context,
        }
    }

    /// Determine if a key has been pressed on the keyboard.
    ///
    /// # Returns
    /// Returns true if a key was pressed; otherwise, returns false.
    pub fn check_for_key(&mut self) -> bool {
        let event = self.context.poll().unwrap();
        event != InputEvent::None
    }
}

impl Drop for KeyInput {
    /// Drop implementation for KeyInput.  Allows for graceful flush of the
    /// input queue.
    fn drop(&mut self) {
        self.context.flush();
    }
}

