
/// @file
/// @brief
/// Implementation of the HandlerChain_Exercise() function as used in the 
/// @ref handlerchain_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HandlerChain_MessageWindow.h"
#include "HandlerChain_HandlerFunctions.h"
#include "HandlerChain_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to construct a list of windows.  Messages will be passed 
/// to these windows via the HandlerChain_SendMessage() function.
/// </summary>
/// <param name="windowIds">Array of ints that will be filled in with the
/// IDs of each window that is created so they can later be destroyed.  Only
/// 3 windows are created, hence the fixed size of the array.</param>
static void _HandlerChain_ConstructWindowChain(int windowIds[3])
{
    windowIds[0] = MessageWindow_Create("Window 1", 0, 0, 10, 10);
    windowIds[1] = MessageWindow_Create("Window 2", 20, 0, 5, 5);
    windowIds[2] = MessageWindow_Create("Window 3", 30, 10, 15, 15);
}


/// <summary>
/// Helper function to destroy all windows that have been created.
/// </summary>
/// <param name="windowIds">List of window IDs to destroy.</param>
static void _HandleChain_DestroyWindows(int windowIds[3])
{
    size_t numIds = 3;
    Message destroyMessage;
    Message_Initialize(&destroyMessage, Destroy, 0, 0);
    for (size_t index = 0; index < numIds; index++)
    {
        HandlerChain_SendMessage(windowIds[index], &destroyMessage);
    }
}

/// <summary>
/// Helper function to display the current handler chain.
/// </summary>
/// <param name="prompt">A prompt to display before the handler chain.</param>
static void _ShowHandlerChain(const char* prompt)
{
    if (prompt == NULL)
    {
        prompt = "<NO PROMPT>";
    }
    printf("  %s\n", prompt);
    DynamicString output = { 0 };
    HandlerChain_ToString(&output);
    printf("%s\n", output.string);
    DynamicString_Clear(&output);
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref handlerchain_pattern or
/// Chain of Responsibility design pattern.
/// 
/// The Handler Chain pattern is used to support a dynamic list of
/// handlers that are passed the same arguments.  It is kind of the
/// inverse of the Visitor pattern, where the Visitor pattern is a
/// handler that is passed to all objects in a list and the Handler
/// Chain pattern is an object passed to handlers in a list.
///
/// In this exercise, multiple rectangular regions represented by the
/// @ref MessageWindow structure are represented by window IDs.  The IDs are
/// kept in a list to which messages can be passed, using the
/// HandlerChain_SendMessage() function.  That function iterates through the
/// list of window IDs and calls MessageWindow_ProcessMessage() for each ID
/// with the desired message.  MessageWindow_ProcessMessage() passes control to
/// one of several handler functions based on the type of the message.
/// </summary>
// ! [Using HandlerChain in C]
void HandlerChain_Exercise()
{
    printf("\nHandlerChain Exercise\n");

    // Construct several windows that can handle messages.  These are
    // automatically handled to the handler chain list during construction.
    int windowIds[3] = { 0 };
    _HandlerChain_ConstructWindowChain(windowIds);

    _ShowHandlerChain("Handler Chain at start:");

    // Now pass messages to the windows.

    printf("  Select Window 2\n");
    Message buttonDownMessage;
    Message_Initialize(&buttonDownMessage, ButtonDown, 22, 1);
    HandlerChain_SendMessage(-1, &buttonDownMessage);

    Message buttonUpMessage;
    Message_Initialize(&buttonUpMessage, ButtonUp, 22, 1);
    HandlerChain_SendMessage(-1, &buttonUpMessage);
    _ShowHandlerChain("Current handler chain:");

    printf("  Select Window 3\n");
    Message_Initialize(&buttonDownMessage, ButtonDown, 35, 11);
    HandlerChain_SendMessage(-1, &buttonDownMessage);

    Message_Initialize(&buttonUpMessage, ButtonUp, 35, 11);
    HandlerChain_SendMessage(-1, &buttonUpMessage);
    _ShowHandlerChain("Current handler chain:");

    printf("  Select Window 1\n");
    Message_Initialize(&buttonDownMessage, ButtonDown, 4, 4);
    HandlerChain_SendMessage(-1, &buttonDownMessage);

    Message_Initialize(&buttonUpMessage, ButtonUp, 4, 4);
    HandlerChain_SendMessage(-1, &buttonUpMessage);
    _ShowHandlerChain("Current handler chain:");

    printf("  Close Window 2\n");
    Message_Initialize(&buttonDownMessage, ButtonDown, 24, 0);
    HandlerChain_SendMessage(-1, &buttonDownMessage);

    Message_Initialize(&buttonUpMessage, ButtonUp, 24, 0);
    HandlerChain_SendMessage(-1, &buttonUpMessage);
    _ShowHandlerChain("Current handler chain:");

    printf("  Removing all windows as part of clean-up.\n");
    _HandleChain_DestroyWindows(windowIds);

    printf("  Done.\n");
}
// ! [Using HandlerChain in C]

