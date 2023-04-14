/// @file
/// @brief
/// Declaration of the Command_TextObject structure and associated functions
/// as used in the @ref command_pattern.

#pragma once
#ifndef __COMMAND_TEXTOBJECT_H__
#define __COMMAND_TEXTOBJECT_H__

#include <stdbool.h>


/// <summary>
/// Container for a string.  Need to use a structure to keep the starting text
/// and the current text together.  Operations applied to an instance of this
/// structure alter the contents but not the structure itself.
/// </summary>
typedef struct Command_TextObject
{
    /// <summary>
    /// Starting string text so we can reset the text to a known point.
    /// </summary>
    const char* startingText;

    /// <summary>
    /// The text that can change.
    /// </summary>
    char* text;

} Command_TextObject;

/// <summary>
/// Initialize a Command_TextObject with the specified text.
/// </summary>
/// <param name="textObject">A Command_TextObject to initialize with the given text.</param>
/// <param name="startingText">The text with which to initialize the object.  String is not
/// duplicated.</param>
/// <returns>Returns true if the initialization was successful; otherwise,
/// returns false (a null pointer was passed in or a out of memory condition
/// occurred.</returns>
bool Command_TextObject_Initialize(Command_TextObject* textObject, const char* startingText);

/// <summary>
/// Clear the contents of the specified Command_TextObject, releasing any allocated
/// resources associated with the Command_TextObject.
/// </summary>
/// <param name="textObject">A Command_TextObject whose contents are to be destroyed.</param>
void Command_TextObject_Clear(Command_TextObject* textObject);

/// <summary>
/// Resets the Command_TextObject to the starting string.
/// </summary>
/// <param name="textObject">The Command_TextObject to reset.</param>
void Command_TextObject_Reset(Command_TextObject* textObject);

/// <summary>
/// Gets the text in the specified Command_TextObject.
/// </summary>
/// <param name="textObject">The Command_TextObject from which to get the text.</param>
/// <returns>Returns a pointer to the mutable text in the Command_TextObject.</returns>
char* Command_TextObject_GetText(Command_TextObject* textObject);

/// <summary>
/// Sets the text in the specified Command_TextObject.
/// </summary>
/// <param name="textObject">The Command_TextObject in which to change the mutable text.
/// </param>
/// <param name="newText">The text to change to.</param>
void Command_TextObject_SetText(Command_TextObject* textObject, const char* newText);

/// <summary>
/// Converts the Command_TextObject to a string (basically, returns the current text
/// from the Command_TextObject).
/// </summary>
/// <param name="textObject">The Command_TextObject from which to get the current text.
/// </param>
/// <returns>Returns a pointer to the current text.  Treat as read-only.</returns>
const char* Command_TextObject_ToString(Command_TextObject* textObject);

#endif // __COMMAND_TEXTOBJECT_H__

