/// @file
/// @brief
/// Declaration of the Mutex structure and supporting functions for working
/// with mutexes.
#pragma once
#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <stdbool.h>

/// <summary>
/// Represents a handle to a mutex.  Call mutex_create() to create the
/// mutex and mutex_destroy() to destroy the mutex (when done with it).
/// </summary>
typedef struct
{

    /// <summary>
    /// An opaque value that represents the operating system-specific mutex.
    /// </summary>
    void* handle;
} Mutex;

/// <summary>
/// Create a new mutex, which is initially not owned.
/// </summary>
/// <param name="mutex">A Mutex object in which the mutex is created.</param>
/// <returns>Returns true if the mutex was created; otherwise, returns false.
/// </returns>
bool mutex_create(Mutex* mutex);

/// <summary>
/// Destroy a previously created mutex.
/// </summary>
/// <param name="mutex">A Mutex object to destroy.</param>
/// <returns>Returns true if the mutex was destroyed; otherwise, returns false.
/// </returns>
bool mutex_destroy(Mutex* mutex);

/// <summary>
/// Lock a previously created and unlocked mutex.  This will block if the mutex
/// is already locked by some other thread.
/// </summary>
/// <param name="mutex">A Mutex object to lock.</param>
/// <returns>Returns true if the mutex was locked; otherwise, returns false.
/// </returns>
bool mutex_lock(Mutex* mutex);

/// <summary>
/// Unlock a previously locked mutex.
/// </summary>
/// <param name="mutex">A Mutex object to unlock.</param>
/// <returns>Returns true if the mutex was unlocked; otherwise, returns false.
/// </returns>
bool mutex_unlock(Mutex* mutex);


#endif // __MUTEX_H__

