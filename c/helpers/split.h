/// @file
/// @brief
/// Declaration of the split() function, for splitting
/// a string on delimiters, along with the SplitList_Clear() function for
/// releasing the resources in a SplitList object.

#pragma once
#ifndef __SPLIT_H__
#define __SPLIT_H__

#include "stringlist.h"

/// <summary>
/// Represents a collection of sub-strings split from a single string using
/// the split() function.
/// </summary>
typedef struct SplitList
{
    const char** strings;  ///< Pointers to each sub-string.
    size_t strings_count;  ///< Number of sub-strings.
} SplitList;

/// <summary>
/// Clear the given SplitList object so it can be reused again.  Releases
/// the list of sub-strings (but does not delete the sub-strings themselves,
/// which are assumed to be pointers into an existing string).
/// </summary>
/// <param name="list">A SplitList object to clear.</param>
void SplitList_Clear(SplitList* list);


/// <summary>
/// Split the given path into multiple strings based on the given delimiter.
/// The pointers to each string are returned in the given StringList object.
/// </summary>
/// <param name="s">String to split into components.  Will be altered.</param>
/// <param name="splitChars">A list of one or more characters on which to split
/// the string.  If NULL or empty, defaults to a single space.</param>
/// <param name="components">A SplitList object that will be updated with
/// pointers to the sub-strings and the count of sub-strings.  This object is
/// cleared of any previous strings before being filled up again.</param>
void split(char* s, const char* splitChars, SplitList* components);

#endif // __SPLIT_H__

