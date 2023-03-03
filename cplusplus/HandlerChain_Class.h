/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::HandlerChain "HandlerChain" class
/// and declaration of the @ref DesignPatternExamples_cpp::IMessageHandler "IMessageHandler" interface.

#pragma once
#ifndef __HANDLERCHAIN_CLASS_H__
#define __HANDLERCHAIN_CLASS_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <algorithm>
#include <list>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>

namespace DesignPatternExamples_cpp
{
    struct Message; // forward declaration

    /// <summary>
    /// Represents a handler in a chain of handlers.  All objects that
    /// participate in the HandlerChain class must implement this
    /// interface.
    /// </summary>
    struct IMessageHandler
    {
        /// <summary>
        /// Alias to make it easier when using a shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<IMessageHandler>;

        /// <summary>
        /// Virtual destructor (required for interfaces in C++)
        /// </summary>
        virtual ~IMessageHandler() { }

        /// <summary>
        /// ID of the window.  This is used to uniquely identify a
        /// window in the collection.
        /// </summary>
        virtual int ID() = 0;

        /// <summary>
        /// Called with a message on each window.
        /// </summary>
        /// <param name="message">Message object representing the message to
        /// process.</param>
        /// <returns>Returns true if the message was processed and the message
        /// should not be passed to subsequent windows.  Returns false to
        /// indicate the message should be passed to subsequent windows.</returns>
        virtual bool ProcessMessage(Message* message) = 0;

        /// <summary>
        /// Convert the handler to a string.
        /// </summary>
        /// <returns>Returns a representation of the handler.</returns>
        virtual std::string ToString() = 0;
    };



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a list of handlers that all implement the IMessageHandler
    /// interface.  This list can be dynamically updated and each element in
    /// the list is passed messages for processing.
    /// </summary>
    class HandlerChain
    {
    public:
        using unique_ptr_t = std::unique_ptr<HandlerChain>;

        /// <summary>
        /// The list of message handlers.
        /// </summary>
        std::list<IMessageHandler::shared_ptr_t> _messageHandlers;

        /// <summary>
        /// Object used to lock access to the message handlers list for
        /// multi-threaded support.
        /// </summary>
        std::mutex _messageHandlersLock;

    public:
        /// <summary>
        /// Send a message to each of the handlers in the list.
        /// </summary>
        /// <param name="message">The Message object to send to each handler.</param>
        void SendMessage(Message* message)
        {
            // We make a copy of the handlers so our processing of handlers
            // is not impacted by updates to the master handler list.
            std::list<IMessageHandler::shared_ptr_t> copyof_MessageHandlers(_messageHandlers.size());
            {
                std::lock_guard<std::mutex> guard(_messageHandlersLock);
                std::copy(std::begin(_messageHandlers), std::end(_messageHandlers), std::begin(copyof_MessageHandlers));
            }

            for(IMessageHandler::shared_ptr_t& window : copyof_MessageHandlers)
            {
                if (window->ProcessMessage(message))
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
        void AddHandler(IMessageHandler::shared_ptr_t window)
        {
            std::lock_guard<std::mutex> guard(_messageHandlersLock);
            // Add the handler if not already in the list.
            std::list<IMessageHandler::shared_ptr_t>::iterator foundIter;
            foundIter = std::find_if(std::begin(_messageHandlers),
                std::end(_messageHandlers),
                [window](IMessageHandler::shared_ptr_t w) { return w->ID() == window->ID(); });

            if (foundIter == std::end(_messageHandlers))
            {
                _messageHandlers.push_back(window);
            }
        }


        /// <summary>
        /// Remove an instance of the IMessageHandler interface from the list.
        /// If the message handler is not in the list, the request to remove
        /// is ignored.
        /// </summary>
        /// <param name="window">The window to remove</param>
        void RemoveHandler(IMessageHandler::shared_ptr_t window)
        {
            std::lock_guard<std::mutex> guard(_messageHandlersLock);
            _messageHandlers.remove_if([window](IMessageHandler::shared_ptr_t w) { return w->ID() == window->ID(); });
        }

        /// <summary>
        /// Remove an instance of the IMessageHandler interface from the list.
        /// If the message handler is not in the list, the request to remove
        /// is ignored.
        /// </summary>
        /// <param name="window">The window to remove</param>
        void RemoveHandler(IMessageHandler* window)
        {
            std::lock_guard<std::mutex> guard(_messageHandlersLock);
            _messageHandlers.remove_if([window](IMessageHandler::shared_ptr_t w) { return w->ID() == window->ID(); });
        }


        /// <summary>
        /// Convert this HandlerChain to a string.
        /// </summary>
        /// <returns>Returns a string representation of this HandlerChain and all
        /// the handlers it contains.</returns>
        std::string ToString()
        {
            std::ostringstream output;

            std::list<IMessageHandler::shared_ptr_t> copyof_MessageHandlers(_messageHandlers.size());
            {
                std::lock_guard<std::mutex> guard(_messageHandlersLock);
                std::copy(std::begin(_messageHandlers), std::end(_messageHandlers), std::begin(copyof_MessageHandlers));
            }

            for(IMessageHandler::shared_ptr_t& window : copyof_MessageHandlers)
            {
                output << std::format("    {0}", window->ToString()) << std::endl;
            }
            return output.str();
        }
    };

} // end namespace

#endif // __HANDLERCHAIN_CLASS_H__

