//! Contains the FlyweightImage struct that holds the ID of the big resource
//! "image" to draw from and a FlyWeightContext struct that specifies the
//! offsets to the Flyweight along with the position of the Flyweight "image"
//! within a "display".

//-----------------------------------------------------------------------------

use super::flyweight_context::FlyweightContext;
use super::flyweight_display::Display;
use super::flyweight_bigresource::BigResource;
use super::flyweight_bigresource_manager::BigResourceManager;

//-----------------------------------------------------------------------------

/// Represents an image that associates a context with a big resource.
pub struct FlyweightImage {
    /// The big resource being referenced by this flyweight image.  This is
    /// represented by a handle to the big resource.
    pub big_resource_id: usize,

    /// The context associated with this image.  The calling entity
    /// uses this context to manipulate the position of the image.
    pub context: FlyweightContext,
}

impl FlyweightImage {
    /// Render the image associated with this flyweight instance into the given
    /// display at the given position.
    ///
    /// # Parameters
    /// - resource_manager
    ///
    ///   The BigResourceManager from which to get the BigResource "image" to
    ///   use
    /// - display
    ///
    ///   The display to render to
    pub fn render(&self, resource_manager: &BigResourceManager, display: &mut Display) {
        let resource: &BigResource = match resource_manager.get_resource(self.big_resource_id) {
            Some(r) => r,
            None =>  {
                eprintln!("Unable to get big resource with id {}.  Cannot render images.", self.big_resource_id);
                return
            }
        };
        
        resource.render(display, self.context.offset_x_to_image,
        self.context.image_width, self.context.image_height,
        self.context.position_x as isize, self.context.position_y as isize);
    }
}
