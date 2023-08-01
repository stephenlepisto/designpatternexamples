/// @file
/// @brief
/// Implementation of the functions used for working with the Mutex structure
/// that deal with mutexes.

#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <Windows.h>
#define MUTEX_TYPE HANDLE
#else
#include <threads.h>
#define MUTEX_TYPE mtx_t
#endif

#include "mutex.h"

//-----------------------------------------------------------------------------
// The following functions are used to hide the differences between different
// mutex handles by storing a copy of the handle in allocated heap space.  The
// pointer to the copy is then kept as an opaque handle.
//
// The MUTEX_TYPE macro contains the actual type of the mutex handle for each
// operating system.
//-----------------------------------------------------------------------------

/// <summary>
/// Helper function to retrieve the mutex handle from the given memory pointer.
/// </summary>
/// <param name="handle">Pointer to the memory containing the mutex handle.
/// Cannot be NULL.</param>
/// <returns>Returns the handle from the memory pointer.</returns>
static MUTEX_TYPE _get_mutex_handle(void* handle)
{
    return *(MUTEX_TYPE*)handle;
}

/// <summary>
/// Helper function to allocate memory from the heap in which to store the
/// given mutex handle.  Returns the pointer to the memory containing the
/// mutex handle.
/// </summary>
/// <param name="handle">The handle to the mutex to store.</param>
/// <returns>Returns pointer to the memory containing the mutex handle.</returns>
static void *_allocate_mutex_handle(MUTEX_TYPE handle)
{
    void *handle_ptr = malloc(sizeof(MUTEX_TYPE));
    if (handle_ptr != NULL)
    {
        *(MUTEX_TYPE*)handle_ptr = handle;
    }
    return handle_ptr;
}

/// <summary>
/// Helper function to deallocate memory that contained a mutex handle.  The
/// mutex handle itself should be destroyed through normal means.
/// </summary>
/// <param name="handle">Pointer to the memory holding a mutex handle.</param>
static void _deallocate_mutex_handle(void *handle)
{
    free(handle);
}

//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// mutex_create()
///////////////////////////////////////////////////////////////////////////////
bool mutex_create(Mutex* mutex)
{
    bool created = false;

    if (mutex != NULL)
    {
        mutex->handle = NULL;
#ifdef _MSC_VER
        HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
        if (hMutex != NULL)
        {
            mutex->handle = _allocate_mutex_handle(hMutex);
            if (mutex->handle != NULL)
            {
                // mutex->handle = hMutex;
                created = true;
            }
            else
            {
                printf("Error! Out of memory saving mutex handle.\n");
                CloseHandle(hMutex);
            }
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("Error (0x%x)!  Failed to create a mutex.\n", lastError);
        }
#else
        mtx_t mutex_handle;
        int err = mtx_init(&mutex_handle, mtx_plain);
        if (err == thrd_success)
        {
            mutex->handle = _allocate_mutex_handle(mutex_handle);
            if (mutex->handle != NULL)
            {
                created = true;
            }
            else
            {
                printf("Error! Out of memory saving mutex handle.\n");
                mtx_destroy(&mutex_handle);
            }
        }
        else
        {
            printf("Error! Failed to create a mutex.\n");
        }
#endif
    }

    return created;
}

///////////////////////////////////////////////////////////////////////////////
// mutex_destroy()
///////////////////////////////////////////////////////////////////////////////
bool mutex_destroy(Mutex* mutex)
{
    bool destroyed = false;

    if (mutex != NULL && mutex->handle != NULL)
    {
#ifdef _MSC_VER
        HANDLE hMutex = _get_mutex_handle(mutex->handle);
        if (CloseHandle(hMutex))
        {
            destroyed = true;
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("Error (0x%x)!  Failed to destroy the mutex.\n", lastError);
        }
#else
        mtx_t mutex_handle = _get_mutex_handle(mutex->handle);
        mtx_destroy(&mutex_handle);
        destroyed = true;
#endif
        _deallocate_mutex_handle(mutex->handle);
        mutex->handle = NULL;
    }

    return destroyed;
}

///////////////////////////////////////////////////////////////////////////////
// mutex_lock()
///////////////////////////////////////////////////////////////////////////////
bool mutex_lock(Mutex* mutex)
{
    bool locked = false;

    if (mutex != NULL && mutex->handle != NULL)
    {
#ifdef _MSC_VER
        HANDLE hMutex = _get_mutex_handle(mutex->handle);
        DWORD waitResult = WaitForSingleObject(hMutex, INFINITE);
        if (waitResult == WAIT_OBJECT_0)
        {
            locked = true;
        }
        else if (waitResult == WAIT_ABANDONED)
        {
            printf("Error! While attempting to lock a mutex, it was found to be abandoned.\n");
        }
#else
        mtx_t mutex_handle = _get_mutex_handle(mutex->handle);
        int err = mtx_lock(&mutex_handle);
        if (err == thrd_success)
        {
            locked = true;
        }
        else
        {
            printf("Error! Failed to lock a mutex.\n");
        }
#endif
    }

    return locked;
}

///////////////////////////////////////////////////////////////////////////////
// mutex_unlock()
///////////////////////////////////////////////////////////////////////////////
bool mutex_unlock(Mutex* mutex)
{
    bool unlocked = false;

    if (mutex != NULL && mutex->handle != NULL)
    {
#ifdef _MSC_VER
        HANDLE hMutex = _get_mutex_handle(mutex->handle);
        if (ReleaseMutex(hMutex))
        {
            unlocked = true;
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("Error (0x%x)!  Failed to unlock a mutex.\n", lastError);
        }
#else
        mtx_t mutex_handle = _get_mutex_handle(mutex->handle);
        int err = mtx_unlock(&mutex_handle);
        if (err == thrd_success)
        {
            unlocked = true;
        }
        else
        {
            printf("Error! Failed to unlock a mutex.\n");
        }
#endif
    }

    return unlocked;
}
