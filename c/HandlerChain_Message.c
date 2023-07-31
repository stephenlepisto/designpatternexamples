/// @file
/// @brief
/// Implementation of the Message and MessagePosition structures, along with
/// the functions, MessagePosition_ToString(), Message_Initialize(), and
/// Message_ToString(), as used in the @ref handlerchain_pattern.

#include <stdlib.h>
#include <stdio.h>

#include "helpers/formatstring.h"

#include "HandlerChain_Message.h"

///////////////////////////////////////////////////////////////////////////////
// MessagePosition_ToString()
///////////////////////////////////////////////////////////////////////////////
bool MessagePosition_ToString(MessagePosition* position, DynamicString* output)
{
    bool success = false;

    if (position != NULL && output != NULL)
    {
        char* buffer = formatstring("x=%2d,y=%2d", position->X, position->Y);
        if (buffer != NULL)
        {
            success = DynamicString_Append(output, buffer);
            if (!success)
            {
                printf("  Error!  out of memory condition appending message position as string in MessagePosition_ToString()!\n");
            }
            free(buffer);
        }
        else
        {
            printf("  Error!  Out of memory formatting position in MessagePosition_ToString()!\n");
        }
    }

    return success;
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
bool Message_ToString(Message* message, DynamicString* output)
{
    bool success = false;

    if (message != NULL && output != NULL)
    {
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

            case Destroy:
                // Handled elsewhere
                break;

            default:
                messageTypeAsString = "Unknown message type";
                break;
        }
        DynamicString positionOutput = { 0 };
        DynamicString_Initialize(&positionOutput);
        success = MessagePosition_ToString(&message->Position, &positionOutput);

        if (success)
        {
                char *buffer = formatstring("%s at (%s)", messageTypeAsString, positionOutput.string);
                if (buffer != NULL)
                {
                    success = DynamicString_Append(output, buffer);
                    if (!success)
                    {
                        printf("  Error!  Out of memory condition in Message_ToString() while appending string to output!\n");
                    }
                    free(buffer);
                }
                else
                {
                    printf("  Error!  out of memory formatting message in Message_ToString()!\n");
                }
        }
        DynamicString_Clear(&positionOutput);
    }

    return success;
}
