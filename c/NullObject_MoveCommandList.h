/// @file
/// @brief
/// Declaration of the MoveCommandList structure along with the support functions,
/// MoveCommandList_Initialize(), MoveCommandList_Clear(), and
/// MoveCommandList_Add(),
/// as used in the @ref nullobject_pattern.

#pragma once
#ifndef __NULLOBJECT_MOVECOMMANDLIST_H__
#define __NULLOBJECT_MOVECOMMANDLIST_H__

#include <stdbool.h>

#include "NullObject_MoveCommand.h"

/// <summary>
/// Represents a list of MoveCommand objects.
/// </summary>
typedef struct
{
    MoveCommand** commands;  ///< Array of pointers to MoveCommand objects.
    size_t commands_count;   ///< Number of commands in the `commands` array.
} MoveCommandList;

/// <summary>
/// Initialize the given MoveCommandList object.  This should be the first
/// function called for an uninitialized MoveCommandList object.
/// </summary>
/// <param name="commandList">The MoveCommandList object to initialize.</param>
void MoveCommandList_Initialize(MoveCommandList* commandList);

/// <summary>
/// Clear the given MoveCommandList, freeing up any allocated resources,
/// so the list can be reused.
/// </summary>
/// <param name="commandList">The MoveCommandList to clear.</param>
void MoveCommandList_Clear(MoveCommandList* commandList);

/// <summary>
/// Add a given MoveCommand object to the given MoveCommandList object.
/// The MoveCommandList takes ownership and thus responsibility for freeing
/// the memory of the MoveCommand object.
/// </summary>
/// <param name="commandList">The MoveCommandList object to add to.</param>
/// <param name="moveCommand">The MoveCommand to add.</param>
/// <returns>Returns true if the command was added successfully; otherwise,
/// returns false (out of memory or a null argument was passed in).</returns>
bool MoveCommandList_Add(MoveCommandList* commandList, MoveCommand* moveCommand);

#endif // __NULLOBJECT_MOVECOMMANDLIST_H__

