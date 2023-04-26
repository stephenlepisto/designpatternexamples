## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.state.state_exercise.State_Exercise "State_Exercise"()
#  function as used in the @ref state_pattern.

from .state_class import StateContext_Class


## Helper method to display text from the State exercise.  Text is
#  displayed with line numbers.
#
#  @param textToDisplay
#         Text to display.
def _State_DisplayText(textToDisplay : str) -> None:
    lines = textToDisplay.split('\n')
    lineNumber = 1
    for line in lines:
        print("    {0:2}) {1}".format(lineNumber, line))
        lineNumber += 1


##  Example of using the @ref state_pattern.
#  
#  The State pattern alters the behavior of the class hierarchy based
#  on some state.  This is the basis of a Finite State Machine.
#  
#  In this exercise, the State class is a filter that parses text to
#  remove C++-style line and block comments.  It needs to be smart
#  enough to ignore comment characters inside quotes.
#  
#  The filtering process starts with creating the context that drives
#  the state machine.  Internal classes are provided for each state.

# ! [Using State in Python]
def State_Exercise():
    print()
    print("State Exercise")

    filterContext = StateContext_Class()
    textToFilter = \
'''/*####################  Block Comment  #################################*/
//####################  Line Comment  ####################################
// A comment.  /* A nested comment */
        
void State_Exercise() // An exercise in state machines
{
    char character = '\\"';
    std::cout << std::endl;
    std::cout << "\\"State\\" /*Exercise*/" << std::endl;
        
    StateContext_Class filterContext;
        
    std::cout << "\\t\\tDone. //(No, really)//" << std::endl;
}'''
    print("  Text to filter:")
    _State_DisplayText(textToFilter)

    print("  Filtering text...")
    filteredText = filterContext.RemoveComments(textToFilter)

    print("  Filtered text:")
    _State_DisplayText(filteredText)

    print("  Done.")
# ! [Using State in Python]
