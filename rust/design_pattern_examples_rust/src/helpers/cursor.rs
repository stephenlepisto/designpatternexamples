//! Contains get_cursor_position() and set_cursor_position() for dealing with
//! the cursor position in a console window.


use winconsole::console;

/// Retrieve the current cursor position in the console window.
///
/// # Returns
/// Returns a tuple (x, y) containing the x and y position of the cursor
/// position in the console window, relative to the upper left corner of the
/// window.
pub fn get_cursor_position() -> (u16, u16) {
    let position = console::get_cursor_position().unwrap();
    // winconsole::console returns the position in the console' buffer, not
    // the screen, so remove the scroll position to create a screen-oriented
    // position (technically, I should subtract out the horizontal scroll
    // position as well, but I don't need that functionality here).
    let scroll_position = console::get_scroll_position(true).unwrap();
    (position.x, position.y - scroll_position)
}

/// Move the text cursor to the specified screen coordinates in the console
/// window.
///
/// # Parameters
/// - position_x
///
///   Column index from left, starting at 0, in characters.
/// - position_y
///
///   Row index from top, starting at 0, in characters
pub fn set_cursor_position(position_x: u16, position_y: u16) {
    // Remember to convert screen-oriented position to scroll buffer-
    // oriented position.
    let scroll_position = console::get_scroll_position(true).unwrap();
    console::set_cursor_position(position_x, position_y + scroll_position).unwrap();
}
