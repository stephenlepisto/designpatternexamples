
/// @file
/// @brief
/// Implementation of the NullObject_Exercise() function as used in the 
/// @ref nullobject_pattern.

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NullObject_MoveCommandList.h"
#include "NullObject_Exercise.h"


/// <summary>
/// Show the move command and its name followed by a newline.
/// </summary>
void MoveCommand_Show(char commandToken, const char* commandName)
{
    if (commandName != NULL)
    {
        printf("    '%c' -> %s\n", commandToken, commandName);
    }
}


/// <summary>
/// Represents the Move Left command.
/// </summary>
void MoveCommandLeft_Execute()
{
    printf("move left");
}


/// <summary>
/// Represents the Move Right command.
/// </summary>
void MoveCommandRight_Execute()
{
    printf("move right");
}


/// <summary>
/// Represents the Move Up command.
/// </summary>
void MoveCommandUp_Execute()
{
    printf("move up");
}


/// <summary>
/// Represents the Move Down command.
/// </summary>
void MoveCommandDown_Execute()
{
    printf("move down");
}


/// <summary>
/// Represents the Do Nothing command.  This is the Null "Object" for this
/// exercise.
/// </summary>
void MoveCommandNone_Execute()
{
    // Do nothing.
}


/// <summary>
/// Represents the processor that translates the move list into a list of
/// MoveCommand objects then either displays them or executes them.
/// 
/// This classes uses a parser to convert the single letter characters in
/// a string into a list of actions (instances of the MoveCommand class).
/// This list of actions is then executed to perform the operations.
/// 
/// This process of executing the list of operations is an example of the
/// @ref command_pattern.  This is also an example of the
/// @ref interpreter_pattern, where the actions are the tokens to be
/// interpreted.
/// </summary>

/// <summary>
/// Helper method to convert a list of single letter commands into a
/// list of MoveCommand objects.
/// 
/// This method recognizes 'L', 'R', 'U', and 'D' (case-insensitive).
/// All other characters default to the "Do Nothing" (Null Object) command.
/// </summary>
/// <param name="moveList">A string containing a list of single letter
/// commands to be parsed.</param>
/// <param name="commandList">A MoveCommandList object in which to return the
/// MoveCommand objects representing the move commands parsed from the string.
/// </param>
/// <returns>Returns true if the string was successfully parsed and the MoveCommand
/// objects were added to the command list; otherwise, returns false, indicating
/// an out of memory condition or a null argument passed in.</returns>
bool _MoveProcessor_ParseMoves(const char* moveList, MoveCommandList* commandList)
{
    bool parsed = false;

    if (moveList != NULL && commandList != NULL)
    {
        parsed = true;
        size_t moveListSize = strlen(moveList);
        for (size_t index = 0; index < moveListSize; index++)
        {
            char commandChar = (char)toupper(moveList[index]);
            MoveCommand* moveCommand = NULL;

            switch (commandChar)
            {
            case 'U':
                moveCommand = MoveCommand_Create(commandChar, "Up", MoveCommandUp_Execute);
                break;

            case 'D':
                moveCommand = MoveCommand_Create(commandChar, "Down", MoveCommandDown_Execute);
                break;

            case 'L':
                moveCommand = MoveCommand_Create(commandChar, "Left", MoveCommandLeft_Execute);
                break;

            case 'R':
                moveCommand = MoveCommand_Create(commandChar, "Right", MoveCommandRight_Execute);
                break;

            default:
                // Everything else is a "do nothing" command.
                moveCommand = MoveCommand_Create(commandChar, "None", MoveCommandNone_Execute);
                break;
            }
            if (moveCommand != NULL)
            {
                if (!MoveCommandList_Add(commandList, moveCommand))
                {
                    printf("  Error!  Out of memory condition adding command %c.\n", commandChar);
                    MoveCommandList_Clear(commandList);
                    parsed = false;
                    break;
                }
            }
            else
            {
                printf("  Error!  Out of memory condition creating MoveCommand for command %c.\n", commandChar);
                parsed = false;
                break;
            }
        }
    }

    return parsed;
}


