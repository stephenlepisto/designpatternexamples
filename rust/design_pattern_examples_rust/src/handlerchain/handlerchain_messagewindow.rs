//! Contains the WindowRectangle struct and the MessageWindow struct.

use std::cmp::max;
use std::fmt::Display;
use std::sync::atomic::{AtomicI32, Ordering};

use super::handlerchain_message::{MessagePosition, MessageType, Message};
use super::handlerchain_imessagehandler_trait::IMessageHandler;
use super::handlerchain_handlerchain::MessageReturnTypes;

//-----------------------------------------------------------------------------

/// Minimum width of a window (to accommodate a close box).
const MINIMUM_WIDTH: i32 = 4;

/// Minimum height of a window (to accommodate a close box).
const MINIMUM_HEIGHT: i32 = 4;

/// Width of the QUIT region in the upper right corner of the region.
const CLOSE_WIDTH: i32 = 2;
/// Height of the QUIT region in the upper right corner of the region.
const CLOSE_HEIGHT: i32 = 2;

/// Retrieve the next window ID.
fn get_next_window_id() -> i32 {
    // Use a static to hold the next window ID.
    static NEXT_WINDOW_ID: AtomicI32 = AtomicI32::new(1);

    NEXT_WINDOW_ID.fetch_add(1, Ordering::Relaxed)
}

//-----------------------------------------------------------------------------

/// Represents a rectangular region, with upper left and lower right
/// coordinates.
///
/// For this example, the minimum width of a rectangle is 4 x 4.
pub struct WindowRectangle {
        pub left: i32,
        pub top: i32,
        pub right: i32,
        pub bottom: i32,
}

impl WindowRectangle {
    /// Constructor.
    ///
    /// # Parameters
    /// - left
    ///
    ///   X coordinate of upper left corner.
    /// - top
    ///
    ///   Y coordinate of upper left corner.
    /// - width
    ///
    ///   Width of rectangle.
    /// - height
    ///
    ///   Height of rectangle.
    ///
    /// # Returns
    /// Returns a new instance of the WindowRectangle struct.
    pub fn new(left: i32, top: i32, width: i32, height: i32) -> WindowRectangle {
        WindowRectangle {
            left, top,
            right : left + max(width, MINIMUM_WIDTH),
            bottom: top + max(height, MINIMUM_HEIGHT),
        }
    }

    /// Determine if the given point is in the rectangle.
    ///
    /// # Parameters
    /// - point
    ///
    ///   A MessagePosition struct to determine if it is inside this WindowRectangle.
    ///
    /// # Returns
    /// Returns true if the point is in this WindowRectangle; otherwise, returns
    /// false.
    pub fn point_inside(&self, point: &MessagePosition) -> bool {
        let mut is_inside = false;

        if point.x >= self.left && point.x < self.right &&
        point.y >= self.top && point.y < self.bottom {
            is_inside = true;
        }
        is_inside
    }
}

impl Display for WindowRectangle {
    /// Convert this WindowRectangle contents to a string.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!("x1={0:2}, y1={1:2}, x2={2:2}, y2={3:2}", self.left, self.top, self.right, self.bottom))
    }
}

//=============================================================================

/// Represents a rectangular region that can handle messages directed to that
/// region.
///
/// Note: The IMessageHandler interface is an example of a
/// "Facade" design pattern, where the complexity of the MessageWindow is
/// exposed only through a few methods to a system that only needs to deal with
/// those few methods.
pub struct MessageWindow {
    /// Unique ID of this window.
    id: i32,

    /// Title/Name of this window.
    title: String,

    /// Position of this window in global coordinates.
    window_box: WindowRectangle,

    /// Position of the close window within the window box, although the
    /// coordinates are also global coordinates to eliminate the need to
    /// convert between window and global coordinates.
    close_box: WindowRectangle,

    /// Whether this window has been selected (a button click occurred
    /// within the window).
    selected: bool,
}

