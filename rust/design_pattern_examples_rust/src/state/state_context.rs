//! Contains the StateContext struct and the other structs used to track state
//! in the finite state machine.

//-----------------------------------------------------------------------------

use super::state_istatecontext_trait::{IStateContext, StateChar};
use super::state_istatebehavior_trait::{IStateBehavior, CurrentState, current_state_to_string};

//-----------------------------------------------------------------------------

//=============================================================================
//=============================================================================

/// Represents the initial state.  Technically, this struct and its
/// implementation is not needed but Rust demands all avenues through code
/// handle all elements of an enum (see StateContext::get_behavior()).
struct StateInitial {
}

impl StateInitial {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateInitial struct as represented by
    /// the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateInitial { })
    }
}

impl IStateBehavior for StateInitial {
    fn go_next(&mut self, _context: &mut dyn IStateContext) -> CurrentState {
        CurrentState::NormalText
    }
}

//=============================================================================
//=============================================================================

/// Represents normal text behavior.
/// 
/// Transitions to the following states for the seen input:
/// - `"`   - go to CurrentState::DoubleQuotedText (start of a double-quoted string)
/// 
/// - `'`   - go to CurrentState::SingleQuotedText (start of a single-quoted string)
/// 
/// - `/`   - go to CurrentState::StartComment (start of a line or block comment)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateNormalText {
}

impl StateNormalText {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateNormalText struct as represented by
    /// the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateNormalText {})
    }
}

impl IStateBehavior for StateNormalText {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::NormalText;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '"' {
                    context.output_character(next_character);
                    current_state = CurrentState::DoubleQuotedText;
                } else if c == '\'' {
                    context.output_character(next_character);
                    current_state = CurrentState::SingleQuotedText;
                } else if c == '/' {
                    current_state = CurrentState::StartComment;
                } else {
                    context.output_character(next_character);
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being inside a double-quote string where filtering is
/// essentially turned off until the end of the string is reached.
/// 
/// Transitions to the following states for the seen input:
/// - `"`   - go to CurrentState::NormalText (end of a double-quoted string)
/// 
/// - `\`   - go to CurrentState::EscapedDoubleQuoteText (start of an escaped character)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateDoubleQuotedText {
}

impl StateDoubleQuotedText {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateDoubleQuotedText struct as
    /// represented by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateDoubleQuotedText {})
    }
}

impl IStateBehavior for StateDoubleQuotedText {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::DoubleQuotedText;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '"' {
                    context.output_character(next_character);
                    current_state = CurrentState::NormalText;
                } else if c == '\\' {
                    context.output_character(next_character);
                    current_state = CurrentState::EscapedDoubleQuoteText;
                } else {
                    context.output_character(next_character);
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being inside a single-quoted string where filtering is
/// effectively turned off until the end of the string is reached.
/// 
/// Transitions to the following states for the seen input:
/// - `'`   - go to CurrentState::NormalText (end of a single-quoted string)
/// 
/// - `\`   - go to CurrentState::EscapedSingleQuoteText (start of an escaped character)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateSingleQuotedText {
}

impl StateSingleQuotedText {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateSingleQuotedText struct as
    /// represented by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateSingleQuotedText {})
    }
}

impl IStateBehavior for StateSingleQuotedText {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::SingleQuotedText;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '\'' {
                    context.output_character(next_character);
                    current_state = CurrentState::NormalText;
                } else if c == '\\' {
                    context.output_character(next_character);
                    current_state = CurrentState::EscapedSingleQuoteText;
                } else {
                    context.output_character(next_character);
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being in an escaped character sequence inside a double-quoted
/// string.  We don't do anything with the escaped character other than output
/// it.  Handling escaped characters allows us to more accurately detect the
/// end of the string.
/// 
/// Transitions to the following states for the seen input:
/// - `{ANY}` - go to CurrentState::DoubleQuotedText (end of escape sequence)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateEscapedDoubleQuotedText {
}

impl StateEscapedDoubleQuotedText {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateEscapedDoubleQuotedText struct as
    /// represented by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateEscapedDoubleQuotedText {})
    }
}

impl IStateBehavior for StateEscapedDoubleQuotedText {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::DoubleQuotedText;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(_) => {
                context.output_character(next_character);
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being in an escaped character sequence inside a single-quoted
/// string.  We don't do anything with the escaped character other than output
/// it.  Handling escaped characters allows us to more accurately detect the
/// end of the string.
/// 
/// Transitions to the following states for the seen input:
/// - `{ANY}` - go to CurrentState::SingleQuotedText (end of escape sequence)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateEscapedSingleQuotedText {
}

impl StateEscapedSingleQuotedText {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateEscapedSingleQuotedText struct as
    /// represented by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateEscapedSingleQuotedText {})
    }
}

