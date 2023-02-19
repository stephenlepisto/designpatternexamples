// The Command pattern is used to associate an object with an operation that
// is deferred to a later time for execution.  The command itself is an object
// that contains the target of the command (known as the receiver) and the
// command.  This means the command object can be treated like any other
// object, even putting it into a list.
//
// A common application for the Command pattern is an undo buffer.  Another
// application is a batch processor.
//
// At its heart, a Command object takes two parameters: The object to work on
// and an operation to use.  The operation is typically a function pointer
// (in C++) or a delegate (in C#).  A Command object can hold additional
// parameters if the associated operation requires additional parameters.
//
// When invoked, the Command object calls the operation with the receiver
// object and whatever additional parameters that might be required.  The
// invocation is typically a single method called execute() so all Command
// objects look the same to the entity doing the invocation of the Commands.
//
// It is typical for the Command objects to be created by one entity and
// passed to another entity for invocation.
//
// For example, a program that supports undo would work like this (this is
// a simplistic undo):
// 1. Define all operations as functions that takes a single receiver (of the
//    command) to operate on, along with any necessary additional parameters.
// 2. Any time an operation other than Undo is invoked by the user:
//    a. Create a Command object with the function for that operation along
//       with the receiver on which the function applies
//    b. Store the Command object in the undo container
//    c. Invoke the Command object just created
// 3. Repeat step 2 until the user selects Undo.
// 4. Perform the Undo:
//    a. If there are any commands to undo then
//    b.   Completely reset the receiver that all commands are applied to
//    c.   Remove the last Command object from the undo container, if any
//    d.   For all Command objects in the undo container, invoke each Command
//         in order on the receiver.  This puts the receiver back into the
//         state it was in before the last command was applied.

using System;

namespace DesignPatternExamples
{
    /// <summary>
    /// Container for a string.  Need to use a class that allows the text to
    /// be changed while the container (this class) remains constant.  This
    /// way, operations can be applied to the text and the container's contents
    /// change but not the container (strings are immutable in C#; this dances
    /// around that problem).
    /// </summary>
    public class Command_TextObject
    {
        // Starting string text so we can reset the text to a known point.
        string _startingText;

        // The text that can change.
        string _text;

        /// <summary>
        /// Constructs a text object with an initial string.
        /// </summary>
        /// <param name="text">The initial string for the text object.</param>
        public Command_TextObject(string text)
        {
            _text = text;
            _startingText = text;
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
        /// Resets the TextObject to the starting string.
        /// </summary>
        public void Reset()
        {
            _text = _startingText;
        }


        /// <summary>
        /// Converts the TextObject to a string.
        /// </summary>
        /// <returns>Returns the text stored in the text object.</returns>
        public override string ToString()
        {
            return _text;
        }
    }


    /// <summary>
    /// Delegate representing an operation applied to a TextObject using two
    /// parameters.
    /// </summary>
    /// <param name="source">TextObject to affect</param>
    /// <param name="argument1">First argument for the operation.</param>
    /// <param name="argument2">Second argument for the operation.</param>
    public delegate void two_parameter_operation(Command_TextObject source, string argument1, string argument2);

    /// <summary>
    /// Delegate representing an operation applied to a TextObject that uses
    /// no additional arguments.
    /// </summary>
    /// <param name="source">TextObject to affect</param>
    public delegate void no_parameter_operation(Command_TextObject source);


    /// <summary>
    /// Represents an operation that can be applied to a TextObject.
    /// This class can handle two kinds of operations, one that takes no
    /// additional parameters and one that takes two additional string
    /// parameters.
    /// </summary>
    /// <remarks>
    /// In a real program, the commands would be represented by an interface
    /// and concrete classes for each type of operation (based on additional
    /// parameters) would be used.  This requires the calling entity to
    /// instantiate the appropriate concrete class as opposed to letting the
    /// C# compiler figure out the correct constructor based on parameters.
    /// Or the calling entity could use a class factory to create the concrete
    /// classes.
    /// 
    /// It is also conceivable to make this Command class general case in
    /// terms of passing in 0 or more arguments along with a delegate that
    /// takes 0 or more arguments.  This complicates the actual calling of the
    /// delegate and obscures some of the functionality here but it would
    /// reduce the API to a single constructor and delegate.  But then it's up
    /// to the user to get the right number of parameters into the command for
    /// the delegate.
    /// </remarks>
    public class Command
    {
        // The receiver of the command.
        Command_TextObject _receiver;

        // Easy-to-read command name.
        string _commandName;

        // Two parameter operation to apply to the receiver.
        two_parameter_operation _two_parameter_operation;

        // No parameter operation to apply to the receiver.
        no_parameter_operation _no_parameter_operation;

        // The first argument to the operation.
        string _argument1;

        // The second argument to the operation.
        string _argument2;

        /// <summary>
        /// Constructor for a command that applies an operation to a TextObject, where the
        /// operation takes two parameters.
        /// </summary>
        /// <param name="source">The TextObject to apply the operation to.</param>
        /// <param name="commandName">Easy-to-read name of the command.</param>
        /// <param name="operation">The operation to apply to the TextObject.</param>
        /// <param name="argument1">First argument to the operation (after the TextObject).</param>
        /// <param name="argument2">Second argument to the operation (after the TextObject).</param>
        public Command(Command_TextObject source, string commandName, two_parameter_operation operation, string argument1, string argument2)
        {
            _receiver = source;
            _commandName = commandName;
            _two_parameter_operation = operation;
            _argument1 = argument1;
            _argument2 = argument2;
        }

        /// <summary>
        /// Constructor for a command that applies an operation to a TextObject but does
        /// not take any additional parameters.
        /// </summary>
        /// <param name="source">The TextObject to apply the operation to.</param>
        /// <param name="commandName">Easy-to-read name of the command.</param>
        /// <param name="operation">The operation to apply to the TextObject.</param>
        public Command(Command_TextObject source, string commandName, no_parameter_operation operation)
        {
            _receiver = source;
            _commandName = commandName;
            _no_parameter_operation = operation;
        }

        /// <summary>
        /// Execute the command on the TextObject.
        /// </summary>
        public void Execute()
        {
            if (_two_parameter_operation != null)
            {
                _two_parameter_operation(_receiver, _argument1, _argument2);
            }
            else // if (_no_parameter_operation != null)
            {
                _no_parameter_operation(_receiver);
            }
        }

        /// <summary>
        /// Convert this command to a string representation.
        /// </summary>
        /// <returns>A string containing the representation of the command.</returns>
        public override string ToString()
        {
            string output = "<NO COMMAND>";
            if (_two_parameter_operation != null)
            {
                output = String.Format("{0} \"{1}\" with \"{2}\"", _commandName, _argument1, _argument2);
            }
            else if (_no_parameter_operation != null)
            {
                output = String.Format("{0}", _commandName);
            }
            return output;
        }
    }
}
