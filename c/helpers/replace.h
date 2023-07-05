/// @file
/// @brief
/// Declaration of various helper functions for replacing characters or strings
/// in a string.

#pragma once
#ifndef __REPLACE_H__
#define __REPLACE_H__

/// <summary>
/// Replace all occurrences of narrow character `c1` with narrow character
/// `c2` in `s`, using case-sensitive search.
/// If `c2` is '\0' then all matches to `c1` are effectively removed from the
/// string.
/// </summary>
/// <param name="s">String to modify</param>
/// <param name="c1">Character to replace</param>
/// <param name="c2">Character to replace with</param>
void replace_chr(char* s, char c1, char c2);

/// <summary>
/// Replace all occurrences of narrow character `c1` with narrow character
/// `c2` in `s`, using case-insensitive search.
/// If `c2` is '\0' then all matches to `c1` are effectively removed from the
/// string.
/// </summary>
/// <param name="s">String to modify</param>
/// <param name="c1">Character to replace</param>
/// <param name="c2">Character to replace with</param>
void replace_chri(char* s, char c1, char c2);

/// <summary>
/// Replace all occurrences of narrow string `str1` with narrow string `str2`
/// in `s`, using case-sensitive search, returning a new string.
/// </summary>
/// <param name="s">String to modify</param>
/// <param name="str1">String to replace</param>
/// <param name="str2">String to replace with (can be an empty string to remove
/// `str1`).</param>
/// <returns>Returns a new string containing the modifications.  The string
/// must be released using free()</returns>
char* replace_str(const char* s, const char* str1, const char* str2);

/// <summary>
/// Replace all occurrences of narrow string `str1` with narrow string `str2`
/// in `s`, using case-insensitive search, returning a new string.
/// </summary>
/// <param name="s">String to modify</param>
/// <param name="str1">String to replace</param>
/// <param name="str2">String to replace with (can be an empty string to remove
/// `str1`).</param>
/// <returns>Returns a new string containing the modifications.  The string
/// must be released using free()</returns>
char* replace_stri(const char* s, const char* str1, const char* str2);

#endif // __REPLACE_H__

