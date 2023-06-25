//! Contains the IMessageHandler trait.

use super::handlerchain_message::Message;
use super::handlerchain_handlerchain::MessageReturnTypes;

//-----------------------------------------------------------------------------

/// Represents a handler in a chain of handlers.  All objects that
/// participate in the HandlerChain class must implement this trait.
pub trait IMessageHandler {
    /// ID of the window.  This is used to uniquely identify a window in the
    /// collection.
    fn id(&self) -> i32;

    /// Called with a message for the window.
    ///
    /// # Parameters
    /// - message
    ///
    ///   Message object representing the message to process.
    ///
    /// # Returns
    /// Returns a value from the MessageReturnTypes enumeration indicating what
    /// action the caller should take: (Stop) This message was handled and
    /// processing should stop, (Continue) this message can be passed on to
    /// other handlers, or (Close) this handler is closed so remove from the
    /// handlers list and stop further processing.
    fn process_message(&mut self, message: &Message) -> MessageReturnTypes;

    /// Return a string representation of the message handler.
    fn to_string(&self) -> String;
}
