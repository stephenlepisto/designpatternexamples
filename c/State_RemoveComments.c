/// @file
/// @brief
/// Implementation of the State_RemoveComments() function, along with the state
/// machine used to filter out comments out of a piece of source code, as used
/// in the @ref state_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "State_RemoveComments.h"

/// <summary>
/// Represents the current state of the state machine.
/// </summary>
typedef enum
{
    State_Initial,                ///< State before the state machine actually starts.  transitions to NormalText
    State_NormalText,             ///< `"` transitions to QuotedText, / transitions to StartComment, EOF_CHAR transitions to Done
    State_DoubleQuotedText,       ///< `\` transitions to EscapedDoubleQuoteText, " transitions to NormalText, EOF_CHAR transitions to Done
    State_SingleQuotedText,       ///< ' transitions to EscapedSingleQuoteText, \ transitions to NormalText, EOF_CHAR transitions to Done
    State_EscapedDoubleQuoteText, ///< `\` transitions to QuotedText, EOF_CHAR transitions to Done
    State_EscapedSingleQuoteText, ///< `\` transitions to SingleQuotedText, EOF_CHAR transitions to Done
    State_StartComment,           ///< `/` transitions to LineComment, * transitions to BlockComment, EOF_CHAR transitions to Done, all else transitions to NormalText
    State_LineComment,            ///< `\n` transitions to NormalText, EOF_CHAR transitions to Done
    State_BlockComment,           ///< `*` transitions to EndBlockComment, EOF_CHAR transitions to Done
    State_EndBlockComment,        ///< `/` transitions to NormalText, EOF_CHAR transitions to Done, all else transitions to BlockComment
    State_Done,                   ///< Indicates processing is done
    State_Error                   ///< Indicates an error occurred and the state machine needs to exit
} CurrentState;

struct StateContext; // forward reference
/// <summary>
/// Alias for a function pointer that takes a StateContext object and returns a
/// value from the @ref CurrentState enumeration.
/// </summary>
typedef CurrentState (*StateFunctionPtr)(struct StateContext*);

/// <summary>
/// Contains constants used in the state machine.
/// </summary>
enum _Constants
{
    EOF_CHAR = (char)-1  ///< Indicates end of string.
};


/// <summary>
/// Represents the context in which the state machine runs.
/// </summary>
typedef struct StateContext
{
    const char* inputText;      ///< The text being filtered
    size_t textIndex;           ///< Index into the text being filtered.
    char* outputText;           ///< Buffer into which output text is written, character by character
    size_t outputTextIndex;     ///< Index of the next point to put the output character
    CurrentState currentState;  ///< Value from the CurrentState enumeration indicating the current state of the machine.
    StateFunctionPtr currentStateBehavior; ///< Pointer to a function that acts on the current state
} StateContext;

//=============================================================================
//=============================================================================

/// <summary>
/// Convert the CurrentState enumeration to a string for output purposes.
/// </summary>
/// <param name="state">A value from the CurrentState enumeration.</param>
/// <returns>Returns a string containing the string version of the given
/// state.</returns>
static const char* _CurrentStateToString(CurrentState state)
{
    // Need something for formatted error string that persists beyond this function.
    static char errorBuffer[64] = { 0 };
    const char* stateAsString = NULL;

    switch (state)
    {
        case State_Initial:
            stateAsString = "Initial";
            break;

        case State_NormalText:
            stateAsString = "NormalText";
            break;

        case State_DoubleQuotedText:
            stateAsString = "DoubleQuotedText";
            break;

        case State_SingleQuotedText:
            stateAsString = "SingleQuotedText";
            break;

        case State_EscapedDoubleQuoteText:
            stateAsString = "EscapedDoubleQuoteText";
            break;

        case State_EscapedSingleQuoteText:
            stateAsString = "EscapedSingleQuoteText";
            break;

        case State_StartComment:
            stateAsString = "StartComment";
            break;

        case State_LineComment:
            stateAsString = "LineComment";
            break;

        case State_BlockComment:
            stateAsString = "BlockComment";
            break;

        case State_EndBlockComment:
            stateAsString = "EndBlockComment";
            break;

        case State_Done:
            stateAsString = "Done";
            break;

        default:
            {
                errorBuffer[0] = '\0';
                int num_chars = sprintf_s(errorBuffer, sizeof(errorBuffer), "Unknown state (%d)", state);
                if (num_chars != -1)
                {
                    stateAsString = errorBuffer;
                }
                else
                {
                    stateAsString = "Error converting state to string";
                }
            }
            break;
    }


    return stateAsString;
}


