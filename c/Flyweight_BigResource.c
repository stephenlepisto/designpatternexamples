/// @file
/// @brief
/// Implementation of the BigResource_Clear() function and the
/// BigResource_Render() function used to render portions of the big resource
/// into a "display" window as used in the @ref flyweight_pattern.

#include <stdlib.h>

#include "Flyweight_BigResourceManager.h"
#include "Flyweight_BigResource.h"


///////////////////////////////////////////////////////////////////////////////
// BigResource_Clear()
///////////////////////////////////////////////////////////////////////////////
void BigResource_Clear(BigResource* resource)
{
    if (resource != NULL)
    {
        free(resource->data);
        resource->data = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BigResource_Render()
///////////////////////////////////////////////////////////////////////////////
void BigResource_Render(Display* display, int bigResourceId, int offset_x,
    int image_width, int image_height, int position_x, int position_y)
{
    if (display != NULL)
    {
        BigResource* resource = BigResourceManager_GetResource(bigResourceId);
        if (resource != NULL)
        {
            size_t display_width = display->width;
            size_t display_height = display->height;
            int starting_position_x = position_x;
            int starting_position_y = position_y;

            // Size of image to render (can be smaller than actual image if image
            // lies partially of right or bottom of display).
            size_t image_render_width = image_width;
            size_t image_render_height = image_height;

            // Position into image to start rendering from (non-zero if
            // image is off the left or top edge of display).
            //int starting_row_in_image = 0;
            int starting_col_in_image = offset_x;

            // Clip the image to the display.
            if (starting_position_x < 0)
            {
                starting_col_in_image = -starting_position_x;
                image_render_width += starting_position_x;
                starting_position_x = 0;
            }
            else if (starting_position_x + image_render_width > display_width)
            {
                image_render_width = display_width - starting_position_x;
            }
            if (starting_position_y < 0)
            {
                //starting_row_in_image = -starting_position_y;
                image_render_height += starting_position_y;
                starting_position_y = 0;
            }
            else if (starting_position_y + image_render_height > display_height)
            {
                image_render_height = display_height - starting_position_y;
            }

            // If the image is even partially visible, render it
            if (image_render_width > 0 && image_render_height > 0)
            {
                int current_display_row = starting_position_y;
                char* resourceRow = resource->data + starting_col_in_image;
                for (size_t row = 0; row < image_render_height; ++row)
                {
                    char* areaRow = display->area[current_display_row];
                    for (size_t col = 0; col < image_render_width; ++col)
                    {
                        areaRow[starting_position_x + col] = resourceRow[col];
                    }
                    current_display_row += 1;
                    resourceRow += resource->numImages * image_width;
                }
            }
        }
    }
}
