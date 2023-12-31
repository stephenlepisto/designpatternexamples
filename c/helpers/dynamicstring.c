/// @file
/// @brief
/// Implementation of the supporting functions for the DynamicString structure
/// to work with dynamic strings.

#include <stdlib.h>
#include <string.h>

#include "dynamicstring.h"


///////////////////////////////////////////////////////////////////////////////
// DynamicString_Initialize()
///////////////////////////////////////////////////////////////////////////////
void DynamicString_Initialize(DynamicString* string)
{
    if (string != NULL)
    {
        string->string = calloc(1, 1);  // An empty string
        string->length = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// DynamicString_Clear()
///////////////////////////////////////////////////////////////////////////////
void DynamicString_Clear(DynamicString* string)
{
    if (string != NULL)
    {
        free(string->string);
        DynamicString_Initialize(string);
    }
}

///////////////////////////////////////////////////////////////////////////////
// DynamicString_Append()
///////////////////////////////////////////////////////////////////////////////
bool DynamicString_Append(DynamicString* string, const char* s)
{
    bool success = false;

    if (string != NULL && s != NULL)
    {
        char* newText = NULL;
        size_t newSize = string->length + strlen(s) + 1;
        if (string->string == NULL)
        {
            newText = calloc(1, newSize);
        }
        else
        {
            newText = realloc(string->string, newSize);
        }
        if (newText != NULL)
        {
            newText[string->length] = '\0';
            string->string = newText;
            // Previous code ensures there is space for s and string is zero-
            // terminated.
            strcat(string->string, s);
            string->length = strlen(string->string);
            success = true;
        }
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
// DynamicString_Set()
///////////////////////////////////////////////////////////////////////////////
bool DynamicString_Set(DynamicString* string, const char* s)
{
    bool success = false;

    if (string != NULL)
    {
        DynamicString_Clear(string);
        success = DynamicString_Append(string, s);
    }

    return success;
}
