/// @file
/// @brief
/// Declaration of the @ref Helpers::DateTime "DateTime" class to simplify
/// getting the local time as a string (modeled after the C# version).

#pragma once
#ifndef __DATETIME_H__
#define __DATETIME_H__

#include <time.h>
#include <string>

namespace Helpers
{
    /// <summary>
    /// Represents a timestamp composed of a date and a time encoded in a
    /// time_t value.  Provides ways of getting the current time and to format
    /// the time in a string.
    /// </summary>
    class DateTime
    {
    private:
        time_t timestamp;

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        DateTime()
            : timestamp(0)
        {}

        /// <summary>
        /// Constructor that takes a time_t.
        /// </summary>
        /// <param name="timestamp">The time to use in this DateTime.</param>
        DateTime(time_t _timestamp) : timestamp(_timestamp) {}
        /// <summary>
        /// Copy constructor.  Construct from another DateTime.
        /// </summary>
        /// <param name="e">Another DateTime object.</param>
        DateTime(const DateTime& e) : timestamp(e.timestamp) {}
        /// <summary>
        /// Copy operator.  Copy from another DateTime.
        /// </summary>
        /// <param name="e">Another DateTime object.</param>
        /// <returns>Returns reference to this DateTime.</returns>
        DateTime& operator=(const DateTime& e) { timestamp = e.timestamp; return *this; }

        /// <summary>
        /// Format the DateTime as a string.  The format is "standard" (in this
        /// case, preset to 02/22/2023 10:26:12 AM, local time).
        /// </summary>
        /// <returns>String containing the date and time.</returns>
        std::string ToString();

        /// <summary>
        /// Return the current date and time.
        /// </summary>
        /// <returns>Returns a DateTime object containing the current date and time.
        /// </returns>
        static DateTime Now();
    };

} // end namespace

#endif // __DATETIME_H__
