//! Contains the IRenderElement trait that represents decorator and text
//! elements.

/// Represents an element that can be rendered in text.  All decorators
/// and the core element class implement this interface.
pub trait IRenderElement {
    /// Render the wrapped element with decorations, returned as a new string.
    fn render(&self) -> String;
}
