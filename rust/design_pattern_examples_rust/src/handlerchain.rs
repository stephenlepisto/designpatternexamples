//! The HandlerChain design pattern example module
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
//! Accessed through the handlerchain_exercise() function.

//-----------------------------------------------------------------------------

pub mod handlerchain_handlerchain;
pub mod handlerchain_imessagehandler_trait;
pub mod handlerchain_message;
pub mod handlerchain_messagewindow;

//-----------------------------------------------------------------------------

use handlerchain_handlerchain::HandlerChain;
use handlerchain_messagewindow::MessageWindow;
use handlerchain_message::{Message, MessageType};

//-----------------------------------------------------------------------------

/// Helper method to construct a list of windows.  Messages will be passed 
/// to these windows via the HandlerChain object.
///
/// The HandlerChain object takes ownership of the windows due to a limitation
/// in Rust.  I would have preferred a separate list own the MessageWindow
/// instances and the HandlerChain would be given a mutable reference to the
/// IMessageHandler trait on each MessageWindow.  But that requires taking a
/// mutable borrow through the list of windows, one for each window, and Rust
/// does not allow multiple mutable borrows (even though technically the
/// mutable borrow should be on the MessageWindow instance, Rust sees the
/// borrow on the list of windows.  If I take the mutable borrow on the
/// MessageWindow instance before adding it to the list of windows and then add
/// the MessageWindow instance to the list of windows, Rust will not allow the
/// window instance to be added (it's an immutable borrow on a reference that
/// is mutable).
///
/// # Parameters
/// - handler_chain
///
///   A reference to a HandlerChain instance that the messages will be passed
///   to.  This HandlerChain instance also takes ownership of the MessageWindow
///   instances.
fn _handlerchain_construct_window_chain(handler_chain: &mut HandlerChain) {
    let mut window = MessageWindow::new("Window 1", 0, 0, 10, 10);
    handler_chain.add_handler(window);
    window = MessageWindow::new("Window 2", 20, 0, 5, 5);
    handler_chain.add_handler(window);
    window = MessageWindow::new("Window 3", 30, 10, 15, 15);
    handler_chain.add_handler(window);
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

    let mut handler_chain = HandlerChain::new();
    _handlerchain_construct_window_chain(&mut handler_chain);

    println!("  Handler Chain at start:");
    println!("{}", handler_chain.to_string());

    // Now pass messages to the windows.

    println!("  Select Window 2");
    handler_chain.send_message(&Message::new(MessageType::ButtonDown, 22, 1));
    handler_chain.send_message(&Message::new(MessageType::ButtonUp, 22, 1));
    println!("  Current handler chain:");
    println!("{}", handler_chain.to_string());

    println!("  Select Window 3");
    handler_chain.send_message(&Message::new(MessageType::ButtonDown, 35, 11));
    handler_chain.send_message(&Message::new(MessageType::ButtonUp, 35, 11));
    println!("  Current handler chain:");
    println!("{}", handler_chain.to_string());

    println!("  Select Window 1");
    handler_chain.send_message(&Message::new(MessageType::ButtonDown, 4, 4));
    handler_chain.send_message(&Message::new(MessageType::ButtonUp, 4, 4));
    println!("  Current handler chain:");
    println!("{}", handler_chain.to_string());

    println!("  Close Window 2");
    handler_chain.send_message(&Message::new(MessageType::ButtonDown, 24, 0));
    handler_chain.send_message(&Message::new(MessageType::ButtonUp, 24, 0));
    println!("  Current handler chain:");
    println!("{}", handler_chain.to_string());

    println!("  Done.");

    Ok(())
}
// ! [Using HandlerChain in Rust]
