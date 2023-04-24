/// @file
/// @brief
/// Declaration of the NumberChangedFunctionList structure along with its
/// support functions,
/// NumberChangedFunctionList_Initialize(), NumberChangedFunctionList_Clear(),
/// NumberChangedFunctionList_Add(), NumberChangedFunctionList_Find(),
/// NumberChangedFunctionList_Remove(), and NumberChangedFunctionList_Copy(),
/// as used in the  @ref observer_pattern.

#pragma once
#ifndef __OBSERVER_NUMBERCHANGEDFUNCTIONLIST_H__
#define __OBSERVER_NUMBERCHANGEDFUNCTIONLIST_H__

#include <stdbool.h>
#include <stdint.h>

/// <summary>
/// Alias for a function that receives notifications about a number change.
/// </summary>
typedef void (*NumberChangedFunction)(uint32_t);

/// <summary>
/// Represents a dynamic list of function pointers of the type
/// @ref NumberChangedFunction.
/// </summary>
typedef struct
{
    NumberChangedFunction* functions;  ///< Array of function pointers.
    size_t functions_count; ///< Number of active function pointers in the `functions` array.
    size_t allocation_count; ///< The number of function pointers that can be held in the `functions` array.
} NumberChangedFunctionList;

/// <summary>
/// Initialize the given function pointer list.
/// </summary>
/// <param name="functionList">The NumberChangedFunctionList object to initialize.</param>
void NumberChangedFunctionList_Initialize(NumberChangedFunctionList* functionList);

/// <summary>
/// Clear the given function pointer list, releasing all associated memory.
/// The function list can then be used for new function pointers.
/// </summary>
/// <param name="functionList">The NumberChangedFunctionList object to clear.</param>
void NumberChangedFunctionList_Clear(NumberChangedFunctionList* functionList);

/// <summary>
/// Add a function pointer to the given function pointer list.
/// </summary>
/// <param name="functionList">The NumberChangedFunctionList object to add to.</param>
/// <param name="function">The @ref NumberChangedFunction pointer to add.</param>
/// <returns>Returns true if the function pointer was successfully added;
/// otherwise, returns false, indicating an out of memory condition (or a NULL
/// argument was passed in).</returns>
bool NumberChangedFunctionList_Add(NumberChangedFunctionList* functionList, NumberChangedFunction function);

/// <summary>
/// Search the function list for the specified function pointer.
/// </summary>
/// <param name="functionList">The NumberChangedFunctionList object to search.</param>
/// <param name="function">The @ref NumberChangedFunction pointer to search for.</param>
/// <returns>Returns the index of the function pointer if found; otherwise,
/// returns -1, indicating the function pointer is not in the function pointer
/// list.</returns>
int NumberChangedFunctionList_Find(NumberChangedFunctionList* functionList, NumberChangedFunction function);

/// <summary>
/// Removed the function pointer at the given index from the function pointer
/// list.
/// </summary>
/// <param name="functionList">The NumberChangedFunctionList object to remove from.</param>
/// <param name="functionIndex">The index of the function pointer to remove.
/// Get this index by calling the NumberChangedFunctionList_Find() function.</param>
void NumberChangedFunctionList_Remove(NumberChangedFunctionList* functionList, int functionIndex);

/// <summary>
/// Duplicate the given source function pointer list into the destination
/// function pointer list.
/// </summary>
/// <param name="sourceList">The NumberChangedFunctionList object to copy from.</param>
/// <param name="destinationList">The NumberChangedFunctionList object to copy to.</param>
/// <returns>Returns true if the copy was successful; otherwise, returns false
/// indicating an out of memory condition (or a NULL argument was passed in).</returns>
bool NumberChangedFunctionList_Copy(NumberChangedFunctionList* sourceList, NumberChangedFunctionList* destinationList);

#endif // __OBSERVER_NUMBERCHANGEDFUNCTIONLIST_H__

