/// @file
/// @brief
/// Declaration of the @ref Helpers::split "split" functions, for splitting
/// a string on delimiters.

#pragma once
#ifndef __SPLIT_H__
#define __SPLIT_H__

#include <string>
#include <vector>

namespace Helpers
{
    /// <summary>
    /// Split the given string into a list of strings given the character on
    /// which to split.  If the split character does not appear, return the
    /// original string as the first entry in the list.
    /// </summary>
    /// <param name="pszString">The string to split.</param>
    /// <param name="splitChars">The character or characters to split on.
    /// This parameter is treated as a list of characters on which to split the
    /// string.</param>
    /// <returns>A list of 1 or more strings resulting from the split.</returns>
    std::vector<std::string> split(const char* pszString, const char* splitChars = " ");

    /// <summary>
    /// Split the given string into a list of strings given the character on
    /// which to split.  If the split character does not appear, return the
    /// original string as the first entry in the list.
    /// </summary>
    /// <param name="szString">The string to split.</param>
    /// <param name="splitChars">The character or characters to split on.
    /// This parameter is treated as a list of characters on which to split the
    /// string.</param>
    /// <returns>A list of 1 or more strings resulting from the split.</returns>
    std::vector<std::string> split(const std::string& szString,
        const std::string& splitChars = " ");

    /// <summary>
    /// Split the given string into a list of strings given the character on
    /// which to split.  If the split character does not appear, return the
    /// original string as the first entry in the list.
    /// </summary>
    /// <param name="pszString">The string to split.</param>
    /// <param name="splitChars">The character or characters to split on.
    /// This parameter is treated as a list of characters on which to split the
    /// string.</param>
    /// <returns>A list of 1 or more strings resulting from the split.</returns>
    std::vector<std::wstring> split(const wchar_t* pszString,
        const wchar_t* splitChars = L" ");
    
    /// <summary>
    /// Split the given string into a list of strings given the character on
    /// which to split.  If the split character does not appear, return the
    /// original string as the first entry in the list.
    /// </summary>
    /// <param name="szString">The string to split.</param>
    /// <param name="splitChars">The character or characters to split on.
    /// This parameter is treated as a list of characters on which to split the
    /// string.</param>
    /// <returns>A list of 1 or more strings resulting from the split.</returns>
    std::vector<std::wstring> split(const std::wstring& szString,
        const std::wstring& splitChars = L" ");

} // end namespace

#endif // __SPLIT_H__
