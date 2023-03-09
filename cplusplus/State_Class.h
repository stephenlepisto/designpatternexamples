/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::IStateContext "IStateContext" and
/// @ref DesignPatternExamples_cpp::IStateBehavior "IStateBehavior" interfaces,
/// as well as the @ref DesignPatternExamples_cpp::StateContext_Class "StateContext_Class"
/// class used in the @ref state_pattern "State pattern".

#pragma once
#ifndef __STATE_CLASS_H__
#define __STATE_CLASS_H__

#include <string>


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents the current state of the state machine.
    /// </summary>
    enum CurrentState
    {
        Initial,                ///< State before the state machine actually starts.  transitions to NormalText
        NormalText,             ///< `"` transitions to QuotedText, / transitions to StartComment, EOF_CHAR transitions to Done
        DoubleQuotedText,       ///< `\` transitions to EscapedDoubleQuoteText, " transitions to NormalText, EOF_CHAR transitions to Done
        SingleQuotedText,       ///< `'` transitions to EscapedSingleQuoteText, \ transitions to NormalText, EOF_CHAR transitions to Done
        EscapedDoubleQuoteText, ///< `\` transitions to QuotedText, EOF_CHAR transitions to Done
        EscapedSingleQuoteText, ///< `\` transitions to SingleQuotedText, EOF_CHAR transitions to Done
        StartComment,           ///< `/` transitions to LineComment, * transitions to BlockComment, EOF_CHAR transitions to Done, all else transitions to NormalText
        LineComment,            ///< `\\n` transitions to NormalText, EOF_CHAR transitions to Done
        BlockComment,           ///< `*` transitions to EndBlockComment, EOF_CHAR transitions to Done
        EndBlockComment,        ///< `/` transitions to NormalText, EOF_CHAR transitions to Done, all else transitions to BlockComment
        Done                    ///< Indicates processing is done
    };


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Interface definitions
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /// <summary>
    /// Indicates End-of-file (no more data available).
    /// </summary>
    const char EOF_CHAR = static_cast<const char>(0xff);


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the context as passed to each state class.
    /// 
    /// Each state class can access the next character or output the current
    /// character through this interface.
    /// </summary>
    struct IStateContext
    {
        /// <summary>
        /// Alias to make using a shared pointer easier.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<IStateContext>;

        /// <summary>
        /// Virtual destructor as required for interfaces.
        /// </summary>
        virtual ~IStateContext() {}

        /// <summary>
        /// Get the next character from the input.
        /// </summary>
        /// <returns>Returns the next character.  Returns EOF_CHAR
        /// if there is no more input.</returns>
        virtual char GetNextCharacter() = 0;

        /// <summary>
        /// Write the character to the context->  This is how the parser
        /// accumulates the filtered text.
        /// </summary>
        /// <param name="character">The character to accumulate</param>
        virtual void OutputCharacter(char character) = 0;
    };


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
    struct IStateBehavior
    {
        /// <summary>
        /// Alias to make using a shared pointer easier.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<IStateBehavior>;

        /// <summary>
        /// Virtual destructor as required for interfaces.
        /// </summary>
        virtual ~IStateBehavior() {}

        virtual CurrentState GoNext(IStateContext* context) = 0;
    };




    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // State context definition
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    /// <summary>
    /// Wraps a private implementation of the state machine.  The implementation
    /// maintains the context in which the state machine runs.
    /// </summary>
    /// <remarks>
    /// To use:
    /// <code>
    /// StateContext_Class filterContext;
    /// std::string filteredText = filterContext.RemoveComments(textToFilter);
    /// </code>
    /// </remarks>
    class StateContext_Class
    {
    private:
        /// <summary>
        /// Pointer to the actual implementation.
        /// </summary>
        std::unique_ptr<IStateContext> _stateContextimpl;

    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        StateContext_Class();


        //--------------------------------------------------------------------
        // StateContext_Class public entry points.
        //--------------------------------------------------------------------

        /// <summary>
        /// Entry point for callers to filter text.  Removes C++-style line
        /// and block comments from the text.
        /// </summary>
        /// <param name="text">The text to filter.</param>
        /// <returns>Returns the filtered text.</returns>
        std::string RemoveComments(std::string text);
    };

} // end namespace

#endif // __STATE_CLASS_H__

