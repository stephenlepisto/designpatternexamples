//! Contains the TextElement struct representing a string that can be decorated.

use std::rc::Rc;

use super::decorator_irenderelement_trait::IRenderElement;

/// Represents the core element that can be decorated.  Note that this
/// struct implements the IRenderElement trait but otherwise has no knowledge
/// of any of the decorators that might be applied.
/// 
/// This struct contains a string and does nothing other than return the
/// string.  This way, this struct can be decorated because it implements
/// the IRenderElement trait.
pub struct TextElement {
    element_text: String,
}

impl TextElement {
    /// Constructor.
    ///
    /// # Parameters
    /// - text
    ///
    ///   The text to be rendered.
    ///
    /// # Returns
    /// Returns a new TextElement structure represented by the IRenderElement
    /// trait.
    pub fn new (text: &str) -> Rc<dyn IRenderElement> {
        Rc::new(TextElement { element_text: text.to_string() })
    }
}

impl IRenderElement for TextElement {
    /// Render this element as a string by returning (a clone of) the string.
    fn render(&self) -> String {
        self.element_text.clone()
    }
}
