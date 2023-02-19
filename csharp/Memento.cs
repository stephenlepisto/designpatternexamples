// The Memento design pattern is used to capture the internal state of an
// object without exposing the details of that internal state.  At a later
// time, the Memento is used to restore the internal state of the object.
//
// The client asks an object for a snapshot of the object's internal state.
// This snapshot is in an opaque form.  The client typically caches this
// snapshot for later use (such as restoring the state to a known good state
// or as part of the process of implementing an undo system).  When the
// client wants to restore the object's state, it passed the snapshot back to
// the object and the object changes its internal state to match the given
// snapshot.
//
// The python pickling mechanism is a form of the Memento pattern, although in
// the process of pickling an object, the entire object is saved off, not just
// the internal state; however, the effect is the same.
//
// To implement the Memento state, the object whose state is to be saved off
// and later restored must be designed to make it easy to save and restore the
// state.  The Private Data pattern can facilitate this by storing the state
// of the main class in another class.  That data class can then be more
// easily converted to some internal state or the data class instance itself
// could be stored in the Memento, which is arguably more effective with
// classes that have a lot of internal data elements (less copying).  A class
// with only a few data elements would be more efficient serializing the data
// elements into another form such as strings or binary images.
//
// In the Command pattern, a simplistic undo/redo stack was created that
// required remembering commands used to get to a particular state.  To undo
// changes to the state, the state was cleared then the commands up to but not
// including the command to undo were replayed, rebuilding the state.
//
// Using Mementos, the state can be saved before each command.  To undo a
// command, the state saved before that command could be restored.  No need to
// replay the commands at all.  This makes for a more efficient undo process.
// However, if the state is very large, such as in a paint program, the undo
// may have to spool the saved states to disk or provide a combination of
// commands and mementos, where the state is saved periodically and the
// commands to get to the next save state are remembered and replayed.
//
// The example used here is a snapshot of a text object.  This is then used
// to create an undo stack.  In fact, this is the same example as used for
// the Command pattern but this example shows how mementos are generally more
// efficient than commands for creating an undo stack.


namespace DesignPatternExamples
{
    /// <summary>
    /// Represents a single memento, a single snapshot of the state of the
    /// Memento_TextObject class as represented by the private class
    /// Memento_TextObject.Memento.
    /// </summary>
    public interface IMemento
    {
        /// <summary>
        /// The name of the memento (snapshot).  Useful for displaying a list
        /// of mementos in an undo list.  In this case, the name of each
        /// memento is the operation that triggered the creation of the
        /// memento.
        /// </summary>
        string Name { get; }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Container for a string.  Need to use a class that allows the text to
    /// be changed while the container (this class) remains constant.  This
    /// way, operations can be applied to the text and the container's contents
    /// change but not the container (strings are immutable in C#; this dances
    /// around that problem).
    /// </summary>
    public class Memento_TextObject
    {
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Inner class Memento

        /// <summary>
        /// Represents a single memento (snapshot) of the text state before
        /// an operation is applied.  The operation becomes the name of the
        /// memento for display purposes.
        /// </summary>
        internal class Memento : IMemento
        {
            /// <summary>
            /// The name of this memento (really just the name of the operation
            /// that triggered the need for this memento).
            /// </summary>
            string _name;

            /// <summary>
            /// The snapshot of the text data as stored in the Memento_TextObject
            /// class instance.
            /// </summary>
            string _text;


            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="name">The name of the memento to create.</param>
            /// <param name="text">The data to be saved in the memento</param>
            internal Memento(string name, string text)
            {
                _name = name;
                _text = text;
            }


            /// <summary>
            /// The saved text in this memento.  This is accessible only by the
            /// Memento_TextObject class since it is the only entity that knows
            /// what to do with the text during an undo.
            /// </summary>
            internal string Text
            {
                get
                {
                    return _text;
                }
            }

            /// <summary>
            /// The name of this memento.  This is seen as the operation that
            /// triggered the need for the memento.
            /// </summary>
            string IMemento.Name
            {
                get
                {
                    return _name;
                }
            }
        }

        // End of Inner class Memento
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Private data of the Memento_TextObject class.

        /// <summary>
        /// The text that can change in this Memento_TextObject class.
        /// </summary>
        string _text;

        // End private data of the Memento_TextObject class.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


        /// <summary>
        /// Constructs a text object with an initial string.
        /// </summary>
        /// <param name="text">The initial string for the text object.</param>
        public Memento_TextObject(string text)
        {
            _text = text;
        }

        /// <summary>
        /// Gets or sets the text in this TextObject.
        /// </summary>
        public string Text
        {
            get
            {
                return _text;
            }
            set
            {
                _text = value;
            }
        }

        /// <summary>
        /// Returns an IMemento object containing a snapshot of the text
        /// stored in this class instance.
        /// </summary>
        public IMemento GetMemento(string operationName)
        {
            return new Memento(operationName, _text);
        }


        /// <summary>
        /// Sets the text in this class instance to the snapshot stored in the
        /// given IMemento object (which is assumed to be from this class).
        /// </summary>
        /// <param name="memento">The IMemento object to restore to.</param>
        public void RestoreMemento(IMemento memento)
        {
            _text = ((Memento)memento).Text;
        }


        /// <summary>
        /// Converts the Memento_TextObject to a string (makes it easier to
        /// use the class in string formatting).
        /// </summary>
        /// <returns>Returns the text stored in the text object.</returns>
        public override string ToString()
        {
            return _text;
        }
    }
}
