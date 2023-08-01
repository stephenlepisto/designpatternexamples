/// @file
/// @brief
/// Implementation of the Flyweight_Exercise() function as used in the
/// @ref flyweight_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/checkforkey.h"
#include "helpers/cursor.h"
#include "helpers/readkey.h"
#include "helpers/sleep.h"

#include "Flyweight_BigResourceManager.h"
#include "Flyweight_Display.h"
#include "Flyweight_Image.h"
#include "Flyweight_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Generate a big resource, in this case, a text master "image" of the
/// specified height, containing the specified number of smaller images
/// laid out horizontally, using the given width for each image.
///
/// If there are 5 images requested, then create a single image that is
/// `5 * width` wide and `1 * height` tall.
/// </summary>
/// <param name="numImages">Number of images to images to store in the
/// single big resource (horizontally), between 1 and 9.</param>
/// <param name="width">Width of the "text" image, in characters.  Minimum
/// width is 3.</param>
/// <param name="height">Height of the "text" image, in characters.  Minimum
/// height is 3.</param>
/// <returns>An index to the generated index in the BigResourceManager.
/// Returns -1 if something went wrong (out of memory error).</returns>
static int _Flyweight_GenerateBigResource(int numImages, int width, int height)
{
    int resourceId = -1;

    if (numImages < 1)
    {
        numImages = 1;
    }
    else if (numImages > 9)
    {
        numImages = 9;
    }
    if (width < 3)
    {
        width = 3;
    }
    if (height < 3)
    {
        height = 3;
    }

    size_t imageSize = (width * height) * numImages;
    BigResource* resource = calloc(1, sizeof(BigResource));
    if (resource != NULL)
    {
        char* image = calloc(1, imageSize + 1);
        if (image != NULL)
        {
            const char imageBackgroundCharacter[] = "0123456789";

            resource->data = image;
            resource->numImages = numImages;

            for (int row = 0; row < height; ++row)
            {
                int imageColumnOffset = row * (width * numImages);
                for (int imageIndex = 0; imageIndex < numImages; imageIndex++)
                {
                    char backgroundChar = imageBackgroundCharacter[imageIndex];
                    for (int colIndex = 0; colIndex < width; colIndex++)
                    {
                        if (row == 0 || (row + 1) == height)
                        {
                            // top and bottom row are the same.
                            if (colIndex == 0 || (colIndex + 1) == width)
                            {
                                image[imageColumnOffset + colIndex] = '+';
                            }
                            else
                            {
                                image[imageColumnOffset + colIndex] = '-';
                            }
                        }
                        else
                        {
                            // top and bottom row are the same.
                            if (colIndex == 0 || (colIndex + 1) == width)
                            {
                                image[imageColumnOffset + colIndex] = '|';
                            }
                            else
                            {
                                // All other rows are each the same -- except that
                                // each image is "numbered" where the background of the
                                // image reflects the number of the image (0, 1, 2, etc.).
                                image[imageColumnOffset + colIndex] = backgroundChar;
                            }
                        }
                    }
                    imageColumnOffset += width;
                }
            }

            resourceId = BigResourceManager_AddResource(resource);
            if (resourceId == -1)
            {
                free(image);
                image = NULL;
            }
        }
        else
        {
            printf("  Error!  Failed to allocate memory for the big image: size = %lu\n", imageSize);
        }
    }
    else
    {
        printf("  Error!  Failed to allocate memory for the big resource structure: size = %lu\n", sizeof(BigResource));
    }
    return resourceId;
}


/// <summary>
/// Move the given flyweight instances within the display, bouncing them off
/// the edges of the display.
///
/// The display size and image size are provided here
/// </summary>
/// <param name="imageList">List of Flyweight_Class instances to move.</param>
/// <param name="display_width">Width of display.</param>
/// <param name="display_height">Height of display.</param>
static void _Flyweight_MoveFlyweights(Flyweight_ImageList* imageList,
    int display_width, int display_height)
{
    if (imageList != NULL)
    {
        for (size_t imageIndex = 0; imageIndex < imageList->images_count; imageIndex++)
        {
            Flyweight_Image* image = &imageList->images[imageIndex];
            Flyweight_Context* context = &image->Context;
            int image_width = context->ImageWidth;
            int image_height = context->ImageHeight;
            double newx = context->Position_X + context->Velocity_X;
            double newy = context->Position_Y + context->Velocity_Y;

            if (newx < 0 || (newx + image_width) > display_width)
            {
                // Bounce off left or right edge.
                context->Velocity_X = -context->Velocity_X;
                if (newx < 0)
                {
                    newx = 0;
                }
                else
                {
                    newx = display_width - image_width;
                }
            }

            if (newy < 0 || (newy + image_height) > display_height)
            {
                // Bounce off top or bottom edge.
                context->Velocity_Y = -context->Velocity_Y;
                if (newy < 0)
                {
                    newy = 0;
                }
                else
                {
                    newy = display_height - image_height;
                }
            }

            context->Position_X = newx;
            context->Position_Y = newy;
        }
    }
}


