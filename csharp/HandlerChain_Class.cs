// The Handler Chain or Chain of Responsibility is a very old pattern.
// A "chain" of handlers are built up.  An object is passed to the head of the
// chain for handling.  The head handler decides whether it can handle the
// object or not.  if so, it handles it and returns.  Otherwise, the handler
// passes the object to the next handler in the chain.  This continues until
// no more handlers remain or a handler processes the object.  The advantage
// of a chain like this is handlers can be inserted into or removed from the
// chain at runtime.
//
// Windows uses this approach for handling messages passed to windows, where
// each window handler either handles the message and/or passes the message
// on to the next window handler in the chain until the default handler is
// eventually called.  By inserting a handler into the chain, it is possible
// to intercept the message and thus making it possible to add new
// functionality to an existing window.
//
// A variation on this is where an additional parameter determines whether a
// handler that handled the object should pass the object to the next handler
// instead of returning.
//
// Another variation is a list of handlers to be called at some point.  For
// example, the atexit() function in the C library takes a functon that is
// added to a list that is then called in reverse order.  Technically, the
// handlers aren't actually chained together except through the containing
// list but the effect is the same; handlers in a dynamic list are called
// until done.
//
// The key to a Handler Chain is the chain of handlers is dynamic and the
// handlers are invoked in order until all handlers have been invoked.  A
// common variation is to allow a handler to stop the processing so no
// additional handlers are called.
//
// Handlers are set up through any number of ways, depending on what the
// handlers do.  For example, with Windows message handlers, the chain is
// updated when a new window is created or destroyed.
//
// The Handler Chain, wherein an object is passed to a number of handlers
// until processed, is also a form of the Observer pattern, where an object
// is passed to a number of handlers.  Unlike the Observer pattern, though,
// a handler in a Handler Chain can abort the sequence of calls to additional
// handlers.
//
// In an "ideal" object-oriented implementation, a Handler Chain is composed
// of handler objects that are linked to the previous handler object and next
// handler object in the chain.  The head of the chain has an empty previous
// link while the last handler object in the chain has an empty next link.
// Each handler object has a Process method that either processes the incoming
// arguments or calls the Process method on the next handler object in the
// chain, if any.
//
// In addition, each handler object knows how to insert itself and remove
// itself from the chain.  This implies each handler object has an Add and
// Remove method, where Add means add to the end of the chain (or insert based
// on some qualifier) and Remove means remove from the chain.
//
// The advantage of this approach is the program only needs to deal with the
// head handler object in the chain, either calling Process on the head object
// or calling Add (or Remove) with a handler object.
//
// Unfortunately, this classic design requires dealing with doubly-linked
// lists, which are a real pain to get right.
//
// A better approach is to designate a different class to handle the chain.
// An instance of this class has Process, Add, and Remove methods on it but
// internally the handler objects are stored in a traditional (and thoroughly-
// tested) container.  The handler of the chain can also take steps to protect
// the list from multi-threaded incursions.  It's still a single object that
// is passed around and it always exists even if there are no handlers.
//
// The example presented here is a collection of "windows" represented by the
// MessageWindow class.  Each window has a common message handler as
// implemented through the IMessageHandler interface.  The windows are stored
// in the HandleChain collection and can interact with that collection.
//
// ButtonDown messages are pushed in by the user of the HandlerChain class,
// selecting and deselecting windows (based on a position associated with the
// ButtonDown message).
//
// A ButtonUp message is pushed in by the user of the HandleChain class.  In a
// window that is selected, the message causes an action to be taken, although
// in this example, only one action is supported and that is the Close action.
// However, the Close action is taken only if the message position is in the
// "Close" region in the upper right corner of the window.
//
// A "Close" action causes the window to send a Close message to the
// collection.  This Close message is processed only by the currently selected
// window and causes the window to remove itself from the collection so it no
// longer receives messages.

using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples
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
