/// @file
/// @brief
/// Declaration of the @ref StringList structure and supporting functions to
/// work with a list of strings: StringList_Create(), StringList_Destroy(), and
/// StringList_AddString().

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

} StringList;


/// <summary>
/// Initialize the given string list.
/// </summary>
/// <param name="stringList">Pointer to a StringList structure that is to be
/// initialized.  Cannot be NULL</param>
void StringList_Initialize(StringList* stringList);

/// <summary>
/// Destroy a string list.  All strings are released as is the given string list.
/// The string list is not valid after this call.
/// </summary>
/// <param name="stringList">The StringList to destroy.</param>
void StringList_Destroy(StringList* stringList);

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

