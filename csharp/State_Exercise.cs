/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.State_Exercise "State_Exercise"
/// class used in the @ref state_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref state_pattern in C#.
    /// 
    /// The State pattern alters the behavior of the class hierarchy based
    /// on some state.  This is the basis of a Finite State Machine.
    /// 
    /// In this exercise, the State class is a filter that parses text to
    /// remove C++-style line and block comments.  It needs to be smart
    /// enough to ignore comment characters inside quotes.
    /// 
    /// The filtering process starts with creating the context that drives
    /// the state machine.  Internal classes are provided for each state.
    /// </summary>
    internal class State_Exercise
    {

        /// <summary>
        /// Helper method to display text from the State exercise.  Text is
        /// displayed with line numbers.
        /// </summary>
        /// <param name="textToDisplay">Text to display.</param>
        void _State_DisplayText(string textToDisplay)
        {
            string[] lines = textToDisplay.Split('\n');
            int lineNumber = 1;
            foreach (string line in lines)
            {
                Console.WriteLine("    {0,2}) {1}", lineNumber, line);
                ++lineNumber;
            }
        }

        /// <summary>
        /// Executes the example for the @ref state_pattern in C#.
        /// </summary>
        // ! [Using State in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("State Exercise");

            StateContext_Class filterContext = new StateContext_Class();
            string textToFilter =
                "/*####################  Block Comment  #################################*/\n" +
                "//####################  Line Comment  ####################################\n" +
                "// A comment.  /* A nested comment */\n" +
                "\n" +
                "void State_Exercise() // An exercise in state machines\n" +
                "{\n" +
                "    char character = '\\\"';\n" +
                "    Console.WriteLine();\n" +
                "    Console.WriteLine(\"\\\"State\\\" /*Exercise*/\");\n" +
                "\n" +
                "    StateContext_Class filterContext = new StateContext_Class();\n" +
                "\n" +
                "    Console.WriteLine(\"\\t\\tDone. //(No, really)//\");\n" +
                "}";

            Console.WriteLine("  Text to filter:");
            _State_DisplayText(textToFilter);

            Console.WriteLine("  Filtering text...");
            string filteredText = filterContext.RemoveComments(textToFilter);

            Console.WriteLine("  Filtered text:");
            _State_DisplayText(filteredText);

            Console.WriteLine("  Done.");
        }
        // ! [Using State in C#]
    }
}
