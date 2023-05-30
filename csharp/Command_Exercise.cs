/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Command_Exercise "Command_Exercise"
/// class used in the @ref command_pattern.

using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref command_pattern in C#.
    /// 
    /// The Command pattern is used to encapsulate an operation or command
    /// associated with an object so that the command can be applied to
    /// the object at a later time.
    /// 
    /// In this exercise, an undo list is implemented using Commands that
    /// associate commands defined in this file with a text object.  The
    /// commands are applied to the text object in succession then
    /// effectively undone.
    /// </summary>
    internal class Command_Exercise
    {

        /// <summary>
        /// The list of commands applied.
        /// </summary>
        Stack<Command> _commandUndoList;

        /// <summary>
        /// Save the given command on the undo list then execute the command on
        /// the given text object.
        /// </summary>
        /// <param name="text">The Command_TextObject on which to apply the command.</param>
        /// <param name="command">The Command object to apply to the text object.</param>
        void Command_Save_And_Execute(Command_TextObject text, Command command)
        {
            _commandUndoList.Push(command);
            command.Execute();
        }

        /// <summary>
        /// An operation to search and replace text in a Command_TextObject.
        /// </summary>
        /// <param name="source">The Command_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Command_Operation_Replace(Command_TextObject source, string searchPattern, string replaceText)
        {
            source.Text = source.Text.Replace(searchPattern, replaceText);
        }

        /// <summary>
        /// An operation to reverse the characters in the given Command_TextObject.
        /// </summary>
        /// <param name="source">The Command_TextObject to affect.</param>
        void Command_Operation_Reverse(Command_TextObject source)
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
        /// Perform an undo on the given Command_TextObject, using the commands in the
        /// "global" undo list.  If the undo list is empty, nothing happens.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Command_Undo(Command_TextObject text)
        {
            if (_commandUndoList.Count > 0)
            {
                // Reset the text to the starting point.
                text.Reset();

                // Get rid of the last command applied and remember it.
                Command lastCommand = _commandUndoList.Pop();

                // Now apply all remaining commands to the text in order.
                foreach (Command command in _commandUndoList)
                {
                    command.Execute();
                }

                // Show off what we (un)did.
                Console.WriteLine("    undoing command {0,-31}: \"{1}\"", lastCommand, text);
            }
        }

        /// <summary>
        /// Helper function to create a Command object that replaces text in the given
        /// Command_TextObject, adds the command to the undo list and then applies the command
        /// to the Command_TextObject.  Finally, it shows off what was done.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Command_ApplyReplaceCommand(Command_TextObject text, string searchPattern, string replaceText)
        {
            Command command = new Command(text, "Replace", Command_Operation_Replace, searchPattern, replaceText);
            Command_Save_And_Execute(text, command);
            Console.WriteLine("    command {0,-31}: \"{1}\"", command, text);
        }


        /// <summary>
        /// Helper function to create a Command object that reverses the order of
        /// the characters in the given Command_TextObject, adds the command to the undo
        /// list and then applies the command to the Command_TextObject.  Finally, it shows
        /// what was done.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Command_ApplyReverseCommand(Command_TextObject text)
        {
            Command command = new Command(text, "Reverse", Command_Operation_Reverse);
            Command_Save_And_Execute(text, command);
            Console.WriteLine("    command {0,-31}: \"{1}\"", command, text);
        }


        /// <summary>
        /// Executes the example for the @ref command_pattern in C#.
        /// </summary>
        // ! [Using Command in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Command Exercise");

            // Start with a fresh undo list.
            _commandUndoList = new Stack<Command>();

            // The base text object to work from.
            Command_TextObject text = new Command_TextObject("This is a line of text on which to experiment.");

            Console.WriteLine("  Starting text: \"{0}\"", text);

            // Apply four operations to the text.
            Command_ApplyReplaceCommand(text, "text", "painting");
            Command_ApplyReplaceCommand(text, "on", "off");
            Command_ApplyReverseCommand(text);
            Command_ApplyReplaceCommand(text, "i", "!");

            Console.WriteLine("  Now perform undo until back to original");

            // Now undo the four operations.
            Command_Undo(text);
            Command_Undo(text);
            Command_Undo(text);
            Command_Undo(text);

            Console.WriteLine("  Final text   : \"{0}\"", text);

            Console.WriteLine("  Done.");
        }
        // ! [Using Command in C#]
    }
}
