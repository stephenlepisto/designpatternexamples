/// @file
/// @brief
/// Declaration of the Memento structure and support functions,
/// Memento_Create() and Memento_Destroy(),
/// as used in the @ref memento_pattern.

#pragma once
#ifndef __MEMENTO_MEMENTO_H__
#define __MEMENTO_MEMENTO_H__

/// <summary>
/// Represents a single memento (snapshot) of the text state before
/// an operation is applied.  The operation becomes the name of the
/// memento for display purposes.
/// </summary>
typedef struct
{
    char* text;         ///< The snapshot to be remembered by the Memento.
    const char* name;   ///< The operation name that triggered the need for this Memento.
} Memento;

//-----------------------------------------------------------------------------

/// <summary>
/// Create a new instance of the Memento structure, initialized to the given
/// text and name.
/// </summary>
/// <param name="text">The text to assign the memento.  This is the snapshot
/// to be remembered.  This is duplicated in the Memento object.</param>
/// <param name="name">The operation name used to on the parent text object.
/// This is duplicated in the Memento object.</param>
/// <returns>Returns a pointer to a new Memento object if successful, otherwise,
/// returns NULL.</returns>
Memento* Memento_Create(const char* text, const char* name);

/// <summary>
/// Destroy an existing instance of the Memento structure.  After this function
/// returns, the pointer to the memento is no longer valid.
/// </summary>
/// <param name="memento">The Memento object to destroy.</param>
void Memento_Destroy(Memento* memento);


#endif // __MEMENTO_MEMENTO_H__

