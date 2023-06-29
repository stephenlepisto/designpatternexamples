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

/// This struct creates a context around the undo list that the
/// command_exercise() executes within.  This gets around the problem of
/// needing a static undo list (or passing the undo list to all functions) as
/// all the methods on this context have ready access to the undo list in the
/// context.
struct CommandContext {
    /// The list of command objects that describe the changes made to the text
    /// object.
    command_list: Vec<Box<dyn ICommand>>,
}


impl CommandContext {
    /// Constructor.
    fn new() -> CommandContext {
        CommandContext { command_list: vec![] }
    }


    /// Execute the given command on the given text object then save the
    /// command on the given undo list.
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
    fn execute_and_save(&mut self, command: Box<dyn ICommand>, text: &mut CommandTextObject) {
        // Execute the command first because the command will be given to the command list
        // and we won't be able to reference it after that.
        command.execute(text);
        self.command_list.push(command);
    }


    /// Helper method to create a Command object that replaces text in the
    /// given CommandTextObject, applies the command to the CommandTextObject,
    /// and then adds the command to the given undo list.  Finally, it shows
    /// off what was done.
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
    fn apply_replace_command(&mut self, text: &mut CommandTextObject, search_pattern: &str, replace_text: &str)
    {
        let command = CommandTwoParameters::new("Replace", operation_replace, &search_pattern, &replace_text);
        // Get the command as a string before it is given to command_save_and_execute()
        let command_name = command.to_string();
        self.execute_and_save(command, text);
        println!("    command {:<31}==> \"{}\"", command_name, text);
    }

    /// Helper method to create a Command object that reverses the order of the
    /// characters in the given CommandTextObject, applies the command to the
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
    fn apply_reverse_command(&mut self, text: &mut CommandTextObject) {
        let command = CommandNoParameters::new("Reverse", operation_reverse);
        // Get the command as a string before it is given to command_save_and_execute()
        let command_name = command.to_string();
        self.execute_and_save(command, text);
        println!("    command {:<31}==> \"{}\"", command_name, text);
    }

    /// Perform an undo on the given CommandTextObject, using the commands in
    /// the given undo list.  If the undo list is empty, nothing happens.
    ///
    /// # Parameters
    /// - command_list
    ///
    ///   The list that holds the commands for later undoing.
    /// - text
    ///
    ///   The CommandTextObject to affect.
    fn undo(&mut self, text: &mut CommandTextObject) {
        if !self.command_list.is_empty() {
            let last_command = self.command_list.pop().unwrap();
            text.reset();
            for command in self.command_list.iter() {
                command.execute(text);
            }
            println!("    undoing command {:<31}==> \"{}\"", last_command.to_string(), text);
        }
    }
}


//#############################################################################
//#############################################################################

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
fn operation_replace(text: &mut CommandTextObject, search_pattern: &str, replace_text: &str) {
    text.text = text.text.replace(search_pattern, replace_text);
}


/// An operation to reverse the characters in the given CommandTextObject.
///
/// # Parameters
/// - text
///
///   The CommandTextObject to affect.
fn operation_reverse(text: &mut CommandTextObject) {
    // Technically, this will work only with ASCII strings since char() does
    // not iterate over graphemes but Unicode points.
    text.text = text.text.chars().rev().collect::<String>();
}

//#############################################################################
//#############################################################################


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

    // Note: The context's undo list owns the commands.  When an undo operation
    // is done, the command is removed from the list and goes away at the end
    // of the undo function.
    let mut command_context = CommandContext::new();

    let mut text_object = CommandTextObject::new("This is a line of text on which to experiment.");

    println!("  Starting text: \"{text_object}\"");

    command_context.apply_replace_command(&mut text_object, "text", "painting");
    command_context.apply_replace_command(&mut text_object, "on", "off");
    command_context.apply_reverse_command(&mut text_object);
    command_context.apply_replace_command(&mut text_object, "i", "!");

    println!("  Now perform undo until back to original");
    command_context.undo(&mut text_object);
    command_context.undo(&mut text_object);
    command_context.undo(&mut text_object);
    command_context.undo(&mut text_object);

    println!("  Final text   : \"{text_object}\"");

    println!("  Done.");

    Ok(())
}
// ! [Using Command in Rust]
