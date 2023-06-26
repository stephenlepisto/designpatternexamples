//! The Interpreter design pattern example module
//!
//! The interpreter is a function that is fed a series of arrays containing
//! integer tokens.  Each token represents a single word or punctuation mark.
//! The interpreter converts that array of tokens to an actual sentence by
//! interpreting the meaning of the tokens.
//! 
//! This is a very simple interpreter that handles the first token in a special
//! way and supports punctuation.  It is an example of a linear interpreter
//! where tokens can appear in any order (it's up to the creator of the token
//! list to make sure the outcome makes any sense).
//!
//! Accessed through the interpreter_exercise() function.

//-----------------------------------------------------------------------------

pub mod interpreter_interpreter;

//-----------------------------------------------------------------------------

use interpreter_interpreter::{InterpreterConstants, interpreter_interpret};

//-----------------------------------------------------------------------------

/// Represents the sentence: "What do you say to that?"
const SENTENCE_TOKENS0: &'static [usize] = &[ 39, 18, 17, 27,  2,  7, InterpreterConstants::QUESTION as usize, InterpreterConstants::EOL as usize ];

/// Represents the sentence: "Will you be the one to be there?"
const SENTENCE_TOKENS1: &'static [usize] = &[ 32, 17,  1,  0, 34,  2,   1,  37, InterpreterConstants::QUESTION as usize, InterpreterConstants::EOL as usize ];

/// Represents the sentence: "Would you have a will to do that?"
const SENTENCE_TOKENS2: &'static [usize] = &[ 36, 17,  8,  5, 32,  2,  18,   7, InterpreterConstants::QUESTION as usize, InterpreterConstants::EOL as usize ];

/// Represents the sentence: "For not you I would not be in this."
const SENTENCE_TOKENS3: &'static [usize] = &[ 11, 12, 17,  9, 36, 12,   1,   6,  20, InterpreterConstants::PERIOD as usize, InterpreterConstants::EOL as usize ];

/// Represents the sentence: "We say that but would you say it?"
const SENTENCE_TOKENS4: &'static [usize] = &[ 26, 27,  7, 21, 36, 17,  27,  10, InterpreterConstants::QUESTION as usize, InterpreterConstants::EOL as usize ];

/// Represents the sentence: "By her will we will do it."
const SENTENCE_TOKENS5: &'static [usize] = &[ 23, 28, 32, 26, 32, 18,  10, InterpreterConstants::PERIOD as usize, InterpreterConstants::EOL as usize ];

/// A list of pre-defined token lists.  Each token list represents a single
/// sentence constructed from the 40 most common words in the English language.
/// I don't use all 40 words, though; that would be silly.
const _SENTENCE_TOKEN_LISTS: &'static [&'static [usize]; 6] = &[
    &SENTENCE_TOKENS0,
    &SENTENCE_TOKENS1,
    &SENTENCE_TOKENS2,
    &SENTENCE_TOKENS3,
    &SENTENCE_TOKENS4,
    &SENTENCE_TOKENS5,
];

//-----------------------------------------------------------------------------

/// Helper function to convert a list of integers to a string representation.
///
/// # Parameters
/// - tokens
///
///   Array of integers to work with.  Assumed to be terminated with a -1 (EOL).
///
/// # Returns
/// Returns a string representation of the integer list.
fn _tokens_to_string(tokens: &[usize]) -> String {
    let mut buffer = String::new();

    buffer.push('[');
    let mut index = 0;
    while tokens[index] != (InterpreterConstants::EOL as usize) {
        buffer.push_str(&format!("{:3}", tokens[index]));

        if tokens[index + 1] != (InterpreterConstants::EOL as usize)
        {
            buffer.push_str(", ");
        }
        index += 1;
    }
    buffer.push(']');

    return buffer;
}

//-----------------------------------------------------------------------------

/// Example of using the "Interpreter" design pattern.
/// 
/// The interpreter is a function that is fed a series of arrays containing
/// integer tokens.  Each token represents a single word or punctuation mark.
/// The interpreter converts that array of tokens to an actual sentence by
/// interpreting the meaning of the tokens.
/// 
/// This is a very simple interpreter that handles the first token in a special
/// way and supports punctuation.  It is an example of a linear interpreter
/// where tokens can appear in any order (it's up to the creator of the token
/// list to make sure the outcome makes any sense).
/// 
/// The output shows the token list followed by the sentence produced
/// from the tokens.
// ! [Using Interpreter in Rust]
pub fn interpreter_exercise() -> Result<(), String> {
    println!("");
    println!("Interpreter Exercise");

    for sentence_index in 0.._SENTENCE_TOKEN_LISTS.len() {
        let token_list = _SENTENCE_TOKEN_LISTS[sentence_index];

        let tokens_as_string = _tokens_to_string(token_list);

        let sentence = interpreter_interpret(token_list);

        // 50 is a magic number corresponding to the longest token list
        // expressed as a string.  Derived empirically.  It makes the
        // output easier to, er, interpret.
        println!("  {:-50} ==> \"{}\"", tokens_as_string, sentence);
    }

    println!("  Done.");

    Ok(())
}
// ! [Using Interpreter in Rust]
