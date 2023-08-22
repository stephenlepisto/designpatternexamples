/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Memento_Exercise "Memento_Exercise"
/// class used in the @ref memento_pattern.

using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref memento_pattern in C#.
    /// 
    /// In this exercise, the Memento pattern is used to take snapshots of
    /// a text object so as to form an undo list of changes to the text
    /// object.  Undoing an operation means restoring a snapshot of the
    /// text object.
    /// 
    /// The undo list is implemented as a stack of memento objects that
    /// each represent a snapshot of the text object taken before each
    /// operation is applied.  After all operations are applied, the
    /// mementos are used to restore the text object in reverse order,
    /// effectively undoing each operation in turn.
    /// 
    /// Compare this to the Command_Exercise() and note that the steps
    /// taken there are identical to here (except for method names, of
    /// course).  The difference lies in how operations are executed
    /// and undone.  Mementos make the undo process much cleaner and
    /// faster since operations do not need to be applied repeatedly to
    /// get the text object into a specific state.  Specifically,
    /// compare Command_Undo() with Memento_Undo().  Also note the
    /// differences in the "Memento_ApplyXXOperation()" methods, which
    /// more cleanly separate the save from the operation.
    /// </summary>
    internal class Memento_Exercise
    {

        /// <summary>
        /// The list of memento objects that form a series of snapshots in time
        /// of a Memento_TextObject.
        /// </summary>
        Stack<IMemento> _mementoUndoList = new Stack<IMemento>();

        /// <summary>
        /// Take a snapshot of the given text object associated with the name of
        /// given operation.
        /// </summary>
        /// <param name="text">The Memento_TextObject to take a snapshot of.</param>
        /// <param name="operation">A string describing the operation that will
        /// be applied after the snapshot is taken.</param>
        void Memento_SaveForUndo(Memento_TextObject text, string operation)
        {
            IMemento memento = text.GetMemento(operation);
            _mementoUndoList.Push(memento);
        }


        /// <summary>
        /// An operation to search and replace text in a Memento_TextObject.
        /// </summary>
        /// <param name="source">The Memento_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Memento_Operation_Replace(Memento_TextObject source, string searchPattern, string replaceText)
        {
            source.Text = source.Text.Replace(searchPattern, replaceText);
        }

        /// <summary>
        /// An operation to reverse the characters in the given Memento_TextObject.
        /// </summary>
        /// <param name="source">The Memento_TextObject to affect.</param>
        void Memento_Operation_Reverse(Memento_TextObject source)
        {
            StringBuilder output = new StringBuilder();
            string text = source.Text;
            for (int index = 0; index < text.Length; ++index)
            {
                output.Append(text[text.Length - 1 - index]);
            }
            source.Text = output.ToString();
        }

        /// <summary>
        /// Perform an undo on the given Command_TextObject, using the mementos in the
        /// "global" undo list.  If the undo list is empty, nothing happens.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Memento_Undo(Memento_TextObject text)
        {
            if (_mementoUndoList.Count > 0)
            {
                IMemento lastMemento = _mementoUndoList.Pop();
                text.RestoreMemento(lastMemento);

                // Show off what we (un)did.
                Console.WriteLine("    undoing operation {0,-31}: \"{1}\"", lastMemento.Name, text);
            }
        }

        /// <summary>
        /// Helper function to replace a pattern with another string in the
        /// given Memento_TextObject after adding a snapshot of the text
        /// object to the undo list.  Finally, it shows off what was done.
        /// </summary>
        /// <param name="text">The Memento_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Memento_ApplyReplaceOperation(Memento_TextObject text, string searchPattern, string replaceText)
        {
            string operationName = String.Format("Replace '{0}' with '{1}'", searchPattern, replaceText);
            Memento_SaveForUndo(text, operationName);
            Memento_Operation_Replace(text, searchPattern, replaceText);
            Console.WriteLine("    operation {0,-31}: \"{1}\"", operationName, text);
        }


        /// <summary>
        /// Helper function to reverse the order of the characters in the
        /// given Memento_TextObject after adding a snapshot of the text
        /// object to an undo list.  Finally, it shows what was done.
        /// </summary>
        /// <param name="text">The Memento_TextObject to affect.</param>
        void Memento_ApplyReverseOperation(Memento_TextObject text)
        {
            string operationName = "Reverse";
            Memento_SaveForUndo(text, operationName);
            Memento_Operation_Reverse(text);
            Console.WriteLine("    operation {0,-31}: \"{1}\"", operationName, text);
        }

        /// <summary>
        /// Executes the example for the @ref memento_pattern in C#.
        /// </summary>
        // ! [Using Memento in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Memento Exercise");

            // Start with a fresh undo list.
            _mementoUndoList.Clear();

            // The base text object to work from.
            Memento_TextObject text = new Memento_TextObject("This is a line of text on which to experiment.");

            Console.WriteLine("  Starting text: \"{0}\"", text);

            // Apply four operations to the text.
            Memento_ApplyReplaceOperation(text, "text", "painting");
            Memento_ApplyReplaceOperation(text, "on", "off");
            Memento_ApplyReverseOperation(text);
            Memento_ApplyReplaceOperation(text, "i", "!");

            Console.WriteLine("  Now perform undo until back to original");

            // Now undo the four operations.
            Memento_Undo(text);
            Memento_Undo(text);
            Memento_Undo(text);
            Memento_Undo(text);

            Console.WriteLine("  Final text   : \"{0}\"", text);

            Console.WriteLine("  Done.");
        }
        // ! [Using Memento in C#]
    }
}
