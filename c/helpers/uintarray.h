/// @file
/// @brief
/// Declaration of the UIntArray structure that represents an array of
/// 32-bit unsigned integers along with the associated functions,
/// UIntArray_Initialize(), UIntArray_Clear(), and UIntArray_AddInt().

#pragma once
#ifndef __UINTARRAY_H__
#define __UINTARRAY_H__

#include <stdint.h>

/// <summary>
/// Represents an array of 32-bit unsigned integers.  The `data` field points
/// to a block of memory allocated on the heap and needs to be freed when the
/// pointer is no longer needed.
/// 
/// Note: The contents of this structure can be copied to another instance but
/// that means the ownership of the `data` field is also transferred to that
/// other instance.
/// </summary>
typedef struct
{
    uint32_t* data; ///< Pointer to array of 32-bit unsigned integers
    size_t length;  ///< Number of 32-bit unsigned integers in the `data` array.

} UIntArray;

/// <summary>
/// Initialize the given UIntArray object.
/// </summary>
/// <param name="array">A UIntArray object to initialize.</param>
void UIntArray_Initialize(UIntArray* array);

/// <summary>
/// Clear the given UIntArray object so it can be reused again.  Releases
/// the list of integers.
/// </summary>
/// <param name="array">A UIntArray object to clear.</param>
void UIntArray_Clear(UIntArray* array);

/// <summary>
/// Add an unsigned 32-bit integer to the given UIntArray object.
/// </summary>
/// <param name="array">The UIntArray object to update.</param>
/// <param name="value">The value to add to the UIntArray object.</param>
void UIntArray_AddInt(UIntArray* array, uint32_t value);


#endif // __UINTARRAY_H__

