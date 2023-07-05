/// @file
/// @brief
/// Declaration of the ConstStringList structure and supporting functions to
/// work with a list of constant strings.

#pragma once
#ifndef __CONSTSTRINGLIST_H__
#define __CONSTSTRINGLIST_H__

#include <stdbool.h>

/// <summary>
/// Represents a list of pointers to zero-terminated strings that are to remain
/// constant and never deleted.  In other words, we assume the lifetime of the
/// strings is at least as long as the instance of this structure that points
/// to those strings.
/// </summary>
typedef struct _ConstStringList
{
    /// <summary>
    /// Pointer to an array of zero-terminated string pointers.  These strings
    /// are constant and will not be duplicated or deleted.
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

} ConstStringList;


/// <summary>
/// Initialize the given string list.
/// </summary>
/// <param name="stringList">Pointer to a ConstStringList structure that is to be
/// initialized.  Cannot be NULL</param>
void ConstStringList_Initialize(ConstStringList* stringList);

/// <summary>
/// Clear the specified string list.  The strings in the list are left alone,
/// but the list itself is deleted.
/// The string list can then be used to add new strings.
/// </summary>
/// <param name="stringList">The ConstStringList to clear.</param>
void ConstStringList_Clear(ConstStringList* stringList);

/// <summary>
/// Add a string to the given string list.
/// </summary>
/// <param name="stringList">A pointer to a ConstStringList representing the list of
/// strings.</param>
/// <param name="string">The string to add to the list.  The string is added
/// as is to the list, so its lifetime must be at least as long as the
/// ConstStringList object.</param>
/// <returns>Returns true if the string was added to the list; otherwise, returns
/// false, indicating an out of memory condition has occurred (the original
/// string list is untouched in this case).</returns>
bool ConstStringList_AddString(ConstStringList* stringList, const char* string);

/// <summary>
/// Add an array of strings to the given string list.
/// </summary>
/// <param name="stringList">A pointer to a ConstStringList representing the list of
/// strings.</param>
/// <param name="strings">Pointer to an array of constant strings to add to the list.
/// The pointers to the strings are copied into the list.</param>
/// <param name="numStrings">Number of strings in the `strings` parameter to
/// add.</param>
/// <returns>Returns true if the string was added to the list; otherwise, returns
/// false, indicating an out of memory condition has occurred (the original
/// string list is untouched in this case).</returns>
bool ConstStringList_AddStrings(ConstStringList* stringList, const char** strings, size_t numStrings);

/// <summary>
/// Remove the specified string from the given string list.
/// </summary>
/// <param name="stringList">A pointer to a ConstStringList representing the list of
/// strings.</param>
/// <param name="removeIndex">Index of the string to remove from the list.  Call
/// ConstStringList_Find() to get the index.</param>
void ConstStringList_Remove(ConstStringList* stringList, int removeIndex);

/// <summary>
/// Search the given string list for the given string.  If found, return the
/// index of the found string.
/// </summary>
/// <param name="stringList">A pointer to a ConstStringList representing the list of
/// string to search.</param>
/// <param name="string">The string to search for.</param>
/// <returns>Returns an index into the string list of the string if found;
/// otherwise, returns -1 if the string is not found.</returns>
int ConstStringList_Find(ConstStringList* stringList, const char* string);

/// <summary>
/// Compare two strings lists to determine if they have the same contents.
/// </summary>
/// <param name="left">A pointer to the first ConstStringList representing a
/// list of strings to compare.</param>
/// <param name="right">A pointer to the second ConstStringList representing
/// a list of strings to compare.</param>
/// <returns>Returns true if the two lists have the same content, regardless of
/// the order of the content in either list; otherwise, returns false.</returns>
bool ConstStringList_AreListsEqual(ConstStringList* left, ConstStringList* right);

#endif // __CONSTSTRINGLIST_H__

