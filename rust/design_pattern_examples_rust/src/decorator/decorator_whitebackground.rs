//! Contains the WhiteBackgroundDecorator struct representing a decorator that
//! renders an element on a white background.

use std::rc::Rc;

use super::decorator_irenderelement_trait::IRenderElement;

/// Represents the WhiteBackground decorator, which changes the background
/// color of the wrapped element to white.
pub struct WhiteBackgroundDecorator {
    wrapped_element: Rc<dyn IRenderElement>,
}

impl WhiteBackgroundDecorator {
    /// Constructor that wraps the specified element.
    ///
    /// # Parameters
    /// - wrapped_element
    ///
    ///   The IRenderElement to be decorated.
    ///
    /// # Returns
    /// Returns a new WhiteBackgroundDecorator structure represented by the
    /// IRenderElement trait.
    pub fn new(wrapped_element: Rc<dyn IRenderElement>) -> Rc<dyn IRenderElement> {
        Rc::new(WhiteBackgroundDecorator{ wrapped_element })
    }
}

impl IRenderElement for WhiteBackgroundDecorator {
    fn render(&self) -> String {
        format!("\x1b[47m{}\x1b[49m", self.wrapped_element.render())
    }
}
