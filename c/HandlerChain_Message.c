/// @file
/// @brief
/// Implementation of the Message and MessagePosition structures, along with
/// the functions, MessagePosition_ToString(), Message_Initialize(), and
/// Message_ToString(), as used in the @ref handlerchain_pattern.

#include <stdlib.h>
#include <stdio.h>
#include "HandlerChain_Message.h"

///////////////////////////////////////////////////////////////////////////////
// MessagePosition_ToString()
///////////////////////////////////////////////////////////////////////////////
void MessagePosition_ToString(MessagePosition* position, DynamicString* output)
{
    if (position != NULL && output != NULL)
    {
        char buffer[64] = { 0 };
        int num_chars = sprintf_s(buffer, sizeof(buffer), "x=%2d,y=%2d", position->X, position->Y);
        if (num_chars != -1)
        {
            DynamicString_Append(output, buffer);
        }
    }
}


//=============================================================================
//=============================================================================
//=============================================================================


///////////////////////////////////////////////////////////////////////////////
// Message_Initialize()
///////////////////////////////////////////////////////////////////////////////
void Message_Initialize(Message* message, MessageType type, int x, int y)
{
    if (message != NULL)
    {
        message->MessageType = type;
        message->Position.X = x;
        message->Position.Y = y;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Message_ToString()
///////////////////////////////////////////////////////////////////////////////
void Message_ToString(Message* message, DynamicString* output)
{
    if (message != NULL && output != NULL)
    {
        char buffer[64] = { 0 };
        const char* messageTypeAsString = NULL;
        switch (message->MessageType)
        {
            case Close:
                messageTypeAsString = "Close";
                break;

            case ButtonDown:
                messageTypeAsString = "ButtonDown";
                break;

            case ButtonUp:
                messageTypeAsString = "ButtonUp";
                break;

            default:
                messageTypeAsString = "Unknown message type";
                break;
        }
        DynamicString positionOutput = { 0 };
        DynamicString_Initialize(&positionOutput);
        MessagePosition_ToString(&message->Position, &positionOutput);

        int num_chars = sprintf_s(buffer, sizeof(buffer), "%s at (%s)", messageTypeAsString, positionOutput.string);
        if (num_chars != -1)
        {
            DynamicString_Append(output, buffer);
        }
        DynamicString_Clear(&positionOutput);
    }
}
