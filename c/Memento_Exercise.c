/// @file
/// @brief
/// Implementation of the Memento_Exercise() function as used in the
/// @ref memento_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/stack.h"
#include "helpers/replace.h"

#include "Memento_Memento.h"
#include "Memento_TextObject.h"
#include "Memento_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// The list of memento objects that form a series of snapshots in time
/// of a Memento_TextObject.
/// </summary>
static StackEntry* _mementoUndoList = NULL;

/// <summary>
/// Take a snapshot of the given text object associated with the name of
/// given operation.
/// </summary>
/// <param name="text">The Memento_TextObject to take a snapshot of.</param>
/// <param name="operation">A string describing the operation that will
/// be applied after the snapshot is taken.</param>
static void Memento_SaveForUndo(Memento_TextObject* text, const char* operation)
{
    if (text != NULL && operation != NULL)
    {
        Memento* memento = Memento_Create(Memento_TextObject_GetText(text), operation);
        if (memento != NULL)
        {
            Stack_Push(&_mementoUndoList, memento);
        }
    }
}


/// <summary>
/// An operation to search and replace text in a Memento_TextObject.
/// </summary>
/// <param name="source">The Memento_TextObject to affect.</param>
/// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
/// <param name="replaceText">What to replace the searchPattern with.</param>
static void Memento_Operation_Replace(Memento_TextObject* source, const char* searchPattern, const char* replaceText)
{
    if (source != NULL && searchPattern != NULL && replaceText != NULL)
    {
        char* newText = replace_str(Memento_TextObject_GetText(source), searchPattern, replaceText);
        if (newText != NULL)
        {
            Memento_TextObject_SetText(source, newText);
            free(newText);
        }
    }
}

/// <summary>
/// An operation to reverse the characters in the given Memento_TextObject.
/// </summary>
/// <param name="source">The Memento_TextObject to affect.</param>
static void Memento_Operation_Reverse(Memento_TextObject* source)
{
    if (source != NULL)
    {
        // We will change the text object in-place because we can.
        char* text = Memento_TextObject_GetText(source);

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
/// Perform an undo on the given Command_TextObject, using the mementos in the
/// "global" undo list.  If the undo list is empty, nothing happens.
/// </summary>
/// <param name="text">The Command_TextObject to affect.</param>
static void Memento_Undo(Memento_TextObject* text)
{
    if (text != NULL)
    {
        if (_mementoUndoList != NULL)
        {
            Memento* lastMemento = Stack_Pop(&_mementoUndoList);
            Memento_TextObject_SetText(text, lastMemento->text);

            // Show off what we (un)did.
            printf("    undoing operation %-31s: \"%s\"\n", lastMemento->name, Memento_TextObject_ToString(text));
            Memento_Destroy(lastMemento);
        }
    }
}

/// <summary>
/// Helper function to replace a pattern with another string in the
/// given Memento_TextObject after adding a snapshot of the text
/// object to the undo list.  Finally, it shows off what was done.
/// </summary>
/// <param name="text">The Memento_TextObject to affect.</param>
/// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
/// <param name="replaceText">What to replace the searchPattern with.</param>
static void Memento_ApplyReplaceOperation(Memento_TextObject* text, const char* searchPattern, const char* replaceText)
{
    if (text != NULL && searchPattern != NULL && replaceText != NULL)
    {
        char operationName[128] = { 0 };
        int num_chars = sprintf_s(operationName, sizeof(operationName), "Replace '%s' with '%s'", searchPattern, replaceText);
        if (num_chars != -1)
        {
            Memento_SaveForUndo(text, operationName);
            Memento_Operation_Replace(text, searchPattern, replaceText);
            printf("    operation %-31s: \"%s\"\n", operationName, Memento_TextObject_ToString(text));
        }
        else
        {
            printf("  Error (code = %u)! sprintf_s() failed to create operation name for replace operation!\n", errno);
        }
    }
}


/// <summary>
/// Helper function to reverse the order of the characters in the
/// given Memento_TextObject after adding a snapshot of the text
/// object to an undo list.  Finally, it shows what was done.
/// </summary>
/// <param name="text">The Memento_TextObject to affect.</param>
static void Memento_ApplyReverseOperation(Memento_TextObject* text)
{
    const char* operationName = "Reverse";
    Memento_SaveForUndo(text, operationName);
    Memento_Operation_Reverse(text);
    printf("    operation %-31s: \"%s\"\n", operationName, Memento_TextObject_ToString(text));
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref memento_pattern "Memento" design pattern.
///
/// In this exercise, the Memento pattern is used to take snapshots of
/// a text object so as to form an undo list of changes to the text
/// object.  Undoing an operation means restoring a snapshot of the
/// text object.
///
/// The undo list is implemented as a stack of memento objects that
/// each represent a snapshot of the text object taken before each
/// operation is applied.  After all operations are applied, the
/// mementos are used to restore the text object in reverse order,
/// effectively undoing each operation in turn.
///
/// Compare this to the Command_Exercise() and note that the steps
/// taken there are identical to here (except for method names, of
/// course).  The difference lies in how operations are executed
/// and undone.  Mementos make the undo process much cleaner and
/// faster since operations do not need to be applied repeatedly to
/// get the text object into a specific state.  Specifically,
/// compare Command_Undo() with Memento_Undo().  Also note the
/// differences in the "Memento_ApplyXXOperation()" methods, which
/// more cleanly separate the save from the operation.
/// </summary>
// ! [Using Memento in C]
void Memento_Exercise(void)
{
    printf("\nMemento_Exercise\n");

    _mementoUndoList = NULL;

    // The base text object to work from.
    Memento_TextObject* text = Memento_TextObject_Create("This is a line of text on which to experiment.");
    if (text != NULL)
    {
        printf("  Starting text: \"%s\"\n", Memento_TextObject_ToString(text));

        // Apply four operations to the text.
        Memento_ApplyReplaceOperation(text, "text", "painting");
        Memento_ApplyReplaceOperation(text, "on", "off");
        Memento_ApplyReverseOperation(text);
        Memento_ApplyReplaceOperation(text, "i", "!");

        printf("  Now perform undo until back to original\n");

        // Now undo the four operations.
        Memento_Undo(text);
        Memento_Undo(text);
        Memento_Undo(text);
        Memento_Undo(text);

        printf("  Final text   : \"%s\"\n", Memento_TextObject_ToString(text));

        Memento_TextObject_Destroy(text);
    }

    printf("  Done.\n");
}
// ! [Using Memento in C]
