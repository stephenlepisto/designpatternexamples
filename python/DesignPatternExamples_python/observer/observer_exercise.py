## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.observer.observer_exercise.Observer_Exercise "Observer_Exercise"()
#  function as used in the @ref observer_pattern.

from .observer_class import ObserverForDecimal, ObserverForHexaDecimal, ObserverForBinary
from .observersubject_numberproducer import ObserverSubject_NumberProducer

##  Example of using the @ref observer_pattern.
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

    numberProducer = ObserverSubject_NumberProducer()

    # The number producer is passed to the observers so the observers
    # can get the number to display.  The observers only see the
    # INumberProducer interface, to minimize knowledge about the
    # Subject.
    observerDecimal = ObserverForDecimal(numberProducer)
    observerHexadecimal = ObserverForHexaDecimal(numberProducer)
    observerBinary = ObserverForBinary(numberProducer)

    # Tell the number producer about the observers who are notified
    # whenever the value changes.
    numberProducer.SubscribeToNumberChanged(observerDecimal)
    numberProducer.SubscribeToNumberChanged(observerHexadecimal)
    numberProducer.SubscribeToNumberChanged(observerBinary)

    # Call the number producer's Update() method a number of times.
    # The observers automatically print out the current value in
    # different bases.
    for index in range(0, 10):
        print("  Update {0} on number producer.  Results from observers:".format(index))
        numberProducer.Update();

    # When done, remove the observers from the number producer.
    # It's always good to clean up after ourselves.
    numberProducer.UnsubscribeFromNumberChanged(observerDecimal)
    numberProducer.UnsubscribeFromNumberChanged(observerHexadecimal)
    numberProducer.UnsubscribeFromNumberChanged(observerBinary)

    print("  Done.")
# ! [Using Observer in Python]
