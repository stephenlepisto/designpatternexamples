/// @file
/// @brief
/// Implementation of the @ref Helpers::stricmp "stricmp" function, case-insensitive
/// string comparison for narrow character strings.
/// 
/// Function to compare two strings in a case-insensitive way.  Handles
/// const char* and std::string as arguments.

#include <string>
#include <string.h>

#include "stricmp.h"

namespace Helpers
{
    int stricmp(const char* first, const char* second)
    {
        return _stricmp(first, second);
    }

    int stricmp(const std::string& first, const std::string& second)
    {
        return _stricmp(first.c_str(), second.c_str());
    }

} // end namespace
