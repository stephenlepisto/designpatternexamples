//! Contains the implementation of a hierarchical list of files and directories
//! to be used for the Composite design pattern example.

use std::cell::RefCell;
use std::rc::Rc;

use time::OffsetDateTime;
use time::macros::format_description;

use super::composite_direntry::DirEntry;
use super::composite_fileentry::FileEntry;
use super::composite_filedirentry_trait::FileDirEntry;

/// Template for constructing a timestamp of the form: 06/04/2023 04:08:26 PM.
const DATE_FORMAT_STR: &[time::format_description::FormatItem<'static>] = format_description!(version = 2, "[month]/[day]/[year]  [hour repr:12]:[minute]:[second] [period]");

/// Construct a string containing the current time expressed as a timestamp
/// in the form "mm/dd/yyy HH:MM:SS AM|PM".
fn _create_time_stamp() -> String {
    let local_time = OffsetDateTime::now_local().unwrap();
    local_time.format(&DATE_FORMAT_STR).unwrap()
}

/// Construct a file/directory tree with a predefined set of files and
/// directories.  Out of memory errors will crash the program with a panic.
pub fn construct_tree() -> Rc<RefCell<dyn FileDirEntry>> {
    let timestamp = _create_time_stamp();
    let mut root_entry = DirEntry::new("root", &timestamp);
    root_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileA.txt", 101, &timestamp))));
    root_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileB.txt", 102, &timestamp))));
    root_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileC.txt", 103, &timestamp))));

    let mut subdir1_entry = DirEntry::new("subdir1", &timestamp);
    subdir1_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileD.txt", 104, &timestamp))));
    subdir1_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileE.txt", 105, &timestamp))));

    let mut subdir2_entry = DirEntry::new("subdir2", &timestamp);
    subdir2_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileF.txt", 106, &timestamp))));
    subdir2_entry.add_child(Rc::new(RefCell::new(FileEntry::new("FileG.txt", 107, &timestamp))));

    subdir1_entry.add_child(Rc::new(RefCell::new(subdir2_entry)));

    root_entry.add_child(Rc::new(RefCell::new(subdir1_entry)));

    Rc::new(RefCell::new(root_entry))
}


/// Return a FileDirEntry object representing the specified file "path" in an
/// internal list of data entries that is organized in a file/directory
/// structure. The root and returned object are reference-counted smart pointers
/// to a reference cell object containing the dynamic pointer to the
/// FileDirEntry trait.
///
/// # Parameters
/// - root
///
///   The FileDirEntry object representing the root of the directory tree to
///   search.
/// - entry_path
///
///   The "path" to search for in the given directory tree.
///
/// # Returns
/// Returns an Option<> containing the found FileDirEntry object.  Returns
/// None if no entry was found.
pub fn get_entry(root: Rc<RefCell<dyn FileDirEntry>>, entry_path: &str) -> Option<Rc<RefCell<dyn FileDirEntry>>> {
    let mut working_root = root.clone();
    let file_path = entry_path.replace("\\", "/");
    let path_components: Vec<&str> = file_path.split('/').collect();
    let num_elements = path_components.len();

    for index in 0..num_elements {
        if path_components[index] != working_root.borrow().name() {
            // Mismatch in path to this entry, bad path
            break;
        }
        if index + 1 >= num_elements {
            // Reached end of path so we found what was asked for.
            return Some(working_root);
        }

        // Still haven't reached end of specified path, look at
        // the current root for children.

        let new_root: Rc<RefCell<dyn FileDirEntry>>;
        if let Some(children) = working_root.borrow().children() {
            let child_component = path_components[index + 1];
            new_root = match children.iter().find(|x| x.borrow().name().eq(child_component)) {
                Some(new_root) => new_root.clone(),
                None => break,
            }
        } else {
            // Path included leaf in the middle, bad path
            // NOTE: COULD BE AN EMPTY DIRECTORY!  NEED TO ACCOMMODATE THIS!
            break;
        }

        working_root = new_root;
    }
    None
}

