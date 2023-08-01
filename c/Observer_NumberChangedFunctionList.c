/// @file
/// @brief
/// Implementation of the NumberChangedFunctionList structure's support functions,
/// NumberChangedFunctionList_Initialize(), NumberChangedFunctionList_Clear(),
/// NumberChangedFunctionList_Add(), NumberChangedFunctionList_Find(),
/// NumberChangedFunctionList_Remove(), and NumberChangedFunctionList_Copy(),
/// as used in the  @ref observer_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "Observer_NumberChangedFunctionList.h"

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void NumberChangedFunctionList_Initialize(NumberChangedFunctionList* functionList)
{
    if (functionList != NULL)
    {
        functionList->functions = NULL;
        functionList->functions_count = 0;
        functionList->allocation_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Clear()
///////////////////////////////////////////////////////////////////////////////
void NumberChangedFunctionList_Clear(NumberChangedFunctionList* functionList)
{
    if (functionList != NULL)
    {
        free(functionList->functions);
        NumberChangedFunctionList_Initialize(functionList);
    }
}

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Add()
///////////////////////////////////////////////////////////////////////////////
bool NumberChangedFunctionList_Add(NumberChangedFunctionList* functionList, NumberChangedFunction function)
{
    bool added = false;

    if (functionList != NULL && function != NULL)
    {
        NumberChangedFunction* new_list = NULL;

        if (functionList->functions == NULL)
        {
            new_list = malloc(sizeof(NumberChangedFunction));
            functionList->allocation_count = 1;
        }
        else if (functionList->functions_count < functionList->allocation_count)
        {
            new_list = functionList->functions;
        }
        else
        {
            size_t new_count = functionList->allocation_count + 1;
            new_list = realloc(functionList->functions, new_count * sizeof(NumberChangedFunction));
            functionList->allocation_count = new_count;
        }
        if (new_list != NULL)
        {
            functionList->functions = new_list;
            functionList->functions[functionList->functions_count] = function;
            functionList->functions_count++;
            added = true;
        }
        else
        {
            printf("  Error!  Out of memory while allocating or reallocating space for the function list!\n");
        }
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Find()
///////////////////////////////////////////////////////////////////////////////
int NumberChangedFunctionList_Find(NumberChangedFunctionList* functionList, NumberChangedFunction function)
{
    int foundIndex = -1;

    if (functionList != NULL && function != NULL)
    {
        for (size_t index = 0; index < functionList->functions_count; index++)
        {
            if (functionList->functions[index] == function)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Remove()
///////////////////////////////////////////////////////////////////////////////
void NumberChangedFunctionList_Remove(NumberChangedFunctionList* functionList, int functionIndex)
{
    if (functionList != NULL && functionIndex >= 0 && (size_t)functionIndex < functionList->functions_count)
    {
        for (size_t index = functionIndex; index < functionList->allocation_count - 1; index++)
        {
            functionList->functions[index] = functionList->functions[index + 1];
        }
        functionList->functions[functionList->allocation_count - 1] = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// NumberChangedFunctionList_Copy()
///////////////////////////////////////////////////////////////////////////////
bool NumberChangedFunctionList_Copy(NumberChangedFunctionList* sourceList, NumberChangedFunctionList* destinationList)
{
    bool copied = false;

    if (sourceList != NULL && destinationList != NULL)
    {
        size_t arraySize = sourceList->allocation_count * sizeof(NumberChangedFunction);
        destinationList->functions = calloc(1, arraySize);
        if (destinationList->functions != NULL)
        {
            memcpy(destinationList->functions, sourceList->functions, arraySize);
            destinationList->allocation_count = sourceList->allocation_count;
            destinationList->functions_count = sourceList->functions_count;
            copied = true;
        }
        else
        {
            printf("  Error!  Out of memory copying a NumberChangedFunctionList!\n");
        }
    }
    return copied;
}
