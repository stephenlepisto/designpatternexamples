//! Contains hide_cursor(), show_cursor, get_cursor_position() and
//! set_cursor_position() for dealing with the cursor and its position in a
//! console window.


use std::io::{stdin, stdout, Read, Write};
use crossterm::{
    ExecutableCommand,
    cursor,
    terminal,
};


/// Hide or turn off the cursor that is normally always visible on the console.
///
/// We could use an ANSI sequence for this (ESC[?25l), but the sequence is
/// private and not necessarily supported everywhere.  The crossterm crate
/// makes this simple and hides any system differences.
pub fn hide_cursor() {
    let mut stdout = stdout();
    stdout.execute(cursor::Hide).unwrap();
}

/// Show or turn on the cursor so it is in the normal visible state.
///
/// We could use an ANSI sequence for this (ESC[?25h), but the sequence is
/// private and not necessarily supported everywhere.  The crossterm crate
/// makes this simple and hides any system differences.
pub fn show_cursor() {
    let mut stdout = stdout();
    stdout.execute(cursor::Show).unwrap();
}

/// Retrieve the current cursor position in the console window.
///
/// This uses an ANSI string sequence to query the cursor position as the
/// crossterm crate does not provide the ability to get the cursor position.
///
/// # Returns
/// Returns a tuple (x, y) containing the x and y position of the cursor
/// position in the console window, relative to the upper left corner of the
/// window.  Position starts at 1,1.
pub fn get_cursor_position() -> (u16, u16) {
    let mut position_x = 0;
    let mut position_y = 0;

    terminal::enable_raw_mode().unwrap();
    print!("\x1b[6n"); // Make sure we don't add a newline
    let mut stdout = stdout();
    stdout.flush().unwrap(); // No newline so we must flush to activate the sequence.
    let mut stdin = stdin();
    let mut buffer = vec!(0u8;16);

    if let Ok(n) = stdin.read(&mut buffer) {
        // Expecting ESC [ <r> ; <c> R (no spaces)
        if n > 2 && buffer[0] == 0x1b && buffer[1] == b'[' {
            if let Ok(s) = String::from_utf8(buffer) {
                let items : Vec<&str> = s.split(&['[', ';', 'R']).collect();
                if items.len() >= 3 {
                    let row_as_string = items[1];
                    let col_as_string = items[2];
                    position_y = row_as_string.parse().unwrap();
                    position_x = col_as_string.parse().unwrap();
                }
            }
        }
    }
    terminal::disable_raw_mode().unwrap();

    (position_x, position_y)
}

/// Move the text cursor to the specified screen coordinates in the console
/// window.
///
/// # Parameters
/// - position_x
///
///   Column index from left, starting at 1, in characters.
/// - position_y
///
///   Row index from top, starting at 1, in characters
pub fn set_cursor_position(position_x: u16, position_y: u16) {
    print!("\x1b[{position_y};{position_x}H");
    let mut stdout = stdout();
    stdout.flush().unwrap();
}