/// <summary>
/// Retrieve the next character from the input.
/// </summary>
/// <returns>Returns the next character from the input.  Returns
/// EOF_CHAR if there is no more input.</returns>
static char _GetNextCharacter(StateContext* context)
{
    char character = EOF_CHAR;

    if (context != NULL)
    {
        if (context->inputText[context->textIndex] != '\0')
        {
            character = context->inputText[context->textIndex];
            context->textIndex++;
        }
    }
    return character;
}

/// <summary>
/// Save the character to the accumulation of the filtered text.
/// </summary>
/// <param name="context">The StateContext object controlling the state machine
/// and which contains the DynamicString object being used to accumulate the
/// filtered text.</param>
/// <param name="character">The character to save.</param>
static void _OutputCharacter(StateContext* context, char character)
{
    if (context != NULL && character != EOF_CHAR)
    {
        context->outputText[context->outputTextIndex] = character;
        context->outputTextIndex++;
        context->outputText[context->outputTextIndex] = '\0';
    }
}

//=============================================================================
//=============================================================================

/// <summary>
/// Handles the state of normal text behavior.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - \" : go to State_DoubleQuotedText (start of a double-quoted string)
/// - '  : go to State_SingleQuotedText (start of a single-quoted string)
/// - /  : go to State_StartComment (start of a line or block comment)
/// - EOF_CHAR : go to State_Done (no more input)
/// 
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_NormalText_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_NormalText;

        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '"':
                _OutputCharacter(context, character);
                nextState = State_DoubleQuotedText;
                break;

            case '\'':
                _OutputCharacter(context, character);
                nextState = State_SingleQuotedText;
                break;

            case '/':
                nextState = State_StartComment;
                break;

            default:
                _OutputCharacter(context, character);
                break;
        }
    }

    return nextState;
}

/// <summary>
/// Handles the state of being inside a double-quote string where filtering
/// is essentially turned off until the end of the string is reached.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - \"  - go to State_NormalText (end of a double-quoted string)
/// - \   - go to State_EscapedDoubleQuoteText (start of an escaped character)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_DoubleQuotedText_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_DoubleQuotedText;

        switch (character)
        {
        case EOF_CHAR:
            nextState = State_Done;
            break;

        case '"':
            _OutputCharacter(context, character);
            nextState = State_NormalText;
            break;

        case '\\':
            _OutputCharacter(context, character);
            nextState = State_EscapedDoubleQuoteText;
            break;

        default:
            _OutputCharacter(context, character);
            break;
        }
    }

    return nextState;
}

/// <summary>
/// Handles the state of being inside a single-quoted string where filtering
/// is effectively turned off until the end of the string is reached.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - '   - go to State_NormalText (end of a single-quoted string)
/// - \   - go to State_EscapedSingleQuoteText (start of an escaped character)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_SingleQuotedText_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_SingleQuotedText;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '\'':
                _OutputCharacter(context, character);
                nextState = State_NormalText;
                break;

            case '\\':
                _OutputCharacter(context, character);
                nextState = State_EscapedSingleQuoteText;
                break;

            default:
                _OutputCharacter(context, character);
                break;
        }
    }

    return nextState;
}

/// <summary>
/// Handles the state of being in an escaped character sequence inside a
/// double-quoted string.  We don't do anything with the escaped character
/// other than output it.  Handling escaped characters allows us to more
/// accurately detect the end of the string.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - {ANY} - go to State_DoubleQuotedText (end of escape sequence)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_EscapedDoubleQuoteText_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_DoubleQuotedText;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            default:
                _OutputCharacter(context, character);
            break;
        }

    }

    return nextState;
}

