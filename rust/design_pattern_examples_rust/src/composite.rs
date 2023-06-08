//! The Composite design pattern example module
//!
//! The Composite pattern is used when a collection of objects is to
//! be formed in a hierarchical form where each object needs to be
//! treated like any other object but some objects can contain other
//! objects.
//! 
//! This example uses a file structure of file and directories to
//! represent each object type.
//!
//! Accessed through the composite_exercise() function.

//-----------------------------------------------------------------------------
// Sub-module definitions.

pub mod composite_filedirentry_trait;
pub mod composite_fileentry;
pub mod composite_direntry;
pub mod composite_fileaccess;

//-----------------------------------------------------------------------------

use std::cell::RefCell;
use std::rc::Rc;

use composite_fileaccess::{construct_tree};
use composite_filedirentry_trait::{FileDirEntry, FileDirTypes};

//-----------------------------------------------------------------------------

/// Helper function to format the specified entry for display.  Returns the
/// fully-built string ready for output.
/// 
/// Note: This is a recursive call.
///
/// # Parameters
/// - root
///
///   The FileDirEntry object to format, including any children of the object.
/// - indent
///
///   The number of spaces to indent each line of the display.
fn composite_format_entry(root: Rc<RefCell<dyn FileDirEntry>>, indent: usize) -> String {
    /// Maximum length of a name field in a hierarchical display
    const NAME_PADDING_SIZE: usize = 20;
    let mut output = String::new();
    let indent_spaces = "  ".repeat(indent);
    let mut padding = NAME_PADDING_SIZE - root.borrow().name().len() - indent_spaces.len();
    output.push_str(&format!("{}{}", indent_spaces, root.borrow().name()));
    if let FileDirTypes::DirType = root.borrow().entry_type() {
        output.push_str("/");
        padding -= 1;
    }
    output.push_str(&" ".repeat(padding));
    let root_length = root.borrow_mut().length();
    output.push_str(&format!("{:4}  {}\n", root_length, root.borrow().timestamp()));

    if let Some(children) = root.borrow().children() {
        for child in children {
            output.push_str(&composite_format_entry(child.clone(), indent + 1));
        }
    }
    output
}


/// Helper function to display the contents of the hierarchical list of objects
/// starting with the given object.
///
/// # Parameters
/// - root
///
///   The FileDirEntry object to display, including any children of the object.
fn composite_show_entry(root: Rc<RefCell<dyn FileDirEntry>>) {
    let entries_as_string = composite_format_entry(root, 2);
    println!("{entries_as_string}");
}

//-----------------------------------------------------------------------------

/// Example of using the "Composite" pattern.
/// 
/// The Composite pattern is used when a collection of objects is to
/// be formed in a hierarchical form where each object needs to be
/// treated like any other object but some objects can contain other
/// objects.
/// 
/// This example uses a file structure of file and directories to
/// represent each object type.
// ! [Using Composite in Rust]
pub fn composite_exercise() -> Result<(), String> {
    println!("");
    println!("Composite Exercise");

    let mut file_path = "root";
    let root: Rc<RefCell<dyn FileDirEntry>> = construct_tree();
    println!("  Showing object '{file_path}'");
    composite_show_entry(root.clone());

    file_path = "root/subdir1/FileD.txt";
    let path_entry = match composite_fileaccess::get_entry(root.clone(), &file_path) {
        Some(entry) => entry,
        None =>  return Err(String::from("Could not find path \"{file_path}\"")),
    };

    println!("  Showing object '{file_path}'");
    composite_show_entry(path_entry.clone());

    println!("  Done.");

    Ok(())
}
// ! [Using Composite in Rust]