/// <summary>
/// Helper method to execute all the given commands.
/// </summary>
/// <param name="commands">A list of MoveCommand objects to "execute".</param>
/// <remarks>
/// In this implementation, the MoveCommand object execute function prints
/// the command as "<move xxx> " on the current line.  When all commands have
/// been printed, a new line is printed to move to the next line.
/// The "Do Nothing" command doesn't print anything, leaving only the
/// empty <>.
/// </remarks>
void _MoveProcessor_ExecuteMoves(MoveCommandList* commands)
{
    if (commands != NULL)
    {
        for (size_t index = 0; index < commands->commands_count; index++)
        {
            MoveCommand* moveCommand = commands->commands[index];
            if (moveCommand->Execute != NULL)
            {
                printf("<");
                moveCommand->Execute();
                printf("> ");
            }
        }
        printf("\n");
    }
}


/// <summary>
/// Show the command character and name of the command for all commands in the
/// given list of commands.
/// </summary>
/// <param name="commands">The list of MoveCommand objects to display.</param>
void _MoveProcessor_ShowMoves(MoveCommandList* commands)
{
    if (commands != NULL)
    {
        for (size_t index = 0; index < commands->commands_count; index++)
        {
            MoveCommand* moveCommand = commands->commands[index];
            MoveCommand_Show(moveCommand->commandToken, moveCommand->commandName);
        }
    }
}

/// <summary>
/// Parse and execute the given list of move commands, where each
/// command is represents by a single character.
/// 
/// Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
/// characters are assigned a "Do Nothing" (Null Object) command.
/// </summary>
/// <param name="moveList">A string of characters to parse and execute.</param>
void MoveProcessor_ExecuteMoveList(const char* moveList)
{
    MoveCommandList commandList;

    MoveCommandList_Initialize(&commandList);

    if (_MoveProcessor_ParseMoves(moveList, &commandList))
    {
        _MoveProcessor_ExecuteMoves(&commandList);
    }
    MoveCommandList_Clear(&commandList);
}


/// <summary>
/// Parse and display the given list of move commands, where each
/// command is represents by a single character.
/// 
/// Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
/// characters are assigned a "Do Nothing" (Null Object) command.
/// </summary>
/// <param name="moveList">A string of characters to parse and display.</param>
void MoveProcessor_ShowMoveList(const char* moveList)
{
    MoveCommandList commandList;
    MoveCommandList_Initialize(&commandList);
    if (_MoveProcessor_ParseMoves(moveList, &commandList))
    {
        _MoveProcessor_ShowMoves(&commandList);
    }
    MoveCommandList_Clear(&commandList);
}


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref nullobject_pattern.
/// 
/// The Null Object pattern is where an object or function acts as a
/// stand-in for real commands but otherwise does nothing.
/// 
/// In this exercise, movement commands are presented as characters in
/// a string, with the characters 'u', 'd', 'l', and 'r' representing
/// the moves "up", "down", "left", and "right", respectively.  To
/// keep the processing of this string simple, all other characters in
/// the string are assigned a Null Object ("Do Nothing") version of
/// the move command.
/// 
/// This example displays the commands after parsing and then
/// "executes" commands, which consists of printing the commands out.
/// 
/// This example highlights the @ref nullobject_pattern while also
/// utilizing the @ref command_pattern and @ref interpreter_pattern.
/// </summary>
// ! [Using NullObject in C]
void NullObject_Exercise()
{
    printf("\nNullObject Exercise\n");

    // A stream of recognized and unrecognized move commands.  The
    // unrecognized commands do nothing.
    const char* moveString = "ur#ld!lr";
    printf("  Showing the move commands:\n");
    MoveProcessor_ShowMoveList(moveString);

    printf("  Executing the move commands:\n");
    printf("    %s -> ", moveString);
    MoveProcessor_ExecuteMoveList(moveString);

    printf("  Done.\n");
}
// ! [Using NullObject in C]

