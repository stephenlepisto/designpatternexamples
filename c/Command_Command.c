/// @file
/// @brief
/// Implementation of the Command structure and associated functions
/// as used in the @ref command_pattern.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Command_Command.h"

///////////////////////////////////////////////////////////////////////////////
// Command_Create_Two_Parameters()
///////////////////////////////////////////////////////////////////////////////
Command* Command_Create_Two_Parameters(const char* commandName, Command_TextObject* receiver, two_parameter_operation operation, const char* arg1, const char* arg2)
{
    Command* commandObject = calloc(1, sizeof(Command));
    if (commandObject != NULL)
    {
        commandObject->commandName = commandName;
        commandObject->receiver = receiver;
        commandObject->operation_two_parameters = operation;
        commandObject->argument1 = arg1;
        commandObject->argument2 = arg2;
    }
    return commandObject;
}

///////////////////////////////////////////////////////////////////////////////
// Command_Create_No_Parameters()
///////////////////////////////////////////////////////////////////////////////
Command* Command_Create_No_Parameters(const char* commandName, Command_TextObject* receiver, no_parameter_operation operation)
{
    Command* commandObject = calloc(1, sizeof(Command));
    if (commandObject != NULL)
    {
        commandObject->commandName = commandName;
        commandObject->receiver = receiver;
        commandObject->operation_no_parameters = operation;
    }
    return commandObject;
}

///////////////////////////////////////////////////////////////////////////////
// Command_Destroy()
///////////////////////////////////////////////////////////////////////////////
void Command_Destroy(Command* commandObject)
{
    free(commandObject);
}

///////////////////////////////////////////////////////////////////////////////
// Command_Execute()
///////////////////////////////////////////////////////////////////////////////
void Command_Execute(Command* commandObject)
{
    if (commandObject != NULL && commandObject->receiver != NULL)
    {
        if (commandObject->operation_two_parameters != NULL)
        {
            commandObject->operation_two_parameters(commandObject->receiver, commandObject->argument1, commandObject->argument2);
        }
        else if (commandObject->operation_no_parameters != NULL)
        {
            commandObject->operation_no_parameters(commandObject->receiver);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Command_ToString()
///////////////////////////////////////////////////////////////////////////////
const char* Command_ToString(Command* commandObject)
{
    static char commandAsString[64] = { '\0'};

    commandAsString[0] = '\0';

    const char* string = commandAsString;

    if (commandObject != NULL)
    {
        if (commandObject->operation_two_parameters != NULL)
        {
            int numChars = snprintf(commandAsString, sizeof(commandAsString), "%s \"%s\" with \"%s\"", commandObject->commandName, commandObject->argument1, commandObject->argument2);
            if (numChars < 0)
            {
                int errorCode = errno;
                printf("  Error(%d)! Failed to format command '%s' as a string: %s\n", errorCode, commandObject->commandName, strerror(errorCode));
            }
        }
        else if (commandObject->operation_no_parameters != NULL)
        {
            string = commandObject->commandName;
        }
    }
    if (string[0] == '\0')
    {
        string = "<NO COMMAND>";
    }
    return string;
}
