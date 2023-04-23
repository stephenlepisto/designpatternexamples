/// @file
/// @brief
/// Implementation of the @ref MoveCommandList structure's support functions,
/// MoveCommandList_Initialize(), MoveCommandList_Clear(), and
/// MoveCommandList_Add(),
/// as used in the @ref nullobject_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "NullObject_MoveCommandList.h"

///////////////////////////////////////////////////////////////////////////////
// MoveCommandList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void MoveCommandList_Initialize(MoveCommandList* commandList)
{
    if (commandList != NULL)
    {
        commandList->commands = NULL;
        commandList->commands_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// MoveCommandList_Clear()
///////////////////////////////////////////////////////////////////////////////
void MoveCommandList_Clear(MoveCommandList* commandList)
{
    if (commandList != NULL)
    {
        for (size_t index = 0; index < commandList->commands_count; index++)
        {
            free(commandList->commands[index]);
        }
        free(commandList->commands);
        MoveCommandList_Initialize(commandList);
    }
}

///////////////////////////////////////////////////////////////////////////////
// MoveCommandList_Add()
///////////////////////////////////////////////////////////////////////////////
bool MoveCommandList_Add(MoveCommandList* commandList, MoveCommand* moveCommand)
{
    bool added = false;

    if (commandList != NULL && moveCommand != NULL)
    {
        MoveCommand** new_list = NULL;
        if (commandList->commands == NULL)
        {
            new_list = malloc(sizeof(MoveCommand*));
        }
        else
        {
            size_t new_count = commandList->commands_count + 1;
            new_list = realloc(commandList->commands, new_count * sizeof(MoveCommand*));
        }
        if (new_list != NULL)
        {
            commandList->commands = new_list;
            commandList->commands[commandList->commands_count] = moveCommand;
            commandList->commands_count++;
            added = true;
        }
    }
    return added;
}
