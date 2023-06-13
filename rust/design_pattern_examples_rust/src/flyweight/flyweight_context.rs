//! Contains the FlyweightContext struct that holds the offsets to the Flyweight
//! "image" (in a big resource "image") along with the position of the Flyweight
//! "image" within a "display".

/// Represents the context for an instance of the Flyweight_Image structure.
/// In this case, the context includes position and velocity.
/// 
/// This context is manipulated outside the Flyweight Image by the
/// controlling entity (in this case, the flyweight_exercise() function).  The
/// FlyweightImage struct just holds onto the context, along with a handle
/// to the big resource.
pub struct FlyweightContext {
    /// Offset into big resource to left edge of image, in characters.
    pub offset_x_to_image: usize,
    /// Width of image, in characters
    pub image_width: usize,
    /// Height of image, in characters
    pub image_height: usize,
    /// Horizontal position of upper left corner of image in a display, in
    /// characters
    pub position_x: f32,
    /// Vertical position of upper left corner of image in a display, in
    /// characters
    pub position_y: f32,
    /// Velocity to apply to the horizontal position, in fractions of a
    /// character
    pub velocity_x: f32,
    /// Velocity to apply to the vertical position, in fractions of a
    /// character
    pub velocity_y: f32,
}


impl FlyweightContext {
    /// Constructor.
    ///
    /// # Parameters
    /// - offset_x_to_image
    ///
    ///   Offset into big resource to left edge of image, in characters.
    /// - image_width
    ///
    ///   Width of image, in characters.
    /// - image_height
    ///
    ///   Height of image, in characters.
    ///
    /// # Returns
    /// Returns a new instance of the FlyweightContext struct.
    pub fn new(offset_x_to_image: usize, image_width: usize, image_height: usize) -> FlyweightContext {
        FlyweightContext {
            offset_x_to_image: offset_x_to_image,
            image_width: image_width,
            image_height: image_height,
            position_x: 0.0,
            position_y: 0.0,
            velocity_x: 0.0,
            velocity_y: 0.0,
        }
    }
}