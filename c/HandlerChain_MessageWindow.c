/// @file
/// @brief
/// Declaration of the @ref MessageWindow structure, along with the
/// implementation of the support functions, MessageWindow_Create(),
/// MessageWindow_Destroy(), MessageWindow_ProcessMessage(), and
/// MessageWindow_ToString(),
/// as used in the @ref handlerchain_pattern.


#include <stdlib.h>
#include <stdio.h>

#include "helpers/formatstring.h"

#include "HandlerChain_WindowRectangle.h"
#include "HandlerChain_HandlerFunctions.h"
#include "HandlerChain_MessageWindow.h"


const int CLOSE_WIDTH = 2; ///< Width of the close region in the window.
const int CLOSE_HEIGHT = 2; ///< Height of the close region in the window.

/// <summary>
/// Represents a window in an arbitrary space. It has an ID, title, and
/// position.  A close box is within the window's rectangle.  The window can be
///  selected by sending a button down message with the position within this
/// window.  If a button down message occurs outside this window, it is
/// deselected.
/// </summary>
struct _Window
{
    // Note: We must specify struct _Window so we can add pointer references for
    // next and prev in the structure.  These cannot be specified with the
    // typedef alias of MessageWindow.

    /// <summary>
    /// Previous window in a linked list.  NULL if this window is the head of the list.
    /// </summary>
    struct _Window* prev;

    /// <summary>
    /// Next window in a linked list.  NULL if this windows is the last in the list.
    /// </summary>
    struct _Window* next;

    /// <summary>
    /// Unique ID of this window.
    /// </summary>
    int _windowId;

    /// <summary>
    /// Title/Name of this window.
    /// </summary>
    const char* _title;

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
};

/// <summary>
/// Alias for struct _Window, which represents a window in an arbitrary space.
/// It has an ID, title, and position.  A close box is within the window's
/// rectangle.  The window can be selected by sending a button down message
/// with the position within this window.  If a button down message occurs
/// outside this window, it is deselected.
/// </summary>
typedef struct _Window MessageWindow;


/// <summary>
/// List of all created @ref MessageWindow objects, in a double-linked list.
/// </summary>
static MessageWindow* _windowList = NULL;

/// <summary>
/// The next ID to use for a new window.
/// </summary>
static int _nextWindowId = 1;

/// <summary>
/// Helper function to append the given @ref MessageWindow to the list of
/// @ref MessageWindow objects.
/// </summary>
/// <param name="window">A @ref MessageWindow object to append to the list.</param>
static void _AppendWindowToList(MessageWindow* window)
{
    if (_windowList == NULL)
    {
        _windowList = window;
    }
    else
    {
        MessageWindow* nextWindow = _windowList;
        while (nextWindow->next != NULL)
        {
            nextWindow = nextWindow->next;
        }
        nextWindow->next = window;
        window->prev = nextWindow;
    }
}

/// <summary>
/// Helper function to remove the given @ref MessageWindow object from the
/// linked list of @ref MessageWindow objects.
/// </summary>
/// <param name="window">The @ref MessageWindow object to remove from the list.</param>
static void _RemoveWindowFromList(MessageWindow* window)
{
    if (window != NULL)
    {
        if (window->prev != NULL)
        {
            window->prev->next = window->next;

        }
        else
        {
            _windowList = window->next;
        }

        if (window->next != NULL)
        {
            window->next->prev = window->prev;
        }

        window->next = NULL;
        window->prev = NULL;
    }
}

