## @file
# @brief
# Implementation of the Bridge_Exercise() function as used in the 
# @ref bridge_pattern "Bridge pattern".

## Example of using the @ref bridge_pattern "Bridge" design pattern.
# 
# The Bridge pattern is used to allow a program to offer multiple
# ways to perform logging without changing how the logging is
# used throughout the program.
#
# In this exercise, note how the calls into the logger are the
# same regardless of the logger used.

# ! [Using Bridge in Python]
def Bridge_Exercise():
    print()
    print("Bridge Exercise")

    print("  Done.")
# ! [Using Bridge in Python]
