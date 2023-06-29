//! Contains the MoveProcessor struct that parses a string of move commands
//! to create move command objects and then displays or executes those command
//! objects as requested.

//-----------------------------------------------------------------------------

use super::nullobject_imovecommand_trait::IMoveCommand;
use super::nullobject_movecommands::{MoveLeft, MoveRight, MoveUp, MoveDown, MoveNone};

//-----------------------------------------------------------------------------

/// Represents the processor that translates the move list into a list of
/// IMoveCommand objects then either displays them or executes them.
/// 
/// This struct uses a parser to convert the single letter characters in
/// a string into a list of actions (instances of the MoveCommandXXX structs).
/// This list of actions is then display or executed to perform the operations.
/// 
/// The process of executing the list of operations is an example of the
/// "Command" pattern.  The parsing step is also an example of the
/// "Interpreter" pattern, where the actions are the tokens to be interpreted.
pub struct MoveProcessor { }

impl MoveProcessor {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the MoveProcessor struct.
    pub fn new() -> MoveProcessor {
        MoveProcessor {}
    }

    /// Parse the given list of move commands, where each command is
    /// represented by a single character, to produce a list of move command
    /// objects.
    /// 
    /// Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
    /// characters are assigned a "Do Nothing" (Null Object) command.
    ///
    /// # Parameters
    /// - moves
    ///
    ///   A string containing the move commands to parse.
    ///
    /// # Returns
    /// Returns a list of the move commands, with each command represented by
    /// the IMoveCommand trait.
    pub fn parse(&self, moves: &str) -> Vec<Box<dyn IMoveCommand>> {
        let mut commands = vec![];
        for c in moves.to_uppercase().chars() {
            let command = match c {
                'L' => MoveLeft::new(&c.to_string()),
                'R' => MoveRight::new(&c.to_string()),
                'U' => MoveUp::new(&c.to_string()),
                'D' => MoveDown::new(&c.to_string()),
                _ => MoveNone::new(&c.to_string()),
            };
            commands.push(command);
        }
        commands
    }

    /// Display the given list of move commands.
    ///
    /// # Parameters
    /// - commands
    ///
    ///   A list of IMoveCommand objects, each representing one move command.
    pub fn show_commands(&self, commands: &Vec<Box<dyn IMoveCommand>>) {
        for command in commands.iter() {
            command.show();
        }
    }

    /// Execute the given list of move commands.  Execution amounts to a series
    /// of command names printed to standard out.
    ///
    /// # Parameters
    /// - commands
    ///
    ///   A list of IMoveCommand objects, each representing one move command.
    pub fn execute_commands(&self, commands: &Vec<Box<dyn IMoveCommand>>) {
        for command in commands.iter() {
            print!("<");
            command.execute();
            print!("> ");
        }
        println!();
    }
}

