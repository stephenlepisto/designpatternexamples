/// @file
/// @brief
/// Declaration of the Command structure and associated functions
/// as used in the @ref command_pattern.

#pragma once
#ifndef __COMMAND_OBJECTS_H__
#define __COMMAND_OBJECTS_H__

#include <stdlib.h>

#include "Command_TextObject.h"


/// <summary>
/// Alias for a function type representing an operation applied to a
/// Command_TextObject using two parameters.
/// </summary>
/// <param name="source">Command_TextObject to affect</param>
/// <param name="argument1">First argument for the operation.</param>
/// <param name="argument2">Second argument for the operation.</param>
typedef void (*two_parameter_operation)(Command_TextObject* source, const char* argument1, const char* argument2);

/// <summary>
/// Alias for a function type representing an operation applied to a
/// Command_TextObject that uses no additional arguments.
/// </summary>
/// <param name="source">Command_TextObject to affect</param>
typedef void (*no_parameter_operation)(Command_TextObject* source);


/// <summary>
/// Represents an operation that can be applied to a Command_TextObject.
/// Can hold one of two kinds of operations, one that takes no
/// additional parameters and one that takes two additional string
/// parameters.
/// </summary>
/// <remarks>
/// In C, this is implemented with function pointers that implement the actual
/// operations.  Each command can have only one of two function pointers set
/// at a time; this is handled in the Command_Create_Two_Parameters() and
/// Command_Create_No_Parameters() functions.
/// </remarks>
typedef struct Command
{
    Command_TextObject* receiver;                     ///< The receiver of the command.
    const char* commandName;                          ///< Easy-to-read command name.
    two_parameter_operation operation_two_parameters; ///< Two parameter operation to apply to the receiver.
    no_parameter_operation operation_no_parameters;   ///< No parameter operation to apply to the receiver.
    const char* argument1;                            ///< The first argument to a two parameter operation.
    const char* argument2;                            ///< The second argument to a two parameter operation.

} Command;


/// <summary>
/// Create a new Command object with the given parameters, creating a command
/// that uses two additional parameters.
/// </summary>
/// <param name="commandName">The name of the command (for display purposes).</param>
/// <param name="receiver">The target or receiver of the command operation.</param>
/// <param name="operation">The function to call to perform the command.</param>
/// <param name="arg1">The first argument to pass to the command function.</param>
/// <param name="arg2">The second argument to pass to the command function.</param>
/// <returns>Returns a new Command object if successful; returns NULL if out of
/// memory</returns>
Command* Command_Create_Two_Parameters(const char* commandName, Command_TextObject* receiver, two_parameter_operation operation, const char* arg1, const char* arg2);

/// <summary>
/// Create a new Command object with the given parameters, creating a command
/// that uses no additional parameters.
/// </summary>
/// <param name="commandName">The name of the command (for display purposes).</param>
/// <param name="receiver">The target or receiver of the command operation.</param>
/// <param name="operation">The function to call to perform the command.</param>
/// <returns>Returns a new Command object if successful; returns NULL if out of
/// memory</returns>
Command* Command_Create_No_Parameters(const char* commandName, Command_TextObject* receiver, no_parameter_operation operation);

/// <summary>
/// Destroy the given command object, releasing it and any associated resources.
/// </summary>
/// <param name="commandObject">The Command object to be destroyed.  After this
/// function returns, the pointer is no longer valid</param>
void Command_Destroy(Command* commandObject);

/// <summary>
/// Execute the given command on the Command_TextObject it knows about.
/// </summary>
/// <param name="commandObject">The Command object to be executed.</param>
void Command_Execute(Command* commandObject);

/// <summary>
/// Convert the given command object to a string representation.
/// </summary>
/// <param name="commandObject">The Command to be rendered as a string.</param>
/// <returns>A string containing the representation of the command.</returns>
const char* Command_ToString(Command* commandObject);


#endif // __COMMAND_OBJECTS_H__
