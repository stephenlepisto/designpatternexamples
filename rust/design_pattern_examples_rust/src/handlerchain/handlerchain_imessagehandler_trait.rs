//! Contains the IMessageHandler trait.

use super::handlerchain_message::Message;

//-----------------------------------------------------------------------------

/// Represents a handler in a chain of handlers.  All objects that
/// participate in the HandlerChain class must implement this trait.
pub trait IMessageHandler {
    /// ID of the window.  This is used to uniquely identify a window in the
    /// collection.
    fn id(&self) -> i32;

    /// Called with a message on each window.
    ///
    /// # Parameters
    /// - message
    ///
    ///   Message object representing the message to process.
    ///
    /// # Returns
    /// Returns true if the message was processed and the message should not be
    /// passed to subsequent windows.  Returns false to indicate the message
    /// should be passed to subsequent windows.
    fn process_message(&mut self, message: &Message) -> bool;

    /// Return a string representation of the message handler.
    fn to_string(&self) -> String;
}
