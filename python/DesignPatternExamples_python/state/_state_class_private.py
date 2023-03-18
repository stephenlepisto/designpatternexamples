## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.state._state_class_private.StateContext_ClassImpl "StateContext_ClassImpl"
#  private class along with the numerous StateXXX classes as used in the
#  @ref state_pattern.

from io import StringIO

from .state_interface import CurrentState, IStateBehavior, IStateContext, SpecialCase

## Convert the
#  @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
#  enumeration to a string for output purposes.
#
#  Yes, this could be expressed as a dictionary.
#
#  @param state
#         A value from the
#         @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
#         enumeration.
#  @returns
#     Returns a string containing the string version of the given state.
def _CurrentStateToString(state : CurrentState) -> str:
    stateAsString = ""

    match state:
        case CurrentState.Initial:
            stateAsString = "Initial"

        case CurrentState.NormalText:
            stateAsString = "NormalText"

        case CurrentState.DoubleQuotedText:
            stateAsString = "DoubleQuotedText"

        case CurrentState.SingleQuotedText:
            stateAsString = "SingleQuotedText"

        case CurrentState.EscapedDoubleQuoteText:
            stateAsString = "EscapedDoubleQuoteText"

        case CurrentState.EscapedSingleQuoteText:
            stateAsString = "EscapedSingleQuoteText"

        case CurrentState.StartComment:
            stateAsString = "StartComment"

        case CurrentState.LineComment:
            stateAsString = "LineComment"

        case CurrentState.BlockComment:
            stateAsString = "BlockComment"

        case CurrentState.EndBlockComment:
            stateAsString = "EndBlockComment"

        case CurrentState.Done:
            stateAsString = "Done"

        case _:
            stateAsString = "Unknown ({0})".format(state)

    return stateAsString


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# State class definitions
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Represents normal text behavior.
#  
#  Transitions to the following states for the seen input:
#  - "   - go to CurrentState.DoubleQuotedText (start of a double-quoted string)
#  - '   - go to CurrentState.SingleQuotedText (start of a single-quoted string)
#  - /   - go to CurrentState.StartComment (start of a line or block comment)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_NormalText(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.NormalText
        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '"':
                context.OutputCharacter(character)
                nextState = CurrentState.DoubleQuotedText

            case '\'':
                context.OutputCharacter(character)
                nextState = CurrentState.SingleQuotedText

            case '/':
                nextState = CurrentState.StartComment

            case _:
                context.OutputCharacter(character)

        return nextState


#########################################################################
#########################################################################


## Represents being inside a double-quote string where filtering is
#  essentially turned off until the end of the string is reached.
#  
#  Transitions to the following states for the seen input:
#  - "   - go to CurrentState.NormalText (end of a double-quoted string)
#  - \   - go to CurrentState.EscapedDoubleQuoteText (start of an escaped character)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_DoubleQuotedText(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.DoubleQuotedText

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '"':
                context.OutputCharacter(character)
                nextState = CurrentState.NormalText

            case '\\':
                context.OutputCharacter(character)
                nextState = CurrentState.EscapedDoubleQuoteText

            case _:
                context.OutputCharacter(character)

        return nextState


#########################################################################
#########################################################################


## Represents being inside a single-quoted string where filtering is
#  effectively turned off until the end of the string is reached.
#  
#  Transitions to the following states for the seen input:
#  - '   - go to CurrentState.NormalText (end of a single-quoted string)
#  - \   - go to CurrentState.EscapedSingleQuoteText (start of an escaped character)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_SingleQuotedText(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.SingleQuotedText

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '\'':
                context.OutputCharacter(character)
                nextState = CurrentState.NormalText

            case '\\':
                context.OutputCharacter(character)
                nextState = CurrentState.EscapedSingleQuoteText

            case _:
                context.OutputCharacter(character)

        return nextState


#########################################################################
#########################################################################


## Represents being in an escaped character sequence inside a double-
#  quoted string.  We don't do anything with the escaped character other
#  than output it.  Handling escaped characters allows us to more
#  accurately detect the end of the string.
#  
#  Transitions to the following states for the seen input:
#  - {ANY} - go to CurrentState.DoubleQuotedText (end of escape sequence)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_EscapedDoubleQuoteText(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.DoubleQuotedText

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case _:
                context.OutputCharacter(character)

        return nextState


