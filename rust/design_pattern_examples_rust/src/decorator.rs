//! The Decorator design pattern example module
//!
//! The Decorator pattern is used when an object at run time needs to have its
//! behavior altered.  This is supported by providing wrappers around the
//! object called decorators.  Those wrappers take instances of the
//! IRenderElement trait.  All elements look the same and can therefore
//! recursively wrap other decorators.  The base element never wraps anything
//! and decorators must ultimately wrap a non-decorator class to be of any
//! use.
//!
//! Accessed through the decorator_exercise() function.

//-----------------------------------------------------------------------------
// Sub-module definitions.

pub mod decorator_irenderelement_trait;
pub mod decorator_textelement;
pub mod decorator_whitebackground;
pub mod decorator_underline;
pub mod decorator_redforeground;

//-----------------------------------------------------------------------------

use super::decorator::decorator_textelement::TextElement;
use super::decorator::decorator_whitebackground::WhiteBackgroundDecorator;
use super::decorator::decorator_underline::UnderlineDecorator;
use super::decorator::decorator_redforeground::RedForegroundDecorator;

//-----------------------------------------------------------------------------

/// Example of using the "Decorator" pattern.
/// 
/// The Decorator pattern is used when an object at run time needs to have its
/// behavior altered.  This is supported by providing wrappers around the
/// object called decorators.  Those wrappers take instances of the
/// IRenderElement trait.  All elements look the same and can therefore
/// recursively wrap other decorators.  The base element never wraps anything
/// and decorators must ultimately wrap a non-decorator class to be of any
/// use.
// ! [Using Decorator in Rust]
pub fn decorator_exercise() -> Result<(), String> {
    println!("");
    println!("Decorator Exercise");

    let base_element = TextElement::new("This is raw text");
    // Wrap the base element in three decorators.
    let mut wrapped_element = WhiteBackgroundDecorator::new(base_element.clone());
    wrapped_element = UnderlineDecorator::new(wrapped_element.clone());
    wrapped_element = RedForegroundDecorator::new(wrapped_element.clone());
    
    // Now render the elements to the console.
    println!("  base Text element: \"{}\"", base_element.render());
    println!("  Decorated element: \"{}\"", wrapped_element.render());

    println!("  Done.");

    Ok(())
}
// ! [Using Decorator in Rust]
