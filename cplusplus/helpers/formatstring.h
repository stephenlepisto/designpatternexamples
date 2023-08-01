/// @file
/// @brief
/// Declaration of the @ref Helpers::formatstring "formatstring()" function
/// that replaces sprintf() and snprintf() by allocating the right-sized buffer
/// and returning it.

#pragma once
#ifndef __FORMATSTRING_H__
#define __FORMATSTRING_H__

#include <string>

namespace Helpers
{

    /// <summary>
    /// Use the given string and arguments to return a buffer containing the
    /// formatted string.  The format and arguments follow the printf()
    /// functionality.
    /// </summary>
    /// <param name="format">String containing formatting codes as used with the
    /// printf() function.</param>
    /// <return>Returns a newly allocated buffer containing the zero-terminated
    /// formatted string.  Use free() to delete the buffer.  Returns NULL if no
    /// memory could be allocated.</returns>
    std::string formatstring(const char* fmt, ...);

} // end namespace


#endif // __FORMATSTRING_H__

