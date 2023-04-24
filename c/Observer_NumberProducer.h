/// @file
/// @brief
/// Declaration of the NumberProducer structure along with its support functions,
/// NumberProducer_Create(), NumberProducer_Destroy(),
/// NumberProducer_SubscribeToNumberChanged(), NumberProducer_UnsubscribeFromNumberChanged(),
/// and NumberProducer_UpdateNumber(),
/// as used in the  @ref observer_pattern.

#pragma once
#ifndef __OBSERVER_NUMBERPRODUCER_H__
#define __OBSERVER_NUMBERPRODUCER_H__

#include "Observer_NumberChangedFunctionList.h"

/// <summary>
/// Represents the Subject in this example.  In this case, a structure that
/// contains a list of observers and a single number that is updated.  When the
/// NumberProducer_UpdateNumber() function is called, the number is incremented
/// and all observers are notified.  The observers are passed the changed
/// number.
/// </summary>
typedef struct
{
    /// <summary>
    /// The number being maintained.
    /// </summary>
    uint32_t number;

    /// <summary>
    /// The list of observers subscribed to this class instance.
    /// </summary>
    NumberChangedFunctionList observerList;
} NumberProducer;

/// <summary>
/// Create an instance of the NumberProducer structure and initialize the
/// structure with the specified number.
/// </summary>
/// <param name="number">The number to start off with.</param>
/// <returns>Returns a pointer to a NumberProducer object if successful;
/// otherwise, returns NULL, indicating an out of memory condition (or a NULL
/// argument).</returns>
NumberProducer* NumberProducer_Create(uint32_t number);

/// <summary>
/// Destroy the given instance of a NumberProducer object.  After this function
/// returns, the pointer to the NumberProducer instance is no longer valid.
/// </summary>
/// <param name="producer">The NumberProducer object to destroy.</param>
void NumberProducer_Destroy(NumberProducer* producer);

/// <summary>
/// Subscribe to the given NumberProducer to received changes to that producer's
/// number.  Does nothing if the given observer is already subscribed.
/// </summary>
/// <param name="producer">The NumberProducer object to subscribe to.</param>
/// <param name="observer">A function to be called when the producer's number
/// changes.</param>
/// <returns>Returns true if the subscribe operation succeeded; otherwise,
/// returns false, indicating an out of memory condition (or a NULL argument
/// was passed in).</returns>
/// <remarks>In a multi-threaded environment, this method would use a
/// lock of some form.  This example doesn't use multiple threads so no
/// lock is needed.  See the
/// @ref DesignPatternExamples_cpp::HandlerChain::SendMessage() "HandlerChain::SendMessage()"
/// method in HandlerChain_Class.cpp for an example of such a lock.
/// </remarks>
bool NumberProducer_SubscribeToNumberChanged(NumberProducer* producer, NumberChangedFunction observer);

/// <summary>
/// Unsubscribe from the Given NumberProducer so the given observer will no
/// longer be called when the producer's number is changed.
/// </summary>
/// <param name="producer">The NumberProducer object to unsubscribe from.</param>
/// <param name="observer">The function that was being called as the observer.</param>
void NumberProducer_UnsubscribeFromNumberChanged(NumberProducer* producer, NumberChangedFunction observer);

/// <summary>
/// Update the number in the given NumberProducer object, triggering a call to
/// all observer in the producer.
/// </summary>
void NumberProducer_UpdateNumber(NumberProducer* producer);

#endif //__OBSERVER_NUMBERPRODUCER_H__

