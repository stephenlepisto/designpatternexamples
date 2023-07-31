/// @file
/// @brief
/// Declaration of the MoveCommand structure along with the support functions,
/// MoveCommand_Create() and MoveCommand_Destroy(),
/// as used in the @ref nullobject_pattern.

#pragma once
#ifndef __NULLOBJECT_MOVECOMMAND_H__
#define __NULLOBJECT_MOVECOMMAND_H__

/// <summary>
/// Alias for a function that executes a move command.
/// </summary>
typedef void (*ExecuteFunction)(void);


/// <summary>
/// Represents a move command.  A move command has a name and the command
/// character that represents the command in the initial string of movement
/// commands.
///
/// Yes, this is a variation of the @ref command_pattern.
///
/// In this example, a move command, when executed, prints "move xxx" on
/// the current line.  A move command, when displayed, shows the command
/// character followed by the name of the command.
/// </summary>
typedef struct
{
    char        commandToken; ///< The character that represents this move command in a string
    const char* commandName;  ///< The name of this move command
    ExecuteFunction Execute;  ///< The function to call to execute the move command (this varies for each command)
} MoveCommand;


/// <summary>
/// Create a MoveCommand object and initialize it with the given arguments.
/// </summary>
/// <param name="commandToken">The character representing the command when it
/// appears in a string.</param>
/// <param name="commandName">The name of the command.</param>
/// <param name="executeFunction">The function to call to execute the move command.</param>
/// <returns>Returns the initialize MoveCommand object if successful;
/// otherwise, returns NULL to indicate an out of memory condition (or missing
/// arguments).</returns>
MoveCommand* MoveCommand_Create(char commandToken, const char* commandName, ExecuteFunction executeFunction);

/// <summary>
/// Destroy the specified MoveCommand object.  After this function returns,
/// the pointer to the MoveCommand is no longer valid.
/// </summary>
/// <param name="moveCommand">The MoveCommand object to destroy.</param>
void MoveCommand_Destroy(MoveCommand* moveCommand);

#endif // __NULLOBJECT_MOVECOMMAND_H__
