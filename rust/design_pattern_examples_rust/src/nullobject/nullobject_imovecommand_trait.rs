//! Definition of the IMoveCommand trait that all move commands must implement
//! in the "Null Object" design pattern example.

pub trait IMoveCommand {
    /// Retrieve the command character representing the move command.
    fn get_command(&self) -> &str;

    /// Retrieve the name of the move command.
    fn get_name(&self) -> &str;

    /// "Execute" the move command.
    fn execute(&self);

    /// Display the move command and its name on a single line.
    fn show(&self) {
        println!("    '{0}' -> {1}", self.get_command(), self.get_name());
    }
}