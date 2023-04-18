/// @file
/// @brief
/// Implementation of the UIntArray structure that represents an array of
/// 32-bit unsigned integers, along with the associated functions,
/// UIntArray_Initialize(), UIntArray_Clear(), and UIntArray_AddInt().

#include <stdlib.h>
#include "uintarray.h"

///////////////////////////////////////////////////////////////////////////////
// UIntArray_Initialize()
///////////////////////////////////////////////////////////////////////////////
void UIntArray_Initialize(UIntArray* array)
{
    if (array != NULL)
    {
        array->data = NULL;
        array->length = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// UIntArray_Clear()
///////////////////////////////////////////////////////////////////////////////
void UIntArray_Clear(UIntArray* array)
{
    if (array != NULL)
    {
        free(array->data);
        UIntArray_Initialize(array);
    }
}

///////////////////////////////////////////////////////////////////////////////
// UIntArray_AddInt()
///////////////////////////////////////////////////////////////////////////////
void UIntArray_AddInt(UIntArray* array, uint32_t value)
{
    if (array != NULL)
    {
        uint32_t* new_list = NULL;
        if (array->data == NULL)
        {
            new_list = calloc(1, sizeof(uint32_t));
        }
        else
        {
            size_t newSize = (array->length + 1) * sizeof(uint32_t);
            new_list = realloc(array->data, newSize);
        }
        if (new_list != NULL)
        {
            array->data = new_list;
            array->data[array->length] = value;
            array->length++;
        }
    }
}
