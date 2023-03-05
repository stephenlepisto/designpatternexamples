/// @file
/// @brief
/// Declaration of the @ref Helpers::titlecase "title" function, for making a
/// word lowercase with the first letter uppercase.

#pragma once
#ifndef __TITLECASE_H__
#define __TITLECASE_H__

#include <string>

namespace Helpers
{
    /// <summary>
    /// Convert the first word (or only word) in the given string to lowercase
    /// then make the first letter uppercase.  It does not touch any of the
    /// other words after the first.
    /// 
    /// Note that this is not locale-sensitive.
    /// </summary>
    /// <param name="s">A string to work on.</param>
    /// <returns>Returns a new string containing the modified string.</returns>
    std::string titlecase(const std::string& s);

}
#endif // __TITLECASE_H__