/// <summary>
/// Handles the state of being in an escaped character sequence inside a
/// single-quoted string.  We don't do anything with the escaped character
/// other than output it.  Handling escaped characters allows us to more
/// accurately detect the end of the string.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - {ANY} - go to State_SingleQuotedText (end of escape sequence)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_EscapedSingleQuoteText_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_SingleQuotedText;
        switch (character)
        {
        case EOF_CHAR:
            nextState = State_Done;
            break;

        default:
            _OutputCharacter(context, character);
            break;
        }

    }

    return nextState;
}

/// <summary>
/// Handles the state of being at the possible start of a line or block
/// comment.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - /   - go to State_LineComment (start of a line comment)
/// - *   - go to State_BlockComment (start of a block comment)
/// - {ANY} - go to State_NormalText (not start of a comment)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_StartComment_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_StartComment;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '/':
                nextState = State_LineComment;
                break;

            case '*':
                nextState = State_BlockComment;
                break;

            default:
                // Not the start of a comment so output the leading slash
                // that led to the state followed by the character we just
                // processed.
                _OutputCharacter(context, '/');
                _OutputCharacter(context, character);
                nextState = State_NormalText;
            break;
        }

    }

    return nextState;
}

/// <summary>
/// Handles the state of being in a line comment.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - \n  - go to State_NormalText (a newline is the end of a line comment)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_LineComment_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_LineComment;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '\n':
                _OutputCharacter(context, character);
                nextState = State_NormalText;
                break;

            default:
                // We are in a comment to be removed, so do nothing here.
                break;
        }

    }

    return nextState;
}

/// <summary>
/// Handles the state of being in a block comment.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - *  - go to State_EndBlockComment (possible end of block comment)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_BlockComment_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_BlockComment;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '*':
                nextState = State_EndBlockComment;
                break;

            default:
                // We are in a comment to be removed, so do nothing here.
                break;
        }
    }

    return nextState;
}

/// <summary>
/// Handles the state of possibly being at the end of a block comment.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - /  - go to State_NormalText (found end of block comment)
/// - {ANY} - go to State_BlockComment (still in block comment)
/// - EOF_CHAR - go to State_Done (no more input)
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_EndBlockComment_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        char character = _GetNextCharacter(context);
        nextState = State_BlockComment;
        switch (character)
        {
            case EOF_CHAR:
                nextState = State_Done;
                break;

            case '/':
                nextState = State_NormalText;
                break;

            default:
                // We are still in a block comment to be removed, so do nothing here.
                break;
        }

    }

    return nextState;
}

/// <summary>
/// Handles the state of being done with input.
/// 
/// Process the next character from the context, returning the next
/// state the context should move to.
/// 
/// Transitions to the following states for the seen input:
/// - Always stay in State_Done
/// </summary>
/// <param name="context">A StateContext object representing the context
/// to use for getting the next character of input and to which to output
/// characters.</param>
/// <returns>Returns a value from the @ref CurrentState enumeration indicating
/// the next state to which the state machine should transition to.</returns>
static CurrentState _State_Done_GoNextState(StateContext* context)
{
    CurrentState nextState = State_Error;

    if (context != NULL)
    {
        // Do nothing (Yes!  Another Null Object example!)
        nextState = State_Done;
    }

    return nextState;
}



//=============================================================================
//=============================================================================

/// <summary>
/// Maps a value from the @ref CurrentState enumeration to a function that handles
/// the transition from that state to the next state based on the context.
/// </summary>
typedef struct
{
    CurrentState state;            ///< Value from the @ref CurrentState enumeration
    StateFunctionPtr stateHandler; ///< Function pointer to be called based on this state.
} StateHandler;

