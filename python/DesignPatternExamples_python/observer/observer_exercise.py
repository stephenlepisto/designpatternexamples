## @file
# @brief
# Implementation of the Observer_Exercise() function as used in the 
# @ref observer_pattern "Observer pattern".


##  Example of using the @ref observer_pattern "Observer" design pattern.
#  
#  The Observer pattern allows for one or more observers to react to
#  changes in a Subject entity.
#  
#  In this exercise, a number producer (the Subject) updates an internal
#  value every time the Update() method is called.  Three different
#  observers are attached to the number producer and print out the
#  current value in different formats whenever the number is changed.
#  
#  Note: Interfaces are used throughout this example.  For example, to
#  subscribe to the number producer, the IEventNotifications interface
#  must be obtained from the number producer.  The number producer is
#  represented to the observers with the INumberProducer interface and
#  the observers are represented to the number producer with the
#  IObserverNumberChanged interface.  This highlights a common way to
#  implement a "pull" style observer without having too much knowledge
#  about the Subject.

# ! [Using Observer in Python]
def Observer_Exercise():
    print()
    print("Observer Exercise")

    print("  Done.")
# ! [Using Observer in Python]