impl IStateBehavior for StateEscapedSingleQuotedText {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::SingleQuotedText;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(_) => {
                context.output_character(next_character);
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents the possible start of a line or block comment.
/// 
/// Transitions to the following states for the seen input:
/// - `/`   - go to CurrentState::LineComment (start of a line comment)
/// 
/// - `*`   - go to CurrentState::BlockComment (start of a block comment)
/// 
/// - `{ANY}` - go to CurrentState::NormalText (not start of a comment)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateStartComment {
}

impl StateStartComment {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateStartComment struct as represented
    /// by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateStartComment {})
    }
}

impl IStateBehavior for StateStartComment {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let current_state;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '/' {
                    current_state = CurrentState::LineComment;
                } else if c == '*' {
                    current_state = CurrentState::BlockComment;
                } else {
                    // Not the start of a comment so output the leading slash
                    // that led to the state followed by the character we just
                    // processed.
                    context.output_character(StateChar::Char('/'));
                    context.output_character(next_character);
                    current_state = CurrentState::NormalText;
                }
            }
        }
        current_state
    }
}


//=============================================================================
//=============================================================================

/// Represents being in a line comment.
/// 
/// Transitions to the following states for the seen input:
/// - `\n`  - go to CurrentState::NormalText (a newline is the end of a line comment)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateLineComment {
}

impl StateLineComment {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateLineComment struct as represented
    /// by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateLineComment {})
    }
}

impl IStateBehavior for StateLineComment {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::LineComment;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '\n' {
                    context.output_character(next_character);
                    current_state = CurrentState::NormalText;
                } else {
                    // We are in a comment to be removed, so do nothing here.
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being in a block comment.
/// 
/// Transitions to the following states for the seen input:
/// - `*`  - go to CurrentState::EndBlockComment (possible end of block comment)
///
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateBlockComment {
}

impl StateBlockComment {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateBlockComment struct as represented
    /// by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateBlockComment {})
    }
}

impl IStateBehavior for StateBlockComment {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::BlockComment;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '*' {
                    current_state = CurrentState::EndBlockComment;
                } else {
                    // We are in a comment to be removed, so do nothing here.
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents possibly being at the end of a block comment.
/// 
/// Transitions to the following states for the seen input:
/// - `/`  - go to CurrentState::NormalText (found end of block comment)
/// 
/// - `{ANY}` - go to CurrentState::BlockComment (still in block comment)
/// 
/// - `StateChar::Eof` - go to CurrentState::Done (no more input)
struct StateEndBlockComment {
}

impl StateEndBlockComment {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateEndBlockComment struct as
    /// represented by the IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateEndBlockComment {})
    }
}

impl IStateBehavior for StateEndBlockComment {
    fn go_next(&mut self, context: &mut dyn IStateContext) -> CurrentState {
        let mut current_state = CurrentState::BlockComment;
        let next_character = context.get_next_character();
        match next_character {
            StateChar::Eof => current_state = CurrentState::Done,
            StateChar::Char(c) => {
                if c == '/' {
                    current_state = CurrentState::NormalText;
                } else {
                    // We are in a comment to be removed, so do nothing here.
                }
            }
        }
        current_state
    }
}

//=============================================================================
//=============================================================================

/// Represents being done with input.
/// 
/// Transitions to the following states for the seen input:
/// Always stay in CurrentState::Done
struct StateDone {
}

impl StateDone {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateDone struct as represented by the
    /// IStateBehavior trait.
    pub fn new() -> Box<dyn IStateBehavior> {
        Box::new(StateDone {})
    }
}

impl IStateBehavior for StateDone {
    fn go_next(&mut self, _context: &mut dyn IStateContext) -> CurrentState {
        CurrentState::Done
    }
}

//=============================================================================
//=============================================================================

/// Represents an input string and an output string, along with an index into
/// the input string.  This is used for running the individual characters of
/// the input through the finite state machine to produce filtered output.
///
/// (Normally, the input and output would appear on the StateContext struct,
/// however, there was a circular reference between the IStateContext trait and
/// the IStateBehavior::go_next() method, resulting in an error where a mutable
/// borrow was occurring on an already mutable borrow.  Only way around this
/// was to separate the input/output stuff from the context stuff.)
struct InputOutput {
    /// Text to be filtered.  The given text is converted to a vector so it can
    /// be indexed, allowing us to easily detect end of string.
    input_text: Vec<char>,
    /// Index into the input text.
    text_index: usize,
    /// The output string that accumulates the filtered text.
    output_text: String,
}

impl InputOutput {
    /// Constructor
    ///
    /// # Parameters
    /// - input_text
    ///
    ///   The text to be filtered.
    ///
    /// # Returns
    /// Returns a new instance of the InputOutput struct.
    fn new(input_text: &str) -> InputOutput {
        InputOutput {
            input_text: input_text.chars().collect(),
            text_index: 0,
            output_text: String::from(""),
        }
    }
}


impl IStateContext for InputOutput {
    fn get_next_character(&mut self) -> StateChar {
        let mut character = StateChar::Eof;
        if self.text_index < self.input_text.len() {
            character = StateChar::Char(self.input_text[self.text_index]);
            self.text_index += 1;
        }
        character
    }

