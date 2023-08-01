/// @file
/// @brief
/// Implementation of the @ref Helpers::formatstring "formatstring()" function
/// that replaces sprintf() and snprintf() by allocating the right-sized buffer
/// and returning it.

#include <cstdlib>
#include <cstring>
#include <cstdarg>

#include <vector>

#include "formatstring.h"

namespace Helpers
{
    std::string formatstring(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        va_list args2;
        va_copy(args2, args);
        int numCharsNeeded = 0;
        std::vector<char> buffer;
        if (fmt != NULL)
        {
            numCharsNeeded = vsnprintf(NULL, 0, fmt, args) + 1;
            buffer.resize(numCharsNeeded);
            memset(&buffer[0], 0, numCharsNeeded);
            vsnprintf(&buffer[0], numCharsNeeded, fmt, args2);
        }
        else
        {
            buffer.resize(1);
            buffer[0] = '\0';
        }
        va_end(args2);
        va_end(args);

        return std::string(&buffer[0]);
    }

} // end namespace Helpers
