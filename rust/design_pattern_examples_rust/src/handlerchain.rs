//! The Flyweight design pattern example module
//!
//! Example of using the "Handle Chain" or "Chain of Responsibility" design
//! pattern.
//! 
//! The Handler Chain pattern is used to support a dynamic list of
//! handlers that are passed the same arguments.  It is kind of the
//! inverse of the Visitor pattern, where the Visitor pattern is a
//! handler that is passed to all objects in a list, while the Handler
//! Chain pattern is an object passed to handlers in a list.
//!
//! In this exercise, multiple rectangular regions called
//! MessageWindows embody the handlers and the HandlerChain object
//! passes message objects to each MessageWindow until the message is
//! handled.
//!
//! Accessed through the flyweight_exercise() function.

//-----------------------------------------------------------------------------

pub mod handlerchain_handlerchain;
pub mod handlerchain_imessagehandler_trait;
pub mod handlerchain_message;
pub mod handlerchain_messagewindow;

//-----------------------------------------------------------------------------

use std::{rc::Rc, cell::RefCell};

use handlerchain_handlerchain::HandlerChain;
use handlerchain_messagewindow::MessageWindow;
use handlerchain_message::{Message, MessageType};
use handlerchain_imessagehandler_trait::IMessageHandler;

//-----------------------------------------------------------------------------

/// Helper method to construct a list of windows.  Messages will be passed 
/// to these windows via the HandlerChain object.
///
/// # Parameters
/// - handler_chain
///
///   A reference to a HandlerChain instance that the messages will be passed
///   to.
//
/// # Returns
/// Returns a vector of the windows created.  This vector owns the windows.
fn _handlerchain_construct_window_chain(handler_chain: &Rc<RefCell<HandlerChain>>) -> Vec<Rc<RefCell<dyn IMessageHandler>>> {
    let mut windows: Vec<Rc<RefCell<dyn IMessageHandler>>> = vec![];
    // Note: This creates each window and adds the new window to the given
    // HandlerChain object.
    
    let mut window = MessageWindow::new("Window 1", 0, 0, 10, 10, handler_chain.clone());
    handler_chain.borrow_mut().add_handler(window.clone());
    windows.push(window);
    window = MessageWindow::new("Window 2", 20, 0, 5, 5, handler_chain.clone());
    handler_chain.borrow_mut().add_handler(window.clone());
    windows.push(window);
    window = MessageWindow::new("Window 3", 30, 10, 15, 15, handler_chain.clone());
    handler_chain.borrow_mut().add_handler(window.clone());
    windows.push(window);

    windows
}

/// Example of using the "Handle Chain" or "Chain of Responsibility" design
/// pattern.
/// 
/// The Handler Chain pattern is used to support a dynamic list of
/// handlers that are passed the same arguments.  It is kind of the
/// inverse of the Visitor pattern, where the Visitor pattern is a
/// handler that is passed to all objects in a list, while the Handler
/// Chain pattern is an object passed to handlers in a list.
///
/// In this exercise, multiple rectangular regions called
/// MessageWindows embody the handlers and the HandlerChain object
/// passes message objects to each MessageWindow until the message is
/// handled.
// ! [Using HandlerChain in Rust]
pub fn handlerchain_exercise() -> Result<(), String> {
    println!("");
    println!("HandlerChain Exercise");

    let handler_chain = HandlerChain::new();
    let _windows = _handlerchain_construct_window_chain(&handler_chain);
    println!("  Handler Chain at start:");
    println!("{}", handler_chain.borrow().to_string());

    // Now pass messages to the windows.

    println!("  Select Window 2");
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonDown, 22, 1));
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonUp, 22, 1));
    println!("  Current handler chain:");
    println!("{}", handler_chain.borrow().to_string());

    println!("  Select Window 3");
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonDown, 35, 11));
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonUp, 35, 11));
    println!("  Current handler chain:");
    println!("{}", handler_chain.borrow().to_string());

    println!("  Select Window 1");
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonDown, 4, 4));
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonUp, 4, 4));
    println!("  Current handler chain:");
    println!("{}", handler_chain.borrow().to_string());

    println!("  Close Window 2");
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonDown, 24, 0));
    handler_chain.borrow_mut().send_message(&Message::new(MessageType::ButtonUp, 24, 0));
    println!("  Current handler chain:");
    println!("{}", handler_chain.borrow().to_string());

    println!("  Done.");

    Ok(())
}
// ! [Using HandlerChain in Rust]