/// <summary>
/// Render the image into the display, once for each flyweight instance.
/// </summary>
/// <param name="imageList">List of Flyweight_Image objects to render.</param>
/// <param name="displayArea">The "display" in which to render.</param>
static void _Flyweight_RenderFlyweights(Flyweight_ImageList* imageList, Display* displayArea)
{
    if (imageList != NULL && displayArea != NULL)
    {
        // Render the image into the "display", one image for each instance
        // of the Flyweight class.
        for (size_t imageIndex = 0; imageIndex < imageList->images_count; imageIndex++)
        {
            Flyweight_Image* image = &imageList->images[imageIndex];
            Flyweight_Context* context = &image->Context;
            BigResource_Render(displayArea, image->BigResourceId,
                context->OffsetXToImage,
                context->ImageWidth,
                context->ImageHeight,
                (int)context->Position_X,
                (int)context->Position_Y);
        }
    }
}


/// <summary>
/// Generate a random velocity, which includes a speed and a direction.
/// The velocity is 0.2 to 1.0 (in increments of 0.2) and the direction
/// is either + or -.
/// </summary>
/// <returns>Returns the velocity.</returns>
static double GenerateVelocity(void)
{
    double speed = ((rand() % 5) + 1) / 5.0;
    double direction = ((rand() % 100) > 50) ? 1.0 : -1.0;
    return speed * direction;
}


/// <summary>
/// Helper function to generate the specified number of Flyweight_image objects
/// and associate those objects with individual contexts and a single big resource.
///
/// The image and display sizes are provided so as to randomize the
/// position of each flyweight within the display.
/// </summary>
/// <param name="bigResourceId">ID of the big resource to use.</param>
/// <param name="numFlyweights">Number of flyweight instances to create.</param>
/// <param name="image_width">Width of the big resource image.</param>
/// <param name="image_height">Height of the big resource image.</param>
/// <param name="display_width">Width of the display in which the flyweight is to be rendered.</param>
/// <param name="display_height">Height of the display in which the flyweight is to be rendered.</param>
/// <param name="imageList">A Flyweight_ImageList object to be filled in with
/// the generated Flyweight_Image objects.</param>
static void _Flyweight_GenerateFlyweightClasses(int bigResourceId, int numFlyweights,
    int image_width, int image_height, int display_width, int display_height,
    Flyweight_ImageList* imageList)
{
    // Generate the instances of the flyweight class, randomizing the position
    // of each flyweight within the display.
    for (int index = 0; index < numFlyweights; ++index)
    {
        Flyweight_Image image = { 0 };
        image.Context.OffsetXToImage = index * image_width;
        image.Context.ImageWidth = image_width;
        image.Context.ImageHeight = image_height;
        // Make sure the entire image can be rendered at each position
        image.Context.Position_X = rand() % (display_width - image_width);
        image.Context.Position_Y = rand() % (display_height - image_height);
        // Randomize the initial velocity.
        image.Context.Velocity_X = GenerateVelocity();
        image.Context.Velocity_Y = GenerateVelocity();

        // Create an instance of the Flyweight_Class for the given big
        // resource and with the new context.
        image.BigResourceId = bigResourceId;
        Flyweight_ImageList_Add(imageList, &image);
    }
}


/// <summary>
/// Clear the "display" to a background image, erasing whatever was there before.
/// </summary>
/// <param name="display">A list of character arrays representing the display.</param>
static void _Flyweight_ClearDisplay(Display* display)
{
    if (display != NULL && display->area != NULL)
    {
        for (int rowIndex = 0; rowIndex < display->height; rowIndex++)
        {
            char* row = display->area[rowIndex];
            for (int colIndex = 0; colIndex < display->width; ++colIndex)
            {
                row[colIndex] = '~';
            }
        }
    }
}


