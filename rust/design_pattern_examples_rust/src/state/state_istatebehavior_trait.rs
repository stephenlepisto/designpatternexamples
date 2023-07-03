//! Contains the CurrentState enum and the IStateBehavior trait, which is used
//! by all states to ensure they are compliant with the expected behavior of
//! the state machine.

//-----------------------------------------------------------------------------

use super::state_istatecontext_trait::IStateContext;
//-----------------------------------------------------------------------------

/// Represents the current state of the state machine.
#[derive(Hash, Eq, PartialEq, Clone)]
pub enum CurrentState {
    /// State before the state machine actually starts.  transitions to NormalText
    Initial,
    /// `"` transitions to QuotedText, / transitions to StartComment, EOF_CHAR transitions to Done
    NormalText,
    /// `\` transitions to EscapedDoubleQuoteText, " transitions to NormalText, EOF_CHAR transitions to Done
    DoubleQuotedText,
    /// `'` transitions to EscapedSingleQuoteText, \ transitions to NormalText, EOF_CHAR transitions to Done
    SingleQuotedText,
    /// `\` transitions to QuotedText, EOF_CHAR transitions to Done
    EscapedDoubleQuoteText,
    /// `\` transitions to SingleQuotedText, EOF_CHAR transitions to Done
    EscapedSingleQuoteText,
    /// `/` transitions to LineComment, * transitions to BlockComment, EOF_CHAR transitions to Done, all else transitions to NormalText
    StartComment,
    /// `\\n` transitions to NormalText, EOF_CHAR transitions to Done
    LineComment,
    /// `*` transitions to EndBlockComment, EOF_CHAR transitions to Done
    BlockComment,
    /// `/` transitions to NormalText, EOF_CHAR transitions to Done, all else transitions to BlockComment
    EndBlockComment,
    /// Indicates processing is done
    Done
}

/// Helper function to convert the CurrentState enumeration to a string for
/// output purposes.
///
/// # Parameters
/// - state
/// 
/// A value from the CurrentState enumeration.
///
/// # Returns
/// Returns a string containing the string version of the given state.
pub fn current_state_to_string(state: &CurrentState) -> String {
    match state {
        CurrentState::Initial => String::from("Initial"),
        CurrentState::NormalText => String::from("NormalText"),
        CurrentState::DoubleQuotedText => String::from("DoubleQuotedText"),
        CurrentState::SingleQuotedText => String::from("SingleQuotedText"),
        CurrentState::EscapedDoubleQuoteText => String::from("EscapedDoubleQuoteText"),
        CurrentState::EscapedSingleQuoteText => String::from("EscapedSingleQuoteText"),
        CurrentState::StartComment => String::from("StartComment"),
        CurrentState::LineComment => String::from("LineComment"),
        CurrentState::BlockComment => String::from("BlockComment"),
        CurrentState::EndBlockComment => String::from("EndBlockComment"),
        CurrentState::Done => String::from("Done"),
    }
}


//#############################################################################
//#############################################################################


/// Represents a state object that implements one state of the state machine.
/// 
/// The context calls each state through this interface.
///
/// Technically, the StateContext struct knows about the actual state structs
/// because it has to instantiate them but this trait makes the code for
/// calling the state structs much simpler.
pub trait IStateBehavior {
    /// Process the next character from the context, returning the next
    /// state the context should move to.
    ///
    /// # Parameters
    /// - context
    ///
    ///   An IStateContext object representing the context to use for getting
    ///   the next character of input and to which to output characters.
    ///
    /// # Returns
    /// Returns a value from the CurrentState enumeration indicating the next
    /// state to which the state machine should transition to.
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState;
}
