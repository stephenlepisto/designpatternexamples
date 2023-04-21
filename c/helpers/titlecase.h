/// @file
/// @brief
/// Declaration of the titlecase() function, for making a
/// word lowercase with the first letter uppercase.

#pragma once
#ifndef __TITLECASE_H__
#define __TITLECASE_H__

/// <summary>
/// Convert the first word (or only word) in the given string to lowercase
/// then make the first letter uppercase.  It does not touch any of the
/// other words after the first.
/// 
/// Note that this is not locale-sensitive.
/// </summary>
/// <param name="s">A string to work on.</param>
/// <returns>Returns a pointer to newly allocated buffer containing the modified
/// string.  Call free() on the pointer when done with it.  Returns NULL if an
/// out of memory condition occurs.</returns>
char* titlecase(const char* s);

#endif // __TITLECASE_H__

