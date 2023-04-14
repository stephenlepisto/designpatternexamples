/// @file
/// @brief
/// Declaration of the StackEntry structure and the functions for a simple
/// stack: StackEntry_Create(), StackEntry_Destroy(), Stack_Push(),
/// Stack_Pop(), and Stack_IsEmpty().

#pragma once
#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

/// <summary>
/// Represents an entry on a simple stack that wraps an "item" represented
/// by an opaque pointer.
/// 
/// This structure is allocated on the heap and then linked into the stack.
/// The item is what is being pushed onto the stack, the StackEntry structure
/// provides the necessary link to the next older StackEntry structure
/// containing the next older item.
/// </summary>
/// <remarks>
/// @code{.c}
/// StackEntry* _undoStack = NULL;
/// 
/// void* item; // A pointer to something to be pushed onto the stack
/// Stack_Push(&_undoStack, item);
/// item = Stack_Pop(&_undoStack);
/// bool is_empty = Stack_IsEmpty(&_undoStack);
/// @endcode
/// </remarks>
typedef struct StackEntry
{
    struct StackEntry* next; ///< Points to the next older entry in the stack.
    void* item;              ///< The item being held in this entry in the stack.
} StackEntry;

/// <summary>
/// Push the given entry onto the given stack.
/// </summary>
/// <param name="stack">A pointer to a pointer to a StackEntry object
/// representing the top of the stack.  Points to a NULL if the stack is empty.
/// This pointer to a pointer cannot be NULL.</param>
/// <param name="item">The item to store on the stack.</param>
void Stack_Push(StackEntry** stack, void* item);

/// <summary>
/// Pop the last entry from the given stack, returning the item.
/// </summary>
/// <param name="stack">A pointer to a pointer to a StackEntry object
/// representing the top of the stack.  Points to a NULL if the stack is empty.
/// This pointer to a pointer cannot be NULL.</param>
/// <returns>Returns the item from the top of the stack.  Returns NULL if the
/// stack was empty at the time of the call.</returns>
void* Stack_Pop(StackEntry** stack);

/// <summary>
/// Determines if the given stack is empty.
/// </summary>
/// <param name="stack">A pointer to a pointer to a StackEntry object
/// representing the top of the stack.  Points to a NULL if the stack is empty.
/// This pointer to a pointer cannot be NULL.</param>
/// <returns>Returns true if the stack is empty; otherwise, returns false,
/// there is at least one item on the stack.</returns>
bool Stack_IsEmpty(StackEntry** stack);

#endif // __STACK_H__

