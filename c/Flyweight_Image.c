/// @file
/// @brief
/// Implementation of the Flyweight_ImageList and Flyweight_Image structures, the
/// latter which wraps the big resource handle and a Flyweight_Context as used
/// in the @ref flyweight_pattern.

#include <stdlib.h>

#include "Flyweight_Image.h"

///////////////////////////////////////////////////////////////////////////////
// Flyweight_ImageList_Clear()
///////////////////////////////////////////////////////////////////////////////
void Flyweight_ImageList_Clear(Flyweight_ImageList* imageList)
{
    if (imageList != NULL && imageList->images != NULL && imageList->images_count != 0)
    {
        free(imageList->images);
        imageList->images = NULL;
        imageList->images_count = 0;
    }
}


///////////////////////////////////////////////////////////////////////////////
// Flyweight_ImageList_Clear()
///////////////////////////////////////////////////////////////////////////////
void Flyweight_ImageList_Add(Flyweight_ImageList* imageList, Flyweight_Image* image)
{
    Flyweight_Image* new_list = NULL;

    if (imageList != NULL && image != NULL)
    {
        if (imageList->images == NULL)
        {
            new_list = malloc(sizeof(Flyweight_Image));
        }
        else
        {
            size_t newSize = (imageList->images_count + 1) * sizeof(Flyweight_Image);
            new_list = realloc(imageList->images, newSize);
        }

        if (new_list != NULL)
        {
            imageList->images = new_list;
            imageList->images[imageList->images_count] = *image;
            imageList->images_count++;
        }
    }
}

///// <summary>
///// Constructor (accessible only to the class factory).
///// </summary>
///// <param name="resource">The resource being represented by this class.  This
///// takes advantage of the fact that C# classes are always passed by reference so
///// no actual copying of the resource is done.</param>
///// <param name="context">A Flyweight_Context instance containing the context for this
///// Flyweight_Class instance.</param>
//Flyweight_Class(BigResource* resource, Flyweight_Context context);
//
///// <summary>
///// Retrieve the context for this class instance.
///// </summary>
//Flyweight_Context Context();
//
//
///// <summary>
///// Set the context for this class instance.
///// </summary>
//void SetContext(Flyweight_Context context);
//
//
///// <summary>
///// Retrieve the "image" width from underlying big resource.
///// </summary>
//int ImageWidth();
//
//
///// <summary>
///// Retrieve the "image" height from underlying big resource.
///// </summary>
//int ImageHeight();
//
///// <summary>
///// Render the image associated with this flyweight instance into the given
///// display at the given position.
///// </summary>
///// <param name="display">A list of character arrays representing the display.</param>
///// <param name="offset_x">Offset from left edge of big resource to the
///// left edge of the image to render.</param>
///// <param name="image_width">Width of image to render.</param>
///// <param name="image_height">Height of image to render.</param>
///// <param name="position_x">leftmost position within the display to place
///// the upper left corner of the image,</param>
///// <param name="position_y">topmost position within the display to place
///// the upper left corner of the image.</param>
///// <remarks>
///// Note that although this class has access to the context, it really
///// shouldn't so as to keep a loose coupling between the context and
///// this class.  Therefore, the entity calling Render() will pass the
///// position in as parameters even though that position is likely
///// coming from the context.
///// </remarks>
//void Render(std::vector<std::vector<char>>& display, int offset_x, int image_width, int image_height, int position_x, int position_y);
