//! Contains the FileDirEntry trait that represents file and directory entries
//! in a hierarchical list.

use std::{rc::Rc, cell::RefCell};

/// Represents the type of entries allowed in the hierarchy for the
/// Composite design pattern example.
pub enum FileDirTypes {
    /// Represents a file entry.
    FileType,
    /// Represents a directory entry that can contain other FileDirEntry components.
    DirType,
}

/// Represents an entry in a hierarchical list of objects composed of files
/// and directories, where the directories can contain nested files and
/// directories.  This is a trait as it is the only way to represent a
/// polymorphic concept like the composite design pattern where all the entries
/// look the same to the rest of the program.
pub trait FileDirEntry {
    /// Returns a reference to the FileDirTypes value representing the type of
    /// entry this trait represents.
    fn entry_type(&self) -> &FileDirTypes;
    /// Returns a reference to the name of this entry.
    fn name(&self) -> &str;
    /// Returns a reference to the timestamp of this entry.
    fn timestamp(&self) -> &str;
    /// Returns the length of this entry.
    fn length(&mut self) -> i32;
    /// Returns an Option<> containing a reference to the vector of the
    /// children of this entry.  If there are no children, returns None.
    fn children(&self) -> Option<&Vec<Rc<RefCell<dyn FileDirEntry>>>>;
}
