//! Contains the BigResource struct that holds the multiple images, each of
//! which is represented by the Fylweight struct.

//-----------------------------------------------------------------------------

use super::flyweight_display::Display;
//-----------------------------------------------------------------------------

/// Represents a big image.  This gets stored in the BigResourceManager struct.
/// 
/// This struct is used in rendering an image to a display using the
/// render() function.
pub struct BigResource {
    data: Vec<Vec<char>>,
    num_images: usize,
}


impl BigResource {
    /// Constructor.
    ///
    /// # Parameters
    /// - data
    ///   The "image" data to store as a "big" resource.  This is a list of
    ///   list of characters, where each list of characters represents a row of
    ///   data, the number of lists of characters representing the height of
    ///   the "image" data.  We are using list of characters because Rust does
    ///   not allow a string to be indexed for an individual character.
    ///
    /// - num_images
    ///   The number of Flyweight images stored in this single "big" resource
    ///   image (images are arranged horizontally, one for each instance of the
    ///   Flyweight struct.  Divide the overall width by the number of images
    ///   to get the width of each individual image, although each Flyweight
    ///   instance stores the individual image width (and height) that instance
    ///   uses).
    ///
    /// # Returns
    /// Returns the given data wrapped in a new BigResource instance.
    pub fn new(data: Vec<Vec<char>>, num_images: usize) -> BigResource {
        BigResource { data, num_images }
    }

    /// Render the specified portion of the big resource into the given display at
    /// the given coordinates in the display.
    ///
    /// # Parameters
    /// - display
    ///
    ///   The display in which to render the image.
    /// - offset_x
    ///
    ///   Offset from left edge of big resource "image" to start of the Flyweight
    ///   image to render.
    /// - image_width
    ///
    ///   Width of the Flyweight "image" to render, in characters.
    /// - image_height
    ///
    ///   Height of the Flyweight "image" to render, in characters.
    /// - position_x
    ///
    ///   Horizontal position, in characters, within the Display to which to
    ///   render the upper left corner of the Flyweight image.  Can be negative
    ///   if the Flyweight image is partially off the left edge of the display.
    /// - position_y
    ///
    ///   Vertical position, in characters, within the Display to which to
    ///   render the upper left corner of the Flyweight image.  Can be negative
    ///   if the Flyweight image is partially off the top edge of the display.
    pub fn render(&self, display: &mut Display, offset_x: usize, image_width: usize, image_height: usize, position_x: isize, position_y: isize) {
        let display_width = display.width;
        let display_height = display.height;
        let mut starting_position_x = position_x;
        let mut starting_position_y = position_y;

        // Size of image to render (can be smaller than actual image if image
        // lies partially of right or bottom of display).
        let mut image_render_width = image_width as isize;
        let mut image_render_height = image_height as isize;

        // Position into image to start rendering from (non-zero if
        // image is off the left or top edge of display).
        let mut starting_row_in_image: isize = 0;
        let mut starting_col_in_image = offset_x as isize;

        // Clip the image to the display.
        if starting_position_x < 0 {
            starting_col_in_image = -(starting_position_x as isize);
            image_render_width += starting_position_x;
            starting_position_x = 0;
        } else if starting_position_x + image_render_width > (display_width as isize) {
            image_render_width = (display_width as isize) - starting_position_x;
        }

        if starting_position_y < 0 {
            starting_row_in_image = -starting_position_y;
            image_render_height += starting_position_y;
            starting_position_y = 0;
        } else if starting_position_y + image_render_height > (display_height as isize) {
            image_render_height = (display_height as isize) - starting_position_y;
        }

        // If the image is even partially visible, render it
        if image_render_width > 0 && image_render_height > 0 {
            let mut current_display_row = starting_position_y;
            let mut current_image_row = starting_row_in_image;
            for _row in 0..image_render_height {
                let display_row = &mut display.display[current_display_row as usize];
                let image_row = &self.data[current_image_row as usize];
                for col in 0..image_render_width {
                    display_row[(starting_position_x + col) as usize] = image_row[(starting_col_in_image + col) as usize];
                }
                current_display_row += 1;
                current_image_row += 1;
            }
        }
    }
}

