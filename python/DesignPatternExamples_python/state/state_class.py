## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.state.state_class.StateContext_Class "StateContext_Class"
#  class as used in the @ref state_pattern.

from ._state_class_private import StateContext_ClassImpl

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# State context definition
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


## Represents the State Machine to the application.
#  
#  Wraps a private implementation of the state machine (as represented by the
#  @ref DesignPatternExamples_python.state._state_class_private.StateContext_ClassImpl "StateContext_ClassImpl"
#  class).  The implementation maintains the context in which the state machine
#  runs.
#
#  To use:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  
#  filterContext = StateContext_Class()
#  filteredText = filterContext.RemoveComments(textToFilter)
#  
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class StateContext_Class:

    ## Constructor
    def __init__(self) -> None:
        self._stateContextimpl = StateContext_ClassImpl()

    ## @var _stateContextimpl
    #       The actual implementation.

    #--------------------------------------------------------------------
    # StateContext_Class public entry points.
    #--------------------------------------------------------------------

    ##  Entry point for callers to filter text.  Removes C++-style line
    #   and block comments from the text.
    #
    #  @param text
    #         The text to filter.
    #  @returns
    #     Returns the filtered text.
    def RemoveComments(self, text : str) -> str:
        return self._stateContextimpl.RemoveComments(text)
