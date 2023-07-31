
/// @file
/// @brief
/// Implementation of the Command_Exercise() function as used in the
/// @ref command_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/replace.h"
#include "helpers/stack.h"

#include "Command_Exercise.h"
#include "Command_Command.h"

/// <summary>
/// The stack used to remember the commands for undo.
/// </summary>
static StackEntry* _commandUndoList = NULL;


//=============================================================================
//=============================================================================

/// <summary>
/// Save the given command on the undo list then execute the command on the
/// text object with which the command was created.
/// </summary>
/// <param name="command">The Command object to apply to the text object.</param>
void Command_Save_And_Execute(Command* command)
{
    Stack_Push(&_commandUndoList, command);
    Command_Execute(command);
}


/// <summary>
/// An operation to search and replace text in a Command_TextObject.
/// </summary>
/// <param name="source">The Command_TextObject to affect.</param>
/// <param name="searchPattern">What to look for in the Command_TextObject.</param>
/// <param name="replaceText">What to replace the searchPattern with.</param>
static void Command_Operation_Replace(Command_TextObject* source, const char* searchPattern, const char* replaceText)
{
    const char* newText = replace_str(Command_TextObject_GetText(source), searchPattern, replaceText);
    if (newText != NULL)
    {
        Command_TextObject_SetText(source, newText);
    }
    else
    {
        printf("  Error replacing text, probably out of memory.\n");
    }
}

/// <summary>
/// An operation to reverse the characters in the given Command_TextObject.
/// </summary>
/// <param name="source">The Command_TextObject to affect.</param>
static void Command_Operation_Reverse(Command_TextObject* source)
{
    if (source != NULL && source->text != NULL)
    {
        char* text = Command_TextObject_GetText(source);

        size_t textSize = strlen(text);
        size_t halftextSize = textSize / 2;
        for (size_t index = 0; index < halftextSize; ++index)
        {
            char c = text[index];
            text[index] = text[textSize - index - 1];
            text[textSize - index - 1] = c;
        }
    }
}


/// <summary>
/// Perform an undo on the given Command_TextObject, using the commands in the
/// "global" undo list.  If the undo list is empty, nothing happens.
/// </summary>
/// <param name="text">The Command_TextObject to affect.</param>
static void Command_Undo(Command_TextObject* text)
{
    if (!Stack_IsEmpty(&_commandUndoList))
    {
        // Reset the text to the starting point.
        Command_TextObject_Reset(text);

        // Get rid of the last command applied and remember it.
        Command* lastCommand = (Command*)Stack_Pop(&_commandUndoList);

        // Reverse the existing stack onto another stack so we can apply
        // the commands in order.
        //
        // Note: A doubly-linked list would eliminate the need for this stack-
        // swapping and be much more efficient but a doubly-linked list is a
        // bear to get right.
        StackEntry* operationsStack = NULL;
        while (!Stack_IsEmpty(&_commandUndoList))
        {
            Command* command = Stack_Pop(&_commandUndoList);
            Stack_Push(&operationsStack, command);
        }

        // Now apply all remaining commands to the text in order
        // (oldest to newest).  Also puts the commands back on the original
        // undo stack.
        while (!(Stack_IsEmpty(&operationsStack)))
        {
            Command* command = Stack_Pop(&operationsStack);
            Command_Execute(command);
            Stack_Push(&_commandUndoList, command);
        }

        // Show off what we (un)did.
        printf("    undoing command %-31s==> \"%s\"\n", Command_ToString(lastCommand), Command_TextObject_ToString(text));
        Command_Destroy(lastCommand);
    }
}


/// <summary>
/// Helper function to create a Command object that replaces text in the given
/// Command_TextObject, adds the command to the undo list and then applies the command
/// to the Command_TextObject.  Finally, it shows off what was done.
/// </summary>
/// <param name="text">The Command_TextObject to affect.</param>
/// <param name="searchPattern">What to look for in the Command_TextObject.</param>
/// <param name="replaceText">What to replace the searchPattern with.</param>
static void Command_ApplyReplaceCommand(Command_TextObject* text, const char* searchPattern, const char* replaceText)
{
    Command* command = Command_Create_Two_Parameters("Replace", text, Command_Operation_Replace, searchPattern, replaceText);
    if (command != NULL)
    {
        Command_Save_And_Execute(command);
        printf("    command %-31s==> \"%s\"\n", Command_ToString(command), Command_TextObject_ToString(text));
    }
    else
    {
        printf("  Error! Out of memory allocating a Command structure for replace operation.\n");
    }
}


/// <summary>
/// Helper function to create a Command object that reverses the order of
/// the characters in the given Command_TextObject, adds the command to the undo
/// list and then applies the command to the Command_TextObject.  Finally, it shows
/// what was done.
/// </summary>
/// <param name="text">The Command_TextObject to affect.</param>
static void Command_ApplyReverseCommand(Command_TextObject* text)
{
    Command* command = Command_Create_No_Parameters("Reverse", text, Command_Operation_Reverse);
    if (command != NULL)
    {
        Command_Save_And_Execute(command);
        printf("    command %-31s==> \"%s\"\n", Command_ToString(command), Command_TextObject_ToString(text));
    }
    else
    {
        printf("  Error! Out of memory allocating a Command structure for reverse operation.\n");
    }
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref command_pattern.
///
/// The Command pattern is used to encapsulate an operation or command
/// associated with an object so that the command can be applied to
/// the object at a later time.
///
/// In this exercise, an undo list is implemented using Commands that
/// associate commands defined in this file with a text object.  The
/// commands are applied to the text object in succession then
/// effectively undone.
/// </summary>
// ! [Using Command in C]
void Command_Exercise(void)
{
    printf("\nCommand_Exercise\n");

    Command_TextObject textObject = { 0 };
    if (Command_TextObject_Initialize(&textObject, "This is a line of text on which to experiment."))
    {
        printf("  Starting text: \"%s\"\n", Command_TextObject_ToString(&textObject));

        // Apply four operations to the text.
        Command_ApplyReplaceCommand(&textObject, "text", "painting");
        Command_ApplyReplaceCommand(&textObject, "on", "off");
        Command_ApplyReverseCommand(&textObject);
        Command_ApplyReplaceCommand(&textObject, "i", "!");

        printf("  Now perform undo until back to original\n");

        // Now undo the four operations.
        Command_Undo(&textObject);
        Command_Undo(&textObject);
        Command_Undo(&textObject);
        Command_Undo(&textObject);

        printf("  Final text   : \"%s\"\n", Command_TextObject_ToString(&textObject));

        Command_TextObject_Clear(&textObject);
    }
    printf("  Done.\n");
}
// ! [Using Command in C]
