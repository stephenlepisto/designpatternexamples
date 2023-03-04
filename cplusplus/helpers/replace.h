/// @file
/// @brief
/// Declaration of the @ref Helpers::Replace "Replace()" functions, for replacing
/// characters and strings in a string.

#pragma once
#ifndef __REPLACE_H__
#define __REPLACE_H__

#include <string>

namespace Helpers
{
    /// <summary>
    /// Replace all occurrences of narrow character `c1` with narrow character
    /// `c2` in `s`. If `c2` is empty then all matches to `str1` are effectively
    /// removed from the string.
    /// </summary>
    /// <param name="s">String to search</param>
    /// <param name="c1">Character to replace</param>
    /// <param name="c2">Character to replace with</param>
    /// <param name="bCaseInsensitive">true if to perform case-insensitive
    /// search; otherwise, use case-sensitive search</param>
    /// <returns>Returns the updated string</returns>
    std::string Replace(
            const std::string& s,
            char c1,
            char c2,
            bool bCaseInsensitive = false);

    /// <summary>
    /// Replace all occurrences of narrow string `str1` with narrow string
    /// `str2` in `s`.  If `str2` is empty then all matches to `str1` are
    /// effectively removed from the string.
    /// </summary>
    /// <param name="s">String to search</param>
    /// <param name="str1">String to replace</param>
    /// <param name="str2">String to replace with</param>
    /// <param name="bCaseInsensitive">true if to perform case-insensitive
    /// search; otherwise, use case-sensitive search</param>
    /// <returns>Returns the updated string</returns>
    std::string Replace(
            const std::string& s,
            const char* str1,
            const char* str2,
            bool bCaseInsensitive = false);

    /// <summary>
    /// Replace all occurrences of wide character `c1` with wide character
    /// `c2` in `s`.  If `c2` is empty then all matches to `str1` are
    /// effectively removed from the string.
    /// </summary>
    /// <param name="s">String to search</param>
    /// <param name="c1">Character to replace</param>
    /// <param name="c2">Character to replace with</param>
    /// <param name="bCaseInsensitive">true if to perform case-insensitive
    /// search; otherwise, use case-sensitive search</param>
    /// <returns>Returns the updated string</returns>
    std::wstring Replace(
            const std::wstring& s,
            wchar_t c1,
            wchar_t c2,
            bool bCaseInsensitive = false);

    /// <summary>
    /// Replace all occurrences of wide string `str1` with wide string
    /// `str2` in `s`.  If `str2` is empty then all matches to `str1` are
    /// effectively removed from the string.
    /// </summary>
    /// <param name="s">String to search</param>
    /// <param name="str1">String to replace</param>
    /// <param name="str2">String to replace with</param>
    /// <param name="bCaseInsensitive">true if to perform case-insensitive
    /// search; otherwise, use case-sensitive search</param>
    /// <returns>Returns the updated string</returns>
    std::wstring Replace(
            const std::wstring& s,
            const wchar_t* str1,
            const wchar_t* str2,
            bool bCaseInsensitive = false);

}; // end namespace Helpers

#endif // __REPLACE_H__
