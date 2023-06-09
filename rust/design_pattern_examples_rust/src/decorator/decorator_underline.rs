//! Contains the UnderlineDecorator struct representing a decorator that
//! renders an element as underlined text.

use std::rc::Rc;

use super::decorator_irenderelement_trait::IRenderElement;

/// Represents the Underline decorator, which causes the text element to be
/// rendered as underlined.
pub struct UnderlineDecorator {
    wrapped_element: Rc<dyn IRenderElement>,
}

impl UnderlineDecorator {
    /// Constructor that wraps the specified element.
    ///
    /// # Parameters
    /// - wrapped_element
    ///
    ///   The IRenderElement to be decorated.
    ///
    /// # Returns
    /// Returns a new UnderlineDecorator structure represented by the
    /// IRenderElement trait.
    pub fn new(wrapped_element: Rc<dyn IRenderElement>) -> Rc<dyn IRenderElement> {
        Rc::new(UnderlineDecorator{ wrapped_element })
    }
}

impl IRenderElement for UnderlineDecorator {
    fn render(&self) -> String {
        format!("\x1b[4m{}\x1b[24m", self.wrapped_element.render())
    }
}
