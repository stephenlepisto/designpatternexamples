//! The Flyweight design pattern example module
//!
//! The Flyweight pattern is used when a large object needs to be
//! represented by a much lighter weight struct, possibly multiple
//! instances of said light-weight struct.
//!
//! In this example, a large object is represented by a so-called "big
//! resource" (a two-dimensional array of text characters) containing
//! multiple images, one associated with each flyweight struct.
//! FlyweightImage structs that contain an offset into the big resource,
//! along with position and velocity, are attached to the big resource
//! image so they all share the same image but have different positions
//! and velocities.  The image is rendered to a display area using the
//! FlyweightImage struct.  The FlyweightImage struct instances then have
//! their positions updated, bouncing off the edges of the display area 60
//! times a second.  This continues for 1000 iterations or until a key
//! is pressed.
//!
//! Accessed through the flyweight_exercise() function.

//-----------------------------------------------------------------------------

pub mod flyweight_bigresource;
pub mod flyweight_bigresource_manager;
pub mod flyweight_display;
pub mod flyweight_context;
pub mod flyweight_image;

//-----------------------------------------------------------------------------

use std::cmp::{min, max};
use std::time::Duration;
use std::thread;

use super::helpers::{cursor, random, key_input};
use flyweight_bigresource_manager::BigResourceManager;
use flyweight_bigresource::BigResource;
use flyweight_display::Display;
use flyweight_image::FlyweightImage;
use flyweight_context::FlyweightContext;

//-----------------------------------------------------------------------------

/// Width of the "display", in characters, in which to render Flyweight "images".
const DISPLAY_WIDTH: usize = 80;
/// Height of the "display", in characters, in which to render Flyweight "images".
const DISPLAY_HEIGHT: usize = 20;
/// Width of an individual Flyweight "image", in characters.
const IMAGE_WIDTH: usize = 30;
/// Height of an individual Flyweight "image", in characters.
const IMAGE_HEIGHT: usize = 5;
/// Number of Flyweight "images" to generate and manipulate.
const NUMFLYWEIGHTS: usize = 5;
/// Number of iterations of moving and rendering the Flyweight "images".
const NUM_ITERATIONS: usize = 1000;

//-----------------------------------------------------------------------------