#########################################################################
#########################################################################


## Represents being in an escaped character sequence inside a single-
#  quoted string.  We don't do anything with the escaped character other
#  than output it.  Handling escaped characters allows us to more
#  accurately detect the end of the string.
#  
#  Transitions to the following states for the seen input:
#  - {ANY} - go to CurrentState.SingleQuotedText (end of escape sequence)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_EscapedSingleQuoteText(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.SingleQuotedText

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case _:
                context.OutputCharacter(character)

        return nextState


#########################################################################
#########################################################################


## Represents the possible start of a line or block comment.
#  
#  Transitions to the following states for the seen input:
#  - /   - go to CurrentState.LineComment (start of a line comment)
#  - *   - go to CurrentState.BlockComment (start of a block comment)
#  - {ANY} - go to CurrentState.NormalText (not start of a comment)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_StartComment(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.StartComment

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '/':
                nextState = CurrentState.LineComment

            case '*':
                nextState = CurrentState.BlockComment

            case _:
                # Is not the start of a comment so output the leading slash
                # that led to the state followed by the character we just
                # processed.
                context.OutputCharacter('/')
                context.OutputCharacter(character)
                nextState = CurrentState.NormalText

        return nextState


#########################################################################
#########################################################################


## Represents being in a line comment.
#  
#  Transitions to the following states for the seen input:
#  - \n  - go to CurrentState.NormalText (a newline is the end of a line comment)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_LineComment(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.LineComment

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '\n':
                context.OutputCharacter(character)
                nextState = CurrentState.NormalText

            case _:
                # We are in a comment to be removed, so do nothing here.
                pass

        return nextState


#########################################################################
#########################################################################


## Represents being in a block comment.
#  
#  Transitions to the following states for the seen input:
#  - *  - go to CurrentState.EndBlockComment (possible end of block comment)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_BlockComment(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.BlockComment

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '*':
                context.OutputCharacter(character)
                nextState = CurrentState.EndBlockComment

            case _:
                # We are in a comment to be removed, so do nothing here.
                pass

        return nextState


#########################################################################
#########################################################################


