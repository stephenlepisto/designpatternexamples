## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.nullobject.nullobject_exercise.NullObject_Exercise "NullObject_Exercise"()
#  function as used in the @ref nullobject_pattern.

from .null_object import MoveProcessor

##  Example of using the @ref nullobject_pattern.
#  
#  The Null Object pattern is where an object or function acts as a
#  stand-in for real commands but otherwise does nothing.
#  
#  In this exercise, movement commands are presented as characters in
#  a string, with the characters 'u', 'd', 'l', and 'r' representing
#  the moves "up", "down", "left", and "right", respectively.  To
#  keep the processing of this string simple, all other characters in
#  the string are assigned a Null Object ("Do Nothing") version of
#  the move command.
#  
#  This example displays the commands after parsing and then
#  "executes" commands, which consists of printing the commands out.
#  
#  This example highlights the Null Object pattern while utilizing
#  the @ref command_pattern and @ref interpreter_pattern.

# ! [Using NullObject in Python]
def NullObject_Exercise():
    print()
    print("Null Object Exercise")

    moveProcessor = MoveProcessor()

    # A stream of recognized and unrecognized move commands.  The
    # unrecognized commands do nothing.
    moveString = "ur#ld!lr";
    print("  Showing the move commands:")
    moveProcessor.ShowMoveList(moveString)

    print("  Executing the move commands:")
    print("    {0} -> ".format(moveString), end="")
    moveProcessor.ExecuteMoveList(moveString)

    print("  Done.")
# ! [Using NullObject in Python]
