//! Contains the DirEntry struct that represents a directory entry in a
//! hierarchical list.

use std::cell::RefCell;
use std::rc::Rc;
use super::composite_filedirentry_trait::{FileDirTypes, FileDirEntry};

//-----------------------------------------------------------------------------

/// Represents the directory entry allowed in the hierarchy for the Composite
/// design pattern example.  A directory can contain other directories and
/// file entries.
pub struct DirEntry {
    /// Name of the directory.
    name: String,
    /// Timestamp of the directory (expressed as a string).
    timestamp: String,
    /// Length of all children of the directory (computed on first call to the
    /// length() method.)
    length: i32,
    /// True if the length has been computed (on the first call to the length()
    /// method).
    length_set: bool,
    /// Type of the entry as a value from the FileDirTypes enumeration.
    entry_type: FileDirTypes,
    /// Vector of FileDirEntry objects representing the children of this
    /// directory.
    children: Vec<Rc<RefCell<dyn FileDirEntry>>>,
}

impl DirEntry {
    /// Constructor for DirEntry
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the file.
    /// - timestamp
    ///
    ///   String containing the timestamp for the file.
    ///
    /// # Returns
    /// Returns the new DirEntry object.
    pub fn new(name: &str, timestamp: &str) -> DirEntry {
        DirEntry {
            name: name.to_string(),
            length: 0,
            length_set: false,
            timestamp: timestamp.to_string(),
            entry_type: FileDirTypes::DirType,
            children: vec![]
        }
    }

    /// Add the specified FileDirEntry object as a child of this directory.
    pub fn add_child(&mut self, entry: Rc<RefCell<dyn FileDirEntry>>) {
        self.children.push(entry);
    }
}


impl FileDirEntry for DirEntry {
    fn entry_type(&self) -> &FileDirTypes {
        &self.entry_type
    }

    fn name(&self) -> &str {
        &self.name
    }
    
    fn timestamp(&self) -> &str {
        &self.timestamp
    }
    
    fn length(&mut self) -> i32 {
        if self.length_set {
            self.length
        } else {
            for child in self.children.iter() {
                self.length += child.borrow_mut().length();
            }
            self.length_set = true;
            self.length
        }
    }
    
    fn children(&self) -> Option<&Vec<Rc<RefCell<dyn FileDirEntry>>>> {
        Some(&self.children)
    }
}
