/// @file
/// @brief
/// Declaration of the @ref MessageWindow support functions, MessageWindow_Create(),
/// MessageWindow_Destroy(), MessageWindow_ProcessMessage(), and
/// MessageWindow_ToString(),
/// as used in the @ref handlerchain_pattern.

#pragma once
#ifndef __HANDLERCHAIN_WINDOW_H__
#define __HANDLERCHAIN_WINDOW_H__

#include <stdbool.h>

#include "HandlerChain_Message.h"

//=============================================================================
//=============================================================================
//=============================================================================

/// <summary>
/// Create a MessageWindow object with the given properties and return the ID
/// of the object.
/// </summary>
/// <param name="title">Title of the window.</param>
/// <param name="x">Horizontal position of the upper left corner of the window.</param>
/// <param name="y">Vertical position of the upper left corner of the window.</param>
/// <param name="w">Width of the window.</param>
/// <param name="h">Height of the window.</param>
/// <returns>Returns the ID of the window, if successfully created; otherwise,
/// returns false.</returns>
int MessageWindow_Create(const char* title, int x, int y, int w, int h);

/// <summary>
/// Destroy the MessageWindow object with the given ID.  Removes the window
/// from any message handling as well.
/// </summary>
/// <param name="windowId">ID of the MessageWindow to destroy.</param>
void MessageWindow_Destroy(int windowId);

/// <summary>
/// Pass a Message object to a window for processing.
/// </summary>
/// <param name="windowId">The ID of the window who will get the message.</param>
/// <param name="message">The Message object to process.</param>
/// <returns>Returns true if the message was handled and no further windows should
/// be notified; otherwise return false to allow the message to be passed to
/// subsequent windows.</returns>
bool MessageWindow_ProcessMessage(int windowId, Message* message);

/// <summary>
/// Convert the specified window to a string representation.
/// </summary>
/// <param name="windowId">ID of the window to convert.</param>
/// <param name="output">A DynamicString that returns the string version of the
/// window.  Call DynamicString_Initialize() on this object before passing
/// as an argument.</param>
void MessageWindow_ToString(int windowId, DynamicString* output);

#endif //__HANDLERCHAIN_WINDOW_H__