/// <summary>
/// Helper function to find a @ref MessageWindow given the window's ID.
/// </summary>
/// <param name="windowId">The ID of the window to find.</param>
/// <returns>Returns a pointer to the @ref MessageWindow that matches the ID;
/// otherwise, returns NULL to indicate no window exists by that ID.</returns>
static MessageWindow* _FindWindow(int windowId)
{
    MessageWindow* foundWindow = NULL;

    if (_windowList != NULL)
    {
        MessageWindow* window = _windowList;
        while (window != NULL)
        {
            if (window->_windowId == windowId)
            {
                foundWindow = window;
                break;
            }
            window = window->next;
        }
    }
    return foundWindow;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/// <summary>
/// Helper function to handle the ButtonDown message.
/// </summary>
/// <param name="window">The @ref MessageWindow that is handling the message</param>
/// <param name="message">A Message object describing the ButtonDown message.</param>
/// <returns>Always returns false even if the message was handled
/// (allows other windows to select/deselect themselves).</returns>
static bool _HandleButtonDownMessage(MessageWindow* window, Message* message)
{
    // Note: we are not saying we handled the message here since
    // we want other windows to get the button down message as
    // well so they can select or deselect themselves.
    bool messageProcessed = false;

    if (window != NULL && message != NULL)
    {
        if (WindowRectangle_PointInside(&window->_windowBox, &message->Position))
        {
            if (!window->_selected)
            {
                window->_selected = true;
                printf("  --> Button Down in \"%s\", window selected\n", window->_title);
            }
        }
        else
        {
            if (window->_selected)
            {
                window->_selected = false;
                printf("  --> Button Down not in \"%s\", window deselected\n", window->_title);
            }
        }
    }

    return messageProcessed;
}


/// <summary>
/// Helper function to handle the ButtonUp message.
/// </summary>
/// <param name="window">The @ref MessageWindow that is handling the message</param>
/// <param name="message">A Message object describing the ButtonUp message.</param>
/// <returns>Returns true if the message was handled; otherwise, returns
/// false indicating the message was not handled.</returns>
static bool _HandleButtonUpMessage(MessageWindow* window, Message* message)
{
    bool messageProcessed = false;

    if (window != NULL && message != NULL)
    {
        if (window->_selected)
        {
            if (WindowRectangle_PointInside(&window->_windowBox, &message->Position))
            {
                // The Button Up is in the same window as Button Down so
                // we will handle this message and let no other window see
                // it.
                messageProcessed = true;
                if (WindowRectangle_PointInside(&window->_closeBox, &message->Position))
                {
                    printf("  --> Button Up in \"%s\" close box, sending Close message\n", window->_title);
                    Message closeMessage;
                    Message_Initialize(&closeMessage, Close, message->Position.X, message->Position.Y);
                    HandlerChain_SendMessage(window->_windowId, &closeMessage);
                }
                else
                {
                    printf("  --> Button Up in \"%s\", no further action taken\n", window->_title);
                }
            }
        }
    }

    return messageProcessed;
}


/// <summary>
/// Helper function to handle the Close message.
/// </summary>
/// <param name="window">The @ref MessageWindow that is handling the message</param>
/// <param name="message">A Message object describing the Close message.</param>
/// <returns>Returns true if the message was handled; otherwise, returns
/// false indicating the message was not handled.</returns>
static bool _HandleCloseMessage(MessageWindow* window, Message* message)
{
    bool messageProcessed = false;

    if (window != NULL && message != NULL)
    {
        if (window->_selected)
        {
            printf("  --> Close in \"%s\", sending Destroy message\n", window->_title);

            // This window is being closed.  We are handling the message
            // so no other window needs to see it.
            messageProcessed = true;
            Message destroyMessage;
            Message_Initialize(&destroyMessage, Destroy, 0, 0);
            HandlerChain_SendMessage(window->_windowId, &destroyMessage);
        }
        else
        {
            printf("  --> Close seen in \"%s\" but this window is not selected, ignoring\n", window->_title);
        }

    }

    return messageProcessed;
}

/// <summary>
/// Helper function to trigger the destruction of the window.  The window is
/// destroyed and can no longer receive any messages.
///
/// The given @ref MessageWindow is destroyed and can no longer be used after this
/// function returns.
/// </summary>
/// <param name="window">The @ref MessageWindow that is handling the message.</param>
/// <param name="message">The Message object describing the Destroy message.</param>
/// <returns>Returns true if the message was handled; otherwise, returns
/// false indicating the message was not handled.</returns>
static bool _HandleDestroyMessage(MessageWindow* window, Message* message)
{
    bool messageProcessed = false;

    if (window != NULL && message != NULL)
    {
        printf("  --> Destroy in \"%s\", removing window from handler chain and destroying window\n", window->_title);
        HandlerChain_RemoveWindow(window->_windowId);
        window->_selected = false;
        MessageWindow_Destroy(window->_windowId);
        messageProcessed = true;
    }

    return messageProcessed;
}

///////////////////////////////////////////////////////////////////////////////
// MessageWindow_Create()
///////////////////////////////////////////////////////////////////////////////
int MessageWindow_Create(const char* title, int x, int y, int w, int h)
{
    int windowId = -1;

    if (title != NULL)
    {
        MessageWindow* window = calloc(1, sizeof(MessageWindow));
        if (window != NULL)
        {
            windowId = _nextWindowId++;
            window->_windowId = windowId;
            bool success = HandlerChain_AddWindow(window->_windowId);
            if (success)
            {
                window->_title = title;
                WindowRectangle_Initialize(&window->_windowBox, x, y, w, h);
                WindowRectangle_Initialize(&window->_closeBox, window->_windowBox.Right - CLOSE_WIDTH, window->_windowBox.Top, CLOSE_WIDTH, CLOSE_HEIGHT);
                _AppendWindowToList(window);
            }
            else
            {
                printf("  Error!  Out of memory condition adding a window to the handler chain in MessageWindow_Create()!\n");
                free(window);
                window = NULL;
                windowId = -1;
            }
        }
    }

    return windowId;
}


///////////////////////////////////////////////////////////////////////////////
// MessageWindow_Destroy()
///////////////////////////////////////////////////////////////////////////////
void MessageWindow_Destroy(int windowId)
{
    MessageWindow* window = _FindWindow(windowId);
    if (window != NULL)
    {
        _RemoveWindowFromList(window);
        free(window);
    }
}

///////////////////////////////////////////////////////////////////////////////
// MessageWindow_ProcessMessage()
///////////////////////////////////////////////////////////////////////////////
bool MessageWindow_ProcessMessage(int windowId, Message* message)
{
    bool processed = false;

    if (message != NULL)
    {
        MessageWindow* window = _FindWindow(windowId);
        if (window != NULL)
        {
            switch (message->MessageType)
            {
                case Close:
                    processed = _HandleCloseMessage(window, message);
                    break;

                case ButtonDown:
                    processed = _HandleButtonDownMessage(window, message);
                    break;

                case ButtonUp:
                    processed = _HandleButtonUpMessage(window, message);
                    break;

                case Destroy:
                    processed = _HandleDestroyMessage(window, message);
                    break;

                default:
                    printf("Error!  Cannot process unrecognized message type: %d!\n", message->MessageType);
                    processed = true;
                    break;
            }
        }
    }

    return processed;
}


///////////////////////////////////////////////////////////////////////////////
// MessageWindow_ProcessMessage()
///////////////////////////////////////////////////////////////////////////////
bool MessageWindow_ToString(int windowId, DynamicString* output)
{
    bool success = false;

    if (output != NULL)
    {
        MessageWindow* window = _FindWindow(windowId);
        if (window != NULL)
        {
            DynamicString boxOutput = { 0 };
            success = WindowRectangle_ToString(&window->_windowBox, &boxOutput);
            if (success)
            {
                char* buffer = formatstring("[id=%2d] \"%s\" (%s), selected=%s",
                    window->_windowId, window->_title, boxOutput.string,
                    (window->_selected) ? "true" : "false");
                if (buffer != NULL)
                {
                    success = DynamicString_Append(output, buffer);
                    if (!success)
                    {
                        printf("  Error!  Out of memory condition formatting a MessageWindow as a string!\n");
                    }
                    free(buffer);
                }
                else
                {
                    printf("  Error!  Out of memory formatting message window in MessageWindow_ToString()!\n");
                }
            }
            DynamicString_Clear(&boxOutput);
        }
    }

    return success;
}