impl MessageWindow {
    /// Constructor
    ///
    /// # Parameters
    /// - title
    ///
    ///   Title of the MessageWindow.
    /// - x
    ///
    ///   X position of the upper left corner of the window's region.
    /// - y
    ///
    ///   Y position of the upper left corner of the window's region.
    /// - width
    ///
    ///   Width of the window's region.
    /// - height
    ///
    ///   Height of the window's region.
    ///
    /// # Returns
    /// Returns a new instance of the MessageWindow struct.
    pub fn new(title: &str, x: i32, y:i32, width: i32, height: i32) -> MessageWindow {
        MessageWindow {
            id : get_next_window_id(),
            title : title.to_string(),
            window_box: WindowRectangle::new(x, y, width, height),
            close_box: WindowRectangle::new(x + width - CLOSE_WIDTH, y, CLOSE_WIDTH, CLOSE_HEIGHT),
            selected: false,
        }
    }


    /// Helper method to handle the ButtonDown message.
    ///
    /// # Parameters
    /// - message
    ///
    ///   A Message object describing the ButtonDown message.
    ///
    /// # Returns
    /// Returns a value from the MessageReturnTypes enumeration indicating what
    /// action the caller should take.  In this case, always return Continue so
    /// other handlers can react to the same message (assumes no windows are
    /// overlapping).
    fn handle_button_down_message(&mut self, message: &Message) -> MessageReturnTypes {
        if self.window_box.point_inside(&message.message_position) {
            if !self.selected {
                self.selected = true;
                println!("  --> Button Down in \"{0}\", window selected", self.title);
            }
        } else {
            if self.selected {
                self.selected = false;
                println!("  --> Button Down not in \"{0}\", window deselected", self.title);
            }
        }

        // Note: we are saying we didn't handled the message here since
        // we want other windows to get the button down message as
        // well so they can select or deselect themselves.
        MessageReturnTypes::Continue
    }

    /// Helper method to handle the ButtonUp message.
    ///
    /// # Parameters
    /// - message
    ///
    ///   A Message object describing the ButtonUp message.
    ///
    /// # Returns
    /// Returns a value from the MessageReturnTypes enumeration indicating what
    /// action the caller should take: (Stop) This message was handled and
    /// processing should stop, (Continue) this message can be passed on to
    /// other handlers, or (Close) this handler is closed so remove from the
    /// handlers list and stop further processing.
    fn handle_button_up_message(&mut self, message: &Message) -> MessageReturnTypes {
        let mut continue_code = MessageReturnTypes::Continue;

        if self.selected {
            if self.window_box.point_inside(&message.message_position) {
                continue_code = MessageReturnTypes::Stop;
                if self.close_box.point_inside(&message.message_position) {
                    println!("  --> Button Up in \"{0}\" close box, forwarding message to close handler", self.title);
                    continue_code = self.handle_close_message(message);
                } else {
                    println!("  --> Button Up in \"{}\", no further action taken", self.title);
                }
            }
        }
        continue_code
    }

    /// Helper method to handle the Close message.
    ///
    /// # Parameters
    /// - _message
    ///
    ///   NOT USED.
    ///
    /// # Returns
    /// Returns a value from the MessageReturnTypes enumeration indicating what
    /// action the caller should take.  In this case, always return Close to
    /// indicate this handler should be removed from the handler list so no
    /// further messages can be sent to this window.
    fn handle_close_message(&mut self, _message: &Message) -> MessageReturnTypes {
        let mut continue_code = MessageReturnTypes::Continue;

        if self.selected {
            println!("  --> Close in \"{}\", removing window from handler chain", self.title);
            // This window is being closed.  We are handling the message
            // so no other window needs to see it.
            continue_code = MessageReturnTypes::Close;
            self.selected = false;
        }
        continue_code
    }
}


impl IMessageHandler for MessageWindow {
    fn id(&self) -> i32 {
        self.id
    }

    fn process_message(&mut self, message: &super::handlerchain_message::Message) -> MessageReturnTypes {
        match message.message_type {
            MessageType::ButtonDown => self.handle_button_down_message(message),
            MessageType::ButtonUp => self.handle_button_up_message(message),
        }
    }

    fn to_string(&self) -> String {
        format!("[id={:2}] \"{}\" ({}), selected={}", self.id, self.title, self.window_box, self.selected)
    }
}
