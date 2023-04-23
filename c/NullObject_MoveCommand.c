/// @file
/// @brief
/// Implementation of the MoveCommand structure's support functions,
/// MoveCommand_Create() and MoveCommand_Destroy(),
/// as used in the @ref nullobject_pattern.

#include <stdlib.h>
#include <stdio.h>

#include "NullObject_MoveCommand.h"

///////////////////////////////////////////////////////////////////////////////
// MoveCommand_Create()
///////////////////////////////////////////////////////////////////////////////
MoveCommand* MoveCommand_Create(char commandToken, const char* commandName, ExecuteFunction executeFunction)
{
    MoveCommand* moveCommand = NULL;

    if (commandName != NULL && executeFunction != NULL)
    {
        moveCommand = calloc(1, sizeof(MoveCommand));
        if (moveCommand != NULL)
        {
            moveCommand->commandToken = commandToken;
            moveCommand->commandName = commandName;
            moveCommand->Execute = executeFunction;
        }
    }

    return moveCommand;
}

///////////////////////////////////////////////////////////////////////////////
// MoveCommand_Destroy()
///////////////////////////////////////////////////////////////////////////////
void MoveCommand_Destroy(MoveCommand* moveCommand)
{
    if (moveCommand != NULL)
    {
        moveCommand->commandToken = 0;
        moveCommand->commandName = NULL;
        moveCommand->Execute = NULL;
        free(moveCommand);
    }
}
