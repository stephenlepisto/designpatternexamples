//! Contains the interpreter function along with the InterpreterConstants
//! enumeration, as used in the Interpreter design example.

//-----------------------------------------------------------------------------

use crate::helpers::titlecase;

//-----------------------------------------------------------------------------

/// Represents constants for special characters to be used as interpreted
/// tokens.
pub enum InterpreterConstants {
    ///< Period
    PERIOD = 100,
    ///< Question mark
    QUESTION = 101,
    ///< Marker for end of a token list.
    EOL = -1
}

//-----------------------------------------------------------------------------

/// The 40 most common words in English (in order but that doesn't really
/// matter here).  A token is nothing more than an index into this list.
static _COMMONWORDS: [&str; 40] = 
[
    "the",
    "be",
    "to",
    "of",
    "and",
    "a",
    "in",
    "that",
    "have",
    "I",
    "it",
    "for",
    "not",
    "on",
    "with",
    "he",
    "as",
    "you",
    "do",
    "at",
    "this",
    "but",
    "his",
    "by",
    "from",
    "they",
    "we",
    "say",
    "her",
    "she",
    "or",
    "an",
    "will",
    "my",
    "one",
    "all",
    "would",
    "there",
    "their",
    "what",
];

/// Helper function to convert the token into its corresponding word or
/// punctuation mark.
///
/// # Parameters
/// - token
///
///   The token to interpret.
///
/// # Returns
/// Returns a string containing the corresponding word or punctuation.  If
/// the token is not recognized, the string returns "<UNKNOWN TOKEN #>",
/// where # is the token value.
fn _interpret_token(token: usize) -> String {
    // Rule 1: token is between 0 and the number of common words.
    if token < _COMMONWORDS.len()
    {
        _COMMONWORDS[token].to_string()
    }
    else
    {
        // Rule 1: token can also be a PERIOD
        if token == (InterpreterConstants::PERIOD as usize) {
            String::from(".")
        }
        // Rule 1: or the token can also be a QUESTION
        else if token == (InterpreterConstants::QUESTION as usize)
        {
            String::from("?")
        }
        else
        {
            // Rule 1: Invalid tokens returned as unknown.
            format!("<UNKNOWN TOKEN {token}>")
        }
    }
}


/// This function is a simple interpreter.
/// 
/// The interpreter takes an array of integer tokens and converts each
/// token into a word or punctuation mark.  The interpreter then arranges
/// the words into a space-separated list in a single string.  In other
/// words, the tokens are converted into a sentence, with the first word
/// capitalized and no space between the last two "words" under the
/// assumption the last word is actually a punctuation mark.
/// 
/// Interpreter Rules:
/// 1. Each token must be in the range of 0 through 39 (maximum number of
///    words known by the interpreter) or must be 100 ('.') or 101 ('?').
/// 2. The word corresponding to the first token is always capitalized.
/// 3. A single space appears between each word.
/// 4. No space appears between the last two tokens.
///
/// # Parameters
/// - tokenList
///
///   List of integer tokens to be interpreted.  The list is assumed to be
///   terminated by -1 (EOL).
///
/// # Returns
/// Returns a new String containing the result of the interpretation.
pub fn interpreter_interpret(token_list: &[usize]) -> String {
    let mut output = String::new();
    let mut token_index = 0;
    while token_list[token_index] != (InterpreterConstants::EOL as usize) {
        let mut token_as_string = _interpret_token(token_list[token_index]);
        if token_index == 0 {
            // Rule 2: First word in sentence gets capitalized according to local rules.
            token_as_string = titlecase::titlecase(&token_as_string);
        }
        output.push_str(&token_as_string);

        // Rule 4: No space between last two tokens (if the following expression is false)
        if token_index + 2 < token_list.len() && token_list[token_index + 2] != (InterpreterConstants::EOL as usize) {
            // Rule 3: Separate all words by a single space.
            output.push(' ');
        }

        token_index += 1;
    }
    output
}