## Represents possibly being at the end of a block comment.
#  
#  Transitions to the following states for the seen input:
#  - /  - go to CurrentState.NormalText (found end of block comment)
#  - {ANY} - go to CurrentState.BlockComment (still in block comment)
#  - EOF_CHAR - go to CurrentState.Done (no more input)
class State_EndBlockComment(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @param context
    #         An
    #         @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #         object representing the context to use for getting the next
    #         character of input and to which to output characters.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        nextState = CurrentState.BlockComment

        character = context.GetNextCharacter()

        match character:
            case SpecialCase.EOF_CHAR:
                nextState = CurrentState.Done

            case '/':
                nextState = CurrentState.NormalText

            case _:
                # We are still in a block comment to be removed, so do nothing here.
                pass

        return nextState


#########################################################################
#########################################################################


## Represents being done with input.
#  
#  Transitions to the following states for the seen input:
#  - Always stay in CurrentState.Done
class State_Done(IStateBehavior):

    ## Process the next character from the context, returning the next
    #  state the context should move to.
    #
    #  @returns
    #     Returns a value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to which the state machine
    #     should transition to.
    def GoNext(self, context : IStateContext) -> CurrentState:
        # Do nothing (Yes!  Another Null Object example!)
        return CurrentState.Done


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# State class factory definition
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


## Class factory for generating the state class instances.
class State_Factory:

    ## Create an instance of the specified state class.
    #
    #  @param state
    #         A value from the
    #         @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #         enumeration indicating  state for which to generate a class instance.
    #
    #  @returns
    #     Returns an
    #     @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
    #     instance for the specified state.
    def CreateState(state : CurrentState) -> IStateBehavior:
        stateBehavior = None # type: IStateBehavior
        match state:
            case CurrentState.NormalText:
                stateBehavior = State_NormalText()

            case CurrentState.DoubleQuotedText:
                stateBehavior = State_DoubleQuotedText()

            case CurrentState.SingleQuotedText:
                stateBehavior = State_SingleQuotedText()

            case CurrentState.EscapedDoubleQuoteText:
                stateBehavior = State_EscapedDoubleQuoteText()

            case CurrentState.EscapedSingleQuoteText:
                stateBehavior = State_EscapedSingleQuoteText()

            case CurrentState.StartComment:
                stateBehavior = State_StartComment()

            case CurrentState.LineComment:
                stateBehavior = State_LineComment()

            case CurrentState.BlockComment:
                stateBehavior = State_BlockComment()

            case CurrentState.EndBlockComment:
                stateBehavior = State_EndBlockComment()

            case CurrentState.Done:
                stateBehavior = State_Done()

            case _:
                msg = "Unknown state: {0}.  Cannot create a state class.".format(
                    _CurrentStateToString(state))
                raise ValueError(msg)

        return stateBehavior


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# State Context implementation class definition
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


## Implementation of the state machine.  This maintains the context in
#  which the state machine runs.  This is in its own module to make it at least
#  a little clearer that it is private and should not be called directly.
#
#  Intended to be called only from the
#  @ref DesignPatternExamples_python.state.state_class.StateContext_Class "StateContext_Class"
#  class.
class StateContext_ClassImpl(IStateContext):

    #--------------------------------------------------------------------
    # StateContext_Class implementation.
    #--------------------------------------------------------------------

    ## Helper method to transition the state machine to the specified
    #  state.  Does nothing if the new state is the same as the old
    #  state.  Instantiates the state class the first time the state class
    #  is needed.
    #
    #  @param newState
    #         A value from the CurrentState enumeration indicating
    #         the state to which to transition.
    def _SetNextState(self, newState : CurrentState) -> None:
        if newState != self._currentState:
            if newState not in self._stateBehaviors:
                self._stateBehaviors[newState] = State_Factory.CreateState(newState)

            print("    --> State Transition: {0} -> {1}".format(
                    _CurrentStateToString(self._currentState),
                    _CurrentStateToString(newState)))

            self._currentStateBehavior = self._stateBehaviors[newState]
            self._currentState = newState


    ## Constructor
    def __init__(self) -> None:
        self._inputText = ""
        self._textIndex = 0
        self._outputText = StringIO()
        self._stateBehaviors = {} # type: dict[CurrentState, IStateBehavior]
        self._currentState = CurrentState.Initial
        self._currentStateBehavior = None # type: IStateBehavior

    ## @var _inputText
    #       The text to be filtered.
    #  @var _textIndex
    #       Index into the text to be filtered.
    #  @var _outputText
    #       The results of the filtering.
    #  @var _stateBehaviors
    #       Maps values from the
    #       @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #       enumeration to instances of the
    #       @ref DesignPatternExamples_python.state.state_interface.IStateBehavior "IStateBehavior"
    #       representing the behavior for that state.
    #  @var _currentState
    #       A value from the
    #       @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #       enumeration indicating the current state of the machine.
    #  @var _currentStateBehavior
    #       The current behavior (that is, a reference to the
    #       @ref DesignPatternExamples_python.state.state_interface.IStateBehavior "IStateBehavior"
    #       instance) for the current state.
    

    #--------------------------------------------------------------------
    # StateContext_Class public entry points.
    #--------------------------------------------------------------------

    ## Entry point for callers to filter text.  Removes C++-style line
    #  and block comments from the text.
    #
    #  @param text
    #         The text to filter.
    #  @returns
    #     Returns the filtered text.
    def RemoveComments(self, text : str) -> str:
        self._inputText = text
        self._textIndex = 0;
        self._outputText.close()
        self._outputText = StringIO()
        self._currentState = CurrentState.Initial
        self._SetNextState(CurrentState.NormalText)

        while (self._currentState != CurrentState.Done):
            nextState = self._currentStateBehavior.GoNext(self)
            self._SetNextState(nextState)

        return self._outputText.getvalue()


    #--------------------------------------------------------------------
    # IStateContext interface implementation.
    #--------------------------------------------------------------------

    ## Retrieve the next character from the input.
    #
    #  @returns
    #     Returns the next character from the input.  Returns `EOF_CHAR` if
    #     there is no more input.
    def GetNextCharacter(self) -> int:
        character = SpecialCase.EOF_CHAR

        if self._textIndex < len(self._inputText):
            character = self._inputText[self._textIndex]
            self._textIndex += 1
        return character

    ## Save the character to the accumulation of the filtered text.
    #
    #  @param character
    #         The character to save.
    def OutputCharacter(self, character : int) -> None:
        if character != SpecialCase.EOF_CHAR:
            self._outputText.write(character)
