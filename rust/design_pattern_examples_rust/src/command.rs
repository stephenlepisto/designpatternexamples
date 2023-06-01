//! The Command design pattern example module
//!
//! The Command pattern is used to encapsulate an operation or command
//! associated with an object so that the command can be applied to
//! the object at a later time.
//! 
//! In this exercise, an undo list is implemented using Commands that
//! associate commands defined in this file with a text object.  The
//! commands are applied to the text object in succession then
//! effectively undone.
//!
//! Accessed through the command_exercise() function.

pub mod command_icommand_trait;
pub mod command_commands;
pub mod command_textobject;

use command_textobject::CommandTextObject;
use command_icommand_trait::ICommand;
use command_commands::{CommandNoParameters, CommandTwoParameters};

//-----------------------------------------------------------------------------

/// Alias for a vector of ICommand objects.
type CommandList = Vec<Box<dyn ICommand>>;

//-----------------------------------------------------------------------------

/// An operation to search and replace text in a CommandTextObject.
///
/// # Parameters
/// - text
///
///   The CommandTextObject to affect.
/// - search_pattern
///
///   What to look for in the CommandTextObject.
/// - replace_text
///
///   What to replace `search_pattern` with.
fn command_operation_replace(text: &mut CommandTextObject, search_pattern: &str, replace_text: &str) {
    text.text = text.text.replace(search_pattern, replace_text);
}


/// An operation to reverse the characters in the given CommandTextObject.
///
/// # Parameters
/// - text
///
///   The CommandTextObject to affect.
fn command_operation_reverse(text: &mut CommandTextObject) {
    // Technically, this will work only with ASCII strings since char() does
    // not iterate over graphemes but Unicode points.
    text.text = text.text.chars().rev().collect::<String>();
}


/// Execute the given command on the given text object then save the command on
/// the given undo list.
///
/// # Parameters
/// - command_list
///
///   The list that holds the commands for later undoing.
/// - command
///
///   The command to apply to the text.
/// - text
///
///   The CommandTextObject to affect.
fn command_execute_and_save(command_list: &mut CommandList, command: Box<dyn ICommand>, text: &mut CommandTextObject) {
    // Execute the command first because the command will be given to the command list
    // and we won't be able to reference it after that.
    command.execute(text);
    command_list.push(command);
}


/// Helper function to create a Command object that replaces text in the given
/// CommandTextObject, applies the command to the CommandTextObject, and then
/// adds the command to the given undo list.  Finally, it shows off what was
/// done.
///
/// # Parameters
/// - command_list
///
///   The list that holds the commands for later undoing.
/// - text
///
///   The CommandTextObject to affect.
/// - search_pattern
///
///   What to look for in the CommandTextObject.
/// - replace_text
///
///   What to replace `search_pattern` with.
fn command_apply_replace_command(command_list: &mut CommandList, text: &mut CommandTextObject, search_pattern: &str, replace_text: &str)
{
    let command = CommandTwoParameters::new("Replace", command_operation_replace, &search_pattern, &replace_text);
    // Get the command as a string before it is given to command_save_and_execute()
    let command_name = command.to_string();
    command_execute_and_save(command_list, command, text);
    println!("    command {:<31}==> \"{}\"", command_name, text.to_string());
}

/// Helper function to create a Command object that reverses the order of
/// the characters in the given CommandTextObject, applies the command to the
/// CommandTextObject, and then adds the command to the given undo list.
/// Finally, it shows what was done.
///
/// # Parameters
/// - command_list
///
///   The list that holds the commands for later undoing.
/// - text
///
///   The CommandTextObject to affect.
fn command_apply_reverse_command(command_list: &mut CommandList, text: &mut CommandTextObject) {
    let command = CommandNoParameters::new("Reverse", command_operation_reverse);
    // Get the command as a string before it is given to command_save_and_execute()
    let command_name = command.to_string();
    command_execute_and_save(command_list, command, text);
    println!("    command {:<31}==> \"{}\"", command_name, text.to_string());
}

/// Perform an undo on the given CommandTextObject, using the commands in the
/// given undo list.  If the undo list is empty, nothing happens.
///
/// # Parameters
/// - command_list
///
///   The list that holds the commands for later undoing.
/// - text
///
///   The CommandTextObject to affect.
fn command_undo(command_list: &mut CommandList, text: &mut CommandTextObject) {
    if !command_list.is_empty() {
        let last_command = command_list.pop().unwrap();
        text.reset();
        for command in command_list {
            command.execute(text);
        }
        println!("    undoing command {:<31}==> \"{}\"", last_command.to_string(), text.to_string());
    }
}

/// Example of using the "Command" pattern.
/// 
/// The Command pattern is used to encapsulate an operation or command
/// associated with an object so that the command can be applied to
/// the object at a later time.
/// 
/// In this exercise, an undo list is implemented using Commands that
/// associate commands defined in this file with a text object.  The
/// commands are applied to the text object in succession then
/// effectively undone.

// ! [Using Command in Rust]
pub fn command_exercise() -> Result<(), String> {
    println!("");
    println!("Command Exercise");

    // Note: This list owns the commands.  When an undo operation is done, the
    // command is removed from the list and goes away at the end of the undo
    // function.
    let mut command_undo_list = CommandList::new();

    let mut text_object = CommandTextObject::new("This is a line of text on which to experiment.");

    println!("  Starting text: \"{text_object}\"");

    command_apply_replace_command(&mut command_undo_list, &mut text_object, "text", "painting");
    command_apply_replace_command(&mut command_undo_list, &mut text_object, "on", "off");
    command_apply_reverse_command(&mut command_undo_list, &mut text_object);
    command_apply_replace_command(&mut command_undo_list, &mut text_object, "i", "!");

    println!("  Now perform undo until back to original");
    command_undo(&mut command_undo_list, &mut text_object);
    command_undo(&mut command_undo_list, &mut text_object);
    command_undo(&mut command_undo_list, &mut text_object);
    command_undo(&mut command_undo_list, &mut text_object);

    println!("  Final text   : \"{text_object}\"");

    println!("  Done.");

    Ok(())
}
// ! [Using Command in Rust]
