/// @file
/// @brief
/// Declaration of the BigResource structure along with the supporting
/// BigResource_Clear function.  Also declares the BigResource_Render()
/// function used to render portions of the big resource into a "display"
/// window as used in the @ref flyweight_pattern.

#pragma once
#ifndef __FLYWEIGHT_BIGRESOURCE_H__
#define __FLYWEIGHT_BIGRESOURCE_H__

#include "Flyweight_Display.h"

/// <summary>
/// Represents a big image.  Call the BigResource_Clear() function to release
/// the memory used by each instance of the BigResource structure (see the
/// BigResourceList structure).
/// 
/// This is used in rendering an image to a display using the BigResource_Render()
/// function.
/// </summary>
typedef struct
{
    char* data;    ///< Image data, row-oriented
    int numImages; ///< Number of images represented in the big image
} BigResource;

/// <summary>
/// Clear the BigResource object, freeing any memory associated with it.
/// </summary>
/// <param name="resource">A BitResource object to clear.</param>
void BigResource_Clear(BigResource* resource);

/// <summary>
/// Render the specified portion of the big resource into the given display at
/// the given coordinates in the display.
/// </summary>
/// <param name="display">The Display object representing the "display" window.</param>
/// <param name="bigResourceId">The handle to the big resource from which to
/// render images.</param>
/// <param name="offset_x">Offset from left edge in the big resource to the left
///  edge of the image to use.</param>
/// <param name="image_width">With of the image to render.</param>
/// <param name="image_height">Height of the image to render.</param>
/// <param name="position_x">Horizontal position in the display of the upper left
/// corner of the image to render.</param>
/// <param name="position_y">Vertical position in the display of the upper left
/// corner of the image to render.</param>
void BigResource_Render(Display* display, int bigResourceId, int offset_x,
    int image_width, int image_height, int position_x, int position_y);

#endif // __FLYWEIGHT_BIGRESOURCE_H__

