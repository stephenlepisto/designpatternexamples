/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.IMessageHandler "IMessageHandler"
/// interface and the @ref DesignPatternExamples_csharp.HandlerChain "HandlerChain"
/// class used in the @ref handlerchain_pattern "HandlerChain pattern".

using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a handler in a chain of handlers.  All objects that
    /// participate in the HandlerChain class must implement this
    /// interface.
    /// </summary>
    public interface IMessageHandler
    {
        /// <summary>
        /// ID of the window.  This is used to uniquely identify a
        /// window in the collection.
        /// </summary>
        int ID { get; }

        /// <summary>
        /// Called with a message on each window.
        /// </summary>
        /// <param name="message">Message object representing the message to process.</param>
        /// <returns>Returns true if the message was processed and the message should not
        /// be passed to subsequent windows.  Returns false to indicate the message should
        /// be passed to subsequent windows.</returns>
        bool ProcessMessage(Message message);

        /// <summary>
        /// Convert the handler to a string.
        /// </summary>
        /// <returns>Returns a representation of the handler.</returns>
        string ToString();
    }



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a list of handlers that all implement the IMessageHandler
    /// interface.  This list can be dynamically updated and each element in
    /// the list is passed messages for processing.
    /// </summary>
    public class HandlerChain
    {
        /// <summary>
        /// The list of message handlers.
        /// </summary>
        List<IMessageHandler> _messageHandlers = new List<IMessageHandler>();

        /// <summary>
        /// Object used to lock access to the message handlers list for
        /// multi-threaded support.
        /// </summary>
        object _messageHandlersLock = new object();


        /// <summary>
        /// Send a message to each of the handlers in the list.
        /// </summary>
        /// <param name="message">The Message object to send to each handler.</param>
        public void SendMessage(Message message)
        {
            // We make a copy of the handlers so our processing of handlers
            // is not impacted by updates to the master handler list.
            IMessageHandler[] copyof_MessageHandlers;
            lock (_messageHandlersLock)
            {
                copyof_MessageHandlers = new IMessageHandler[_messageHandlers.Count];
                _messageHandlers.CopyTo(copyof_MessageHandlers);
            }

            foreach (IMessageHandler window in copyof_MessageHandlers)
            {
                if (window.ProcessMessage(message))
                {
                    break;
                }
            }
        }


        /// <summary>
        /// Add an instance of the IMessageHandler interface to end of the
        /// list of handlers.  If a message handler is already in the list, it
        /// is not added again.
        /// </summary>
        /// <param name="window">The IMessageHandler object to add.</param>
        public void AddHandler(IMessageHandler window)
        {
            lock (_messageHandlersLock)
            {
                // Add the handler if not already in the list.
                if (_messageHandlers.FindIndex(w => w.ID == window.ID) == -1)
                {
                    _messageHandlers.Add(window);
                }
            }
        }


        /// <summary>
        /// Remove an instance of the IMessageHandler interface from the list.
        /// If the message handler is not in the list, the request to remove
        /// is ignored.
        /// </summary>
        /// <param name="window"></param>
        public void RemoveHandler(IMessageHandler window)
        {
            lock(_messageHandlersLock)
            {
                int foundIndex = _messageHandlers.FindIndex(w => w.ID == window.ID);
                if (foundIndex != -1)
                {
                    _messageHandlers.RemoveAt(foundIndex);
                }
            }
        }


        /// <summary>
        /// Convert this HandlerChain to a string.
        /// </summary>
        /// <returns>Returns a string representation of this HandlerChain and all
        /// the handlers it contains.</returns>
        public override string ToString()
        {
            StringBuilder output = new StringBuilder();

            IMessageHandler[] copyof_MessageHandlers;
            lock (_messageHandlersLock)
            {
                copyof_MessageHandlers = new IMessageHandler[_messageHandlers.Count];
                _messageHandlers.CopyTo(copyof_MessageHandlers);
            }

            foreach (IMessageHandler window in copyof_MessageHandlers)
            {
                output.AppendFormat("    {0}{1}", window.ToString(), Environment.NewLine);
            }
            return output.ToString();
        }
    }
}
