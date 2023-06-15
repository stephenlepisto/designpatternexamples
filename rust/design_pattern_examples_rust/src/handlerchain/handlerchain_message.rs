//! Contains the Message and MessagePosition structs, along with the MessageType
//! enumeration, which are the foundation of the "Handler Chain" design pattern
//! example.

use std::fmt::Display;


pub enum MessageType {
    /// Window is asked to close itself, generally sent by the window itself
    /// in response to a button up in a Close region.  Applies only to the
    /// currently selected window.
    Close = 0,

    /// Selects a window based on position.
    ButtonDown = 1,

    /// Take an action on the currently selected window.
    ButtonUp,
}

//=============================================================================

/// Position of the message in global coordinates (same scope of coordinates as
/// windows).  Although this can handle negative coordinates, the example is
/// careful to use only positive coordinates.
pub struct MessagePosition {
    /// X position.
    pub x: i32,
    /// Y position.
    pub y: i32,
}

impl MessagePosition {
    /// Constructor
    ///
    /// # Parameters
    /// - x
    ///
    ///   X position to use.
    /// - y
    ///
    ///   Y position to use.
    ///
    /// # Returns
    /// Returns a new instance of the MessagePosition struct.
    pub fn new(x:i32, y:i32) -> MessagePosition {
        MessagePosition{ x, y }
    }
}

impl Display for MessagePosition {
    /// Convert The MessagePosition struct contents to a string.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!("x={:2},y={:2}", self.x, self.y))
    }
}

//=============================================================================

pub struct Message {
    /// Value from the MessageType enumeration indicating the type of this message.
    pub message_type: MessageType,
    /// Position of message when the message was sent.  In a real system, this
    /// would generally represent the position of a cursor at the time the message
    /// was generated.
    pub message_position: MessagePosition,
}

impl Message {
    /// Constructor.
    ///
    /// # Parameters
    /// - message_type
    ///
    ///   Value from the MessageType enumeration indicating the type of message
    ///   being created.
    /// - x
    ///
    ///   X Position of the message.
    /// - y
    ///
    ///   Y Position of the message.
    ///
    /// # Returns
    /// Returns a new instance of the Message struct.
    pub fn new(message_type: MessageType, x: i32, y: i32) -> Message {
        Message {
            message_type,
            message_position: MessagePosition::new(x, y),
        }
    }
}


impl Display for Message {
    /// Convert the Message struct contents to a string.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let type_as_string = match self.message_type {
            MessageType::Close => "Close",
            MessageType::ButtonDown => "ButtonDown",
            MessageType::ButtonUp => "ButtonUp",
        };

        f.write_fmt(format_args!("{0} at ({1})", type_as_string, self.message_position))
    }
}

