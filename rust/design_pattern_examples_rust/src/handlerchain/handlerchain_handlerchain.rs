//! Contains the HandlerChain struct that manages all windows represented by
//! the IMessageHandler trait.

use std::cell::RefCell;
use std::fmt::Display;

use super::handlerchain_message::Message;
use super::handlerchain_imessagehandler_trait::IMessageHandler;

//-----------------------------------------------------------------------------

/// Represents the type of actions the process_message() method returns for the
/// HandlerChain::send_message() to act on.
pub enum MessageReturnTypes {
    /// Message was processed, stop further processing of the message.
    Stop,
    /// Continue with processing of the message.
    Continue,
    /// Window is closed, remove from handlers list and stop further processing
    /// of the message.
    Close,
}

//-----------------------------------------------------------------------------

/// Represents a list of handlers that all implement the IMessageHandler
/// trait.  This list can be dynamically updated and each element in
/// the list is passed messages for processing.
pub struct HandlerChain {
    /// The list of message handlers.
    message_handlers: Vec<Box<RefCell<dyn IMessageHandler>>>,
}

impl HandlerChain {
    /// Constructor.
    ///
    /// # Returns
    /// Returns a new instance of the HandlerChain struct.
    pub fn new() -> HandlerChain {
        HandlerChain {
            message_handlers: vec![],
        }
    }

    /// Add the given instance of the IMessageHandler interface to end of the
    /// list of handlers.
    /// 
    /// Normally this would guard against adding the same window twice, but this
    /// HandlerChain takes ownership of the window and therefore the same
    /// window can never be added twice to this HandlerChain.
    pub fn add_handler(&mut self, handler: impl IMessageHandler+'static) {
        self.message_handlers.push(Box::new(RefCell::new(handler)))
    }

    /// Remove an instance of the IMessageHandler interface from the list.
    /// 
    /// If the message handler is not in the list, the request to remove
    /// is ignored.
    pub fn remove_handler(&mut self, handler_id: i32) {
        let found_index = self.message_handlers.iter_mut().position(|x| x.borrow().id() == handler_id);
        if let Some(index) = found_index {
            self.message_handlers.remove(index);
        }
    }

    /// Send a message to each of the handlers in the list.
    ///
    /// # Parameters
    /// - message
    ///
    ///   The Message object to send to each handler.
    pub fn send_message(&mut self, message: &Message) {
        for handler in self.message_handlers.iter() {
            let result = handler.borrow_mut().process_message(&message);
            match result {
                MessageReturnTypes::Stop => break,
                MessageReturnTypes::Continue => continue,
                MessageReturnTypes::Close => { 
                    let handler_id = handler.borrow().id();
                    self.remove_handler(handler_id);
                    break;
                }
            }
        }
    }
}

impl Display for HandlerChain {
    /// Convert this HandlerChain to a string that is returned.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        // We make a copy of the handlers so our processing of handlers
        // is not impacted by updates to the master handler list.
        let mut output = String::new();
        for handler in self.message_handlers.iter() {
            output.push_str(&format!("    {}\n", handler.borrow().to_string()))
        }

        f.write_fmt(format_args!("{}", output))
    }
}
