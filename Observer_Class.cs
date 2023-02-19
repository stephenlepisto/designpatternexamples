// The Observer pattern is used when one or more entities need to be told
// about a change in state of another entity (typically known as the Subject)
// and those entities, upon notification, pull data from the Subject to
// complete their own specific tasks.  Alternatively, the Subject could push
// the data to the observing entities.
//
// The Observer pattern uses a publish/subscribe model, where entities
// interested in changes in the Subject subscribe to the Subject for change
// notifications.  This allows the Subject to notify multiple subscribers
// (observers) about a single change.  It is then up to the observer to do
// something in response to the change notification.
//
// One common example of the observer pattern is the View element of the
// Model-View-Controller architecture.  In this architecture, the Model holds
// all the data, the Controller is the input mediator (yes, an example of the
// Mediator pattern) between the Model and the outside world, and the View is
// what shows the Model to the outside world.  There can be multiple Views.
// When a change occurs in the Model, the Views are notified of the change.
// Each View then pulls data from the Model to render that specific view.
//
// At its most general, any event-based system is the Observer pattern in
// action.  A subscriber to the event -- the observer -- receives
// notifications when something occurs (a change).  The subscriber then reacts
// to that event as appropriate.
//
// The Subject typically defines a minimal interface an Observer must
// implement to subscribe to change notifications.  This interface can be
// literally an interface with one or more methods on it or it could be just a
// single function that is called (for a non-object-oriented approach).
//
// The Observer knows what it is observing because it has to not only
// subscribe to the Subject but potentially access the Subject for data that
// may have changed.  This knowledge of the Subject can be partially mitigated
// by defining an interface on the Subject the Observer can use to fetch data
// from the Subject.
//
// There are two ways the Observer and the Subject can interact:
//  1) The Observer pulls data from the Subject in response to a change
//     notification.
//  2) The Subject pushes the data to the Observer as part of the change
//     notification.
//
// The pull approach can be inefficient if multiple observers are observing
// the same Subject.  When each observer gets the change notification, each
// observer fetches potentially the same data from the Subject, producing
// redundant data fetches.  There is not a lot that can be done about this but
// at least the coupling is very loose between the Subject and the observers.
//
// The push approach can be more efficient as the data is part of the change
// notification and needs to be computed only once, regardless of the number
// of observers.  The question is how much data should be pushed to each
// observer and in what form.  This can be made easier if the observers
// implement an interface known to the Subject with one or more methods to be
// called as part of the process of sending the event notifications.
//
// In this example of the Observer pattern, a Subject contains a numerical
// value that can change.  There are three observers to the subject who are
// notified whenever the value changes.  Each observer pulls the number from
// the Subject and displays the number in a different base.  Typically these
// observers would run on different threads but in the interest of keeping
// things readable, everything runs on the same thread.  The order of the
// output is dictated by the order of the observers subscribing to the
// Subject.
//
// Note: This example could be made simpler by having the Subject push the
// data to the observers.  I wanted to show the more complex form of the
// Observer pattern, however, so I went with a pull model.
//
// The push model would have eliminated the need for the INumberProducer
// interface on the Subject as well as the need to take and store the
// INumberProducer object in each observer.  And that in turn would simplify
// each observer class down to a single method to support the
// IObserverNumberChanged interface.

using System;
using System.Text;

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in decimal.
    /// </summary>
    public class ObserverForDecimal : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        private INumberProducer _numberProducer;


        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForDecimal(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForDecimal constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
        }

        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in decimal.
        /// </remarks>
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            Console.WriteLine("    Decimal    : {0}", number);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in hexadecimal.
    /// </summary>
    public class ObserverForHexaDecimal : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer _numberProducer;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForHexaDecimal(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForHexaDecimal constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in hexadecimal using C#'s number formatting.
        /// </remarks>
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            Console.WriteLine("    Hexadecimal: 0x{0:X8}", number);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in binary.
    /// </summary>
    public class ObserverForBinary : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer _numberProducer;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForBinary(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForBinary constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in binary.  The value needs to be manually converted to
        /// binary as C# does not provide this support.
        /// </remarks>
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            StringBuilder output = new StringBuilder();
            uint mask = (uint)1 << 31;

            for (uint index = 0; index < 32; ++index)
            {
                if ((number & mask) != 0)
                {
                    output.Append("1");
                }
                else
                {
                    output.Append("0");
                }
                mask >>= 1;
            }

            Console.WriteLine("    Binary     : {0}", output);
        }
    }
}
