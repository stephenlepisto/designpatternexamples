/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::IStateContext "IStateContext" and
/// @ref DesignPatternExamples_cpp::IStateBehavior "IStateBehavior" interfaces,
/// along with the private implementation of the StateContext_ClassImpl class
/// and the various StateXXX classes used in the @ref state_pattern "State pattern".
/// 
/// The class implementations are in an anonymous namespace in a .cpp file to
/// better hide them from the rest of the program.

#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <stdexcept>
#include <exception>
#include <map>
#include <memory>
#include <sstream>

#include "State_Class.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// Convert the CurrentState enumeration to a string for output purposes.
    /// </summary>
    /// <param name="state">A value from the CurrentState enumeration.</param>
    /// <returns>Returns a string containing the string version of the given
    /// state.</returns>
    std::string _CurrentStateToString(CurrentState state)
    {
        std::string stateAsString;

        switch (state)
        {
        case CurrentState::Initial:
            stateAsString = "Initial";
            break;

        case CurrentState::NormalText:
            stateAsString = "NormalText";
            break;

        case CurrentState::DoubleQuotedText:
            stateAsString = "DoubleQuotedText";
            break;

        case CurrentState::SingleQuotedText:
            stateAsString = "SingleQuotedText";
            break;

        case CurrentState::EscapedDoubleQuoteText:
            stateAsString = "EscapedDoubleQuoteText";
            break;

        case CurrentState::EscapedSingleQuoteText:
            stateAsString = "EscapedSingleQuoteText";
            break;

        case CurrentState::StartComment:
            stateAsString = "StartComment";
            break;

        case CurrentState::LineComment:
            stateAsString = "LineComment";
            break;

        case CurrentState::BlockComment:
            stateAsString = "BlockComment";
            break;

        case CurrentState::EndBlockComment:
            stateAsString = "EndBlockComment";
            break;

        case CurrentState::Done:
            stateAsString = "Done";
            break;

        default:
            stateAsString = std::format("Unknown ({0})", static_cast<int>(state));
            break;
        }


        return stateAsString;
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
    /// "   - go to CurrentState::DoubleQuotedText (start of a double-quoted string)
    /// '   - go to CurrentState::SingleQuotedText (start of a single-quoted string)
    /// /   - go to CurrentState::StartComment (start of a line or block comment)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_NormalText : public IStateBehavior
    {
    public:
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::NormalText;
            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '"':
                context->OutputCharacter(character);
                nextState = CurrentState::DoubleQuotedText;
                break;

            case '\'':
                context->OutputCharacter(character);
                nextState = CurrentState::SingleQuotedText;
                break;

            case '/':
                nextState = CurrentState::StartComment;
                break;

            default:
                context->OutputCharacter(character);
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being inside a double-quote string where filtering is
    /// essentially turned off until the end of the string is reached.
    /// 
    /// Transitions to the following states for the seen input:
    /// "   - go to CurrentState::NormalText (end of a double-quoted string)
    /// \   - go to CurrentState::EscapedDoubleQuoteText (start of an escaped character)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_DoubleQuotedText : public IStateBehavior
    {
    public:
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <param name="context">An IStateContext object representing the context
        /// to use for getting the next character of input and to which to output
        /// characters.</param>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::DoubleQuotedText;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '"':
                context->OutputCharacter(character);
                nextState = CurrentState::NormalText;
                break;

            case '\\':
                context->OutputCharacter(character);
                nextState = CurrentState::EscapedDoubleQuoteText;
                break;

            default:
                context->OutputCharacter(character);
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being inside a single-quoted string where filtering is
    /// effectively turned off until the end of the string is reached.
    /// 
    /// Transitions to the following states for the seen input:
    /// '   - go to CurrentState::NormalText (end of a single-quoted string)
    /// \   - go to CurrentState::EscapedSingleQuoteText (start of an escaped character)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_SingleQuotedText : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::DoubleQuotedText;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '\'':
                context->OutputCharacter(character);
                nextState = CurrentState::NormalText;
                break;

            case '\\':
                context->OutputCharacter(character);
                nextState = CurrentState::EscapedSingleQuoteText;
                break;

            default:
                context->OutputCharacter(character);
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in an escaped character sequence inside a double-
    /// quoted string.  We don't do anything with the escaped character other
    /// than output it.  Handling escaped characters allows us to more
    /// accurately detect the end of the string.
    /// 
    /// Transitions to the following states for the seen input:
    /// {ANY} - go to CurrentState::DoubleQuotedText (end of escape sequence)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_EscapedDoubleQuoteText : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::DoubleQuotedText;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            default:
                context->OutputCharacter(character);
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in an escaped character sequence inside a single-
    /// quoted string.  We don't do anything with the escaped character other
    /// than output it.  Handling escaped characters allows us to more
    /// accurately detect the end of the string.
    /// 
    /// Transitions to the following states for the seen input:
    /// {ANY} - go to CurrentState::SingleQuotedText (end of escape sequence)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_EscapedSingleQuoteText : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::SingleQuotedText;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            default:
                context->OutputCharacter(character);
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the possible start of a line or block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// /   - go to CurrentState::LineComment (start of a line comment)
    /// *   - go to CurrentState::BlockComment (start of a block comment)
    /// {ANY} - go to CurrentState::NormalText (not start of a comment)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_StartComment : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::StartComment;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '/':
                nextState = CurrentState::LineComment;
                break;

            case '*':
                nextState = CurrentState::BlockComment;
                break;

            default:
                // Not the start of a comment so output the leading slash
                // that led to the state followed by the character we just
                // processed.
                context->OutputCharacter('/');
                context->OutputCharacter(character);
                nextState = CurrentState::NormalText;
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in a line comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// \n  - go to CurrentState::NormalText (a newline is the end of a line comment)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_LineComment : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::LineComment;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '\n':
                context->OutputCharacter(character);
                nextState = CurrentState::NormalText;
                break;

            default:
                // We are in a comment to be removed, so do nothing here.
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being in a block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// *  - go to CurrentState::EndBlockComment (possible end of block comment)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_BlockComment : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::BlockComment;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '*':
                context->OutputCharacter(character);
                nextState = CurrentState::EndBlockComment;
                break;

            default:
                // We are in a comment to be removed, so do nothing here.
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents possibly being at the end of a block comment.
    /// 
    /// Transitions to the following states for the seen input:
    /// /  - go to CurrentState::NormalText (found end of block comment)
    /// {ANY} - go to CurrentState::BlockComment (still in block comment)
    /// EOF_CHAR - go to CurrentState::Done (no more input)
    /// </summary>
    class State_EndBlockComment : public IStateBehavior
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
        CurrentState GoNext(IStateContext* context)
        {
            CurrentState nextState = CurrentState::BlockComment;

            char character = context->GetNextCharacter();

            switch (character)
            {
            case EOF_CHAR:
                nextState = CurrentState::Done;
                break;

            case '/':
                nextState = CurrentState::NormalText;
                break;

            default:
                // We are still in a block comment to be removed, so do nothing here.
                break;
            }

            return nextState;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents being done with input.
    /// 
    /// Transitions to the following states for the seen input:
    /// Always stay in CurrentState::Done
    /// </summary>
    class State_Done : public IStateBehavior
    {
        /// <summary>
        /// Process the next character from the context, returning the next
        /// state the context should move to.
        /// </summary>
        /// <returns>Returns a value from the CurrentState enumeration indicating
        /// the next state to which the state machine should transition to.</returns>
        CurrentState GoNext(IStateContext* /*context*/)
        {
            // Do nothing (Yes!  Another Null Object example!)
            return CurrentState::Done;
        }
    };


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State class factory definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    /// <summary>
    /// Class factory for generating the state class instances.
    /// </summary>
    class State_Factory
    {
    public:
        /// <summary>
        /// Create an instance of the specified state class.
        /// </summary>
        /// <param name="state">A value from the CurrentState enumeration indicating 
        /// state for which to generate a class instance.</param>
        /// <returns>Returns an IStateBehavior instance for the specified state.</returns>
        static IStateBehavior::shared_ptr_t CreateState(CurrentState state)
        {
            IStateBehavior::shared_ptr_t stateBehavior;
            switch (state)
            {
            case CurrentState::NormalText:
                stateBehavior = std::make_shared<State_NormalText>();
                break;

            case CurrentState::DoubleQuotedText:
                stateBehavior = std::make_shared<State_DoubleQuotedText>();
                break;

            case CurrentState::SingleQuotedText:
                stateBehavior = std::make_shared<State_SingleQuotedText>();
                break;

            case CurrentState::EscapedDoubleQuoteText:
                stateBehavior = std::make_shared<State_EscapedDoubleQuoteText>();
                break;

            case CurrentState::EscapedSingleQuoteText:
                stateBehavior = std::make_shared<State_EscapedSingleQuoteText>();
                break;

            case CurrentState::StartComment:
                stateBehavior = std::make_shared<State_StartComment>();
                break;

            case CurrentState::LineComment:
                stateBehavior = std::make_shared<State_LineComment>();
                break;

            case CurrentState::BlockComment:
                stateBehavior = std::make_shared<State_BlockComment>();
                break;

            case CurrentState::EndBlockComment:
                stateBehavior = std::make_shared<State_EndBlockComment>();
                break;

            case CurrentState::Done:
                stateBehavior = std::make_shared<State_Done>();
                break;

            default:
            {
                std::string msg = std::format("Unknown state: {0}.  Cannot create a state class.",
                    _CurrentStateToString(state));
                throw std::exception(msg.c_str());
            }
            }

            return stateBehavior;
        }
    };


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State Context implementation class definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    /// <summary>
    /// Implementation of the state machine.  This maintains the context in
    /// which the state machine runs.  This is in the anonymous namespace as
    /// its inner workings are private.
    /// </summary>
    /// <remarks>
    /// Intended to be called only from the StateContext_Class class.
    /// </remarks>
    class StateContext_ClassImpl : public IStateContext
    {
    private:
        /// <summary>
        /// The text to be filtered.
        /// </summary>
        std::string _inputText;

        /// <summary>
        /// Index into the text to be filtered.
        /// </summary>
        size_t _textIndex;

        /// <summary>
        /// The results of the filtering.
        /// </summary>
        std::ostringstream _outputText;

        using StateMapping = std::map<CurrentState, IStateBehavior::shared_ptr_t>;

        /// <summary>
        /// Maps values from the CurrentState enumeration to instances of the
        /// IStateBehavior representing the behavior for that state.
        /// </summary>
        StateMapping _stateBehaviors;

        /// <summary>
        /// The current state of the machine.
        /// </summary>
        CurrentState _currentState;

        /// <summary>
        /// The current behavior (that is, a reference to the state behavior
        /// class) for the current state.
        /// </summary>
        IStateBehavior::shared_ptr_t _currentStateBehavior;


    private:
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
        void _SetNextState(CurrentState newState)

        {
            if (newState != _currentState)
            {
                StateMapping::const_iterator foundIter = _stateBehaviors.find(newState);

                if (foundIter == std::cend(_stateBehaviors))
                {
                    _stateBehaviors[newState] = State_Factory::CreateState(newState);
                }

                std::cout
                    << std::format("    --> State Transition: {0} -> {1}",
                        _CurrentStateToString(_currentState), _CurrentStateToString(newState))
                    << std::endl;

                _currentStateBehavior = _stateBehaviors[newState];
                _currentState = newState;
            }
        }


    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        StateContext_ClassImpl()
            : _textIndex(0)
            , _currentState(CurrentState::Initial)
        {
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
        std::string RemoveComments(std::string text)
        {
            _inputText = text;
            _textIndex = 0;
            _outputText.str("");
            _outputText.clear();
            _currentState = CurrentState::Initial;
            _SetNextState(CurrentState::NormalText);

            while (_currentState != CurrentState::Done)
            {
                CurrentState nextState = _currentStateBehavior->GoNext(this);
                _SetNextState(nextState);
            }

            return _outputText.str();
        }


        //--------------------------------------------------------------------
        // IStateContext interface implementation.
        //--------------------------------------------------------------------

        /// <summary>
        /// Retrieve the next character from the input.
        /// </summary>
        /// <returns>Returns the next character from the input.  Returns
        /// EOF_CHAR if there is no more input.</returns>
        char GetNextCharacter()
        {
            char character = EOF_CHAR;

            if (_textIndex < _inputText.size())
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
        void OutputCharacter(char character)
        {
            if (character != EOF_CHAR)
            {
                _outputText << character;
            }
        }
    };

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


namespace DesignPatternExamples_cpp
{
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State Context public class definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    StateContext_Class::StateContext_Class()
    : _stateContextimpl(std::make_unique<StateContext_ClassImpl>())
    {
    }


    std::string StateContext_Class::RemoveComments(std::string text)
    {
        StateContext_ClassImpl* stateImpl = dynamic_cast<StateContext_ClassImpl*>(_stateContextimpl.get());
        if (stateImpl != nullptr)
        {
            return stateImpl->RemoveComments(text);
        }
        return std::string();
    }

} // end namespace
