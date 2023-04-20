/// @file
/// @brief
/// Implementation of the Handler Chain functions, HandlerChain_SendMessage(),
/// HandlerChain_AddWindow(), HandlerChain_RemoveWindow(), and
/// HandlerChain_ToString(),
/// as used in the @ref handlerchain_pattern.

#include <stdlib.h>
#include <stdbool.h>

#include "helpers/mutex.h"
#include "helpers/uintarray.h"

#include "HandlerChain_MessageWindow.h"
#include "HandlerChain_HandlerFunctions.h"

/// <summary>
/// A mutex used to protect the handler list from cross-thread corruption.
/// </summary>
static Mutex _mutex;

/// <summary>
/// A flag to indicate whether the mutex has been initialized and is ready for use.
/// </summary>
static bool  _mutex_initialized = false;


//#############################################################################
//#############################################################################
//#############################################################################


/// <summary>
/// An atexit() handler to destroy the mutex on program exit.
/// </summary>
static void _DestroyMutex(void)
{
    if (_mutex_initialized)
    {
        mutex_destroy(&_mutex);
        _mutex_initialized = false;
    }
}

/// <summary>
/// Helper function to create the mutex, if not already created.
/// </summary>
/// <returns>Returns true if the mutex was created or already exists;
/// otherwise, returns false, the mutex is not usable.</returns>
static bool _CreateMutex()
{
    if (!_mutex_initialized)
    {
        _mutex_initialized = mutex_create(&_mutex);
        if (_mutex_initialized)
        {
            atexit(_DestroyMutex);
        }
    }
    return _mutex_initialized;
}

/// <summary>
/// Helper function to lock the mutex.
/// </summary>
static void _LockMutex()
{
    if (_CreateMutex())
    {
        mutex_lock(&_mutex);
    }
}

/// <summary>
/// Helper function to unlock the mutex.
/// </summary>
static void _UnlockMutex()
{
    if (_CreateMutex())
    {
        mutex_unlock(&_mutex);
    }
}



//#############################################################################
//#############################################################################
//#############################################################################

/// <summary>
/// List of IDs of @ref MessageWindow objects that can be sent messages.
/// </summary>
static UIntArray _handleList = { 0 };

//#############################################################################
//#############################################################################
//#############################################################################


///////////////////////////////////////////////////////////////////////////////
// HandlerChain_SendMessage()
///////////////////////////////////////////////////////////////////////////////
void HandlerChain_SendMessage(int windowId, Message* message)
{
    _LockMutex();
    UIntArray localList = { 0 };
    UIntArray_Copy(&_handleList, &localList);
    _UnlockMutex();

    for (size_t index = 0; index < localList.length; index++)
    {
        if (windowId == -1 || windowId == (int)localList.data[index])
        {
            if (MessageWindow_ProcessMessage((int)localList.data[index], message))
            {
                // Processing terminated
                break;
            }
        }
    }
    UIntArray_Clear(&localList);
}

///////////////////////////////////////////////////////////////////////////////
// HandlerChain_AddWindow()
///////////////////////////////////////////////////////////////////////////////
void HandlerChain_AddWindow(int windowId)
{
    _LockMutex();
    int foundIndex = UIntArray_Find(&_handleList, (uint32_t)windowId);
    if (foundIndex == -1)
    {
        UIntArray_AddInt(&_handleList, (uint32_t)windowId);
    }
    _UnlockMutex();
}

///////////////////////////////////////////////////////////////////////////////
// HandlerChain_RemoveWindow()
///////////////////////////////////////////////////////////////////////////////
void HandlerChain_RemoveWindow(int windowId)
{
    _LockMutex();
    int foundIndex = UIntArray_Find(&_handleList, (uint32_t)windowId);
    if (foundIndex != -1)
    {
        UIntArray_RemoveInt(&_handleList, foundIndex);
    }
    _UnlockMutex();
}

///////////////////////////////////////////////////////////////////////////////
// HandlerChain_ToString()
///////////////////////////////////////////////////////////////////////////////
void HandlerChain_ToString(DynamicString* output)
{
    if (output != NULL)
    {
        _LockMutex();
        UIntArray localList = { 0 };
        UIntArray_Copy(&_handleList, &localList);
        _UnlockMutex();

        for (size_t index = 0; index < _handleList.length; index++)
        {
            DynamicString localOutput = { 0 };
            MessageWindow_ToString((int)_handleList.data[index], &localOutput);
            if (localOutput.length != 0)
            {
                DynamicString_Append(output, "    ");
                DynamicString_Append(output, localOutput.string);
                DynamicString_Append(output, "\n");
            }
            DynamicString_Clear(&localOutput);
        }
        UIntArray_Clear(&localList);
    }
}
