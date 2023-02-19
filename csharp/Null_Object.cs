// The Null Object pattern is used in those places where a default object of
// some kind is needed to do nothing.  A Null (or Default) Object is an actual
// object that can be called on but does not do anything.  This is not the
// same thing as a null reference or pointer, which represents an
// uninitialized variable.
//
// A Null Object works only in those places where abstract classes or
// interfaces are used to represent all objects of a particular kind.  One of
// those kinds can be a Null Object.  So if you have an interface that
// represents commands that can be applied to a picture, it may be useful to
// create a command that does nothing (in assembly language parlance, a NOP or
// No Operation).
//
// The concept of a "do nothing" object can be extended to functions,
// typically in situations where pointers to the functions (or delegates) are
// stored in dynamic lists to be executed in order.  A function that fits in
// the list but otherwise does nothing when called is a Null Object (in this
// case, the function is treated as an object).
//
// During initial development of such a system, it is often quite useful to
// have a Null Object in place.  Such objects are easy to implement so no bugs
// are likely to be present.  Then the rest of the system that actually works
// with the commands can be created, using the Null Object as a stand-in for
// real commands.
//
// An explicit class representing a Null Object is not always needed.  A class
// that does something could be designed to do nothing if created in a certain
// way or a flag is set (or cleared) on the class instance.  The idea is there
// is an object that does nothing but acts as a stand-in for a real object
// that does do something.
//
// For one example, the Bridge pattern example has a Bridge_NullLogger class
// that represents a logger that does nothing.  This is a classic case of a
// null object.  See Bridge_NullLogger.cs.
//
// The somewhat contrived example here parses a string for single letter move
// commands, converting them into class objects for each command.  For all
// other characters in the string, a null object is used to represent the move
// command.  Bad commands are not simply ignored so as to allow for showing
// them along with the command class assigned to execute the command.
//
// This example also uses a form of the Command pattern and the Interpreter
// pattern.

using System;
using System.Collections.Generic;

namespace DesignPatternExamples
{
    /// <summary>
    /// Base class that represents a move command.  A move command has a name
    /// and the command character that represents the command in the initial
    /// string of movement commands.
    /// 
    /// Yes, this is a variation of the Command pattern.
    /// 
    /// In this example, a move command, when executed, prints "move xxx" on
    /// the current line.  When displayed, the move command shows the command
    /// character followed by the name of the command.
    /// </summary>
    public abstract class MoveCommand
    {
        /// <summary>
        /// Name of the command (assigned in the class constructor).
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// The command character from the original list of commands.
        /// Used when displaying the commands as opposed to when executing
        /// the commands (assigned in the class constructor).
        /// </summary>
        public string Command { get; private set; }


        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="command">The character that represents the command in the original move list.</param>
        /// <param name="commandName">The name of the command (for display purposes).</param>
        public MoveCommand(string command, string commandName)
        {
            Command = command;
            Name = commandName;
        }


        /// <summary>
        /// Display the move command and its name followed by a newline.
        /// </summary>
        public void Show()
        {
            Console.WriteLine("    '{0}' -> {1}", Command, Name);
        }


        /// <summary>
        /// Execute the command.  Derived classes must implement this.
        /// </summary>
        public abstract void Execute();
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Left command.
    /// </summary>
    class MoveCommandLeft : MoveCommand
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        public MoveCommandLeft(string command) : base(command, "Left")
        {
        }


