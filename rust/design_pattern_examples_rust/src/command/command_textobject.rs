//! Contains the CommandTextObject implementation.

use std::fmt;

/// Container for a string.  Need to use a class that allows the text to
/// be changed while the container (this class) remains constant.  This
/// way, operations can be applied to the text and the container's contents
/// change but not the container.
pub struct CommandTextObject {
    /// Starting string text so we can reset the text to a known point.
    starting_text: String,

    /// The text that can change.
    pub text: String,
}

impl CommandTextObject {
    /// Constructs a text object with an initial string.
    ///
    /// # Parameters
    /// - text
    ///
    ///   The initial string for the text object.
    pub fn new(text: &str) -> CommandTextObject {
        CommandTextObject {
            starting_text: text.to_string(),
            text: text.to_string(),
        }
    }

    /// Resets the TextObject to the starting string.
    pub fn reset(&mut self) {
        self.text = self.starting_text.clone();
    }
}

impl fmt::Display for CommandTextObject {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.text)
    }
}
