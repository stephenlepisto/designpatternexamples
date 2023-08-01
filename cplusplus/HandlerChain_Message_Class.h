/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Message "Message"
/// and @ref DesignPatternExamples_cpp::MessagePosition "MessagePosition" structs
/// used in the @ref handlerchain_pattern

#pragma once
#ifndef __HANDLERCHAIN_MESSAGE_CLASS_H__
#define __HANDLERCHAIN_MESSAGE_CLASS_H__

#include <string>

#include "helpers/formatstring.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Type of message handled by MessageWindow.
    /// </summary>
    enum MessageType
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
        ButtonUp,
    };



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Position of the message in global coordinates (same scope of
    /// coordinates as windows).  Although this can handle negative
    /// coordinates, the example is careful to use only positive coordinates.
    /// </summary>
    struct MessagePosition
    {
        /// <summary>
        /// X position.
        /// </summary>
        int X;

        /// <summary>
        /// Y position.
        /// </summary>
        int Y;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="x">X position to use.</param>
        /// <param name="y">Y position to use.</param>
        MessagePosition(int x, int y)
            : X(x)
            , Y(y)
        {
        }

        /// <summary>
        /// Convert this position to a string.
        /// </summary>
        /// <returns>A string containing a string representation of the position.</returns>
        std::string ToString()
        {
            return Helpers::formatstring("x=%2d,y=%2d", X, Y);
        }
    };



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a message sent to the windows.  A message contains a type
    /// and a position.
    /// </summary>
    struct Message
    {
        /// <summary>
        /// Value from the MessageType enumeration indicating the type of this message.
        /// </summary>
        enum MessageType MessageType;

        /// <summary>
        /// Position of message when the message was sent.  In a real system, this
        /// would generally represent the position of a cursor at the time the message
        /// was generated.
        /// </summary>
        MessagePosition Position;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="type">Value from the MessageType enumeration indicating the
        /// type of message being created.</param>
        /// <param name="position">Position of the message, expressed as a MessagePosition
        /// object.</param>
        Message(enum MessageType type, struct MessagePosition position)
            : MessageType(type)
            , Position(position)
        {
        }

        /// <summary>
        /// Convert this message to a string.
        /// </summary>
        /// <returns>Returns a string representation of this message.</returns>
        std::string ToString()
        {
            std::string messageTypeAsString;
            switch (MessageType)
            {
                case MessageType::Close:
                    messageTypeAsString = "Close";
                    break;

                case MessageType::ButtonDown:
                    messageTypeAsString = "ButtonDown";
                    break;

                case MessageType::ButtonUp:
                    messageTypeAsString = "ButtonUp";
                    break;

                default:
                    messageTypeAsString = "Unknown message type";
                    break;
            }
            return Helpers::formatstring("%s at (%s)", messageTypeAsString.c_str(), Position.ToString().c_str());
        }
    };

} // end namespace

#endif // __HANDLERCHAIN_MESSAGE_CLASS_H__
