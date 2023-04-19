/// @file
/// @brief
/// Declaration of the Flyweight_ImageList and Flyweight_Image structures, the
/// latter which wraps the big resource handle and a Flyweight_Context as used
/// in the @ref flyweight_pattern.

#pragma once
#ifndef __FLYWEIGHT_IMAGE_H__
#define __FLYWEIGHT_IMAGE_H__

#include "Flyweight_Context.h"

/// <summary>
/// Represents an image that associates a context with a big resource.
/// </summary>
typedef struct
{
    /// <summary>
    /// The big resource being referenced by this flyweight image.  This is
    /// represented by a handle to the big resource.
    /// </summary>
    int BigResourceId;

    /// <summary>
    /// The context associated with this image.  The calling entity
    /// uses this context to manipulate the position of the image.
    /// </summary>
    Flyweight_Context Context;

} Flyweight_Image;


/// <summary>
/// Represents an expandable list of Flyweight_Image objects.  This is managed
/// by the Flyweight_ImageList_Clear() and Flyweight_ImageList_Add() functions.
/// 
/// Note that this contains a list of Flyweight_Image structures, not pointers
/// to Flyweight_image structures.
/// </summary>
typedef struct
{
    Flyweight_Image* images; ///< Dynamic list of Flyweight_Image objects.
    size_t images_count;     ///< Number of Flyweight_image objects in the list

} Flyweight_ImageList;


/// <summary>
/// Clear the given Flyweight_ImageList object by freeing up all allocated 
/// Flyweight_image objects and resetting the list to a "new" state so it can
/// be reused.
/// </summary>
/// <param name="imageList">A pointer to the Flyweight_ImageList to be cleared.</param>
void Flyweight_ImageList_Clear(Flyweight_ImageList* imageList);

/// <summary>
/// Add a Flyweight_Image object to the given Flyweight_ImageList object.  The
/// list takes ownership of the BigResource object and is responsible for
/// releasing all memory associated with it.
/// </summary>
/// <param name="imageList">The Flyweight_ImageList object to add to.</param>
/// <param name="image">The Flyweight_Image object to be copied to the
/// Flyweight_ImageList.</param>
void Flyweight_ImageList_Add(Flyweight_ImageList* imageList, Flyweight_Image* image);

#endif // __FLYWEIGHT_IMAGE_H__
