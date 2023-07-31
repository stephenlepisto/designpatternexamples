/// @file
/// @brief
/// Implementation of the Observer_Exercise() function as used in the
/// @ref observer_pattern.

#include <stdio.h>
#include <stdlib.h>

#include "helpers/uint32_to_binary.h"

#include "Observer_NumberProducer.h"
#include "Observer_Exercise.h"


//=============================================================================
//=============================================================================

//=============================================================================
//=============================================================================

/// <summary>
/// Represents an observer that prints out the specified number from the
/// Subject in decimal.
/// </summary>
/// <param name="number">The number that was changed.</param>
static void ObserverForDecimal_NumberChanged(uint32_t number)
{
    printf("    Decimal    : %u\n", number);
}

/// <summary>
/// Represents an observer that prints out the specified number from the
/// Subject in hexadecimal.
/// </summary>
/// <param name="number">The number that was changed.</param>
static void ObserverForHexadecimal_NumberChanged(uint32_t number)
{
    printf("    Hexadecimal: 0X%08X\n", number);
}

/// <summary>
/// Represents an observer that prints out the specified number from the
/// Subject in binary.
/// </summary>
/// <param name="number">The number that was changed.</param>
static void ObserverForBinary_NumberChanged(uint32_t number)
{
    char buffer[(sizeof(uint32_t) * 8) + 1];
    uint32_to_binary(number, buffer, sizeof(buffer));
    printf("    Binary     : %s\n", buffer);
}


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref observer_pattern.
///
/// The Observer pattern allows for one or more observers to react to
/// changes in a Subject entity.
///
/// In this exercise, a number producer (the Subject) updates an internal
/// value every time the NumberProducer_UpdateNumber() function is called.
/// Three different observers are attached to the number producer and print out
/// the current value in different formats whenever the number is changed.
///
/// Since functions are used as the observers of the NumberProducer object,
/// the "push" model is used to push the updated number to each observer.
/// Otherwise, the observers would have to be given the NumberProducer object
/// so as to call a function to fetch the number from that object.
/// </summary>
// ! [Using Observer in C]
void Observer_Exercise(void)
{
    printf("\nObserver_Exercise\n");

    NumberProducer* producer = NumberProducer_Create(0);

    if (producer != NULL)
    {
        // Tell the number producer about the observers who are notified
        // whenever the value changes.
        bool subscribed = NumberProducer_SubscribeToNumberChanged(producer, ObserverForDecimal_NumberChanged);
        if (subscribed)
        {
            subscribed = NumberProducer_SubscribeToNumberChanged(producer, ObserverForHexadecimal_NumberChanged);
        }
        if (subscribed)
        {
            subscribed = NumberProducer_SubscribeToNumberChanged(producer, ObserverForBinary_NumberChanged);
        }

        // If everyone subscribed, trigger the observers
        if (subscribed)
        {
            // Call the number producer's Update() method a number of times.
            // The observers automatically print out the current value in
            // different bases.
            for (int index = 0; index < 10; ++index)
            {
                printf("  Update %d on number producer.  Results from observers:\n", index);
                NumberProducer_UpdateNumber(producer);
            }
        }

        // When done, remove the observers from the number producer.
        // It's always good to clean up after ourselves.
        NumberProducer_UnsubscribeFromNumberChanged(producer, ObserverForBinary_NumberChanged);
        NumberProducer_UnsubscribeFromNumberChanged(producer, ObserverForHexadecimal_NumberChanged);
        NumberProducer_UnsubscribeFromNumberChanged(producer, ObserverForDecimal_NumberChanged);

        NumberProducer_Destroy(producer);
        producer = NULL;
    }

    printf("  Done.\n");
}
// ! [Using Observer in C]
