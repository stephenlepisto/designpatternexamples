/// @file
/// @brief
/// Declaration of the Display_Create() and Display_Destroy() functions for
/// managing the Display structure that represents a "display" windows as
/// used in the @ref flyweight_pattern.

#pragma once
#ifndef __FLYWEIGHT_DISPLAY_H__
#define __FLYWEIGHT_DISPLAY_H__

#include <stdbool.h>

/// <summary>
/// Represents a "display" window, in which to render Flyweight images.  This
/// "display" window is then printed to the console window at a specified
/// coordinate to render a "frame" of motion in the "display".
/// </summary>
typedef struct
{
    char** area; ///< 2-dimensional array of strings, representing rows.  Each row is zero-terminated.
    int width;   ///< Width of each row
    int height;  ///< Height of each row
} Display;

/// <summary>
/// Create a "display" window in the given Display object, with the given
/// width and height.
/// </summary>
/// <param name="display">The Display object in which to construct the
/// "display" window.</param>
/// <param name="width">The width of the window, in characters.</param>
/// <param name="height">The height of the window, in character.</param>
bool Display_Create(Display* display, int width, int height);

/// <summary>
/// Destroy the "display" window in the given Display object by releasing the
/// memory associated with it.  After this function returns, the Display
/// object is no longer usable without calling Display_Create() again.
/// </summary>
/// <param name="display">The Display object to free.</param>
void Display_Destroy(Display* display);

#endif // __FLYWEIGHT_DISPLAY_H__
