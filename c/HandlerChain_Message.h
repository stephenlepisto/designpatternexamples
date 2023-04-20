/// @file
/// @brief
/// Declaration of the Message and MessagePosition structures, along with the
/// functions, MessagePosition_ToString(), Message_Initialize(), and
/// Message_ToString(), as used in the @ref handlerchain_pattern.

#pragma once
#ifndef __HANDLERCHAIN_MESSAGE_H__
#define __HANDLERCHAIN_MESSAGE_H__

#include "helpers/dynamicstring.h"

/// <summary>
/// Type of message handled by MessageWindow.
/// </summary>
typedef enum
{
    /// <summary>
    /// Window is asked to close itself, generally sent by the window itself
    /// in response to a button up in a Close region.  Applies only to the
    /// currently selected window.
    /// </summary>
    Close = 0,

    /// <summary>
    /// Selects a window based on position.
    /// </summary>
    ButtonDown = 1,

    /// <summary>
    /// Take an action on the currently selected window.
    /// </summary>
    ButtonUp = 2,

    /// <summary>
    /// Window is being told to destroy itself.  This is sent in response to
    /// seeing the Close message.
    /// </summary>
    Destroy = 3,

} MessageType;


//========================================================================
//========================================================================
//========================================================================


/// <summary>
/// Position of the message in global coordinates (same scope of
/// coordinates as windows).  Although this can handle negative
/// coordinates, the example is careful to use only positive coordinates.
/// </summary>
typedef struct
{
    /// <summary>
    /// X position.
    /// </summary>
    int X;

    /// <summary>
    /// Y position.
    /// </summary>
    int Y;
} MessagePosition;


/// <summary>
/// Convert a MessagePosition object to a string representation.
/// </summary>
/// <param name="position">The MessagePosition object to convert.</param>
/// <param name="output">A DynamicString in which to store the string
/// representation of the `position` argument.  Call DynamicString_Initialize()
/// on this object before passing as an argument.</param>
void MessagePosition_ToString(MessagePosition* position, DynamicString* output);


//========================================================================
//========================================================================
//========================================================================


/// <summary>
/// Represents a message sent to the windows.  A message contains a type
/// and a position.
/// </summary>
typedef struct
{
    /// <summary>
    /// Value from the MessageType enumeration indicating the type of this message.
    /// </summary>
    MessageType MessageType;

    /// <summary>
    /// Position of message when the message was sent.  In a real system, this
    /// would generally represent the position of a cursor at the time the message
    /// was generated.
    /// </summary>
    MessagePosition Position;
} Message;


/// <summary>
/// Initialize a Message structure.
/// </summary>
/// <param name="message">The Message structure to initialize.</param>
/// <param name="type">Value from the MessageType enumeration indicating the
/// type of message being created.</param>
/// <param name="x">Horizontal position of the message.</param>
/// <param name="y">Vertical position of the message.</param>
void Message_Initialize(Message* message, MessageType type, int x, int y);

/// <summary>
/// Convert a Message object to a string representation.
/// </summary>
/// <param name="message">The Message object to convert.</param>
/// <param name="output">The string representation of the Message object.
/// Call DynamicString_Initialize() on this object before passing as an argument.</param>
void Message_ToString(Message* message, DynamicString* output);

#endif // __HANDLERCHAIN_MESSAGE_H__

