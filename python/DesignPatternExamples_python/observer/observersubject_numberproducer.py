## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.ObserverSubject_NumberProducer "ObserverSubject_NumberProducer"
#  class as well as the declarations of the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.IObserverNumberChanged "IObserverNumberChanged",
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.IEventNotifications "IEventNotifications",
#  and
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer"
#  interfaces as used in the @ref observer_pattern.

from abc import ABC, abstractmethod


## Represents an observer to the Subject class.  An observer implements
#  this interface and then subscribes to the Subject with the interface.
#  The observer will be called whenever a change in the number is made.
#  
#  This interface is specific to the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.ObserverSubject_NumberProducer "ObserverSubject_NumberProducer"
#  example, which is a typical requirement for a Subject that supports
#  observers.
class IObserverNumberChanged(ABC):
    ## This is called whenever the number in the
    #  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.ObserverSubject_NumberProducer "ObserverSubject_NumberProducer"
    #  object is changed.
    @abstractmethod
    def NumberChanged(self) -> None:
        pass


#########################################################################
#########################################################################


## Represents a Subject that takes observers implementing the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.IObserverNumberChanged "IObserverNumberChanged"
#  interface.
#
#  In more complex systems, an interface like this might have
#  multiple subscribe/unsubscribe methods for different kinds of
#  observers.  For C#, such multiple methods might actually be one
#  Subscribe/Unsubscribe method that uses overloading to take different
#  observer interfaces.
#  
#  This interface is use to ensure the Subject implements all the
#  necessary methods to support observers.
class IEventNotifications(ABC):
    ## Call this with an observer to subscribe to the "number changed" event.
    @abstractmethod
    def SubscribeToNumberChanged(self, observer : IObserverNumberChanged) -> None:
        pass

    ## Call this with an observer to unsubscribe from the "number changed" event.
    @abstractmethod
    def UnsubscribeFromNumberChanged(self, observer : IObserverNumberChanged) -> None:
        pass


#########################################################################
#########################################################################


## Represents the Subject to the observers.  This is the minimum
#  needed by observers to get access to the data provided by the Subject
#  class.
#
#  An interface is used to represent the Subject to the observers so the
#  observers do not have too much knowledge about the Subject, allowing
#  more freedom to change the Subject class implementation without
#  affecting observers.  This interface would naturally have to change if
#  the observers needed more data from the Subject.
class INumberProducer(ABC):

    ## Update the number then notify all observers.
    @abstractmethod
    def Update(self) -> None:
        pass

    ## Return the current value from the Subject.
    #
    #  @returns
    #     Returns an integer that is the current value.
    def FetchNumber(self) -> int:
        pass


#########################################################################
#########################################################################


## Represents the Subject to be observed; in this case, a class that
#  contains a single number that is updated with a call to the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.ObserverSubject_NumberProducer.Update() "Update()"
#  method.  Whenever Update() is called, the number is incremented and
#  all observers are notified.  The observers then fetch the current
#  number via the
#  @ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer"
#  interface.
class ObserverSubject_NumberProducer(IEventNotifications, INumberProducer):

    ## Helper method to notify all observers that the number has changed.
    def _NotifyNumberChanged(self) -> None:
        # Copy the list so observers can change the original observers
        # during the notification (this isn't strictly needed in this
        # example but it is good practice for any notification system
        # that handles multiple observers where multiple threads might
        # be in play or observers can unsubscribe at any time, even in
        # the event notification).
        observers = self._observers.copy()
        for observer in observers:
            observer.NumberChanged();


    ## Helper method to retrieve the iterator to the specified observer
    #  if the observer is in the list.
    #
    #  @param observer
    #         An observer to look for.
    #  @returns
    #      Returns the index of the found observer; otherwise, returns -1.
    def _FindObserver(self, observer : IObserverNumberChanged) -> int:
        foundIndex = -1
        try:
            foundIndex = self._observers.index(observer)
        except ValueError:
            # observer was not found
            pass
        return foundIndex


    ## Helper method to determine if the specified observer is already
    #  present in the list of observers for this class.
    #
    #  @param observer
    #         An observer to look for.
    #  @returns
    #     Returns True if the observer is on this class's list of observers;
    #     otherwise, returns False.
    def _ContainsObserver(self, observer : IObserverNumberChanged) -> bool:
        foundObserver = self._FindObserver(observer)
        return foundObserver != -1


    ## Constructor
    def __init__(self) -> None:
        self._observers = [] # type: list[IObserverNumberChanged]
        self._number = 0

    ## @var _observers
    #       The list of observers subscribed to this class instance.
    #  @var _number
    #       The number being maintained.


    ## Update the number then notify all observers.
    def Update(self) -> None:
        self._number += 1
        self._NotifyNumberChanged()


    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Implementation of the INumberProducer interface.
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ## Observers call this method to fetch the current number.
    #
    #  @returns
    #     Returns the current number.
    def FetchNumber(self) -> int:
        return self._number


    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Implementation of the IEventNotifications interface.
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ## A client calls this to subscribe an observer to this class instance
    #  for notifications about changing numbers.  Does nothing if the
    #  given observer is already subscribed.
    #
    #  In a multi-threaded environment, this method would use a lock of some
    #  form.  This example doesn't use multiple threads so no lock is needed.
    #  See the
    #  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain.SendMessage "HandlerChain.SendMessage()"
    #  method in handlerchain_class.py for an example of such a lock.
    #
    #  @param observer
    #         An observer represented by the
    #         @ref DesignPatternExamples_python.observer.observersubject_numberproducer.IObserverNumberChanged "IObserverNumberChanged"
    #         interface.
    def SubscribeToNumberChanged(self, observer : IObserverNumberChanged) -> None:
        if not self._ContainsObserver(observer):
            self._observers.append(observer)


    ## A client calls this to unsubscribe an observer from this class
    #  instance so notifications are no longer received.  Does nothing
    #  if the given observer was not subscribed.
    #
    #  In a multi-threaded environment, this method would use a lock of some
    #  form.  This example doesn't use multiple threads so no lock is needed.
    #  See the
    #  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain.SendMessage "HandlerChain.SendMessage()"
    #  method in handlerchain_class.py for an example of such a lock.
    #
    #  @param observer
    #         An observer represented by the
    #         @ref DesignPatternExamples_python.observer.observersubject_numberproducer.IObserverNumberChanged "IObserverNumberChanged"
    #         interface.
    def UnsubscribeFromNumberChanged(self, observer : IObserverNumberChanged) -> None:
        if self._ContainsObserver(observer):
            self._observers.remove(observer)
