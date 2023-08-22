/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.MessageWindow "MessageWindow"
/// and @ref DesignPatternExamples_csharp.WindowRectangle "WindowRectangle"
/// classes used in the @ref handlerchain_pattern "HandlerChain pattern".

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a rectangular region, with upper left and lower right
    /// coordinates.
    /// 
    /// For this example, the minimum width of a rectangle is 4 x 4.
    /// </summary>
    public class WindowRectangle
    {
        const int MINIMUM_WIDTH = 4;
        const int MINIMUM_HEIGHT = 4;

        public int Left;
        public int Top;
        public int Right;
        public int Bottom;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="x">X coordinate of upper left corner.</param>
        /// <param name="y">Y coordinate of upper left corner.</param>
        /// <param name="width">Width of rectangle.</param>
        /// <param name="height">Height of rectangle.</param>
        public WindowRectangle(int x, int y, int width, int height)
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
        public bool PointInside(MessagePosition point)
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
        public override string ToString()
        {
            return String.Format("x1={0,2}, y1={1,2}, x2={2,2}, y2={3,2}", Left, Top, Right, Bottom);
        }
    }



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
    public class MessageWindow : IMessageHandler
    {
        // Size of QUIT region in the upper right corner of the region.
        const int CLOSE_WIDTH = 2;
        const int CLOSE_HEIGHT = 2;

        delegate bool MessageHandler(Message message);

        /// <summary>
        /// Maps a message type to a handler method of type MessageHandler.
        /// </summary>
        private Dictionary<MessageType, MessageHandler> _messageHandlers = new Dictionary<MessageType, MessageHandler>();

        /// <summary>
        /// Unique ID of this window.
        /// </summary>
        private int _windowId;

        /// <summary>
        /// Title/Name of this window.
        /// </summary>
        private string _title;
        
        /// <summary>
        /// Position of this window in global coordinates.
        /// </summary>
        private WindowRectangle _windowBox;

        /// <summary>
        /// Position of the close window within the window box, although the
        /// coordinates are also global coordinates to eliminate the need to
        /// convert between window and global coordinates.
        /// </summary>
        private WindowRectangle _closeBox;

        /// <summary>
        /// Whether this window has been selected (a button click occurred
        /// within the window).
        /// </summary>
        private bool _selected;

        /// <summary>
        /// The HandlerChain to which this window belongs (as an IMessageHandler object).
        /// </summary>
        private HandlerChain _handlerChain;


        /// <summary>
        /// Used for assigning a unique ID to each created window.
        /// </summary>
        static int _nextWindowId = 1;

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
        public static MessageWindow CreateWindow(string title, int x, int y, int width, int height, HandlerChain handlerChain)
        {
            MessageWindow window = new MessageWindow(_nextWindowId, title, x, y, width, height, handlerChain);
            ++_nextWindowId;

            handlerChain.AddHandler(window);
            return window;
        }


        /// <summary>
        /// Determine if the specified point is in this MessageWindow's region.
        /// </summary>
        /// <param name="position">The global coordinate to examine.</param>
        /// <returns>Returns true if the point is contained within the MessageWindow's region.</returns>
        private bool _PointInWindow(MessagePosition position)
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
        private bool _PointInCloseBox(MessagePosition position)
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
        private MessageWindow(int windowId, string title, int x, int y, int width, int height, HandlerChain handlerChain)
        {
            _windowId = windowId;
            _title = title;
            _windowBox = new WindowRectangle(x, y, width, height); // Guaranteed to be at least 4x4
            _closeBox = new WindowRectangle(_windowBox.Right - CLOSE_WIDTH, _windowBox.Top, CLOSE_WIDTH, CLOSE_HEIGHT);
            _selected = false;
            _handlerChain = handlerChain;

            // Construct our lookup table for message handlers.
            _messageHandlers[MessageType.ButtonDown] = _HandleButtonDownMessage;
            _messageHandlers[MessageType.ButtonUp] = _HandleButtonUpMessage;
            _messageHandlers[MessageType.Close] = _HandleCloseMessage;
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
        /// <param name="message">A Message object describing the ButtonDown message.</param>
        /// <returns>Always returns false even if the message was handled
        /// (allows other windows to select/deselect themselves).</returns>
        private bool _HandleButtonDownMessage(Message message)
        {
            // Note: we are not saying we handled the message here since
            // we want other windows to get the button down message as
            // well so they can select or deselect themselves.
            bool messageProcessed = false;

            if (_PointInWindow(message.Position))
            {
                if (!_selected)
                {
                    _selected = true;
                    Console.WriteLine("  --> Button Down in \"{0}\", window selected", _title);
                }
            }
            else
            {
                if (_selected)
                {
                    _selected = false;
                    Console.WriteLine("  --> Button Down not in \"{0}\", window deselected", _title);
                }
            }
            return messageProcessed;
        }


        /// <summary>
        /// Helper method to handle the ButtonUp message.
        /// </summary>
        /// <param name="message">A Message object describing the ButtonUp message.</param>
        /// <returns>Returns true if the message was handled; otherwise, returns
        /// false indicating the message was not handled.</returns>
        private bool _HandleButtonUpMessage(Message message)
        {
            bool messageProcessed = false;
            if (_selected)
            {
                if (_PointInWindow(message.Position))
                {
                    // The Button Up is in the same window as Button Down so
                    // we will handle this message and let no other window see
                    // it.
                    messageProcessed = true;
                    if (_PointInCloseBox(message.Position))
                    {
                        Console.WriteLine("  --> Button Up in \"{0}\" close box, sending Close message", _title);
                        _handlerChain.SendMessage(new Message(MessageType.Close, message.Position));
                    }
                    else
                    {
                        Console.WriteLine("  --> Button Up in \"{0}\", no further action taken", _title);
                    }
                }
            }
            return messageProcessed;
        }


        /// <summary>
        /// Helper method to handle the Close message.
        /// </summary>
        /// <param name="message">A Message object describing the Close message.</param>
        /// <returns>Returns true if the message was handled; otherwise, returns
        /// false indicating the message was not handled.</returns>
        private bool _HandleCloseMessage(Message message)
        {
            bool messageProcessed = false;
            if (_selected)
            {
                Console.WriteLine("  --> Close in \"{0}\", removing window from handler chain", _title);
                // This window is being closed.  We are handling the message
                // so no other window needs to see it.
                messageProcessed = true;
                _handlerChain.RemoveHandler(this);
                _selected = false;
            }
            else
            {
                Console.WriteLine("  --> Close seen in \"{0}\" but this window is not selected, ignoring", _title);
            }
            return messageProcessed;
        }


        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Implementation of the IMessageHandler interface.
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        /// <summary>
        /// Returns the ID of the message handler.
        /// </summary>
        public int ID
        {
            get
            {
                return _windowId;
            }
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
        public bool ProcessMessage(Message message)
        {
            bool messageProcessed = false;
            MessageHandler? handler;

            if (_messageHandlers.TryGetValue(message.MessageType, out handler))
            {
                messageProcessed = handler(message);
            }

            return messageProcessed;
        }


        /// <summary>
        /// Convert this handler to a string.
        /// </summary>
        /// <returns>Returns a string representation of the message handler.</returns>
        public override string ToString()
        {
            return String.Format("[id={0,2}] \"{1}\" ({2}), selected={3}", ID, _title, _windowBox, _selected);
        }
    }

}
