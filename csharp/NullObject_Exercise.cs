/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.NullObject_Exercise "NullObject_Exercise"
/// class used in the @ref nullobject_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref nullobject_pattern in C#.
    /// 
    /// The Null Object pattern is where an object or function acts as a
    /// stand-in for real commands but otherwise does nothing.
    /// 
    /// In this exercise, movement commands are presented as characters in
    /// a string, with the characters 'u', 'd', 'l', and 'r' representing
    /// the moves "up", "down", "left", and "right", respectively.  To
    /// keep the processing of this string simple, all other characters in
    /// the string are assigned a Null Object ("Do Nothing") version of
    /// the move command.
    /// 
    /// This example displays the commands after parsing and then
    /// "executes" commands, which consists of printing the commands out.
    /// 
    /// This example highlights the Null Object pattern while utilizing
    /// the Command and Interpreter patterns.
    /// </summary>
    internal class NullObject_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref nullobject_pattern in C#.
        /// </summary>
        // ! [Using NullObject in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Null Object Exercise");

            MoveProcessor moveProcessor = new MoveProcessor();

            // A stream of recognized and unrecognized move commands.  The
            // unrecognized commands do nothing.
            string moveString = "ur#ld!lr";
            Console.WriteLine("  Showing the move commands:");
            moveProcessor.ShowMoveList(moveString);

            Console.WriteLine("  Executing the move commands:");
            Console.Write("    {0} -> ", moveString);
            moveProcessor.ExecuteMoveList(moveString);

            Console.WriteLine("  Done.");
        }
        // ! [Using NullObject in C#]
    }
}
