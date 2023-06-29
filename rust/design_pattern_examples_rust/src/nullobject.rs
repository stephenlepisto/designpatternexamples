//! The Null Object design pattern example module
//! 
//! The "Null Object" pattern is where an object or function acts as a stand-in
//! for real commands but otherwise does nothing.
//! 
//! In this exercise, movement commands are presented as characters in a
//! string, with the characters 'u', 'd', 'l', and 'r' representing the moves
//! "up", "down", "left", and "right", respectively.  To keep the processing of
//! this string simple, all other characters in the string are assigned a Null
//! Object ("Do Nothing") version of the move command.
//! 
//! This example displays the commands after parsing and then "executes" the
//! commands, which consists of printing the commands out.
//!
//! Accessed through the nullobject_exercise() function.

//-----------------------------------------------------------------------------

pub mod nullobject_imovecommand_trait;
pub mod nullobject_movecommands;
pub mod nullobject_moveprocessor;

//-----------------------------------------------------------------------------

use nullobject_moveprocessor::MoveProcessor;

//-----------------------------------------------------------------------------


/// Example of using the "Null Object" design pattern.
/// 
/// The "Null Object" pattern is where an object or function acts as a stand-in
/// for real commands but otherwise does nothing.
/// 
/// In this exercise, movement commands are presented as characters in a
/// string, with the characters 'u', 'd', 'l', and 'r' representing the moves
/// "up", "down", "left", and "right", respectively.  To keep the processing of
/// this string simple, all other characters in the string are assigned a Null
/// Object ("Do Nothing") version of the move command.
/// 
/// This example displays the commands after parsing and then "executes" the
/// commands, which consists of printing the commands out.
/// 
/// This example highlights the ""Null Object"" pattern while also utilizing
/// the "Command" pattern and "Interpreter" pattern.
// ! [Using NullObject in Rust]
pub fn nullobject_exercise() -> Result<(), String> {
    println!("");
    println!("NullObject Exercise");

    // A stream of recognized and unrecognized move commands.  The
    // unrecognized commands do nothing.
    let move_string = "ur#ld!lr";
    let move_processor = MoveProcessor::new();

    let move_commands = move_processor.parse(move_string);
    println!("  Showing the move commands:");
    move_processor.show_commands(&move_commands);

    println!("  Executing the move commands:");
    print!("    {0} -> ", move_string);
    move_processor.execute_commands(&move_commands);

    println!("  Done.");

    Ok(())
}
// ! [Using NullObject in Rust]
