## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.state.state_interface.IStateContext "IStateContext"
#  and
#  @ref DesignPatternExamples_python.state.state_interface.IStateBehavior "IStateBehavior"
#  interfaces as used in the @ref state_pattern.

from enum import Enum
from abc import ABC, abstractmethod


##  Represents the current state of the state machine.
class CurrentState(Enum):
    ## State before the state machine actually starts.  transitions to NormalText
    Initial = 0
    
    ## \" transitions to QuotedText, / transitions to StartComment,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    NormalText = 1
    
    ## \ transitions to EscapedDoubleQuoteText, \" transitions to NormalText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    DoubleQuotedText = 2
    
    ## ' transitions to EscapedSingleQuoteText, \ transitions to NormalText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    SingleQuotedText = 3
    
    ## \ transitions to QuotedText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    EscapedDoubleQuoteText = 4
    
    ## \ transitions to SingleQuotedText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    EscapedSingleQuoteText = 5
    
    ## / transitions to LineComment, `*` transitions to BlockComment,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done all else transitions to NormalText
    StartComment = 6
    
    ## \\n transitions to NormalText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    LineComment = 7
    
    ## `*` transitions to EndBlockComment,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done
    BlockComment = 8
    
    ## / transitions to NormalText,
    #  @ref DesignPatternExamples_python.state.state_interface.SpecialCase.EOF_CHAR "EOF_CHAR"
    #  transitions to Done all else transitions to BlockComment
    EndBlockComment = 9
    
    ## Indicates processing is done
    Done = 10



#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Interface definitions
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## This class contain special characters.  In Python, it is necessary to
#  reference these labels in dotted notation (`SpecialCharacter.EOF_CHAR`) in a
#  case statement in a match block; otherwise, the bare label (`EOF_CHAR`) is
#  treated as a "capture pattern" and causes an "irrefutable pattern" error (a
#  pattern that must be last in the case statement list as it is always
#  matched).
class SpecialCase:
    ## Indicates End-of-file (no more data available).
    EOF_CHAR = 0xff


#########################################################################
#########################################################################


## Represents the context as passed to each state class.
#  
#  Each state class can access the next character or output the current
#  character through this interface.
#  </summary>
class IStateContext(ABC):

    ## (IStateContext) Get the next character from the input.
    #
    #  @returns
    #     Returns the next character.  Returns `EOF_CHAR` if there is no more
    #     input.
    @abstractmethod
    def GetNextCharacter(self) -> int:
        pass

    ## (IStateContext) Write the character to the context.  This is how the parser
    #  accumulates the filtered text.
    #
    #  @param character
    #         The character to accumulate
    @abstractmethod
    def OutputCharacter(self, character : int) -> None:
        pass


#########################################################################
#########################################################################


## Represents a class that implements one state of the state machine.
#  
#  The context calls each state through this interface.
#
#  Technically, the
#  @ref DesignPatternExamples_python.state.state_class.StateContext_Class "StateContext_Class"
#  knows about the actual state classes because it has to instantiate them but
#  this interface makes the code for calling the state classes much simpler.
class IStateBehavior(ABC):

    ## (IStateBehavior) Retrieve to the next state given the current context
    #
    #  @returns
    #     A value from the
    #     @ref DesignPatternExamples_python.state.state_interface.CurrentState "CurrentState"
    #     enumeration indicating the next state to use.
    def GoNext(context : IStateContext) -> CurrentState:
        pass
