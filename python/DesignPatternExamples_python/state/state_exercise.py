## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.state.state_exercise.State_Exercise "State_Exercise"()
# function as used in the @ref state_pattern.


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

    print("  Done.")
# ! [Using State in Python]
