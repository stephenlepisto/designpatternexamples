/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::MessageWindow "MessageWindow" class
/// and @ref DesignPatternExamples_cpp::WindowRectangle "WindowRectangle" class
/// used in the @ref handlerchain_pattern

#pragma once
#ifndef __HANDLECHAIN_MESSAGEWINDOW_CLASS_H__
#define __HANDLECHAIN_MESSAGEWINDOW_CLASS_H__

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "helpers/formatstring.h"

#include "HandlerChain_Class.h"
#include "HandlerChain_Message_Class.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a rectangular region, with upper left and lower right
    /// coordinates.
    ///
    /// For this example, the minimum width of a rectangle is 4 x 4.
    /// </summary>
    class WindowRectangle
    {
    private:
        /// <summary>
        /// Minimum width of a window (to accommodate a close box).
        /// </summary>
        const int MINIMUM_WIDTH = 4;
        /// <summary>
        /// Minimum height of a window (to accommodate a close box).
        /// </summary>
        const int MINIMUM_HEIGHT = 4;

    public:
        int Left;
        int Top;
        int Right;
        int Bottom;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="x">X coordinate of upper left corner.</param>
        /// <param name="y">Y coordinate of upper left corner.</param>
        /// <param name="width">Width of rectangle.</param>
        /// <param name="height">Height of rectangle.</param>
        WindowRectangle(int x, int y, int width, int height)
        {
            if (width < MINIMUM_WIDTH)
            {
                width = MINIMUM_WIDTH;
            }
            if (height < MINIMUM_HEIGHT)
            {
                height = MINIMUM_HEIGHT;
            }
            Left = x;
            Top = y;
            Right = x + width;
            Bottom = y + height;
        }

        /// <summary>
        /// Determine if the given point is in the rectangle.
        /// </summary>
        /// <param name="point">Point to examine.</param>
        /// <returns>Return true if the point is in the rectangle.</returns>
        bool PointInside(MessagePosition point)
        {
            bool isInside = false;

            if (point.X >= Left && point.X < Right &&
                point.Y >= Top && point.Y < Bottom)
            {
                isInside = true;
            }

            return isInside;
        }

        /// <summary>
        /// Convert this rectangle to a string.
        /// </summary>
        /// <returns>Returns a representation of this rectangle.</returns>
        std::string ToString()
        {
            return Helpers::formatstring("x1=%2d, y1=%2d, x2=%2d, y2=%2d", Left, Top, Right, Bottom);
        }
    };



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a rectangular region that can handle messages directed to that
    /// region.
    /// </summary>
    /// <remarks>
    /// Note: The IMessageHandler interface is an example of a
    /// @ref facade_pattern "Facade design pattern", where the complexity of
    /// the MessageWindow is exposed only through a few methods to a system
    /// that only needs to deal with those few methods.
    /// </remarks>
    class MessageWindow : public IMessageHandler
    {
    public:
        using shared_ptr_t = std::shared_ptr<MessageWindow>;

    private:
        // Size of QUIT region in the upper right corner of the region.
        const int CLOSE_WIDTH = 2;
        const int CLOSE_HEIGHT = 2;

        /// <summary>
        /// Alias for the function that handles the messages.
        /// </summary>
        using MessageHandler = bool (*)(MessageWindow* window, Message* message);

        /// <summary>
        /// Maps a message type to a handler method of type MessageHandler.
        /// </summary>
        std::map<MessageType, MessageHandler> _messageHandlers;

        /// <summary>
        /// Unique ID of this window.
        /// </summary>
        int _windowId;

        /// <summary>
        /// Title/Name of this window.
        /// </summary>
        std::string _title;

        /// <summary>
        /// Position of this window in global coordinates.
        /// </summary>
        WindowRectangle _windowBox;

        /// <summary>
        /// Position of the close window within the window box, although the
        /// coordinates are also global coordinates to eliminate the need to
        /// convert between window and global coordinates.
        /// </summary>
        WindowRectangle _closeBox;

        /// <summary>
        /// Whether this window has been selected (a button click occurred
        /// within the window).
        /// </summary>
        bool _selected;

        /// <summary>
        /// The HandlerChain to which this window belongs (as an IMessageHandler object).
        /// </summary>
        HandlerChain* _handlerChain;

        /// <summary>
        /// Used for assigning a unique ID to each created window.
        /// </summary>
        static int _nextWindowId;

    public:
        /// <summary>
        /// Creates an instance of the MessageWindow class with the specified
        /// attributes and adds the new instance to the given HandlerChain object.
        /// </summary>
        /// <param name="title">Title of the MessageWindow.</param>
        /// <param name="x">X position of the upper left corner of the window's region.</param>
        /// <param name="y">Y position of the upper left corner of hte window's region.</param>
        /// <param name="width">Width of the window's region.</param>
        /// <param name="height">Height of the window's region.</param>
        /// <param name="handlerChain">A HandlerChain object that will be given the window.
        /// </param>
        /// <returns>Returns the newly created MessageWindow.</returns>
        /// <remarks>
        /// Each MessageWindow instance is assigned a unique ID, which is required by
        /// the HandlerChain object.
        /// </remarks>
        static MessageWindow::shared_ptr_t CreateWindow(std::string title, int x, int y, int width, int height, HandlerChain* handlerChain);


        /// <summary>
        /// Determine if the specified point is in this MessageWindow's region.
        /// </summary>
        /// <param name="position">The global coordinate to examine.</param>
        /// <returns>Returns true if the point is contained within the MessageWindow's region.</returns>
        bool _PointInWindow(MessagePosition position)
        {
            return _windowBox.PointInside(position);
        }


        /// <summary>
        /// Determine if the specified point is in this MessageWindow's "close"
        /// region.
        /// </summary>
        /// <param name="position">The point to examine.</param>
        /// <returns>Returns true if the point is contained within the MessageWindow's
        /// "close" region.</returns>
        bool _PointInCloseBox(MessagePosition position)
        {
            return _closeBox.PointInside(position);
        }


        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="windowId">Unique ID of the window to use.</param>
        /// <param name="title">Title of the window.</param>
        /// <param name="x">Global x position of the upper left corner of the window's region.</param>
        /// <param name="y">Global y position of the upper left corner of the window's region.</param>
        /// <param name="width">Width of the window's region.</param>
        /// <param name="height">Height of the window's region.</param>
        /// <param name="handlerChain">A HandlerChain object that will be used for removal of
        /// this window when it is closed.
        /// </param>
        MessageWindow(int windowId, std::string title, int x, int y, int width, int height, HandlerChain* handlerChain)
            : _windowId(windowId)
            , _title(title)
            , _windowBox(WindowRectangle(x, y, width, height))
            , _closeBox(WindowRectangle(_windowBox.Right - CLOSE_WIDTH, _windowBox.Top, CLOSE_WIDTH, CLOSE_HEIGHT))
            , _selected(false)
            , _handlerChain(handlerChain)
        {
            // Construct our lookup table for message handlers.
            _messageHandlers[MessageType::ButtonDown] = &_HandleButtonDownMessage;
            _messageHandlers[MessageType::ButtonUp] = &_HandleButtonUpMessage;
            _messageHandlers[MessageType::Close] = &_HandleCloseMessage;
        }


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // The message handlers.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // To add a new message handler:
        //  - Add a new message type to the MessageTypes enumeration.
        //  - Add a new handler method here for the new message type.
        //  - Update MessageWindow constructor to add a mapping from the
        //    new message type to the new handler method.

        /// <summary>
        /// Helper method to handle the ButtonDown message.
        /// </summary>
        /// <param name="window">The window that is handling the message</param>
        /// <param name="message">A Message object describing the ButtonDown message.</param>
        /// <returns>Always returns false even if the message was handled
        /// (allows other windows to select/deselect themselves).</returns>
        static bool _HandleButtonDownMessage(MessageWindow* window, Message* message);


        /// <summary>
        /// Helper method to handle the ButtonUp message.
        /// </summary>
        /// <param name="window">The window that is handling the message</param>
        /// <param name="message">A Message object describing the ButtonUp message.</param>
        /// <returns>Returns true if the message was handled; otherwise, returns
        /// false indicating the message was not handled.</returns>
        static bool _HandleButtonUpMessage(MessageWindow* window, Message* message);


        /// <summary>
        /// Helper method to handle the Close message.
        /// </summary>
        /// <param name="window">The window that is handling the message</param>
        /// <param name="message">A Message object describing the Close message.</param>
        /// <returns>Returns true if the message was handled; otherwise, returns
        /// false indicating the message was not handled.</returns>
        static bool _HandleCloseMessage(MessageWindow* window, Message* message);


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Implementation of the IMessageHandler interface.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        /// <summary>
        /// Returns the ID of the message handler.
        /// </summary>
        int ID()
        {
            return _windowId;
        }


        /// <summary>
        /// Processes a message.
        /// </summary>
        /// <param name="message">The Message object to process.</param>
        /// <returns>Returns true if the message was handled and no further windows should
        /// be notified; otherwise return false to allow the message to be passed to
        /// subsequent windows.</returns>
        /// <remarks>
        /// The message types are mapped to handlers in the MessageWindow
        /// constructor and stored in the _messageHandlers dictionary.
        /// </remarks>
        bool ProcessMessage(Message* message)
        {
            bool messageProcessed = false;

            std::map<MessageType, MessageHandler>::const_iterator foundIter;
            foundIter = _messageHandlers.find(message->MessageType);
            if (foundIter != std::cend(_messageHandlers))
            {
                MessageHandler handler = foundIter->second;
                messageProcessed = handler (this, message);
            }

            return messageProcessed;
        }


        /// <summary>
        /// Convert this handler to a string.
        /// </summary>
        /// <returns>Returns a string representation of the message handler.</returns>
        std::string ToString()
        {
            return Helpers::formatstring("[id=%2d] \"%s\" (%s), selected=%s", ID(),
                _title.c_str(), _windowBox.ToString().c_str(),
                _selected ? "true" : "false");
        }
    };

} // end namespace

#endif //__HANDLECHAIN_MESSAGEWINDOW_CLASS_H__
