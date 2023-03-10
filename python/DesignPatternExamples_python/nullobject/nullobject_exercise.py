## @file
# @brief
# Implementation of the NullObject_Exercise() function as used in the 
# @ref nullobject_pattern "NullObject pattern".


##  Example of using the @ref nullobject_pattern "Null Object" design pattern.
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
#  the Command and Interpreter patterns.
##! [Using NullObject in Python]
def NullObject_Exercise():
    print()
    print("Null Object Exercise")

    print("  Done.")
##! [Using NullObject in Python]