/// <summary>
/// Generate a display area in which to render the big resource.
/// </summary>
/// <param name="display">A Display object to initialize as the "display" window.</param>
/// <param name="width">Width of the display area.</param>
/// <param name="height">Height of the display area.</param>
static void _Flyweight_GenerateDisplay(Display* display, int width, int height)
{
    if (Display_Create(display, width, height))
    {
        _Flyweight_ClearDisplay(display);
    }
}

/// <summary>
/// Render the display to the screen.
/// </summary>
/// <param name="display">The Display object to output to the console.</param>
static void _Flyweight_ShowDisplay(Display* display)
{
    if (display != NULL && display->area != NULL)
    {
        for (int rowIndex = 0; rowIndex < display->height; rowIndex++)
        {
            printf("  %s\n", display->area[rowIndex]);
        }
        printf("\n");
    }
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref flyweight_pattern "Flyweight" design pattern.
///
/// The Flyweight pattern is used when a large object needs to be
/// represented by a much lighter weight class, possibly multiple
/// instances of said light-weight class.
///
/// In this example, a large object is represented by a so-called "big
/// resource" (a two-dimensional array of text characters) containing
/// multiple images, one associated with each flyweight class.
/// Flyweight classes that represent offset into the big resource,
/// along with position and velocity, are attached to the big resource
/// image so they all share the same image but have different positions
/// and velocities.  The image is rendered to a display area through
/// the Flyweight class.  The Flyweight class instances then have their
/// positions updated, bouncing off the edges of the display area 60
/// times a second.  This continues for 1000 iterations or until a key
/// is pressed.
/// </summary>
// ! [Using Flyweight in C]
void Flyweight_Exercise(void)
{
    printf("\nFlyweight_Exercise\n");

    // Define the display and image size.
    const int DISPLAY_WIDTH = 80;
    const int DISPLAY_HEIGHT = 20;
    const int IMAGE_WIDTH = 30;
    const int IMAGE_HEIGHT = 5;
    const int NUMFLYWEIGHTS = 5;
    const int NUM_ITERATIONS = 1000;

    int bigResourceId = _Flyweight_GenerateBigResource(NUMFLYWEIGHTS, IMAGE_WIDTH, IMAGE_HEIGHT);
    printf("bigResourceId = %d\n", bigResourceId);

    Flyweight_ImageList imageList = { 0 };
    _Flyweight_GenerateFlyweightClasses(bigResourceId, NUMFLYWEIGHTS,
        IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT, &imageList);

    // Create the "display".
    // We use a list of character arrays so we can write to each
    // character position individually.  In C#, strings are immutable
    // and changing a character in a string is not allowed.
    Display displayArea = { 0 };
    _Flyweight_GenerateDisplay(&displayArea, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    // Finally, display the rendered output.
    printf("  The image rendered %d times:\n", NUMFLYWEIGHTS);
    printf("\n"); // Blank line for iteration count
    _Flyweight_RenderFlyweights(&imageList, &displayArea);
    _Flyweight_ShowDisplay(&displayArea);

    // Now let's have some fun and bounce those images around for a while!
    // (Or until a keypress.)
    int cursorLeft = -1;
    int cursorTop = -1;
    getcursorposition(&cursorTop, &cursorLeft);
    if (cursorLeft != -1 && cursorTop != -1)
    {
        cursorTop -= DISPLAY_HEIGHT + 1;
    }

    for (int index = 0; index < NUM_ITERATIONS; ++index)
    {
        if (cursorLeft != -1)
        {
            setcursorposition(cursorTop - 1, cursorLeft);
        }
        printf("  %5d/%d iterations [press a key to exit early]\n", index + 1, NUM_ITERATIONS);
        if (cursorLeft != -1)
        {
            setcursorposition(cursorTop, cursorLeft);
        }

        _Flyweight_ClearDisplay(&displayArea);
        _Flyweight_MoveFlyweights(&imageList, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        _Flyweight_RenderFlyweights(&imageList, &displayArea);
        _Flyweight_ShowDisplay(&displayArea);
        sleep(16); // 60 frames a second
        if (checkforkey())
        {
            readkey();
            break;
        }
    }

    // Cleanup
    Display_Destroy(&displayArea);
    Flyweight_ImageList_Clear(&imageList);
    BigResourceManager_Clear();

    printf("  Done.\n");
}
// ! [Using Flyweight in C]
