//! Contains the MementoTextObject struct that contains the text to be managed.
//! Also contain the Memento struct that represents the snapshot of the text
//! object for later restoration.

//-----------------------------------------------------------------------------

use std::fmt::Display;

//-----------------------------------------------------------------------------

/// Represents a single memento (snapshot) of the text state before an
/// operation is applied.  The operation becomes the name of the memento for
/// display purposes.
pub struct Memento {
    /// The name of this memento (really just the name of the operation
    /// that triggered the need for this memento).
    name: String,
    /// The snapshot of the text data as stored in the MementoTextObject
    /// struct instance.
    text: String,
}

impl Memento {
    /// Constructor.
    ///
    /// # Parameters
    /// - name
    ///
    ///   The name of the memento to create
    /// - text
    ///
    ///   The data to be saved in the memento
    ///
    /// # Returns
    /// Returns a new instance of the Memento struct.
    fn new(name: &str, text: &str) -> Memento {
        Memento {
            name: name.to_string(),
            text: text.to_string(),
        }
    }

    /// The saved text in this memento.  This is accessible only by the
    /// MementoTextObject struct since it is the only entity that knows
    /// what to do with the text during an undo.
    fn text(&self) -> &str {
        &self.text
    }

    /// The name of the memento (snapshot).  Useful for displaying a list
    /// of mementos in an undo list.  In this case, the name of each
    /// memento is the operation that triggered the creation of the
    /// memento.
    pub fn name(&self) -> &str {
        &self.name
    }
}


/// Container for a string.  Need to use a struct that allows the text to be
/// changed while the container (this struct) remains constant.  This way,
/// operations can be applied to the text and the container's contents change
/// but not the container.
pub struct MementoTextObject {
    /// The text that can change in this MementoTextObject class.
    text: String,
}

impl MementoTextObject {
    /// Constructs a text object with an initial string.
    ///
    /// # Parameters
    /// - text
    ///
    ///   The text that will be managed by this MementoTextObject.
    ///
    /// # Returns
    /// Returns a new instance of the MementoTextObject struct.
    pub fn new(text: &str) -> MementoTextObject {
        MementoTextObject {
            text: text.to_string()
        }
    }

    /// Gets the text in this MementoTextObject.
    pub fn text(&self) -> &str {
        &self.text
    }

    /// Sets the text in this MementoTextObject.
    pub fn set_text(&mut self, text: &str) {
        self.text = text.to_string();
    }

    /// Returns a Memento object containing a snapshot of the text stored in
    /// this instance.
    ///
    /// # Parameters
    /// - operation_name
    ///
    ///   The name of the memento to create.  In this case, the name is the
    ///   operation that is to be applied to the text object.
    ///
    /// # Returns
    ///  Returns an instance of the Memento struct, representing the snapshot
    ///  of this MementoTextObject.
    pub fn get_memento(&self, operation_name: &str) -> Memento {
        Memento::new(operation_name, &self.text)
    }

    /// Sets the text in this MementoTextObject instance to the snapshot
    /// stored in the given Memento object (which is assumed to be from the
    /// MementoTextObject::get_memento() method).
    ///
    /// # Parameters
    /// - memento
    ///
    ///   A Memento object containing the text that will be copied over the
    ///   text in this MementoTextObject.
    pub fn restore_memento(&mut self, memento: &Memento) {
        self.text = memento.text().to_string()
    }
}

impl Display for MementoTextObject {
    /// Converts the MementoTextObject to a string (makes it easier to
    /// use the struct in string formatting).
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!("{0}", self.text()))
    }
}
