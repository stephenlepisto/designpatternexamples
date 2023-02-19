// The Observer pattern is used when one or more entities need to be told
// about a change in state of another entity (typically known as the Subject)
// and those entities, upon notification, pull data from the Subject to
// complete their own specific tasks.  Alternatively, the Subject could push
// the data to the observing entities.  The example uses a pull approach.
//
// The code in this file defines the Subject for the example.  In addition,
// this file contains the interfaces needed for the observers and the Subject
// to interact "at arms length" from each other, so neither has any more
// information about the other than is strictly necessary.

using System.Collections.Generic;

namespace DesignPatternExamples
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
    public interface IObserverNumberChanged
    {
        /// <summary>
        /// This is called whenever the number in the
        /// ObserverSubject_NumberProducer object is changed.
        /// </summary>
        void NumberChanged();
    }


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
    public interface IEventNotifications
    {
        void SubscribeToNumberChanged(IObserverNumberChanged observer);
        void UnsubscribeFromNumberChanged(IObserverNumberChanged observer);
    }


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
    public interface INumberProducer
    {
        /// <summary>
        /// Return the current value from the Subject.
        /// </summary>
        /// <returns>Returns an unsigned integer that is the current value.</returns>
        uint FetchNumber();
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Subject in this example, in this case, a class that
    /// contains a single number that is updated with a call to the Update()
    /// method.  Whenever Update() is called, the number is incremented and
    /// all observers are notified.  The observers then fetch the current
    /// number via the INumberProducer interface.
    /// </summary>
    class ObserverSubject_NumberProducer : IEventNotifications, INumberProducer
    {
        /// <summary>
        /// The list of observers subscribed to this class instance.
        /// </summary>
        private List<IObserverNumberChanged> _observers = new List<IObserverNumberChanged>();

        /// <summary>
        /// The number being maintained.
        /// </summary>
        private uint _number;


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
            IObserverNumberChanged[] observers = _observers.ToArray();

            foreach(IObserverNumberChanged observer in observers)
            {
                observer.NumberChanged();
            }
        }


        /// <summary>
        /// Update the number then notify all observers.
        /// </summary>
        public void Update()
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
        uint INumberProducer.FetchNumber()
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
        void IEventNotifications.SubscribeToNumberChanged(IObserverNumberChanged observer)
        {
            // In a multi-threaded environment, this would be protected by
            // a lock of some form.  This example doesn't use multiple threads
            // so no lock is needed.
            if (!_observers.Contains(observer))
            {
                _observers.Add(observer);
            }
        }


        /// <summary>
        /// A client calls this to unsubscribe an observer from this class
        /// instance so notifications are no longer received.  Does nothing
        /// if the given observer was not subscribed.
        /// </summary>
        /// <param name="observer">An observer represented by the IObserverNumberChanged interface.</param>
        void IEventNotifications.UnsubscribeFromNumberChanged(IObserverNumberChanged observer)
        {
            // In a multi-threaded environment, this would be protected by
            // a lock of some form.  This example doesn't use multiple threads
            // so no lock is needed.
            if (_observers.Contains(observer))
            {
                _observers.Remove(observer);
            }
        }
    }
}
