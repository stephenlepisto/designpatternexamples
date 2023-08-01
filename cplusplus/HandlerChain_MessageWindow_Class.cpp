/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::MessageWindow "MessageWindow" class
/// used in the @ref handlerchain_pattern

#include "helpers/formatstring.h"

#include "HandlerChain_MessageWindow_Class.h"

namespace DesignPatternExamples_cpp
{
    int MessageWindow::_nextWindowId = 1;


    MessageWindow::shared_ptr_t MessageWindow::CreateWindow(std::string title,
        int x, int y, int width, int height, HandlerChain* handlerChain)
    {
        MessageWindow::shared_ptr_t window;
        window = std::make_shared<MessageWindow>(_nextWindowId, title, x, y,
            width, height, handlerChain);
        ++_nextWindowId;

        if (handlerChain != nullptr)
        {
            handlerChain->AddHandler(window);
        }
        return window;
    }


    bool MessageWindow::_HandleButtonDownMessage(MessageWindow* window, Message* message)
    {
        // Note: we are not saying we handled the message here since
        // we want other windows to get the button down message as
        // well so they can select or deselect themselves.
        bool messageProcessed = false;

        if (window->_PointInWindow(message->Position))
        {
            if (!window->_selected)
            {
                window->_selected = true;
                std::cout
                    << Helpers::formatstring("  --> Button Down in \"%s\", window selected", window->_title.c_str())
                    << std::endl;
            }
        }
        else
        {
            if (window->_selected)
            {
                window->_selected = false;
                std::cout
                    << Helpers::formatstring("  --> Button Down not in \"%s\", window deselected", window->_title.c_str())
                    << std::endl;
            }
        }
        return messageProcessed;
    }


    bool MessageWindow::_HandleButtonUpMessage(MessageWindow* window, Message* message)
    {
        bool messageProcessed = false;
        if (window->_selected)
        {
            if (window->_PointInWindow(message->Position))
            {
                // The Button Up is in the same window as Button Down so
                // we will handle this message and let no other window see
                // it.
                messageProcessed = true;
                if (window->_PointInCloseBox(message->Position))
                {
                    std::cout
                        << Helpers::formatstring("  --> Button Up in \"%s\" close box, sending Close message", window->_title.c_str())
                        << std::endl;
                    window->_handlerChain->SendMessage(std::make_unique<Message>(MessageType::Close, message->Position).get());
                }
                else
                {
                    std::cout
                        << Helpers::formatstring("  --> Button Up in \"%s\", no further action taken", window->_title.c_str())
                        << std::endl;
                }
            }
        }
        return messageProcessed;
    }


    bool MessageWindow::_HandleCloseMessage(MessageWindow* window, Message* /*message*/)
    {
        bool messageProcessed = false;
        if (window->_selected)
        {
            std::cout
                << Helpers::formatstring("  --> Close in \"%s\", removing window from handler chain", window->_title.c_str())
                << std::endl;

            // This window is being closed.  We are handling the message
            // so no other window needs to see it.
            messageProcessed = true;
            window->_handlerChain->RemoveHandler(window);
            window->_selected = false;
        }
        else
        {
            std::cout
                << Helpers::formatstring("  --> Close seen in \"%s\" but this window is not selected, ignoring", window->_title.c_str())
                << std::endl;
        }
        return messageProcessed;
    }

} // end namespace