/// <summary>
/// Array of StateHandler objects that map @ref CurrentState value to functions
/// that transition from that state to the next based on the context.
/// </summary>
static StateHandler _stateHandlers[] = {
    { State_NormalText            , _State_NormalText_GoNextState             },
    { State_DoubleQuotedText      , _State_DoubleQuotedText_GoNextState       },
    { State_SingleQuotedText      , _State_SingleQuotedText_GoNextState       },
    { State_EscapedDoubleQuoteText, _State_EscapedDoubleQuoteText_GoNextState },
    { State_EscapedSingleQuoteText, _State_EscapedSingleQuoteText_GoNextState },
    { State_StartComment          , _State_StartComment_GoNextState           },
    { State_LineComment           , _State_LineComment_GoNextState            },
    { State_BlockComment          , _State_BlockComment_GoNextState           },
    { State_EndBlockComment       , _State_EndBlockComment_GoNextState        },
    { State_Done                  , _State_Done_GoNextState                   },
    { State_Initial               , NULL }, // end of list
};

/// <summary>
/// Retrieve the function that is used to transition from the given state to
/// another state.
/// </summary>
/// <param name="state">A value from the @ref CurrentState enumeration indicating 
/// state for which to get a transition function.</param>
/// <returns>Returns a StateFunctionPtr for the specified state.</returns>
static StateFunctionPtr _GetStateFunction(CurrentState state)
{
    StateFunctionPtr functionPtr = NULL;

    for (size_t index = 0; _stateHandlers[index].stateHandler != NULL; index++)
    {
        if (_stateHandlers[index].state == state)
        {
            functionPtr = _stateHandlers[index].stateHandler;
            break;
        }
    }

    if (functionPtr == NULL)
    {
        printf("Error!  _GetStateFunction() received an unrecognized state.  Cannot retrieve the state function.\n");
    }

    return functionPtr;
}


/// <summary>
/// Helper method to transition the state machine to the specified
/// state.  Does nothing if the new state is the same as the old
/// state.  Instantiates the state class the first time the state class
/// is needed.
/// </summary>
/// <param name="context">The StateContext object that controls the state
/// machine.</param>
/// <param name="newState">A value from the CurrentState enumeration indicating
/// the state to which to transition.</param>
/// <returns>Returns true if the next state was successfully set; otherwise,
/// returns false, indicating some kind of problem.</returns>
bool _SetNextState(StateContext* context, CurrentState newState)
{
    bool success = false;

    if (context != NULL)
    {
        success = true;
        if (newState != context->currentState)
        {
            context->currentStateBehavior = _GetStateFunction(newState);
            if (context->currentStateBehavior != NULL)
            {
                printf("    --> State Transition: %s -> %s\n",
                    _CurrentStateToString(context->currentState),
                    _CurrentStateToString(newState));

                context->currentState = newState;
            }
            else
            {
                success = false;
            }
        }
    }

    return success;
}


///////////////////////////////////////////////////////////////////////////////
// State_RemoveComments()
///////////////////////////////////////////////////////////////////////////////
bool State_RemoveComments(const char* text, DynamicString* filteredText)
{
    bool success = false;

    if (text != NULL && filteredText != NULL)
    {
        StateContext context = { 0 };
        // Filtered text is guaranteed to be no larger than the raw text, so
        // allocate a buffer the same size for the output text.  This avoids
        // a lot of messy out of memory error checking in the code.
        context.outputText = calloc(1, strlen(text) + 1);
        if (context.outputText != NULL)
        {
            context.inputText = text;
            context.textIndex = 0;
            context.outputTextIndex = 0;
            context.currentState = State_Initial;
            success = _SetNextState(&context, State_NormalText);
        }
        else
        {
            printf("  Error!  Unable to allocate memory for the output text in the state machine!\n");
        }

        if (success)
        {
            while (context.currentState != State_Done && success)
            {
                CurrentState newState = context.currentStateBehavior(&context);
                if (newState == State_Error)
                {
                    printf("  Error!  The state machine ran into an error condition (likely a NULL argument)!\n");
                    break;
                }
                success = _SetNextState(&context, newState);
            }

            if (success)
            {
                success = DynamicString_Set(filteredText, context.outputText);
                free(context.outputText);
            }
        }
    }

    return success;
}