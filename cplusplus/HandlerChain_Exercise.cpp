
/// @file
/// @brief
/// Implementation of the HandlerChain_Exercise() function as used in the 
/// @ref handlerchain_pattern "HandlerChain pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "HandlerChain_Exercise.h"
#include "HandlerChain_Class.h"
#include "HandlerChain_Message_Class.h"
#include "HandlerChain_MessageWindow_Class.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// Helper method to construct a list of windows.  Messages will be passed 
    /// to these windows via the HandlerChain object.
    /// </summary>
    /// <param name="handlerChain">The HandlerChain object that receives the
    /// new windows.</param>
    void _HandlerChain_ConstructWindowChain(HandlerChain* handlerChain)
    {
        // Note: This creates each window and adds the new window to the given
        // HandlerChain object.
        //
        // This example doesn't care about each individual window so the
        // return value is ignored.
        MessageWindow::CreateWindow("Window 1", 0, 0, 10, 10, handlerChain);
        MessageWindow::CreateWindow("Window 2", 20, 0, 5, 5, handlerChain);
        MessageWindow::CreateWindow("Window 3", 30, 10, 15, 15, handlerChain);
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref handlerchain_pattern "Handle Chain" or
    /// Chain of Responsibility design pattern.
    /// 
    /// The Handler Chain pattern is used to support a dynamic list of
    /// handlers that are passed the same arguments.  It is kind of the
    /// inverse of the Visitor pattern, where the Visitor pattern is a
    /// handler that is passed to all objects in a list and the Handler
    /// Chain pattern is an object passed to handlers in a list.
    ///
    /// In this exercise, multiple rectangular regions called
    /// MessageWindows embody the handlers and the HandlerChain object
    /// passes message objects to each MessageWindow until the message is
    /// handled.
    /// </summary>
    //! [Using HandlerChain in C++]
    void HandlerChain_Exercise()
    {
        std::cout << std::endl;
        std::cout << "HandlerChain Exercise" << std::endl;

        // Construct a handler chain and populate with windows that can
        // handle messages.
        HandlerChain::unique_ptr_t handlerChain = std::make_unique<HandlerChain>();
        _HandlerChain_ConstructWindowChain(handlerChain.get());

        std::cout << "  Handler Chain at start:" << std::endl;
        std::cout << handlerChain->ToString() << std::endl;

        // Now pass messages to the windows.

        std::cout << "  Select Window 2" << std::endl;
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonDown, MessagePosition(22, 1)).get());
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonUp, MessagePosition(22, 1)).get());
        std::cout << "  Current handler chain:" << std::endl;
        std::cout << handlerChain->ToString() << std::endl;

        std::cout << "  Select Window 3" << std::endl;
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonDown, MessagePosition(35, 11)).get());
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonUp, MessagePosition(35, 11)).get());
        std::cout << "  Current handler chain:" << std::endl;
        std::cout << handlerChain->ToString() << std::endl;

        std::cout << "  Select Window 1" << std::endl;
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonDown, MessagePosition(4, 4)).get());
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonUp, MessagePosition(4, 4)).get());
        std::cout << "  Current handler chain:" << std::endl;
        std::cout << handlerChain->ToString() << std::endl;

        std::cout << "  Close Window 2" << std::endl;
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonDown, MessagePosition(24, 0)).get());
        handlerChain->SendMessage(std::make_unique<Message>(MessageType::ButtonUp, MessagePosition(24, 0)).get());
        std::cout << "  Current handler chain:" << std::endl;
        std::cout << handlerChain->ToString() << std::endl;

        std::cout << "  Done." << std::endl;
    }
    //! [Using HandlerChain in C++]

} // end namespace
