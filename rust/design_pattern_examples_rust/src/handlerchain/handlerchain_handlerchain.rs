//! Contains the HandlerChain struct that manages all windows represented by
//! the IMessageHandler trait.

use std::cell::RefCell;
use std::fmt::Display;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

use super::handlerchain_message::Message;
use super::handlerchain_imessagehandler_trait::IMessageHandler;


/// Represents a list of handlers that all implement the IMessageHandler
/// trait.  This list can be dynamically updated and each element in
/// the list is passed messages for processing.
pub struct HandlerChain {
    /// The list of message handlers.
    message_handlers: Vec<Rc<RefCell<dyn IMessageHandler>>>,
    /// Object used to lock access to the message handlers list for
    /// multi-threaded support.
    message_handlers_lock: Arc<Mutex<u32>>,
}

impl HandlerChain {
    /// Constructor.
    ///
    /// # Returns
    /// Returns a new instance of the HandlerChain struct.
    pub fn new() -> Rc<RefCell<HandlerChain>> {
        Rc::new(RefCell::new(HandlerChain {
            message_handlers: vec![],
            message_handlers_lock: Arc::new(Mutex::new(0)),
        }))
    }

    /// Add an instance of the IMessageHandler interface to end of the
    /// list of handlers, protected by a multi-threading lock.
    /// 
    /// If a message handler is already in the list, it is not added again.
    pub fn add_handler(&mut self, handler: Rc<RefCell<dyn IMessageHandler>>) {
        let _locked = self.message_handlers_lock.lock().unwrap();
        if self.message_handlers.iter().any(|x| x.borrow().id() == handler.borrow().id()) {
            // Don't add a handler that is already in the list.
        } else {
            self.message_handlers.push(handler.clone())
        }
    }

    /// Remove an instance of the IMessageHandler interface from the list,
    /// protected by a multi-threading lock.
    /// 
    /// If the message handler is not in the list, the request to remove
    /// is ignored.
    pub fn remove_handler(&mut self, handler: &dyn IMessageHandler) {
        let _locked = self.message_handlers_lock.lock().unwrap();
        let found_index = self.message_handlers.iter().position(|x| x.borrow().id() == handler.id());
        if let Some(index) = found_index {
            self.message_handlers.remove(index);
        }
    }

    /// Send a message to each of the handlers in the list, protected by
    /// a multi-threading lock.
    ///
    /// # Parameters
    /// - message
    ///
    ///   The Message object to send to each handler.
    pub fn send_message(&mut self, message: &Message) {
        // We make a copy of the handlers so our processing of handlers
        // is not impacted by updates to the master handler list.
        let mut handlers: Vec<Rc<RefCell<dyn IMessageHandler>>> = vec![];
        {
            let _locked = self.message_handlers_lock.lock().unwrap();
            handlers.clone_from(&self.message_handlers);
        }

        for handler in handlers.iter_mut() {
            if handler.borrow_mut().process_message(&message) {
                break;
            }
        }
    }
}

impl Display for HandlerChain {
    /// Convert this HandlerChain to a string, protected by a multi-threading
    /// lock.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        // We make a copy of the handlers so our processing of handlers
        // is not impacted by updates to the master handler list.
        let mut handlers: Vec<Rc<RefCell<dyn IMessageHandler>>> = vec![];
        {
            let _locked = self.message_handlers_lock.lock().unwrap();
            handlers.clone_from(&self.message_handlers);
        }
        let mut output = String::new();
        for handler in handlers {
            output.push_str(&format!("    {}\n", handler.borrow().to_string()))
        }

        f.write_fmt(format_args!("{}", output))
    }
}
