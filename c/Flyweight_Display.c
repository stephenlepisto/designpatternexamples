/// @file
/// @brief
/// Implementation of the Display_Create() and Display_Destroy() functions for
/// managing the Display structure that represents a "display" windows as
/// used in the @ref flyweight_pattern.

#include <stdlib.h>

#include "Flyweight_Display.h"

///////////////////////////////////////////////////////////////////////////////
// Display_Create()
///////////////////////////////////////////////////////////////////////////////
bool Display_Create(Display* display, int width, int height)
{
    bool created = false;

    if (display != NULL)
    {
        char** rows = calloc(1, height * sizeof(char*));
        if (rows != NULL)
        {
            display->area = rows;
            display->width = width;
            display->height = height;
            created = true;
            for (int rowIndex = 0; rowIndex < height; rowIndex++)
            {
                char* row = calloc(1, width + 1);
                if (row == NULL)
                {
                    created = false;
                    break;
                }
                rows[rowIndex] = row;
            }

            if (!created)
            {
                Display_Destroy(display);
            }
        }
    }
    return created;
}

///////////////////////////////////////////////////////////////////////////////
// Display_Create()
///////////////////////////////////////////////////////////////////////////////
void Display_Destroy(Display* display)
{
    if (display != NULL)
    {
        if (display->area != NULL)
        {
            for (int rowIndex = 0; rowIndex < display->height; rowIndex++)
            {
                free(display->area[rowIndex]);
            }
            free(display->area);
            display->area = NULL;
        }
        display->width = 0;
        display->height = 0;
    }
}

