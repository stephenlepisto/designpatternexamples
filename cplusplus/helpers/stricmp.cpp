/// @file
/// @brief
/// Implementation of the @ref Helpers::stricmp "stricmp" function, case-insensitive
/// string comparison for narrow character strings.
///
/// Function to compare two strings in a case-insensitive way.  Handles
/// const char* and std::string as arguments.

#include <string>
#include <cstring>

#include "stricmp.h"

namespace Helpers
{
    int stricmp(const char* first, const char* second)
    {
#ifdef _MSC_VER
        return _stricmp(first, second);
#else
        int result = -1;
        if (first != nullptr && second != nullptr)
        {
            result = 0;
            while (*first != '\0' && *second != '\0')
            {
                char first_c = toupper(*first);
                char second_c = toupper(*second);
                if (first_c < second_c)
                {
                    result = -1;
                    break;
                }
                if (first_c > second_c)
                {
                    result = 1;
                    break;
                }
                first++;
                second++;
            }
            if (result == 0 && *first != *second)
            {
                // shorter string is lexically before longer string.
                if (*first == '\0')
                {
                    result = -1;
                }
                else
                {
                    result = 1;
                }
            }
        }
        return result;
#endif
    }

    int stricmp(const std::string& first, const std::string& second)
    {
        return stricmp(first.c_str(), second.c_str());
    }

} // end namespace
