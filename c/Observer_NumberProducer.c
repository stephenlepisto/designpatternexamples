/// @file
/// @brief
/// Declaration of the NumberProducer structure along with its support functions,
/// NumberProducer_Create(), NumberProducer_Destroy(),
/// NumberProducer_SubscribeToNumberChanged(), NumberProducer_UnsubscribeFromNumberChanged(),
/// and NumberProducer_UpdateNumber(),
/// as used in the  @ref observer_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "Observer_NumberProducer.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to notify all observers that the number has changed in the
/// given NumberProducer object.
/// </summary>
static void _NumberProducer_NotifyNumberChanged(NumberProducer* producer)
{
    if (producer != NULL)
    {
        uint32_t localNumber = producer->number;
        NumberChangedFunctionList localObserverList;
        // Copy the list so observers can change the original observers
        // during the notification (this isn't strictly needed in this
        // example but it is good practice for any notification system
        // that handles multiple observers where multiple threads might
        // be in play or observers can unsubscribe at any time, even in
        // the event notification).
        if (NumberChangedFunctionList_Copy(&producer->observerList, &localObserverList))
        {
            for (size_t index = 0; index < localObserverList.functions_count; index++)
            {
                NumberChangedFunction observer = localObserverList.functions[index];
                observer(localNumber);
            }

            NumberChangedFunctionList_Clear(&localObserverList);
        }
    }
}

//=============================================================================
//=============================================================================


///////////////////////////////////////////////////////////////////////////////
// NumberProducer_Create()
///////////////////////////////////////////////////////////////////////////////
NumberProducer* NumberProducer_Create(uint32_t number)
{
    NumberProducer* producer = calloc(1, sizeof(NumberProducer));

    if (producer != NULL)
    {
        producer->number = number;
    }
    else
    {
        printf("  Error!  Out of memory allocating space for the NumberProducer!\n");
    }

    return producer;
}

///////////////////////////////////////////////////////////////////////////////
// NumberProducer_Destroy()
///////////////////////////////////////////////////////////////////////////////
void NumberProducer_Destroy(NumberProducer* producer)
{
    if (producer != NULL)
    {
        NumberChangedFunctionList_Clear(&producer->observerList);
        free(producer);
    }
}

///////////////////////////////////////////////////////////////////////////////
// NumberProducer_SubscribeToNumberChanged()
///////////////////////////////////////////////////////////////////////////////
bool NumberProducer_SubscribeToNumberChanged(NumberProducer* producer, NumberChangedFunction observer)
{
    bool subscribed = false;

    if (producer != NULL && observer != NULL)
    {
        subscribed = true;
        int foundIndex = NumberChangedFunctionList_Find(&producer->observerList, observer);
        if (foundIndex == -1)
        {
            subscribed = NumberChangedFunctionList_Add(&producer->observerList, observer);
        }
    }
    return subscribed;
}

///////////////////////////////////////////////////////////////////////////////
// NumberProducer_UnsubscribeFromNumberChanged()
///////////////////////////////////////////////////////////////////////////////
void NumberProducer_UnsubscribeFromNumberChanged(NumberProducer* producer, NumberChangedFunction observer)
{
    if (producer != NULL && observer != NULL)
    {
        int foundIndex = NumberChangedFunctionList_Find(&producer->observerList, observer);
        if (foundIndex != -1)
        {
            NumberChangedFunctionList_Remove(&producer->observerList, foundIndex);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// NumberProducer_UpdateNumber()
///////////////////////////////////////////////////////////////////////////////
void NumberProducer_UpdateNumber(NumberProducer* producer)
{
    if (producer != NULL)
    {
        producer->number++;
        _NumberProducer_NotifyNumberChanged(producer);
    }
}
