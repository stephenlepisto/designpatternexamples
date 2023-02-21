﻿// The State pattern is used when a finite state machine needs to be expressed
// in an object-oriented form.
//
// A finite state machine is something that changes its behavior based on its
// state.  It is a way to isolate specific behaviors from each other so that
// changes in one behavior doesn't affect other behaviors.  There is also a
// performance benefit in that only a minimum amount of code is executed at
// any given time for any given state.
//
// Here is a simple state machine, written in C:
//
// /* Describes the current state of the state machine. */
// enum CurrentState
// {
//     InitState,  /* Always transitions to State1 */
//     State1,     /* Can transition to State1 or State2 */
//     State2,     /* Can transition to State1 or EndState */
//     EndState    /* Exit condition and transitions to InitState */
// };
//
// /*
//    Execute one step of the state machine, returning 1 if more state
//    needs to be executed; otherwise, returns 0 if processing is done
// */
// int ProcessData(CurrentState* pState, void* pData)
// {
//     int continueProcessing = 1;
//
//     switch (*pState):
//     {
//         case InitState:
//             DoInitialize(pData);
//             *pState = State1;
//             break;
//
//         case State1:
//             *pState = DoState1();
//             break;
//
//         case State2:
//             *pState = DoState2();
//             break;
//
//         case EndState:
//             DoEndState();
//             continueProcessing = 0;
//             *pState = InitState;
//             break;
//     }
//     return continueProcessing;
// }
//
// /* Execute the state machine on the given data, returning when done. */
// void ExecuteStateMachine(void *pData)
// {
//     CurrentState state = InitState;
//     while (ProcessData(&state, pData) != 0)
//     {
//     }
// }
//
// For the above example, the details of DoInitialize(), DoState1(), DoState2()
// and DoEndState() don't matter except that DoState1() and DoState2() can
// change the state depending on some internal decision-making process.
// However, the overall flow should be clear that only one function is called
// for any given state.
//
// The State design pattern describes a way to convert the above functional
// definition into an object-oriented one.
//
// The CurrentState enumeration and the functions that do stuff for each state
// are encapsulated into classes.  These state classes derive from a common
// base class or interface.  The ProcessData() function is encapsulated in a
// context class that is passed to each state class (so the state class can
// operate on the data in the context).  The driving force (that is, whatever
// makes the call to the state machine) is typically from outside the context
// class and will tend to look a lot like the ExecuteStateMachine() function
// in the above example, although the driving force could be anything from a
// timer to the user clicking a button.
//
// As the state changes in the context class, a pointer to the current state
// class instance is changed to the next state class instance (as opposed to
// changing a simple integer or enumeration).  There are two basic ways in
// which the state is changed:
//   1) each state class knows what the next state class needs to be and
//      returns an instance of that class
//   2) The context maintains a dictionary of the state class instances and
//      uses an enumeration such as CurrentState to look up the next state
//      instance to use.  Each state class then returns a value from the
//      CurrentState to set the next state.
// The second approach is better so that only one entity (the context class)
// knows about the instances of the state classes.
//
//
// The demonstration example parses a block of C++ or C# code to remove all
// comments.  It ignores comments inside of quotes.  The context maintains an
// iterator through the text and an accumulator of comment-free text.  The
// context also maintains the current state.  The changes in state are
// displayed along the way.
//
// This example also demonstrates a parser that does not use a look-ahead
// approach, in which the next character coming is peeked at to determine
// which state should be next.  The look-ahead can potentially simplify the
// number of states needed but the example would get quite messy with
// potentially multiple if statements for each state change.
//
// Note: This example highlights one problem of an object-oriented approach
// to a state machine and that is the sheer number of small classes that need
// to be managed.  You either get many classes in a single file or many files
// each with a small class.

using System;
using System.Collections.Generic;
using System.Text;


