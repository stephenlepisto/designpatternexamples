/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Memento_TextObject "Memento_TextObject"
/// class used in the @ref memento_pattern "Memento pattern".

namespace DesignPatternExamples_csharp
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
