//! Contains the Display struct that represents the "display" in which to render
//! The Flyweight "images".

/// Represents a "display" window, in which to render Flyweight images.  This
/// "display" window is then printed to the console window at a specified
/// coordinate to render a "frame" of motion in the "display".
pub struct Display {
    pub display: Vec<Vec<char>>,
    pub width: usize,
    pub height: usize,
}

impl Display {
    /// Create a "display" window in the given Display object, with the given
    /// width and height.
    ///
    /// # Parameters
    /// - width
    ///
    ///   The width of the window, in characters.
    /// - height
    ///
    ///   The height of the window, in characters.
    ///
    /// # Returns
    /// Returns an instance of the Display struct, ready for use.
    pub fn new(width: usize, height: usize) -> Display {
        let mut row: Vec<char> = Vec::new();
        row.resize(width, ' ');
        let mut display: Vec<Vec<char>> = Vec::new();
        display.resize(height, row);
        Display { display, width, height }
    }

    /// Clear the "display" to a background character, erasing whatever was
    /// there before.
    ///
    /// # Parameters
    /// - fill_character
    ///
    ///   The character with which to fill the display.
    pub fn clear_display(&mut self, fill_character: char) {
        for row in 0..self.height {
            for col in 0..self.width {
                self.display[row][col] = fill_character;
            }
        }
    }
}

