/// @file
/// @brief
/// Declaration of the Flyweight_Context structure that is associated with a
/// Flyweight_Image as used in the @ref flyweight_pattern.

#pragma once
#ifndef __FLYWEIGHT_CONTEXT_H__
#define __FLYWEIGHT_CONTEXT_H__

/// <summary>
/// Represents the context for an instance of the Flyweight_Image structure.
/// In this case, the context includes position and velocity.
/// 
/// This context is manipulated outside the Flyweight Image by the
/// controlling entity (in this case, the Flyweight_Exercise() function).  The
/// Flyweight_Image structure just holds onto the context, along with a handle
/// to the big resource.
/// </summary>
typedef struct
{
    int OffsetXToImage;   ///< Offset into big resource to left edge of image
    int ImageWidth;       ///< Width of image
    int ImageHeight;      ///< Height of image
    double Position_X;    ///< Horizontal position of upper left corner of image in a display
    double Position_Y;    ///< Vertical position of upper left corner of image in a display
    double Velocity_X;    ///< Velocity to apply to the horizontal position
    double Velocity_Y;    ///< Velocity to apply to the vertical position
} Flyweight_Context;

#endif // __FLYWEIGHT_CONTEXT_H__

