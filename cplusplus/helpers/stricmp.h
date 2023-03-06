/// @file
/// @brief
/// Declaration of the @ref Helpers::stricmp "stricmp" function, case-insensitive
/// string comparison for narrow character strings.
/// 
/// Function to compare two strings in a case-insensitive way.  Handles
/// const char* and std::string as arguments.
#pragma once
#ifndef __STRICMP_H__
#define __STRICMP_H__

#include <string>

namespace Helpers
{
    /// <summary>
    /// Compare two strings in a case-insensitive manner to determine their
    /// alphabetical order relative to each other.
    /// </summary>
    /// <param name="first">First string compare.</param>
    /// <param name="second">Second string to compare</param>
    /// <returns>Returns &lt; 0 if first comes before second; 0 if first equals
    /// second; and &gt; 0 if first comes after second.</returns>
    int stricmp(const char* first, const char* second);

    /// <summary>
    /// Compare two strings in a case-insensitive manner to determine their
    /// alphabetical order relative to each other.
    /// </summary>
    /// <param name="first">First string compare.</param>
    /// <param name="second">Second string to compare</param>
    /// <returns>Returns &lt; 0 if first comes before second; 0 if first equals
    /// second; and &gt; 0 if first comes after second.</returns>
    int stricmp(const std::string& first, const std::string& second);

} // end namespace

#endif // __STRICMP_H__