namespace DesignPatternExamples
{
    /// <summary>
    /// Represents the current state of the state machine.
    /// </summary>
    enum CurrentState
    {
        Initial,                // State before the state machine actually starts.  transitions to NormalText
        NormalText,             // " transitions to QuotedText, / transitions to StartComment, EOF transitions to Done
        DoubleQuotedText,       // \ transitions to EscapedDoubleQuoteText, " transitions to NormalText, EOF transitions to Done
        SingleQuotedText,       // ' transitions to EscapedSingleQuoteText, \ transitions to NormalText, EOF transitions to Done
        EscapedDoubleQuoteText, // \ transitions to QuotedText, EOF transitions to Done
        EscapedSingleQuoteText, // \ transitions to SingleQuotedText, EOF transitions to Done
        StartComment,           // / transitions to LineComment, * transitions to BlockComment, EOF transitions to Done, all else transitions to NormalText
        LineComment,            // \n transitions to NormalText, EOF transitions to Done
        BlockComment,           // * transitions to EndBlockComment, EOF transitions to Done
        EndBlockComment,        // / transitions to NormalText, EOF transitions to Done, all else transitions to BlockComment
        Done                    // Indicates processing is done
    }


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Interface definitions
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /// <summary>
    /// Represents constants used in the State machine.  This is needed in a
    /// separate class because 1) C# requires constants to be defined inside a
    /// class or struct and 2) the constant is needed across multiple classes.
    /// 
    /// In this case, only EOF is needed.
    /// </summary>
    internal class State_Constants
    {
        /// <summary>
        /// Indicates End-of-file (no more data available).
        /// </summary>
        public const char EOF = (char)0xff;
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the context as passed to each state class.
    /// 
    /// Each state class can access the next character or output the current
    /// character through this interface.
    /// </summary>
    internal interface IStateContext
    {
        /// <summary>
        /// Get the next character from the input.
        /// </summary>
        /// <returns>Returns the next character.  Returns State_Constants.EOF
        /// if there is no more input.</returns>
        char GetNextCharacter();

        /// <summary>
        /// Write the character to the context.  This is how the parser
        /// accumulates the filtered text.
        /// </summary>
        /// <param name="character">The character to accumulate</param>
        void OutputCharacter(char character);
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a class that implements one state of the state machine.
    /// 
    /// The context calls each state through this interface.
    /// </summary>
    /// <remarks>
    /// Technically, the StateContext_Class knows about the actual state
    /// classes because it has to instantiate them but this interface makes
    /// the code for calling the state classes much simpler.
    /// </remarks>
    internal interface IStateBehavior
    {
        CurrentState GoNext(IStateContext context);
    }


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State class definitions
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    /// <summary>
    /// Represents normal text behavior.
    /// 
    /// Transitions to the following states for the seen input:
    /// "   - go to CurrentState.DoubleQuotedText (start of a double-quoted string)
    /// '   - go to CurrentState.SingleQuotedText (start of a single-quoted string)
    /// /   - go to CurrentState.StartComment (start of a line or block comment)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_NormalText : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.NormalText;
            char character = context.GetNextCharacter();

