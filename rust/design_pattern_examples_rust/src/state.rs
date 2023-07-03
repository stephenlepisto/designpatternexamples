//! The State design pattern example module
//! 
//! The State pattern alters the behavior of an object hierarchy based on some
//! state.  This is the basis of a Finite State Machine.
//! 
//! In this exercise, the State struct is a filter that parses text to remove
//! Rust-style line and block comments.  It needs to be smart enough to ignore
//! comment characters inside quotes.
//! 
//! The filtering process starts with creating the context that drives
//! the state machine.  Internal structs are provided for each state.
//!
//! Accessed through the state_exercise() function.

//-----------------------------------------------------------------------------

pub mod state_context;
pub mod state_istatebehavior_trait;
pub mod state_istatecontext_trait;

//-----------------------------------------------------------------------------

use state_context::StateContext;

//-----------------------------------------------------------------------------

/// Helper function to display text from the State exercise.  Text is displayed
/// with line numbers.
///
/// # Parameters
/// - text
///
///   Text to display
fn state_display_text(text: &str) {
    let local_text = text.to_string();
    let lines = local_text.split("\n");
    let mut line_number = 1;
    for line in lines {
        println!("    {0:2}) {1}", line_number, line);
        line_number += 1;
    }
}


/// Example of using the "State" design pattern.
/// 
/// The State pattern alters the behavior of an object hierarchy based on some
/// state.  This is the basis of a Finite State Machine.
/// 
/// In this exercise, the State struct is a filter that parses text to remove
/// Rust-style line and block comments.  It needs to be smart enough to ignore
/// comment characters inside quotes.
/// 
/// The filtering process starts with creating the context that drives
/// the state machine.  Internal structs are provided for each state.
// ! [Using State in Rust]
pub fn state_exercise() -> Result<(), String> {
    println!("");
    println!("State Exercise");

    let mut context = StateContext::new();

    let text_to_filter =
r#"/*####################  Block Comment  #################################*/
//####################  Line Comment  ####################################
// A comment.  /* A nested comment */

fn state_exercise() { // An exercise in state machines
    let character = '\"';
    println!("");
    println!("\"State\" /*Exercise*/");

    let mut context = StateContext::new();

    println!("\t\tDone. //(No, really)//");
}"#;

    println!("  Text to filter:");
    state_display_text(text_to_filter);

    println!("  Filtering text...");
    let filtered_text = context.remove_comments(text_to_filter);

    println!("  Filtered text:");
    state_display_text(&filtered_text);

    println!("  Done.");

    Ok(())
}
// ! [Using State in Rust]
