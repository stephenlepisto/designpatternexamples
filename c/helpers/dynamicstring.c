/// @file
/// @brief
/// Implementation of the DynamicString structure, along with
/// DynamicString_Initialize(), DynamicString_Clear(), and DynamicString_Append()
/// functions that work with that structure.

#include <stdlib.h>
#include <string.h>

#include "dynamicstring.h"


/// <summary>
/// Initialize a DynamicString object.
/// </summary>
/// <param name="string">The DynamicString object to initialize.</param>
void DynamicString_Initialize(DynamicString* string)
{
    if (string != NULL)
    {
        string->string = NULL;
        string->length = 0;
    }
}

/// <summary>
/// Clear a DynamicString object, releasing any allocated memory.
/// </summary>
/// <param name="string">The DynamicString object to clear.</param>
void DynamicString_Clear(DynamicString* string)
{
    if (string != NULL)
    {
        free(string->string);
        string->string = NULL;
        string->length = 0;
    }
}

/// <summary>
/// Append the specified string to the DynamicString object.
/// </summary>
/// <param name="string">The DynamicString object to append to.</param>
/// <param name="s">The string to append.</param>
void DynamicString_Append(DynamicString* string, const char* s)
{
    if (string != NULL)
    {
        if (string->string == NULL)
        {
            string->string = _strdup(s);
            string->length = strlen(string->string);
        }
        else
        {
            size_t newSize = string->length + strlen(s) + 1;
            char* newText = realloc(string->string, newSize);
            if (newText != NULL)
            {
                string->string = newText;
                strcat_s(string->string, newSize, s);
                string->length = strlen(string->string);
            }
        }
    }
}
