/// @file
/// @brief
/// Implementation of the formatstring() function that replaces sprintf() and
/// snprintf() by allocating the right-sized buffer and returning it.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "formatstring.h"

//////////////////////////////////////////////////////////////////////////////
// formatstring()
//////////////////////////////////////////////////////////////////////////////
char* formatstring(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    va_list args2;
    va_copy(args2, args);
    int numCharsNeeded = 0;
    char *buffer = NULL;
    if (format != NULL)
    {
        numCharsNeeded = vsnprintf(NULL, 0, format, args) + 1;
        buffer = calloc(numCharsNeeded, sizeof(char));
        if (buffer != NULL)
        {
            vsnprintf(buffer, numCharsNeeded, format, args2);
        }
    }
    else
    {
        buffer = calloc(1, sizeof(char));
    }
    va_end(args2);
    va_end(args);

    return buffer;
}
