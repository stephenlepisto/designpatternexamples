/// @file
/// @brief
/// The @ref DesignPatternExamples_cpp::IObserverNumberChanged "IObserverNumberChanged",
/// @ref DesignPatternExamples_cpp::IEventNotifications "IEventNotifications",
/// and @ref DesignPatternExamples_cpp::INumberProducer "INumberProducer" interfaces,
/// and the @ref DesignPatternExamples_cpp::ObserverSubject_NumberProducer "ObserverSubject_NumberProducer"
/// class used in the @ref observer_pattern.
///
/// The Observer pattern is used when one or more entities need to be told
/// about a change in state of another entity (typically known as the Subject)
/// and those entities, upon notification, pull data from the Subject to
/// complete their own specific tasks.  Alternatively, the Subject could push
/// the data to the observing entities.  The example uses a pull approach.
///
/// The code in this file defines the Subject for the example.  In addition,
/// this file contains the interfaces needed for the observers and the Subject
/// to interact "at arms length" from each other, so neither has any more
/// information about the other than is strictly necessary.

#pragma once
#ifndef __OBSERVERSUBJECT_NUMBERPRODUCER_H__
#define __OBSERVERSUBJECT_NUMBERPRODUCER_H__

#include <algorithm>
#include <memory>
#include <stdint.h>
#include <vector>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents an observer to the Subject class.  An observer implements
    /// this interface and then subscribes to the Subject with the interface.
    /// The observer will be called whenever a change in the number is made.
    /// 
    /// This interface is specific to the ObserverSubject_NumberProducer
    /// example, which is a typical requirement for a Subject that supports
    /// observers.
    /// </summary>
    struct IObserverNumberChanged
    {
        /// <summary>
        /// Alias to make it easier to use this shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<IObserverNumberChanged>;

        /// <summary>
        /// Virtual destructor required for interfaces in abstract classes.
        /// </summary>
        virtual ~IObserverNumberChanged() {}

        /// <summary>
        /// This is called whenever the number in the
        /// ObserverSubject_NumberProducer object is changed.
        /// </summary>
        virtual void NumberChanged() = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a Subject that takes observers implementing the
    /// IObserverNumberChanged interface.
    /// </summary>
    /// <remarks>
    /// In more complex systems, an interface like this might have
    /// multiple subscribe/unsubscribe methods for different kinds of
    /// observers.  For C#, such multiple methods might actually be one
    /// Subscribe/Unsubscribe method that uses overloading to take different
    /// observer interfaces.
    /// 
    /// This interface is use to ensure the Subject implements all the
    /// necessary methods to support observers.
    /// </remarks>
    struct IEventNotifications
    {
        /// <summary>
        /// Virtual destructor required for interfaces in abstract classes.
        /// </summary>
        virtual ~IEventNotifications() {}

        virtual void SubscribeToNumberChanged(IObserverNumberChanged::shared_ptr_t observer) = 0;
        virtual void UnsubscribeFromNumberChanged(IObserverNumberChanged::shared_ptr_t observer) = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Subject to the observers.  This is the minimum
    /// needed by observers to get access to the data provided by the Subject
    /// class.
    /// </summary>
    /// <remarks>
    /// An interface is used to represent the Subject to the observers so the
    /// observers do not have too much knowledge about the Subject, allowing
    /// more freedom to change the Subject class implementation without
    /// affecting observers.  This interface would naturally have to change if
    /// the observers needed more data from the Subject.
    /// </remarks>
    struct INumberProducer
    {
        /// <summary>
        /// Alias to make it easier to use this shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<INumberProducer>;

        /// <summary>
        /// Virtual destructor required for interfaces in abstract classes.
        /// </summary>
        virtual ~INumberProducer() {}

        /// <summary>
        /// Update the number then notify all observers.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Return the current value from the Subject.
        /// </summary>
        /// <returns>Returns an unsigned integer that is the current value.</returns>
        virtual uint32_t FetchNumber() = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Subject in this example, in this case, a class that
    /// contains a single number that is updated with a call to the Update()
    /// method.  Whenever Update() is called, the number is incremented and
    /// all observers are notified.  The observers then fetch the current
    /// number via the INumberProducer interface.
    /// </summary>
    class ObserverSubject_NumberProducer : public IEventNotifications, public INumberProducer
    {
    private:
        
        using ObserversList = std::vector<IObserverNumberChanged::shared_ptr_t>;

        /// <summary>
        /// The list of observers subscribed to this class instance.
        /// </summary>
        ObserversList _observers;

        /// <summary>
        /// The number being maintained.
        /// </summary>
        uint32_t _number;


    private:
        /// <summary>
        /// Helper method to notify all observers that the number has changed.
        /// </summary>
        void _NotifyNumberChanged()
        {
            // Copy the list so observers can change the original observers
            // during the notification (this isn't strictly needed in this
            // example but it is good practice for any notification system
            // that handles multiple observers where multiple threads might
            // be in play or observers can unsubscribe at any time, even in
            // the event notification).
            ObserversList observers = _observers;

            for(IObserverNumberChanged::shared_ptr_t observer : observers)
            {
                observer->NumberChanged();
            }
        }

        /// <summary>
        /// Helper method to retrieve the iterator to the specified observer
        /// if the observer is in the list.
        /// </summary>
        /// <param name="observer">An observer to look for.</param>
        /// <returns>Returns an iterator to the found observer; otherwise,
        /// returns `std::end(_observers)`.</returns>
        ObserversList::iterator _FindObserver(const IObserverNumberChanged::shared_ptr_t& observer)
        {
            ObserversList::iterator foundIter;
            return std::find(std::begin(_observers), std::end(_observers), observer);
        }


        /// <summary>
        /// Helper method to determine if the specified observer is already
        /// present in the list of observers for this class.
        /// </summary>
        /// <param name="observer">An observer to look for.</param>
        /// <returns>Returns true if the observer is on this class's list of
        /// observers; otherwise, returns false.</returns>
        bool _ContainsObserver(const IObserverNumberChanged::shared_ptr_t& observer)
        {
            ObserversList::iterator foundIter;
            foundIter = _FindObserver(observer);
            return foundIter != std::end(_observers);
        }

    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        ObserverSubject_NumberProducer()
            : _number(0)
        {
        }


        /// <summary>
        /// Update the number then notify all observers.
        /// </summary>
        void Update() override
        {
            ++_number;
            _NotifyNumberChanged();
        }


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Implementation of the INumberProducer interface.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        /// <summary>
        /// Observers call this method to fetch the current number.
        /// </summary>
        /// <returns>Returns the current number.</returns>
        uint32_t FetchNumber() override
        {
            return _number;
        }


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Implementation of the IEventNotifications interface.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        /// <summary>
        /// A client calls this to subscribe an observer to this class instance
        /// for notifications about changing numbers.  Does nothing if the
        /// given observer is already subscribed.
        /// </summary>
        /// <param name="observer">An observer represented by the IObserverNumberChanged interface.</param>
        /// <remarks>In a multi-threaded environment, this method would use a
        /// lock of some form.  This example doesn't use multiple threads so no
        /// lock is needed.  See the
        /// @ref DesignPatternExamples_cpp::HandlerChain::SendMessage() "HandlerChain::SendMessage()"
        /// method in HandlerChain_Class.cpp for an example of such a lock.
        /// </remarks>
        void SubscribeToNumberChanged(IObserverNumberChanged::shared_ptr_t observer)
        {
            if (!_ContainsObserver(observer))
            {
                _observers.push_back(observer);
            }
        }


        /// <summary>
        /// A client calls this to unsubscribe an observer from this class
        /// instance so notifications are no longer received.  Does nothing
        /// if the given observer was not subscribed.
        /// </summary>
        /// <param name="observer">An observer represented by the IObserverNumberChanged interface.</param>
        /// <remarks>In a multi-threaded environment, this method would use a
        /// lock of some form.  This example doesn't use multiple threads so no
        /// lock is needed.  See the
        /// @ref DesignPatternExamples_cpp::HandlerChain::SendMessage() "HandlerChain::SendMessage()"
        /// method in HandlerChain_Class.cpp for an example of such a lock.
        /// </remarks>
        void UnsubscribeFromNumberChanged(IObserverNumberChanged::shared_ptr_t observer)
        {
            ObserversList::iterator foundIter;
            foundIter = _FindObserver(observer);
            if (foundIter != std::end(_observers))
            {
                _observers.erase(foundIter);
            }
        }
    };

} // end namespace


#endif // __OBSERVERSUBJECT_NUMBERPRODUCER_H__

