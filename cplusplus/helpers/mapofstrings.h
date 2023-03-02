#pragma once

#include <map>
#include <string>

#include "stringlist.h"

/// <summary>
/// Alias to make it easier to deal with a map of strings key by a string.
/// </summary>
using MapOfStrings = std::map<std::string, StringList>;
