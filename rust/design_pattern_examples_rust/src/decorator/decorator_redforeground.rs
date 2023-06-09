//! Contains the RedForegroundDecorator struct representing a decorator that
//! renders an element with red foreground (text) color.

use std::rc::Rc;

use super::decorator_irenderelement_trait::IRenderElement;

/// Represents the RedForeground decorator, which causes the text to be rendered
/// in red.
pub struct RedForegroundDecorator {
    wrapped_element: Rc<dyn IRenderElement>,
}

impl RedForegroundDecorator {
    /// Constructor that wraps the specified element.
    ///
    /// # Parameters
    /// - wrapped_element
    ///
    ///   The IRenderElement to be decorated.
    ///
    /// # Returns
    /// Returns a new RedForegroundDecorator structure represented by the
    /// IRenderElement trait.
    pub fn new(wrapped_element: Rc<dyn IRenderElement>) -> Rc<dyn IRenderElement> {
        Rc::new(RedForegroundDecorator{ wrapped_element })
    }
}

impl IRenderElement for RedForegroundDecorator {
    fn render(&self) -> String {
        format!("\x1b[31m{}\x1b[39m", self.wrapped_element.render())
    }
}
