/// @file
/// @brief
/// Declaration of the DynamicString structure, along with
/// DynamicString_Initialize(), DynamicString_Clear(), and DynamicString_Append()
/// functions that work with that structure.
 
#pragma once
#ifndef __DYNAMICSTRING_H__
#define __DYNAMICSTRING_H__

/// <summary>
/// Represents a string that can be grown dynamically.
/// </summary>
typedef struct DynamicString
{
    char* string;   ///< The string that can grow
    size_t length;  ///< The current length of the string
} DynamicString;

/// <summary>
/// Initialize a DynamicString object.
/// </summary>
/// <param name="string">The DynamicString object to initialize.</param>
void DynamicString_Initialize(DynamicString* string);

/// <summary>
/// Clear a DynamicString object, releasing any allocated memory.
/// </summary>
/// <param name="string">The DynamicString object to clear.</param>
void DynamicString_Clear(DynamicString* string);

/// <summary>
/// Append the specified string to the DynamicString object.
/// </summary>
/// <param name="string">The DynamicString object to append to.</param>
/// <param name="s">The string to append.</param>
void DynamicString_Append(DynamicString* string, const char* s);

#endif // __DYNAMICSTRING_H__
