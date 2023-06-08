//! Contains the FileEntry struct that represents a file entry in a
//! hierarchical list.

use std::cell::RefCell;
use std::rc::Rc;
use super::composite_filedirentry_trait::{FileDirTypes, FileDirEntry};

//-----------------------------------------------------------------------------

/// Represents the file entry allowed in the hierarchy for the Composite design
/// pattern example.
pub struct FileEntry {
    /// Name of the file
    name: String,
    /// Timestamp of the file (expressed as a string)
    timestamp: String,
    /// Length of the file
    length: i32,
    /// Type of the entry as a value from the FileDirTypes enumeration.
    entry_type: FileDirTypes,
}


impl FileEntry {
    /// Constructor for FileEntry
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the file.
    /// - length
    ///
    ///   Length of the file.
    /// - timestamp
    ///
    ///   String containing the timestamp for the file.
    ///
    /// # Returns
    /// Returns the new FileEntry object.
    pub fn new(name: &str, length: i32, timestamp: &str) -> FileEntry {
        FileEntry {
            name: name.to_string(),
            length: length,
            timestamp: timestamp.to_string(),
            entry_type: FileDirTypes::FileType,
        }
    }
}

impl FileDirEntry for FileEntry {
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
        self.length
    }
    
    fn children(&self) -> Option<&Vec<Rc<RefCell<dyn FileDirEntry>>>> {
        None
    }
}
