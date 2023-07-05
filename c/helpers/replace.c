/// @file
/// @brief
/// Implementation of various helper functions for replacing characters or
/// strings in a string.

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "replace.h"
#include "strstri.h"

///////////////////////////////////////////////////////////////////////////////
// replace_chr()
///////////////////////////////////////////////////////////////////////////////
void replace_chr(char* s, char c1, char c2)
{
    if (s != NULL && c1 != '\0')
    {
        size_t length = strlen(s);
        if (c2 != '\0')
        {
            for (size_t index = 0; index < length; index++)
            {
                if (s[index] == c1)
                {
                    s[index] = c2;
                }
            }
        }
        else
        {
            size_t writeIndex = 0;
            for (size_t readIndex = 0; readIndex < length; readIndex++)
            {
                if (s[readIndex] != c1)
                {
                    s[writeIndex] = s[readIndex];
                    writeIndex++;
                }
            }
            s[writeIndex] = '\0';
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// replace_chri()
///////////////////////////////////////////////////////////////////////////////
void replace_chri(char* s, char c1, char c2)
{
    if (s != NULL && c1 != '\0')
    {
        size_t length = strlen(s);
        int upperc1 = toupper(c1);
        if (c2 != '\0')
        {
            for (size_t index = 0; index < length; index++)
            {
                if (toupper(s[index]) == upperc1)
                {
                    s[index] = c2;
                }
            }
        }
        else
        {
            size_t writeIndex = 0;
            for (size_t readIndex = 0; readIndex < length; readIndex++)
            {
                if (toupper(s[readIndex]) != upperc1)
                {
                    s[writeIndex] = s[readIndex];
                    writeIndex++;
                }
            }
            s[writeIndex] = '\0';
        }
    }
}

/// <summary>
/// Helper function to append a range of characters to a string that may need
/// to be resized to accommodate the range of characters.
/// </summary>
/// <param name="buffer">Pointer to a pointer to a character string.  This will
/// contain the pointer to the updated string on return.</param>
/// <param name="start">Pointer to first character of range to copy.</param>
/// <param name="end">Pointer to one after last character of range to copy.
/// Must be greater than or equal to `start` and must point into the same string.
/// </param>
static void _append_range(char** buffer, const char* start, const char* end)
{
    if (buffer != NULL && start < end)
    {
        size_t charsToCopy = end - start;
        char* text = *buffer;
        if (text == NULL)
        {
            text = malloc(charsToCopy + 1);
            if (text != NULL)
            {
                errno_t err = strncpy_s(text, charsToCopy + 1, start, charsToCopy);
                if (err == 0)
                {
                    text[charsToCopy] = '\0';
                    *buffer = text;
                }
            }
        }
        else
        {
            size_t currentLength = strlen(text);
            char* reallocText = realloc(text, currentLength + charsToCopy + 1);
            if (reallocText != NULL)
            {
                errno_t err = strncpy_s(reallocText + currentLength, charsToCopy + 1, start, charsToCopy);
                if (err == 0)
                {
                    reallocText[currentLength + charsToCopy] = '\0';
                    *buffer = reallocText;
                }
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// replace_str()
///////////////////////////////////////////////////////////////////////////////
char* replace_str(const char* s, const char* str1, const char* str2)
{
    char* newText = NULL;
    if (s != NULL && str1 != NULL && str2 != NULL)
    {
        size_t length = strlen(s);
        size_t str1Length = strlen(str1);
        size_t str2Length = strlen(str2);
        const char* start = s;
        const char* end = start + length;
        while (start < end)
        {
            const char* found = strstr(start, str1);
            if (found != NULL)
            {
                _append_range(&newText, start, found);
                if (str2Length > 0)
                {
                    _append_range(&newText, str2, str2 + str2Length);
                }
                start = found + str1Length;
            }
            else
            {
                _append_range(&newText, start, start + strlen(start));
                start = end;
            }
        }
    }

    return newText;
}

///////////////////////////////////////////////////////////////////////////////
// replace_stri()
///////////////////////////////////////////////////////////////////////////////
char* replace_stri(const char* s, const char* str1, const char* str2)
{
    char* newText = NULL;
    if (s != NULL && str1 != NULL && str2 != NULL)
    {
        size_t length = strlen(s);
        size_t str1Length = strlen(str1);
        size_t str2Length = strlen(str2);
        const char* start = s;
        const char* end = start + length;
        while (start < end)
        {
            const char* found = strstri(start, str1);
            if (found != NULL)
            {
                _append_range(&newText, start, found);
                if (str2Length > 0)
                {
                    _append_range(&newText, str2, str2 + str2Length);
                }
                start = found + str1Length;
            }
            else
            {
                _append_range(&newText, start, start + strlen(start));
                start = end;
            }
        }
    }

    return newText;
}

