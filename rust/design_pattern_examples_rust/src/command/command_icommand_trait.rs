//! Contains the ICommand trait that commands implement so they look the same
//! to the main program.

use super::command_textobject::CommandTextObject;

/// Represents a general command that does something.
pub trait ICommand {
    /// Execute the command on the given CommandTextObject.
    fn execute(&self, receiver: &mut CommandTextObject);
    /// Convert the command to a string representation.
    fn to_string(&self) -> String;
}
