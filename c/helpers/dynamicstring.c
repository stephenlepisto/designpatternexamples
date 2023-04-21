/// @file
/// @brief
/// Implementation of the DynamicString structure, along with
/// DynamicString_Initialize(), DynamicString_Clear(), and DynamicString_Append()
/// functions that work with that structure.

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
void DynamicString_Append(DynamicString* string, const char* s)
{
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
            strcat_s(string->string, newSize, s);
            string->length = strlen(string->string);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// DynamicString_Set()
///////////////////////////////////////////////////////////////////////////////
void DynamicString_Set(DynamicString* string, const char* s)
{
    if (string != NULL)
    {
        DynamicString_Clear(string);
        DynamicString_Append(string, s);
    }
}