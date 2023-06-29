//! Contains the MoveLeft, MoveRight, MoveUp, MoveDown, and MoveNone command
//! structs that represent the specific movement commands.

use super::nullobject_imovecommand_trait::IMoveCommand;

//-----------------------------------------------------------------------------

/// Represents the Move Left command.
pub struct MoveLeft {
    /// The command character representing this move command.
    command: String,
    /// The name of this move command.
    name: String,
}

impl MoveLeft {
    /// Constructor.
    ///
    /// # Parameters
    /// - command
    ///
    ///   The command character representing this move command.
    ///
    /// # Returns
    /// Returns a new instance of the MoveLeft command represented by the
    /// IMoveCommand trait.
    pub fn new(command: &str) -> Box<dyn IMoveCommand> {
        Box::new(MoveLeft {
            command: command.to_string(),
            name: String::from("Left"),
        })
    }
}

impl IMoveCommand for MoveLeft {
    fn get_command(&self) -> &str {
        &self.command
    }

    fn get_name(&self) -> &str {
        &self.name
    }

    /// Executes the move left command.
    fn execute(&self) {
        print!("move left");
    }
}

//#############################################################################
//#############################################################################

/// Represents the Move Right command.
pub struct MoveRight {
    /// The command character representing this move command.
    command: String,
    /// The name of this move command.
    name: String,
}

impl MoveRight {
    /// Constructor.
    ///
    /// # Parameters
    /// - command
    ///
    ///   The command character representing this move command.
    ///
    /// # Returns
    /// Returns a new instance of the MoveRight command represented by the
    /// IMoveCommand trait.
    pub fn new(command: &str) -> Box<dyn IMoveCommand> {
        Box::new(MoveRight {
            command: command.to_string(),
            name: String::from("Right"),
        })
    }
}

impl IMoveCommand for MoveRight {
    fn get_command(&self) -> &str {
        &self.command
    }

    fn get_name(&self) -> &str {
        &self.name
    }

    /// Executes the move right command.
    fn execute(&self) {
        print!("move right");
    }
}

//#############################################################################
//#############################################################################

/// Represents the Move Up command.
pub struct MoveUp {
    /// The command character representing this move command.
    command: String,
    /// The name of this move command.
    name: String,
}

impl MoveUp {
    /// Constructor.
    ///
    /// # Parameters
    /// - command
    ///
    ///   The command character representing this move command.
    ///
    /// # Returns
    /// Returns a new instance of the MoveUp command represented by the
    /// IMoveCommand trait.
    pub fn new(command: &str) -> Box<dyn IMoveCommand> {
        Box::new(MoveUp {
            command: command.to_string(),
            name: String::from("Up"),
        })
    }
}

impl IMoveCommand for MoveUp {
    fn get_command(&self) -> &str {
        &self.command
    }

    fn get_name(&self) -> &str {
        &self.name
    }

    /// Executes the move up command.
    fn execute(&self) {
        print!("move up");
    }
}

//#############################################################################
//#############################################################################

/// Represents the Move Down command.
pub struct MoveDown {
    /// The command character representing this move command.
    command: String,
    /// The name of this move command.
    name: String,
}

impl MoveDown {
    /// Constructor.
    ///
    /// # Parameters
    /// - command
    ///
    ///   The command character representing this move command.
    ///
    /// # Returns
    /// Returns a new instance of the MoveDown command represented by the
    /// IMoveCommand trait.
    pub fn new(command: &str) -> Box<dyn IMoveCommand> {
        Box::new(MoveDown {
            command: command.to_string(),
            name: String::from("Down"),
        })
    }
}

impl IMoveCommand for MoveDown {
    fn get_command(&self) -> &str {
        &self.command
    }

    fn get_name(&self) -> &str {
        &self.name
    }

    /// Executes the move down command.
    fn execute(&self) {
        print!("move down");
    }
}

//#############################################################################
//#############################################################################

/// Represents the Do Nothing command.  This is the Null Object for this
/// exercise.
pub struct MoveNone {
    /// The command character representing this move command.
    command: String,
    /// The name of this move command.
    name: String,
}

impl MoveNone {
    /// Constructor.
    ///
    /// # Parameters
    /// - command
    ///
    ///   The command character representing this move command.
    ///
    /// # Returns
    /// Returns a new instance of the MoveNone command represented by the
    /// IMoveCommand trait.
    pub fn new(command: &str) -> Box<dyn IMoveCommand> {
        Box::new(MoveNone {
            command: command.to_string(),
            name: String::from("None"),
        })
    }
}

impl IMoveCommand for MoveNone {
    fn get_command(&self) -> &str {
        &self.command
    }

    fn get_name(&self) -> &str {
        &self.name
    }

    /// Executes the move none command.  In this case, the method does nothing.
    fn execute(&self) {
        // do nothing
    }
}