            switch(character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '"':
                    context.OutputCharacter(character);
                    nextState = CurrentState.DoubleQuotedText;
                    break;

                case '\'':
                    context.OutputCharacter(character);
                    nextState = CurrentState.SingleQuotedText;
                    break;

                case '/':
                    nextState = CurrentState.StartComment;
                    break;

                default:
                    context.OutputCharacter(character);
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being inside a double-quote string where filtering is
    /// essentially turned off until the end of the string is reached.
    /// 
    /// Transitions to the following states for the seen input:
    /// "   - go to CurrentState.NormalText (end of a double-quoted string)
    /// \   - go to CurrentState.EscapedDoubleQuoteText (start of an escaped character)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_DoubleQuotedText : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.DoubleQuotedText;

            char character = context.GetNextCharacter();

            switch(character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '"':
                    context.OutputCharacter(character);
                    nextState = CurrentState.NormalText;
                    break;

                case '\\':
                    context.OutputCharacter(character);
                    nextState = CurrentState.EscapedDoubleQuoteText;
                    break;

                default:
                    context.OutputCharacter(character);
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being inside a single-quoted string where filtering is
    /// effectively turned off until the end of the string is reached.
    /// 
    /// Transitions to the following states for the seen input:
    /// '   - go to CurrentState.NormalText (end of a single-quoted string)
    /// \   - go to CurrentState.EscapedSingleQuoteText (start of an escaped character)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_SingleQuotedText : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.DoubleQuotedText;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '\'':
                    context.OutputCharacter(character);
                    nextState = CurrentState.NormalText;
                    break;

                case '\\':
                    context.OutputCharacter(character);
                    nextState = CurrentState.EscapedSingleQuoteText;
                    break;

                default:
                    context.OutputCharacter(character);
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in an escaped character sequence inside a double-
    /// quoted string.  We don't do anything with the escaped character other
    /// than output it.  Handling escaped characters allows us to more
    /// accurately detect the end of the string.
    /// 
    /// Transitions to the following states for the seen input:
    /// {ANY} - go to CurrentState.DoubleQuotedText (end of escape sequence)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_EscapedDoubleQuoteText : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.DoubleQuotedText;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                default:
                    context.OutputCharacter(character);
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in an escaped character sequence inside a single-
    /// quoted string.  We don't do anything with the escaped character other
    /// than output it.  Handling escaped characters allows us to more
    /// accurately detect the end of the string.
    /// 
    /// Transitions to the following states for the seen input:
    /// {ANY} - go to CurrentState.SingleQuotedText (end of escape sequence)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_EscapedSingleQuoteText : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.SingleQuotedText;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                default:
                    context.OutputCharacter(character);
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the possible start of a line or block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// /   - go to CurrentState.LineComment (start of a line comment)
    /// *   - go to CurrentState.BlockComment (start of a block comment)
    /// {ANY} - go to CurrentState.NormalText (not start of a comment)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_StartComment : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.StartComment;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '/':
                    nextState = CurrentState.LineComment;
                    break;

                case '*':
                    nextState = CurrentState.BlockComment;
                    break;

                default:
                    // Not the start of a comment so output the leading slash
                    // that led to the state followed by the character we just
                    // processed.
                    context.OutputCharacter('/');
                    context.OutputCharacter(character);
                    nextState = CurrentState.NormalText;
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in a line comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// \n  - go to CurrentState.NormalText (a newline is the end of a line comment)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_LineComment : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.LineComment;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '\n':
                    context.OutputCharacter(character);
                    nextState = CurrentState.NormalText;
                    break;

                default:
                    // We are in a comment to be removed, so do nothing here.
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in a block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// *  - go to CurrentState.EndBlockComment (possible end of block comment)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_BlockComment : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.BlockComment;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '*':
                    context.OutputCharacter(character);
                    nextState = CurrentState.EndBlockComment;
                    break;

                default:
                    // We are in a comment to be removed, so do nothing here.
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents possibly being at the end of a block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// /  - go to CurrentState.NormalText (found end of block comment)
    /// {ANY} - go to CurrentState.BlockComment (still in block comment)
    /// EOF - go to CurrentState.Done (no more input)
    /// </summary>
    internal class State_EndBlockComment : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            CurrentState nextState = CurrentState.BlockComment;

            char character = context.GetNextCharacter();

            switch (character)
            {
                case State_Constants.EOF:
                    nextState = CurrentState.Done;
                    break;

                case '/':
                    nextState = CurrentState.NormalText;
                    break;

                default:
                    // We are still in a block comment to be removed, so do nothing here.
                    break;
            }

            return nextState;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being done with input.
    /// 
    /// Transitions to the following states for the seen input:
    /// Always stay in CurrentState.Done
    /// </summary>
    internal class State_Done : IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState IStateBehavior.GoNext(IStateContext context)
        {
            // Do nothing (Yes!  Another Null Object example!)
            return CurrentState.Done;
        }
    }


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State class factory definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        
    /// <summary>
    /// Class factory for generating the state class instances.
    /// </summary>
    static internal class State_Factory
    {
        /// <summary>
        /// Create an instance of the specified state class.
        /// </summary>
        /// <param name="state">A value from the CurrentState enumeration indicating 
        /// state for which to generate a class instance.</param>
        /// <returns>Returns an IStateBehavior instance for the specified state.</returns>
        static public IStateBehavior CreateState(CurrentState state)
        {
            IStateBehavior stateBehavior = null;
            switch(state)
            {
                case CurrentState.NormalText:
                    stateBehavior = new State_NormalText();
                    break;

                case CurrentState.DoubleQuotedText:
                    stateBehavior = new State_DoubleQuotedText();
                    break;

                case CurrentState.SingleQuotedText:
                    stateBehavior = new State_SingleQuotedText();
                    break;

                case CurrentState.EscapedDoubleQuoteText:
                    stateBehavior = new State_EscapedDoubleQuoteText();
                    break;

                case CurrentState.EscapedSingleQuoteText:
                    stateBehavior = new State_EscapedSingleQuoteText();
                    break;

                case CurrentState.StartComment:
                    stateBehavior = new State_StartComment();
                    break;

                case CurrentState.LineComment:
                    stateBehavior = new State_LineComment();
                    break;

                case CurrentState.BlockComment:
                    stateBehavior = new State_BlockComment();
                    break;

                case CurrentState.EndBlockComment:
                    stateBehavior = new State_EndBlockComment();
                    break;

                case CurrentState.Done:
                    stateBehavior = new State_Done();
                    break;

                default:
                    throw new ApplicationException(string.Format("Unknown state: {0}.  Cannot create a state class.", state));
            }

            return stateBehavior;
        }
    }


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State context definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    /// <summary>
    /// Represents the state machine.  This maintains the context in which the
    /// state machine runs.
    /// </summary>
    /// <remarks>
    /// To use:
    /// <code>
    /// StateContext_Class filterContext = new StateContext_Class();
    /// string filteredText = filterContext.RemoveComments(textToFilter);
    /// </code>
    /// </remarks>
    public class StateContext_Class : IStateContext
    {
        /// <summary>
        /// The text to be filtered.
        /// </summary>
        private string _inputText;

        /// <summary>
        /// Index into the text to be filtered.
        /// </summary>
        private int _textIndex;

        /// <summary>
        /// The results of the filtering.
        /// </summary>
        private StringBuilder _outputText;

        /// <summary>
        /// Maps values from the CurrentState enumeration to instances of the
        /// IStateBehavior representing the behavior for that state.
        /// </summary>
        private Dictionary<CurrentState, IStateBehavior> _stateBehaviors = new Dictionary<CurrentState, IStateBehavior>();

        /// <summary>
        /// The current state of the machine.
        /// </summary>
        private CurrentState _currentState;

        /// <summary>
        /// The current behavior (that is, a reference to the state behavior
        /// class) for the current state.
        /// </summary>
        private IStateBehavior _currentStateBehavior;


        //--------------------------------------------------------------------
        // StateContext_Class implementation.
        //--------------------------------------------------------------------

        /// <summary>
        /// Helper method to transition the state machine to the specified
        /// state.  Does nothing if the new state is the same as the old
        /// state.  Instantiates the state class the first time the state class
        /// is needed.
        /// </summary>
        /// <param name="newState">A value from the CurrentState enumeration indicating
        /// the state to which to transition.</param>
        private void _SetNextState(CurrentState newState)
        {
            if (newState != _currentState)
            {
                if (!_stateBehaviors.ContainsKey(newState))
                {
                    _stateBehaviors[newState] = State_Factory.CreateState(newState);
                }

                Console.WriteLine("    --> State Transition: {0} -> {1}", _currentState, newState);

                _currentStateBehavior = _stateBehaviors[newState];
                _currentState = newState;
            }
        }


        //--------------------------------------------------------------------
        // StateContext_Class public entry points.
        //--------------------------------------------------------------------
            
        /// <summary>
        /// Entry point for callers to filter text.  Removes C++-style line
        /// and block comments from the text.
        /// </summary>
        /// <param name="text">The text to filter.</param>
        /// <returns>Returns the filtered text.</returns>
        public string RemoveComments(string text)
        {
            _inputText = text;
            _textIndex = 0;
            _outputText = new StringBuilder();
            _currentState = CurrentState.Initial;
            _SetNextState(CurrentState.NormalText);

            while (_currentState != CurrentState.Done)
            {
                CurrentState nextState = _currentStateBehavior.GoNext(this);
                _SetNextState(nextState);
            }

            return _outputText.ToString();
        }


        //--------------------------------------------------------------------
        // IStateContext interface implementation.
        //--------------------------------------------------------------------
        // Note: These methods are accessible only through the IStateContext
        // interface so are not directly available on the StateContext_Class
        // instance.

        /// <summary>
        /// Retrieve the next character from the input.
        /// </summary>
        /// <returns>Returns the next character from the input.  Returns
        /// State_Constants.EOF if there is no more input.</returns>
        char IStateContext.GetNextCharacter()
        {
            char character = State_Constants.EOF;

            if (_textIndex < _inputText.Length)
            {
                character = _inputText[_textIndex];
                ++_textIndex;
            }
            return character;
        }

        /// <summary>
        /// Save the character to the accumulation of the filtered text.
        /// </summary>
        /// <param name="character">The character to save.</param>
        void IStateContext.OutputCharacter(char character)
        {
            if (character != State_Constants.EOF)
            {
                _outputText.Append(character);
            }
        }
    }
}