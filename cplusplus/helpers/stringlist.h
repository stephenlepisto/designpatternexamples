/// @file
/// @brief
/// Declaration of the @ref StringList and @ref StringListW typedefs for
/// declaring a vector of strings.

#pragma once
#ifndef __STRINGLIST_H__
#define __STRINGLIST_H__

#include <vector>
#include <string>

/// <summary>
/// Typedef for a vector of std::string.
/// </summary>
typedef std::vector<std::string> StringList;

/// <summary>
/// Typedef for a vector of std::wstring.
/// </summary>
typedef std::vector<std::wstring> StringListW;

#endif // __STRINGLIST_H__