    fn output_character(&mut self, character: StateChar) {
        if let StateChar::Char(c) = character {
            self.output_text.push(c);
        }
    }
}


//=============================================================================
//=============================================================================


/// Implementation of the state machine.  This maintains the context in which
/// the state machine runs.
pub struct StateContext {
    /// The current state of the machine.
    current_state: CurrentState,
    /// Maps values from the CurrentState enumeration to instances of the
    /// IStateBehavior representing the behavior for that state.  This vector
    /// owns the StateXXX struct instances.
    behaviors: Vec<(CurrentState, Box<dyn IStateBehavior>)>,
}

impl StateContext {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the StateContext struct.
    pub fn new() -> StateContext {
        StateContext {
            current_state: CurrentState::Initial,
            behaviors: vec![],
        }
    }

    /// Entry point for callers to filter text.  Removes Rust-style line and
    /// block comments from the text.
    ///
    /// # Parameters
    /// - text
    ///
    ///   The text from which to remove comments.
    ///
    /// # Returns
    /// Returns the text as a new string, without the comments.
    pub fn remove_comments(&mut self, text: &str) -> String {
        let mut inputoutput = InputOutput::new(text);
        self.current_state = CurrentState::Initial;
        self.set_next_state(&CurrentState::NormalText);

        while self.current_state != CurrentState::Done {
            let state = self.current_state.clone();
            let behavior = self.get_behavior(&state);
            let current_state = behavior.go_next(&mut inputoutput);
            self.set_next_state(&current_state);
        }
        inputoutput.output_text.clone()
    }


    /// Helper method to transition the state machine to the specified state.
    /// Does nothing if the new state is the same as the old state.
    ///
    /// # Parameters
    /// - new_state
    ///
    ///   A value from the CurrentState enumeration indicating the state to
    ///   which to transition.
    fn set_next_state(&mut self, new_state: &CurrentState) {
        if self.current_state != *new_state {
            println!("    --> State Transition: {0} -> {1}",
                current_state_to_string(&self.current_state),
                current_state_to_string(new_state));
            self.current_state = (*new_state).clone();
        }
    }

    /// Helper method to retrieve the behavior corresponding to the given
    /// state.  A behavior is an implementation of the IStateBehavior trait
    /// that can be called to get a new state.  There is a different behavior
    /// for each state.
    ///
    /// The behaviors are created as needed and cached in the StateContext
    /// struct.
    ///
    /// # Parameters
    /// - state
    ///
    ///   A value from the CurrentState enumeration indicating which behavior
    ///   to return.
    ///
    /// # Returns
    /// Returns a mutable reference to a IStateBehavior instance representing
    /// the specified state.
    fn get_behavior(&mut self, state: &CurrentState) -> &mut Box<dyn IStateBehavior> {
        let mut found_index = self.behaviors.iter().position(|x| x.0 == *state);
        if let None = found_index {
            let behavior = match state {
                CurrentState::Initial => StateInitial::new(),
                CurrentState::NormalText => StateNormalText::new(),
                CurrentState::DoubleQuotedText => StateDoubleQuotedText::new(),
                CurrentState::SingleQuotedText => StateSingleQuotedText::new(),
                CurrentState::EscapedDoubleQuoteText => StateEscapedDoubleQuotedText::new(),
                CurrentState::EscapedSingleQuoteText => StateEscapedSingleQuotedText::new(),
                CurrentState::StartComment => StateStartComment::new(),
                CurrentState::LineComment => StateLineComment::new(),
                CurrentState::BlockComment => StateBlockComment::new(),
                CurrentState::EndBlockComment => StateEndBlockComment::new(),
                CurrentState::Done => StateDone::new(),
            };
            found_index = Some(self.behaviors.len());
            let new_entry = (state.clone(), behavior);
            self.behaviors.push(new_entry);
        }
        let index = found_index.unwrap();
        &mut self.behaviors[index].1
    }
}
