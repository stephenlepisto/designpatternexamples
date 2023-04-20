/// @file
/// @brief
/// Declaration of the WindowRectangle structure and its support functions,
/// WindowRectangle_Initialize(), WindowRectangle_PointInside(), and
/// WindowRectangle_ToString(),
/// as used in the @ref handlerchain_pattern.
/// 
#pragma once
#ifndef __HANDLERCHAIN_WINDOWRECTANGLE_H__
#define __HANDLERCHAIN_WINDOWRECTANGLE_H__

#include <stdbool.h>

#include "helpers/dynamicstring.h"
#include "HandlerChain_Message.h"

/// <summary>
/// Represents a rectangular region, with upper left and lower right
/// coordinates.
/// 
/// For this example, the minimum width of a rectangle is 4 x 4.
/// </summary>
typedef struct
{
    int Left;
    int Top;
    int Right;
    int Bottom;

}  WindowRectangle;

/// <summary>
/// Initialize the specified WindowRectangle based on the given position and
/// size in some arbitrary space.  Ensures a minimum size.
/// </summary>
/// <param name="rectangle">A WindowRectangle object to initialize.</param>
/// <param name="x">Horizontal position of the upper left corner.</param>
/// <param name="y">Vertical position of the upper left corner.</param>
/// <param name="width">Width of the rectangle.</param>
/// <param name="height">Height of the rectangle.</param>
void WindowRectangle_Initialize(WindowRectangle* rectangle, int x, int y, int width, int height);

/// <summary>
/// Determine if the given WindowRectangle object contains the given
/// MessagePosition.
/// </summary>
/// <param name="rectangle">A WindowRectangle object to examine.</param>
/// <param name="point">A MessagePosition object specifying a point in the
/// same space as the `rectangle` value.</param>
/// <returns>Returns true if the MessagePosition is in the WindowRectangle;
/// otherwise, returns false.</returns>
bool WindowRectangle_PointInside(WindowRectangle* rectangle, MessagePosition* point);

/// <summary>
/// Convert the given WindowRectangle to a string representation.
/// </summary>
/// <param name="rectangle">A WindowRectangle to convert.</param>
/// <param name="output">A DynamicString that returns the string version of the
/// rectangle.  Call DynamicString_Initialize() on this object before passing
/// as an argument.</param>
void WindowRectangle_ToString(WindowRectangle* rectangle, DynamicString* output);


#endif // __HANDLERCHAIN_WINDOWRECTANGLE_H__

