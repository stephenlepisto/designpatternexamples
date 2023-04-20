/// @file
/// @brief
/// Implementation of the Mutex structure along with mutex_create(),
/// mutex_destroy(), mutex_lock(), and mutex_unlock() functions.

#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#include <stdio.h>
#else
// WARNING! WARNING! WARNING! WARNING! WARNING! WARNING! WARNING! WARNING!
// The POSIX mutex code has not been compiled, let alone tested.  If the
// documentation is correct, what I've written here should work, but I've
// heard that before.
#include <threads.h>
#endif

#include "mutex.h"

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
            mutex->handle = hMutex;
            created = true;
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("Error (0x%x)!  Failed to create a mutex.\n", lastError);
        }
#else
        mtx_t mutex_handle;
        int err = mtx_init(&mutex_handle, mtx_plain);
        if (err = thrd_success)
        {
            mutex->handle = mutex_handle;
            created = true;
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
        HANDLE hMutex = mutex->handle;
        if (CloseHandle(hMutex))
        {
            destroyed = true;
            mutex->handle = NULL;
        }
        else
        {
            DWORD lastError = GetLastError();
            printf("Error (0x%x)!  Failed to destroy the mutex.\n", lastError);
        }
#else
        mtx_t mutex_handle = mutex->handle;
        int err = mtx_destroy(&mutex_handle);
        if (err == thrd_success)
        {
            destroyed = true;
            mutex->handle = NULL;
        }
        else
        {
            printf("Error!  Failed to destroy a mutex.\n");
        }
#endif
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
        HANDLE hMutex = mutex->handle;
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
        mtx_t mutex_handle = mutex->handle;
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
        HANDLE hMutex = mutex->handle;
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
        mtx_t mutex_handle = mutex->handle;
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
