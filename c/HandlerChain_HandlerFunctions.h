/// @file
/// @brief
/// Declaration of the Handler Chain functions, HandlerChain_SendMessage(),
/// HandlerChain_AddWindow(), HandlerChain_RemoveWindow(), and
/// HandlerChain_ToString(),
/// as used in the @ref handlerchain_pattern.
#pragma once

#ifndef __HANDLECHAIN_HANDLERFUNCTIONS_H__
#define __HANDLECHAIN_HANDLERFUNCTIONS_H__

#include "HandlerChain_Message.h"

/// <summary>
/// Send a message to each of the handlers in the list, protected by
/// a multi-threading lock.
/// </summary>
/// <param name="windowId">ID of window to target message with.  -1 to target
/// all windows.</param>
/// <param name="message">The Message object to send to each handler.</param>
void HandlerChain_SendMessage(int windowId, Message* message);

/// <summary>
/// Add an instance of a MessageWindow to end of the list of windows,
/// protected by a multi-threading lock.
/// 
/// If a MessageWindow is already in the list, it is not added again.
/// </summary>
/// <param name="windowId">ID of the MessageWindow to add.</param>
/// <returns>Returns true if the handler chain was successfully added to the
/// list; otherwise, returns false, indicating an out of memory condition
/// (or a NULL argument).</returns>
bool HandlerChain_AddWindow(int windowId);

/// <summary>
/// Remove an instance of a MessageWindow from the list,
/// protected by a multi-threading lock.
/// 
/// If the MessageWindow is not in the list, the request to remove
/// is ignored.
/// </summary>
/// <param name="windowId">ID of the MessageWindow to remove.</param>
void HandlerChain_RemoveWindow(int windowId);

/// <summary>
/// Convert the Handler Chain to a string, protected by a multi-threading
/// lock.
/// </summary>
/// <param name="output">Returns a string representation of the Handler Chain
/// and all the handlers it contains.</param>
/// <returns>Returns true if the handler chain was successfully converted to
/// a string; otherwise, returns false, indicating an out of memory condition
/// (or a NULL argument).</returns>
bool HandlerChain_ToString(DynamicString* output);


#endif // __HANDLECHAIN_HANDLERFUNCTIONS_H__

