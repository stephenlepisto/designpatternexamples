## @file
# @brief
# Implementation of the Command_Exercise() function as used in the 
# @ref command_pattern "Command pattern".


##  Example of using the @ref command_pattern "Command" design pattern.
#  
#  The Command pattern is used to encapsulate an operation or command
#  associated with an object so that the command can be applied to
#  the object at a later time.
#  
#  In this exercise, an undo list is implemented using Commands that
#  associate commands defined in this file with a text object.  The
#  commands are applied to the text object in succession then
#  effectively undone.
##! [Using Command in Python]
def Command_Exercise():
    print()
    print("Command Exercise")

    print("  Done.")
##! [Using Command in Python]
