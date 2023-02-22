// See HandlerChain_Class.cs for details of how the classes in this file are
// used.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Type of message handled by MessageWindow.
    /// </summary>
    public enum MessageType
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
    }



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Position of the message in global coordinates (same scope of
    /// coordinates as windows).  Although this can handle negative
    /// coordinates, the example is careful to use only positive coordinates.
    /// </summary>
    public struct MessagePosition
    {
        /// <summary>
        /// X position.
        /// </summary>
        public int X;

        /// <summary>
        /// Y position.
        /// </summary>
        public int Y;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="x">X position to use.</param>
        /// <param name="y">Y position to use.</param>
        public MessagePosition(int x, int y)
        {
            X = x;
            Y = y;
        }

        /// <summary>
        /// Convert this position to a string.
        /// </summary>
        /// <returns>A string containing a string representation of the position.</returns>
        public override string ToString()
        {
            return String.Format("x={0,2},y={1,2}", X, Y);
        }
    }



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a message sent to the windows.  A message contains a type
    /// and a position.
    /// </summary>
    public struct Message
    {
        /// <summary>
        /// Value from the MessageType enumeration indicating the type of this message.
        /// </summary>
        public MessageType MessageType;

        /// <summary>
        /// Position of message when the message was sent.  In a real system, this
        /// would generally represent the position of a cursor at the time the message
        /// was generated.
        /// </summary>
        public MessagePosition Position;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="type">Value from the MessageType enumeration indicating the
        /// type of message being created.</param>
        /// <param name="position">Position of the message, expressed as a MessagePosition
        /// object.</param>
        public Message(MessageType type, MessagePosition position)
        {
            MessageType = type;
            Position = position;
        }

        /// <summary>
        /// Convert this message to a string.
        /// </summary>
        /// <returns>Returns a string representation of this message.</returns>
        public override string ToString()
        {
            return String.Format("{0} at ({1})", MessageType, Position);
        }
    }
}
