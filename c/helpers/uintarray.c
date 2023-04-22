/// @file
/// @brief
/// Implementation of the UIntArray structure that represents an array of
/// 32-bit unsigned integers, along with the associated functions,
/// UIntArray_Initialize(), UIntArray_Clear(), and UIntArray_AddInt(),
/// UIntArray_RemoveInt(), UIntArray_Find(), and UIntArray_Copy().

#include <stdlib.h>
#include <memory.h>
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
        array->allocatedLength = 0;
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
            array->allocatedLength = 1;
        }
        else if (array->length < array->allocatedLength)
        {
            new_list = array->data;
        }
        else
        {
            size_t newCount = (array->length + 1);
            new_list = realloc(array->data, newCount * sizeof(uint32_t));
            array->allocatedLength = newCount;
        }
        if (new_list != NULL)
        {
            array->data = new_list;
            array->data[array->length] = value;
            array->length++;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// UIntArray_RemoveInt()
///////////////////////////////////////////////////////////////////////////////
void UIntArray_RemoveInt(UIntArray* array, int removeIndex)
{
    if (array != NULL && array->data != NULL)
    {
        if (removeIndex >= 0 && removeIndex < array->length)
        {
            for (int index = removeIndex; index < array->allocatedLength - 1; index++)
            {
                array->data[index] = array->data[index + 1];
            }
            array->length--;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// UIntArray_Find()
///////////////////////////////////////////////////////////////////////////////
int UIntArray_Find(UIntArray* array, uint32_t value)
{
    int foundIndex = -1;

    if (array != NULL && array->data != NULL)
    {
        for (size_t index = 0; index < array->length; index++)
        {
            if (array->data[index] == value)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}


///////////////////////////////////////////////////////////////////////////////
// UIntArray_Copy()
///////////////////////////////////////////////////////////////////////////////
void UIntArray_Copy(UIntArray* sourceArray, UIntArray* destinationArray)
{
    if (sourceArray != NULL && destinationArray != NULL)
    {
        if (sourceArray->data != NULL)
        {
            UIntArray_Clear(destinationArray);
            size_t new_size = sourceArray->allocatedLength * sizeof(uint32_t);
            uint32_t* new_list = malloc(new_size);
            if (new_list != NULL)
            {
                errno_t err = memcpy_s(new_list, new_size, sourceArray->data, new_size);
                if (err == 0)
                {
                    destinationArray->data = new_list;
                    destinationArray->allocatedLength = new_size;
                    destinationArray->length = sourceArray->length;
                }
                else
                {
                    free(new_list);
                    new_list = NULL;
                }
            }
        }
    }
}
