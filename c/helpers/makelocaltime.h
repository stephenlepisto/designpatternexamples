/// @file
/// @brief
/// Declaration of the makelocaltime() function
/// to convert a time_t to a struct tm containing the local time.

#pragma once
#ifndef __MAKELOCALTIME_H__
#define __MAKELOCALTIME_H__

#include <time.h>

/// <summary>
/// Convert the given time to local time.
/// 
/// Hides the differences between multiple C library implementations.
/// </summary>
/// <param name="time">Pointer to the time_t object representing the time to
/// convert.</param>
/// <param name="timestruct">Pointer to a struct tm in which to put the results
/// of converting to local time.</param>
/// <returns>Returns the pointer to the struct tm if all is well; otherwise,
/// returns NULL, indicating an error (runtime constraint violation or a
/// failure to convert the specified time to local calendar time).</returns>
/// <remarks>
/// This is an example of a function acting as an adapter (see @ref adapter_pattern).
/// The rest of the program just wants to convert a time stamp to local time
/// and doesn't want to know about the differences between implementations of
/// the C library.
/// </remarks>
struct tm* makelocaltime(const time_t* time, struct tm* timestruct);

#endif // __MAKELOCALTIME_H__

