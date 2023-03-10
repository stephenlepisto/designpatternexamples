## @file
# @brief
# Implementation of the Mediator_Exercise() function as used in the 
# @ref mediator_pattern "Mediator pattern".


##  Example of using the @ref mediator_pattern "Mediator" design pattern.
#  
#  A mediator is instantiated then populated with users and groups.
#  Users are added to some of the groups.
#  
#  A series of operations are then performed through the mediator.
#  The output shows the results of each operation.  Note that all
#  operations are done using user and group names, with no knowledge
#  of the actual lists of users and groups.  The mediator hides all
#  the details.
##! [Using Mediator in Python]
def Mediator_Exercise():
    print()
    print("Mediator Exercise")

    print("  Done.")
##! [Using Mediator in Python]
