/// @file
/// @brief
/// Declaration of the Memento_TextObject structure and support functions,
/// Memento_TextObject_Create(), Memento_TextObject_Destroy(),
/// Memento_TextObject_GetText(), Memento_TextObject_SetText(), and
/// Memento_TextObject_ToString(),
/// as used in the @ref memento_pattern.

#pragma once
#ifndef __MEMENTO_TEXTOBJECT_H__
#define __MEMENTO_TEXTOBJECT_H__

/// <summary>
/// Container for a string.
/// </summary>
typedef struct
{
    char* text; ///< The text object contained within this Memento_TextObject.
} Memento_TextObject;

/// <summary>
/// Create a new instance of the Memento_TextObject structure and initialize it
/// with the given text.
/// </summary>
/// <param name="text">The text with which to initialize the Memento_TextObject.
/// This is duplicated.</param>
/// <returns>Returns a pointer to a new Memento_TextObject instance if successful;
/// otherwise, returns NULL (out of memory condition).</returns>
Memento_TextObject* Memento_TextObject_Create(const char* text);

/// <summary>
/// Destroy the given Memento_TextObject object and release any used memory.
/// After this function returns, the pointer is no longer valid.
/// </summary>
/// <param name="textObject">The Memento_TextObject to destroy.</param>
void Memento_TextObject_Destroy(Memento_TextObject* textObject);

/// <summary>
/// Retrieve a pointer to the text contained within the Memento_TextObject.
/// The text can be altered through this pointer or can be replaced entirely
/// using the Memento_TextObject_SetText() function.
/// </summary>
/// <param name="textObject">The Memento_TextObject object from which to get
/// the text.</param>
/// <returns>Returns the pointer to the text as stored in the Memento_TextObject.</returns>
char* Memento_TextObject_GetText(Memento_TextObject* textObject);

/// <summary>
/// Replace the existing text in the Memento_TextObject object with the given
/// text.
/// </summary>
/// <param name="textObject">The Memento_TextObject from which to get the text.</param>
/// <param name="newText">The new text to set the Memento_TextObject to.  This
/// string is duplicated.</param>
void Memento_TextObject_SetText(Memento_TextObject* textObject, const char* newText);

/// <summary>
/// Return a string representation of the Memento_TextObject.  In this case, it
/// is just the underlying text.
/// </summary>
/// <param name="textObject">The Memento_TextObject from which to create a string.</param>
/// <returns>Returns a pointer to a string representation of the contents of the
/// Memento_TextObject.</returns>
const char* Memento_TextObject_ToString(Memento_TextObject* textObject);

#endif // __MEMENTO_TEXTOBJECT_H__

