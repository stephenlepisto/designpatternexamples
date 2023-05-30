/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Observer_Exercise "Observer_Exercise"
/// class used in the @ref observer_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref observer_pattern in C#.
    /// 
    /// The Observer pattern allows for one or more observers to react to
    /// changes in a Subject entity.
    /// 
    /// In this exercise, a number producer (the Subject) updates an internal
    /// value every time the Update() method is called.  Three different
    /// observers are attached to the number producer and print out the
    /// current value in different formats whenever the number is changed.
    /// 
    /// Note: Interfaces are used throughout this example.  For example, to
    /// subscribe to the number producer, the IEventNotifications interface
    /// must be obtained from the number producer.  The number producer is
    /// represented to the observers with the INumberProducer interface and
    /// the observers are represented to the number producer with the
    /// IObserverNumberChanged interface.  This highlights a common way to
    /// implement a "pull" style observer without having too much knowledge
    /// about the Subject.
    /// </summary>
    internal class Observer_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref observer_pattern in C#.
        /// </summary>
        // ! [Using Observer in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Observer Exercise");

            ObserverSubject_NumberProducer numberProducer = new ObserverSubject_NumberProducer();

            // The number producer is passed to the observers so the observers
            // can get the number to display.  The observers only see the
            // INumberProducer interface, to minimize knowledge about the
            // Subject.
            ObserverForDecimal observerDecimal = new ObserverForDecimal(numberProducer);
            ObserverForHexaDecimal observerHexadecimal = new ObserverForHexaDecimal(numberProducer);
            ObserverForBinary observerBinary = new ObserverForBinary(numberProducer);

            // Tell the number producer about the observers who are notified
            // whenever the value changes.
            IEventNotifications eventNotifier = numberProducer as IEventNotifications;
            eventNotifier.SubscribeToNumberChanged(observerDecimal);
            eventNotifier.SubscribeToNumberChanged(observerHexadecimal);
            eventNotifier.SubscribeToNumberChanged(observerBinary);

            // Call the number producer's Update() method a number of times.
            // The observers automatically print out the current value in
            // different bases.
            for (int index = 0; index < 10; ++index)
            {
                Console.WriteLine("  Update {0} on number producer.  Results from observers:", index);
                numberProducer.Update();
            }

            // When done, remove the observers from the number producer.
            // It's always good to clean up after ourselves.
            eventNotifier.UnsubscribeFromNumberChanged(observerDecimal);
            eventNotifier.UnsubscribeFromNumberChanged(observerHexadecimal);
            eventNotifier.UnsubscribeFromNumberChanged(observerBinary);

            Console.WriteLine("  Done.");
        }
        // ! [Using Observer in C#]
    }
}
