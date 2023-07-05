/// @file
/// @brief
/// Declaration of the StringList structure and supporting functions to
/// work with a list of allocated strings.

#pragma once
#ifndef __STRINGLIST_H__
#define __STRINGLIST_H__

#include <stdbool.h>

/// <summary>
/// Represents a list of pointers to zero-terminated strings.
/// </summary>
typedef struct _StringList
{
    /// <summary>
    /// Pointer to an array of zero-terminated string pointers.
    /// </summary>
    const char** strings;

    /// <summary>
    /// Number of strings in the @p strings list.
    /// </summary>
    size_t strings_count;

    /// <summary>
    /// The number of strings that can be held in the @p strings list.
    /// </summary>
    size_t allocated_count;

} StringList;


/// <summary>
/// Initialize the given string list.
/// </summary>
/// <param name="stringList">Pointer to a StringList structure that is to be
/// initialized.  Cannot be NULL</param>
void StringList_Initialize(StringList* stringList);

/// <summary>
/// Clear the specified string list.  All strings in the list are released.
/// The string list can then be used to add new strings.
/// </summary>
/// <param name="stringList">The StringList to clear.</param>
void StringList_Clear(StringList* stringList);

/// <summary>
/// Add a string to the given string list.
/// </summary>
/// <param name="stringList">A pointer to a StringList representing the list of
/// strings.</param>
/// <param name="string">The string to add to the list.  The string is duplicated
/// and appended to the list.</param>
/// <returns>Returns true if the string was added to the list; otherwise, returns
/// false, indicating an out of memory condition has occurred (the original
/// string list is untouched in this case).</returns>
bool StringList_AddString(StringList* stringList, const char* string);

/// <summary>
/// Add an array of strings to the given string list.
/// </summary>
/// <param name="stringList">A pointer to a StringList representing the list of
/// strings.</param>
/// <param name="strings">Pointer to an array of strings to add to the list.
/// The strings are duplicated and appended to the list.</param>
/// <param name="numStrings">Number of strings in the `strings` parameter to
/// add.</param>
/// <returns>Returns true if the string was added to the list; otherwise, returns
/// false, indicating an out of memory condition has occurred (the original
/// string list is untouched in this case).</returns>
bool StringList_AddStrings(StringList* stringList, const char** strings, size_t numStrings);

/// <summary>
/// Remove the specified string from the given string list.
/// </summary>
/// <param name="stringList">A pointer to a StringList representing the list of
/// strings.</param>
/// <param name="removeIndex">Index of the string to remove from the list.  Call
/// StringList_Find() to get the index.</param>
void StringList_Remove(StringList* stringList, int removeIndex);

/// <summary>
/// Search the given string list for the given string.  If found, return the
/// index of the found string.
/// </summary>
/// <param name="stringList">A pointer to a StringList representing the list of
/// string to search.</param>
/// <param name="string">The string to search for.</param>
/// <returns>Returns an index into the string list of the string if found;
/// otherwise, returns -1 if the string is not found.</returns>
int StringList_Find(StringList* stringList, const char* string);

#endif // __STRINGLIST_H__

