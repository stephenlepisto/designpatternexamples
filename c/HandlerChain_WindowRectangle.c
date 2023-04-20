/// @file
/// @brief
/// Implementation of the WindowRectangle support functions,
/// WindowRectangle_Initialize(), WindowRectangle_PointInside(), and
/// WindowRectangle_ToString(),
/// as used in the @ref handlerchain_pattern.

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "HandlerChain_WindowRectangle.h"

/// <summary>
/// Minimum width of a window (to accommodate a close box).
/// </summary>
const int MINIMUM_WIDTH = 4;
/// <summary>
/// Minimum height of a window (to accommodate a close box).
/// </summary>
const int MINIMUM_HEIGHT = 4;


///////////////////////////////////////////////////////////////////////////////
// WindowRectangle_Initialize()
///////////////////////////////////////////////////////////////////////////////
void WindowRectangle_Initialize(WindowRectangle* rectangle, int x, int y, int width, int height)
{
    if (rectangle != NULL)
    {
        if (width < MINIMUM_WIDTH)
        {
            width = MINIMUM_WIDTH;
        }
        if (height < MINIMUM_HEIGHT)
        {
            height = MINIMUM_HEIGHT;
        }
        rectangle->Left = x;
        rectangle->Top = y;
        rectangle->Right = x + width;
        rectangle->Bottom = y + height;
    }
}

///////////////////////////////////////////////////////////////////////////////
// WindowRectangle_PointInside()
///////////////////////////////////////////////////////////////////////////////
bool WindowRectangle_PointInside(WindowRectangle* rectangle, MessagePosition* point)
{
    bool isInside = false;
    if (rectangle != NULL && point != NULL)
    {

        if (point->X >= rectangle->Left && point->X < rectangle->Right &&
            point->Y >= rectangle->Top && point->Y < rectangle->Bottom)
        {
            isInside = true;
        }

    }
    return isInside;
}

///////////////////////////////////////////////////////////////////////////////
// WindowRectangle_ToString()
///////////////////////////////////////////////////////////////////////////////
void WindowRectangle_ToString(WindowRectangle* rectangle, DynamicString* output)
{
    if (rectangle != NULL && output != NULL)
    {
        char buffer[64] = { 0 };
        int num_chars = sprintf_s(buffer, sizeof(buffer), "x1=%2d, y1=%2d, x2=%2d, y2=%2d",
            rectangle->Left, rectangle->Top, rectangle->Right, rectangle->Bottom);
        if (num_chars != -1)
        {
            DynamicString_Append(output, buffer);
        }
    }
}
