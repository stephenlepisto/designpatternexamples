//! Contains the CommandNoParameters and CommandTwoParameters implementations.

use super::command_icommand_trait::ICommand;
use super::CommandTextObject;

//-----------------------------------------------------------------------------

/// Alias for a function that takes no parameters other than a CommandTextObject.
type NoParameterOperation = fn(source: &mut CommandTextObject);

/// Alias for a function that takes two string parameters along with a
/// CommandTextObject.
type TwoParametersOperation = fn(source: &mut CommandTextObject, arg1:&str, arg2:&str);

//-----------------------------------------------------------------------------

/// Represents an operation that can be applied to a CommandTextObject with
/// no additional parameters.
///
/// This struct implements the ICommand trait so it can be treated the same as
/// any other kind of command.
pub struct CommandNoParameters {
    /// Easy-to-read command name.
    name: String,
    /// No parameter operation to apply to a CommandTextObject.
    operation: NoParameterOperation,
}

impl CommandNoParameters {
    /// Constructor for a command that applies an operation to a
    /// CommandTextObject but does not require any additional parameters.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Easy-to-read name of the command.
    /// - operation
    ///
    ///   The operation to apply to a CommandTextObject and that takes no
    ///   parameters.
    ///
    /// # Returns
    /// Returns an ICommand object representing the command.
    pub fn new(name: &str, operation: NoParameterOperation) -> Box<dyn ICommand> {
        Box::new(CommandNoParameters{
            name: name.to_string(),
            operation: operation,
        })
    }
}

impl ICommand for CommandNoParameters {
    fn execute(&self, receiver: &mut CommandTextObject) {
        (self.operation)(receiver);
    }
    fn to_string(&self) -> String {
        self.name.clone()
    }
}

//=============================================================================
//=============================================================================


/// Represents an operation that can be applied to a CommandTextObject that
/// requires two additional parameters.
///
/// This struct implements the ICommand trait so it can be treated the same as
/// any other kind of command.
pub struct CommandTwoParameters {
    /// Easy-to-read command name.
    name: String,
    /// Two parameter operation to apply to a CommandTextObject.
    operation: TwoParametersOperation,
    /// The first argument to the operation.
    arg1: String,
    /// The second argument to the operation.
    arg2: String,
}

impl CommandTwoParameters {
    /// Constructor for a command that applies an operation to a
    /// CommandTextObject, where the operation takes two parameters.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Easy-to-read name of the command.
    /// - operation
    ///
    ///   The operation to apply to a CommandTextObject and that takes two
    ///   parameters.
    /// - arg1
    ///
    ///   First argument to the operation (after the CommandTextObject).
    /// - arg2
    ///
    ///   Second argument to the operation (after the CommandTextObject).
    /// # Returns
    /// Returns an ICommand object representing the command.
    pub fn new(name: &str, operation: TwoParametersOperation, arg1: &str, arg2: &str) -> Box<dyn ICommand> {
        Box::new(CommandTwoParameters{
            name: name.to_string(),
            operation: operation,
            arg1: arg1.to_string(),
            arg2: arg2.to_string(),
        })
    }
}

impl ICommand for CommandTwoParameters {
    fn execute(&self, receiver: &mut CommandTextObject) {
        (self.operation)(receiver, &self.arg1, &self.arg2);
    }

    fn to_string(&self) -> String {
        format!("{0} \"{1}\" with \"{2}\"", self.name, self.arg1, self.arg2)
    }
}
