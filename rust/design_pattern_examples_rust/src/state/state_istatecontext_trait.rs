//! Contains the IStateContext trait, which is implemented on the StateContext
//! struct.  Each of the state structs holds a reference to the StateContext
//! struct as an IStateContext trait.

/// Represents a set of characters that can include an end-of-file marker
/// without having the marker one of the characters.
pub enum StateChar {
    /// Represents a parsable character.
    Char(char),
    /// Indicates End-of-file (no more data available).
    Eof,
}


/// Represents the context as passed to each state struct.
/// 
/// Each state struct can access the next character or output the current
/// character through this trait.
pub trait IStateContext {
    /// Get the next character from the input.
    ///
    /// # Returns
    /// Returns the next character wrapped in a StateChar::Char().  Returns
    /// StateChar::Eof if there is no more input.
    fn get_next_character(&mut self) -> StateChar;

    /// Write the character to the context.  This is how the parser
    /// accumulates the filtered text.
    ///
    /// # Parameters
    /// - character
    ///
    /// The character to accumulate expressed as a StateChar::Char(c).
    fn output_character(&mut self, character: StateChar);
}
