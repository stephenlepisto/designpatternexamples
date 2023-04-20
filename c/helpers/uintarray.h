/// @file
/// @brief
/// Declaration of the UIntArray structure that represents an array of
/// 32-bit unsigned integers along with the associated functions,
/// UIntArray_Initialize(), UIntArray_Clear(), UIntArray_AddInt(),
/// UIntArray_RemoveInt(), UIntArray_Find(), and UIntArray_Copy().

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
    size_t length;  ///< Number of 32-bit unsigned integers actually in the `data` array.
    size_t allocatedLength; ///< Number of elements that the `data` array can hold.

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

/// <summary>
/// Remove the unsigned 32-bit integer from the given UIntArray object at the
/// given index.  All subsequent integers are moved up one.  Does nothing if
/// the index is not valid.
/// </summary>
/// <param name="array">The UIntArray object to update.</param>
/// <param name="removeIndex">Index of the value to remove.</param>
void UIntArray_RemoveInt(UIntArray* array, int removeIndex);

/// <summary>
/// Search the given UIntArray object for the specified value and return the
/// index of that found value.
/// </summary>
/// <param name="array">The UIntArray object to search.</param>
/// <param name="value">The value to search for.</param>
/// <returns>Returns an index into the list to the position of the value if
/// found; otherwise, returns -1, indicating the value is not in the list.</returns>
int UIntArray_Find(UIntArray* array, uint32_t value);

/// <summary>
/// Copy the source UIntArray to the destination UIntArray.  The destination
/// UIntArray is erased before getting a copy of the contents of the source.
/// </summary>
/// <param name="sourceArray">The UIntArray to copy from.</param>
/// <param name="destinationArray">The UIntArray to copy to.</param>
void UIntArray_Copy(UIntArray* sourceArray, UIntArray* destinationArray);

#endif // __UINTARRAY_H__

