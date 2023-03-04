/// @file
/// @brief
/// Declaration of the @ref MapOfStrings typedef for declaring a map of
/// strings keyed by another string.

#pragma once

#include <map>
#include <string>

#include "stringlist.h"

/// <summary>
/// Alias to make it easier to deal with a map of strings key by a string.
/// </summary>
using MapOfStrings = std::map<std::string, StringList>;
