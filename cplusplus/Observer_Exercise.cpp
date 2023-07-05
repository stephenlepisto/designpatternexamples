/// @file
/// @brief
/// Implementation of the Observer_Exercise() function as used in the 
/// @ref observer_pattern.

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Observer_Exercise.h"
#include "Observer_Class.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref observer_pattern "Observer" design pattern.
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
    // ! [Using Observer in C++]
    void Observer_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Observer Exercise" << std::endl;

        INumberProducer::shared_ptr_t numberProducer = std::make_shared<ObserverSubject_NumberProducer>();

        // The number producer is passed to the observers so the observers
        // can get the number to display.  The observers only see the
        // INumberProducer interface, to minimize knowledge about the
        // Subject.
        IObserverNumberChanged::shared_ptr_t observerDecimal = std::make_shared<ObserverForDecimal>(numberProducer);
        IObserverNumberChanged::shared_ptr_t observerHexadecimal = std::make_shared<ObserverForHexaDecimal>(numberProducer);
        IObserverNumberChanged::shared_ptr_t observerBinary = std::make_shared<ObserverForBinary>(numberProducer);

        // Tell the number producer about the observers who are notified
        // whenever the value changes.
        IEventNotifications* eventNotifier = dynamic_cast<IEventNotifications*>(numberProducer.get());
        if (eventNotifier != nullptr)
        {
            eventNotifier->SubscribeToNumberChanged(observerDecimal);
            eventNotifier->SubscribeToNumberChanged(observerHexadecimal);
            eventNotifier->SubscribeToNumberChanged(observerBinary);
        }

        // Call the number producer's Update() method a number of times.
        // The observers automatically print out the current value in
        // different bases.
        for (int index = 0; index < 10; ++index)
        {
            std::cout
                << std::format("  Update {0} on number producer.  Results from observers:", index)
                << std::endl;
            numberProducer->Update();
        }

        if (eventNotifier != nullptr)
        {
            // When done, remove the observers from the number producer.
            // It's always good to clean up after ourselves.
            eventNotifier->UnsubscribeFromNumberChanged(observerDecimal);
            eventNotifier->UnsubscribeFromNumberChanged(observerHexadecimal);
            eventNotifier->UnsubscribeFromNumberChanged(observerBinary);
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Observer in C++]

} // end namespace
