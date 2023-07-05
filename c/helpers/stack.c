/// @file
/// @brief
/// Implementation of the supporting functions for the StackEntry structure
/// that represents a simple stack.

#include <stdlib.h>

#include "stack.h"

/// <summary>
/// Create a new StackEntry object with the given item.
/// </summary>
/// <param name="item">The item to add to the stack.</param>
/// <returns>Returns a new StackEntry object if successful; otherwise, returns
/// NULL, indicating an out of memory error.</returns>
static StackEntry* StackEntry_Create(void* item)
{
    StackEntry* entry = calloc(1, sizeof(StackEntry));
    if (entry != NULL)
    {
        entry->item = item;
    }

    return entry;
}

/// <summary>
/// Destroys the specified StackEntry object.  After this function returns,
/// the object is no longer valid.
/// </summary>
/// <param name="entry">The StackEntry object to destroy.</param>
static void StackEntry_Destroy(StackEntry* entry)
{
    free(entry);
}

///////////////////////////////////////////////////////////////////////////////
// Stack_Push()
///////////////////////////////////////////////////////////////////////////////
void Stack_Push(StackEntry** stack, void* item)
{
    if (stack != NULL && item != NULL)
    {
        StackEntry* entry = StackEntry_Create(item);
        if (entry != NULL)
        {
            if (*stack != NULL)
            {
                entry->next = *stack;
                *stack = entry;
            }
            else
            {
                *stack = entry;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Stack_Pop()
///////////////////////////////////////////////////////////////////////////////
void* Stack_Pop(StackEntry** stack)
{
    void* item = NULL;
    if (stack != NULL)
    {
        StackEntry* entry = *stack;
        if (entry != NULL)
        {
            item = entry->item;
            *stack = entry->next;
            StackEntry_Destroy(entry);
        }
    }
    return item;
}

///////////////////////////////////////////////////////////////////////////////
// Stack_IsEmpty()
///////////////////////////////////////////////////////////////////////////////
bool Stack_IsEmpty(StackEntry** stack)
{
    return stack == NULL || *stack == NULL;
}