/// Generate a big resource, in this case, a text master "image" of the
/// specified height, containing the specified number of smaller images
/// laid out horizontally, using the given width for each image.
///
/// If there are 5 images requested, then create a single image that is
/// `5 * width` wide and `1 * height` tall.
fn _flyweight_generate_big_resource(image_count: usize, image_width: usize, image_height: usize) -> BigResource {
    let image_background_character = vec!['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

    let mut data: Vec<Vec<char>> = vec![];
    let num_images = min(image_count, 9);
    let clipped_image_width = max(image_width, 3);
    let clipped_image_height = max(image_height, 3);

    let width = clipped_image_width * num_images;
    let height = clipped_image_height;

    data.resize(height, vec![]);
    for row in 0..height {
        let mut image_row: Vec<char> = Vec::new();
        image_row.resize(width, ' ');
        for image_index in 0..num_images {
            let image_offset_x = image_index * clipped_image_width;
            let background_character = image_background_character[image_index];
            for col in 0..clipped_image_width {
                // top and bottom row are the same.
                if row == 0 || (row + 1) == height {
                    if col == 0 || (col + 1) == clipped_image_width {
                        image_row[image_offset_x + col] = '+';
                    } else {
                        image_row[image_offset_x + col] = '-';
                    }
                } else {
                    // top and bottom row are the same.
                    if col == 0 || (col + 1) == clipped_image_width {
                        image_row[image_offset_x + col] = '|';
                    } else {
                        // All other rows are each the same -- except that
                        // each image is "numbered" where the background of the
                        // image reflects the number of the image (0, 1, 2, etc.).
                        image_row[image_offset_x + col] = background_character;
                    }
                }
            }
        }
        data[row] = image_row;
    }
    BigResource::new(data)
}

/// Generate a random velocity, which includes a speed and a direction.
/// The velocity is 0.2 to 1.0 (in increments of 0.2) and the direction
/// is either + or -.
fn _flyweight_generate_velocity() -> f32 {
    let speed_range = random::random(1..(5+1)) as f32;
    let speed = speed_range / 5.0;
    let direction = match random::random(1..100+1) {
        1..=50 => -1.0,
        51..=101 => 1.0,
        _ => 1.0,
    };

    speed * direction
}


/// Helper function to generate the specified number of FlyweightImage struct
/// instances and associate those objects with individual contexts and a single
/// big resource.
///
/// The image and display sizes are provided so as to randomize the
/// position of each flyweight within the display.
fn _flyweight_generate_flyweight_images(big_resource_id: usize, num_flyweights: usize,
    image_width: usize, image_height: usize, display_width: usize, display_height: usize,
    image_list: &mut Vec<FlyweightImage>) {

    for _image_index in 0..num_flyweights {
        let mut context = FlyweightContext::new(_image_index * image_width, image_width, image_height);
        // Make sure the entire image can be rendered at each position
        context.position_x = random::random(0..(display_width - image_width) as u32) as f32;
        context.position_y = random::random(0..(display_height - image_height) as u32) as f32;
        context.velocity_x = _flyweight_generate_velocity();
        context.velocity_y = _flyweight_generate_velocity();

        let flyweight_image = FlyweightImage{ big_resource_id, context };
        image_list.push(flyweight_image);
    }
}


/// Move the given flyweight instances within the display, bouncing them off
/// the edges of the display.
///
/// The display size and image size are provided here
fn _flyweight_move_images(images: &mut Vec<FlyweightImage>, display_width: usize, display_height: usize) {
    for image in images.iter_mut() {
        let image_width = image.context.image_width;
        let image_height = image.context.image_height;
        let mut new_x = image.context.position_x + image.context.velocity_x;
        let mut new_y = image.context.position_y + image.context.velocity_y;
        if new_x < 0.0 || (new_x + (image_width as f32)) > display_width as f32 {
            image.context.velocity_x = -image.context.velocity_x;
            if new_x < 0.0 {
                new_x = 0.0;
            } else {
                new_x = (display_width - image_width) as f32;
            }
        }

        if new_y < 0.0 || (new_y + (image_height as f32)) > display_height as f32 {
            image.context.velocity_y = -image.context.velocity_y;
            if new_y < 0.0 {
                new_y = 0.0;
            } else {
                new_y = (display_height - image_height) as f32;
            }
        }

        image.context.position_x = new_x;
        image.context.position_y = new_y;
    }
}

/// Clear the given "display" to a background character, erasing whatever was
/// there before.
///
/// # Parameters
/// - display
///
///   The display to clear.
fn _flyweight_clear_display(display: &mut Display) {
    display.clear_display('~');
}

/// Generate a display area in which to render the big resource.
///
/// # Parameters
/// - width
///
///   Width of display area, in characters.
/// - height
///
///   Height of display area, in characters.
///
/// # Returns
/// Returns a new instance of the Display struct, ready for use.
fn _fylweight_generate_display(width: usize, height: usize) -> Display {
    let mut display = Display::new(width, height);
    _flyweight_clear_display(&mut display);
    display
}

/// Render the given images into the display, drawing on the big resource
/// "image" found in the given Big Resource Manager.
fn _flyweight_render_images(resource_manager: &BigResourceManager, images: &Vec<FlyweightImage>, display: &mut Display) {
    // Render the image into the "display", one image for each instance
    // of the Flyweight class.
    for index in 0..images.len() {
        images[index].render(resource_manager, display);
    }
}

/// Render the display to the screen.
///
/// # Parameters
/// - display
///
///   The display to render to the console.
fn _flyweight_show_display(display: &Display) {
    let mut output = String::new();
    for row in 0..display.height {
        let mut row_string = String::new();
        row_string.push_str("  ");
        for col in 0..display.width {
            row_string.push(display.display[row][col]);
        }
        row_string.push('\n');
        output.push_str(&row_string);
    }

    println!("{output}");
}

//-----------------------------------------------------------------------------
/// Example of using the "Flyweight" design pattern.
///
/// The Flyweight pattern is used when a large object needs to be
/// represented by a much lighter weight struct, possibly multiple
/// instances of said light-weight struct.
///
/// In this example, a large object is represented by a so-called "big
/// resource" (a two-dimensional array of text characters) containing
/// multiple images, one associated with each flyweight struct.
/// FlyweightImage structs that represent an offset into the big resource,
/// along with position and velocity, are attached to the big resource
/// image so they all share the same image but have different positions
/// and velocities.  The image is rendered to a display area using the
/// FlyweightImage struct.  The FlyweightImage struct instances then have their
/// positions updated, bouncing off the edges of the display area 60
/// times a second.  This continues for 1000 iterations or until a key
/// is pressed.
// ! [Using Flyweight in Rust]
pub fn flyweight_exercise() -> Result<(), String> {
    println!("");
    println!("Flyweight Exercise");

    let mut big_resource_manager = BigResourceManager::new();
    let big_resource = _flyweight_generate_big_resource(NUMFLYWEIGHTS, IMAGE_WIDTH, IMAGE_HEIGHT);
    let resource_id = big_resource_manager.add_resource(big_resource);
    println!("bigResourceId = {resource_id}");

    let mut flyweight_images: Vec<FlyweightImage> = Vec::new();
    _flyweight_generate_flyweight_images(resource_id, NUMFLYWEIGHTS,
        IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT,
        &mut flyweight_images);

    // Create the "display".
    // We use a list of character arrays so we can write to each
    // character position individually.  In Rust, strings are immutable
    // and changing a character in a string is not allowed.
    let mut display = _fylweight_generate_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    // Finally, display the rendered output.
    println!("  The image rendered {} times:", NUMFLYWEIGHTS);
    println!(); // Blank line for iteration count
    _flyweight_render_images(&big_resource_manager, &flyweight_images, &mut display);
    _flyweight_show_display(&display);

    // Initialize raw key input before getting cursor position.
    cursor::hide_cursor();

    // Now let's have some fun and bounce those images around for a while!
    // (Or until a keypress.)
    let (cursor_left, mut cursor_top) = cursor::get_cursor_position();
    cursor_top -= (DISPLAY_HEIGHT + 1) as u16;

    for index in 0..NUM_ITERATIONS {
        cursor::set_cursor_position(cursor_left, cursor_top - 1);
        println!("  {:5}/{} iterations [press a key to exit early]", index + 1, NUM_ITERATIONS);
        cursor::set_cursor_position(cursor_left, cursor_top);
        _flyweight_clear_display(&mut display);
        _flyweight_move_images(&mut flyweight_images, display.width, display.height);
        _flyweight_render_images(&big_resource_manager, &flyweight_images, &mut display);
        _flyweight_show_display(&display);
        thread::sleep(Duration::from_millis(16)); // 60 frames a second
        if key_input::check_for_key() {
            break;
        }
    }
    cursor::show_cursor();

    println!("  Done.");

    Ok(())
}
// ! [Using Flyweight in Rust]
