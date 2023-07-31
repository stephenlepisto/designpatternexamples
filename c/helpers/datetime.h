/// @file
/// @brief
/// Declaration of the DateTime functions, datetime_to_string() and datetime_now(),
/// to simplify getting the local time as a string.

#pragma once
#ifndef __DATETIME_H__
#define __DATETIME_H__

#include <time.h>

/// <summary>
/// Convert the specified time stamp to a string.
/// </summary>
/// <param name="timestamp">A time_t value representing the time stamp.</param>
/// <returns>Returns a string representation of the time stamp.  The pointer is
/// valid until the next time this function is called.</returns>
const char* datetime_to_string(time_t timestamp);

/// <summary>
/// Retrieve a time stamp that represents the current time.
/// </summary>
/// <returns>A time_t value representing the current time.</returns>
time_t datetime_now(void);

#endif // __DATETIME_H__