        /// <summary>
        /// Executes the move left command.
        /// </summary>
        public override void Execute()
        {
            Console.Write("move left");
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Right command.
    /// </summary>
    class MoveCommandRight : MoveCommand
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        public MoveCommandRight(string command) : base(command, "Right")
        {
        }


        /// <summary>
        /// Executes the move right command.
        /// </summary>
        public override void Execute()
        {
            Console.Write("move right");
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Up command.
    /// </summary>
    class MoveCommandUp : MoveCommand
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        public MoveCommandUp(string command) : base(command, "Up")
        {
        }


        /// <summary>
        /// Executes the move up command.
        /// </summary>
        public override void Execute()
        {
            Console.Write("move up");
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Down command.
    /// </summary>
    class MoveCommandDown : MoveCommand
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        public MoveCommandDown(string command) : base(command, "Down")
        {
        }


        /// <summary>
        /// Executes the move down command.
        /// </summary>
        public override void Execute()
        {
            Console.Write("move down");
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Do Nothing command.  This is the Null Object for this
    /// exercise.
    /// </summary>
    class MoveCommandNone : MoveCommand
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        public MoveCommandNone(string command) : base(command, "None")
        {
        }


        /// <summary>
        /// Does nothing when executed (this is the Null Object, after all).
        /// </summary>
        public override void Execute()
        {
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the processor that translates the move list into a list of
    /// MoveCommand objects then either displays them or executes them.
    /// 
    /// This classes uses a parser to convert the single letter characters in
    /// a string into a list of actions (instances of the MoveCommand).  This
    /// list of actions is then executed to perform the operations.
    /// 
    /// This process of executing the list of operations is an example of the
    /// Command pattern.  However, this can also be considered an example of
    /// the Interpreter pattern, where the actions are the tokens to be
    /// interpreted.
    /// </summary>
    public class MoveProcessor
    {
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Private methods.

        /// <summary>
        /// Helper method to convert a list of single letter commands into a
        /// list of MoveCommand objects.  This method recognizes 'L', 'R',
        /// 'U', and 'D' (case-insensitive).  All other characters default to
        /// the "Do Nothing" command.
        /// </summary>
        /// <param name="moveList">A string containing a list of single letter
        /// commands to be parsed.</param>
        /// <returns>Returns a list of MoveCommand objects.</returns>
        private List<MoveCommand> _ParseMoves(string moveList)
        {
            List<MoveCommand> commands = new List<MoveCommand>();
            foreach (char command in moveList)
            {
                string testCommand = command.ToString().ToUpper();
                MoveCommand moveCommand = null;

                switch (testCommand)
                {
                    case "U":
                        moveCommand = new MoveCommandUp(command.ToString());
                        break;

                    case "D":
                        moveCommand = new MoveCommandDown(command.ToString());
                        break;

                    case "L":
                        moveCommand = new MoveCommandLeft(command.ToString());
                        break;

                    case "R":
                        moveCommand = new MoveCommandRight(command.ToString());
                        break;

                    default:
                        // Everything else is a "do nothing" command.
                        moveCommand = new MoveCommandNone(command.ToString());
                        break;
                }
                commands.Add(moveCommand);
            }

            return commands;
        }


        /// <summary>
        /// Helper method to execute all the given commands.
        /// </summary>
        /// <param name="commands">A list of MoveCommand objects to "execute".</param>
        /// <remarks>
        /// In this implementation, the MoveCommand prints the command as
        /// "move xxx" on the current line, followed by a single space.  When
        /// all commands have been printed, a new line is printed to move to
        /// the next line.  The "Do Nothing" command doesn't print anything
        /// but the intervening space is still printed.  This means the "Do
        /// Nothing" command shows up in the output as a double space.
        /// </remarks>
        private void _ExecuteMoves(List<MoveCommand> commands)
        {
            foreach(MoveCommand command in commands)
            {
                command.Execute();
                Console.Write(" ");
            }
            Console.WriteLine();
        }


        /// <summary>
        /// Display the command character and name of the command for each
        /// command in the given list of commands.
        /// </summary>
        /// <param name="commands">The list of MoveCommand objects to display.</param>
        private void _ShowMoves(List<MoveCommand> commands)
        {
            foreach(MoveCommand command in commands)
            {
                command.Show();
            }
        }

        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Public methods.

        /// <summary>
        /// Parse and execute the given list of move commands, where each
        /// command is represents by a single character.  Recognizes 'U', 'D',
        /// 'L', and 'R' (case-insensitive).  All other characters are
        /// assigned a "Do Nothing" command.
        /// </summary>
        /// <param name="moveList">A string of characters to parse and execute.</param>
        public void ExecuteMoveList(string moveList)
        {
            List<MoveCommand> commands = _ParseMoves(moveList);
            _ExecuteMoves(commands);
        }


        /// <summary>
        /// Parse and display the given list of move commands, where each
        /// command is represents by a single character.  Recognizes 'U', 'D',
        /// 'L', and 'R' (case-insensitive).  All other characters are
        /// assigned a "Do Nothing" command.
        /// </summary>
        /// <param name="moveList">A string of characters to parse and display.</param>
        public void ShowMoveList(string moveList)
        {
            List<MoveCommand> commands = _ParseMoves(moveList);
            _ShowMoves(commands);
        }
    }
}
