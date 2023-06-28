//! The Memento design pattern example module
//! 
//! In this exercise, the Memento pattern is used to take snapshots of a text
//! object so as to form an undo list of changes to the text object.  Undoing
//! an operation means restoring a snapshot of the text object.
//! 
//! The undo list is implemented as a stack of memento objects that each
//! represent a snapshot of the text object taken before each operation is
//! applied.  After all operations are applied, the mementos are used to
//! restore the text object in reverse order, effectively undoing each
//! operation in turn.
//!
//! Accessed through the memento_exercise() function.

//-----------------------------------------------------------------------------

pub mod memento_textobject;

//-----------------------------------------------------------------------------

use memento_textobject::{Memento, MementoTextObject};

//-----------------------------------------------------------------------------

/// This struct creates a context around the undo list that the
/// memento_exercise() executes within.  This gets around the problem of
/// needing a static undo list as all the methods on this context have ready
/// access to the undo list in the context.
struct MementoContext {
    /// The list of memento objects that form a series of snapshots in time
    /// of a MementoTextObject.
    undo_list: Vec<Memento>,
}

impl MementoContext {
    /// Constructor.
    fn new() -> MementoContext {
        MementoContext {
            undo_list: vec![]
        }
    }


    /// Take a snapshot of the given text object associated with the name of
    /// given operation.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to take a snapshot of.
    /// - operation
    ///
    ///   A string describing the operation that will be applied after the
    ///   snapshot is taken.
    fn save_for_undo(&mut self, text_object: &MementoTextObject, operation: &str) {
        self.undo_list.push(text_object.get_memento(operation));
    }

    /// An operation to search and replace text in a MementoTextObject.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to work with.
    /// - search_pattern
    ///
    ///   What to look for in the MementoTextObject
    /// - replace_text
    ///
    ///   What to replace the `search_pattern` with
    fn operation_replace(&mut self, text_object: &mut MementoTextObject, search_pattern: &str, replace_text: &str) {
        let text = text_object.text().to_string();
        text_object.set_text(&text.replace(search_pattern, replace_text));
    }

    /// An operation to reverse the characters in the given MementoTextObject.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to work with.
    fn operation_reverse(&mut self, text_object: &mut MementoTextObject) {
        let text = text_object.text().to_string();
        text_object.set_text(&text.chars().rev().collect::<String>());
    }

    /// Perform an undo on the given Command_TextObject, using the mementos in the
    /// "global" undo list.  If the undo list is empty, nothing happens.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to update.
    fn undo(&mut self, text_object: &mut MementoTextObject) {
        if !self.undo_list.is_empty() {
            let last_memento = self.undo_list.pop().unwrap();
            text_object.restore_memento(&last_memento);

            // Show off what we (un)did.
            println!("    undoing operation {0:<31}: \"{1}\"", last_memento.name(), text_object);
        }
    }

    /// Helper function to replace a pattern with another string in the
    /// given MementoTextObject after adding a snapshot of the text
    /// object to the undo list.  Finally, it shows off what was done.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to update.
    /// - search_pattern
    ///
    ///   What to look for in the MementoTextObject
    /// - replace_text
    ///
    ///   What to replace the `search_pattern` with
    fn apply_replace_operation(&mut self, text_object: &mut MementoTextObject, search_pattern: &str, replace_text: &str) {
        let operation_name = format!("Replace '{0}' with '{1}'", search_pattern, replace_text);
        self.save_for_undo(text_object, &operation_name);
        self.operation_replace(text_object, search_pattern, replace_text);
        println!("    operation {0:<31}: \"{1}\"", operation_name, text_object);
    }

    /// Helper function to reverse the order of the characters in the
    /// given MementoTextObject after adding a snapshot of the text
    /// object to an undo list.  Finally, it shows what was done.
    ///
    /// # Parameters
    /// - text_object
    ///
    ///   The MementoTextObject to work with.
    fn apply_reverse_operation(&mut self, text_object: &mut MementoTextObject) {
        let operation_name = "Reverse";
        self.save_for_undo(text_object, operation_name);
        self.operation_reverse(text_object);
        println!("    operation {0:<31}: \"{1}\"", operation_name, text_object);
    }

}

/// Example of using the "Memento" design pattern.
/// 
/// In this exercise, the Memento pattern is used to take snapshots of a text
/// object so as to form an undo list of changes to the text object.  Undoing
/// an operation means restoring a snapshot of the text object.
/// 
/// The undo list is implemented as a stack of memento objects that each
/// represent a snapshot of the text object taken before each operation is
/// applied.  After all operations are applied, the mementos are used to
/// restore the text object in reverse order, effectively undoing each
/// operation in turn.
/// 
/// Compare this to the command_exercise() and note that the steps taken there
/// are identical to here (except for method names, of course).  The difference
/// lies in how operations are executed and undone.  Mementos make the undo
/// process much cleaner and faster since operations do not need to be applied
/// repeatedly to get the text object into a specific state.  Specifically,
/// compare command_undo() with memento_undo().  Also note the differences in
/// the "memento_applyXXOperation()" methods, which more cleanly separate the
/// save from the operation.
// ! [Using Memento in Rust]
pub fn memento_exercise() -> Result<(), String> {
    println!("");
    println!("Memento Exercise");

    // Start with a fresh undo list.
    let mut memento_context = MementoContext::new();

    // The base text object to work from.
    let mut text_object = MementoTextObject::new("This is a line of text on which to experiment.");

    println!("  Starting text: \"{0}\"", text_object);

    // Apply four operations to the text.
    memento_context.apply_replace_operation(&mut text_object, "text", "painting");
    memento_context.apply_replace_operation(&mut text_object, "on", "off");
    memento_context.apply_reverse_operation(&mut text_object);
    memento_context.apply_replace_operation(&mut text_object, "i", "!");

    println!("  Now perform undo until back to original");

    // Now undo the four operations.
    memento_context.undo(&mut text_object);
    memento_context.undo(&mut text_object);
    memento_context.undo(&mut text_object);
    memento_context.undo(&mut text_object);

    println!("  Final text   : \"{0}\"", text_object);

    println!("  Done.");

    Ok(())
}
// ! [Using Memento in Rust]
