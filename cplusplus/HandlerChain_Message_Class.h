/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Message "Message" struct
/// and @ref DesignPatternExamples_cpp::MessagePosition "MessagePosition" struct.

#pragma once
#ifndef __HANDLERCHAIN_MESSAGE_CLASS_H__
#define __HANDLERCHAIN_MESSAGE_CLASS_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20
#include <string>

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
            return std::format("x={0:2},y={1:2}", X, Y);
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
        MessageType MessageType;

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
            return std::format("{0} at ({1})", messageTypeAsString, Position.ToString());
        }
    };

} // end namespace

#endif // __HANDLERCHAIN_MESSAGE_CLASS_H__

