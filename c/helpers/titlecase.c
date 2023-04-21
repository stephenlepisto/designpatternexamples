/// @file
/// @brief
/// Implementation of the titlecase() function, for making
/// a word lowercase with the first letter uppercase.

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "titlecase.h"

char* titlecase(const char* s)
{
    char* buffer = NULL;

    if (s != NULL)
    {
        size_t stringSize = strlen(s);
        buffer = calloc(1, stringSize + 1);
        if (buffer != NULL)
        {
            for (size_t index = 0; index < stringSize; index++)
            {
                int c = s[index];
                // Stop on space or non-alphabetic character (presumably punctuation)
                if (isspace(c) || !isalpha(c))
                {
                    // Reached end of a word, copy rest of string over
                    errno_t err = strcat_s(buffer, stringSize, s + index);
                    if (err)
                    {
                        printf("  Error!  strcat_s failed in titlecase()!\n");
                    }
                    // And we are done
                    break;
                }

                if (index == 0)
                {
                    c = toupper(c);
                }
                else
                {
                    c = tolower(c);
                }
                buffer[index] = (char)c;
            }
        }
    }

    return buffer;
}
