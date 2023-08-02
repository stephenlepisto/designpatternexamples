
/// @file
/// @brief
/// Implementation of the Flyweight_Exercise() function as used in the
/// @ref flyweight_pattern.

#include <iostream>
#include <sstream>

#include "helpers/sleep.h"
#include "helpers/cursor.h"
#include "helpers/readkey.h"
#include "helpers/checkforkey.h"
#include "helpers/formatstring.h"

#include "Flyweight_Exercise.h"
#include "Flyweight_Classes.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

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
    /// <returns>An index to the generated index in the BigResourceManager.</returns>
    int _Flyweight_GenerateBigResource(int numImages, int width, int height)
    {
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

        std::vector<std::string> image;
        for (int row = 0; row < height; ++row)
        {
            std::string image_row("");
            for (int imageIndex = 0; imageIndex < numImages; imageIndex++)
            {
                if (row == 0 || (row + 1) == height)
                {
                    // top and bottom row are the same.
                    image_row += Helpers::formatstring("+%s+", std::string((size_t)width - 2, '-').c_str());
                }
                else
                {
                    // All other rows are each the same -- except that
                    // each image is "numbered" where the background of the
                    // image reflects the number of the image (0, 1, 2, etc.).
                    char c = Helpers::formatstring("%d", imageIndex)[0];
                    image_row += Helpers::formatstring("|%s|", std::string((size_t)width - 2, c).c_str());
                }
            }
            image.push_back(image_row);
        }

        int resourceId = BigResourceManager::AddResource(image);
        return resourceId;
    }


    /// <summary>
    /// Clear the "display" to a background image, erasing whatever was there before.
    /// </summary>
    /// <param name="display">A list of character arrays representing the display.</param>
    void _Flyweight_ClearDisplay(std::vector<std::vector<char>>& display)
    {
        for (std::vector<char>& row : display)
        {
            for (size_t index = 0; index < row.size(); ++index)
            {
                row[index] = '~';
            }
        }
    }


    /// <summary>
    /// Generate a display area in which to render the big resource.
    /// </summary>
    /// <param name="width">Width of the display area.</param>
    /// <param name="height">Height of the display area.</param>
    /// <returns>A List of character arrays representing the display area.</returns>
    std::vector<std::vector<char>> _Flyweight_GenerateDisplay(int width, int height)
    {
        std::vector<std::vector<char>> display;

        for (int row = 0; row < height; ++row)
        {
            display.push_back(std::vector<char>(width));
        }

        _Flyweight_ClearDisplay(display);
        return display;
    }


    /// <summary>
    /// Render the display to the screen.
    /// </summary>
    /// <param name="display">A list of character arrays representing the display.</param>
    void _Flyweight_ShowDisplay(std::vector<std::vector<char>>& display)
    {
        std::ostringstream output;
        for (auto& row : display)
        {
            output << "  ";
            for (size_t col = 0; col < row.size(); col++)
            {
                output << row[col];
            }
            output << std::endl;
        }
        std::cout << output.str() << std::endl;
    }


    /// <summary>
    /// Move the given flyweight instances within the display, bouncing them off
    /// the edges of the display.
    ///
    /// The display size and image size are provided here
    /// </summary>
    /// <param name="flyweightInstances">List of Flyweight_Class instances to move.</param>
    /// <param name="display_width">Width of display.</param>
    /// <param name="display_height">Height of display.</param>
    void _Flyweight_MoveFlyweights(
        FlyweightClassList& flyweightInstances,
        int display_width, int display_height)
    {
        for (FlyweightClassList::iterator flyweightIter = std::begin(flyweightInstances);
            flyweightIter != std::end(flyweightInstances);
            flyweightIter++)
        {
            Flyweight_Class* flyweight = (*flyweightIter).get();
            Flyweight_Context context = flyweight->Context();
            int image_width = flyweight->ImageWidth();
            int image_height = flyweight->ImageHeight();
            double newx = context.Position_X + context.Velocity_X;
            double newy = context.Position_Y + context.Velocity_Y;

            if (newx < 0 || (newx + image_width) > display_width)
            {
                // Bounce off left or right edge.
                context.Velocity_X = -context.Velocity_X;
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
                context.Velocity_Y = -context.Velocity_Y;
                if (newy < 0)
                {
                    newy = 0;
                }
                else
                {
                    newy = display_height - image_height;
                }
            }

            context.Position_X = newx;
            context.Position_Y = newy;
            flyweight->SetContext(context);
        }
    }


    /// <summary>
    /// Render the image into the display, once for each flyweight instance.
    /// </summary>
    /// <param name="flyweightInstances">List of Flyweight_Class instances to render.</param>
    /// <param name="displayArea">The "display" in which to render.</param>
    void _Flyweight_RenderFlyweights(FlyweightClassList& flyweightInstances, std::vector<std::vector<char>>& displayArea)
    {
        // Render the image into the "display", one image for each instance
        // of the Flyweight class.
        for (FlyweightClassList::iterator flyweightIter = std::begin(flyweightInstances);
            flyweightIter != std::end(flyweightInstances);
            flyweightIter++)
        {
            Flyweight_Class* flyweight = (*flyweightIter).get();
            Flyweight_Context context = flyweight->Context();
            flyweight->Render(displayArea,
                context.OffsetXToImage,
                flyweight->ImageWidth(),
                flyweight->ImageHeight(),
                (int)context.Position_X,
                (int)context.Position_Y);
        }
    }

    /// <summary>
    /// Generate a random velocity, which includes a speed and a direction.
    /// The velocity is 0.2 to 1.0 (in increments of 0.2) and the direction
    /// is either + or -.
    /// </summary>
    /// <returns>Returns the velocity.</returns>
    double GenerateVelocity()
    {
        double speed = ((rand() % 5) + 1) / 5.0;
        double direction = ((rand() % 100) > 50) ? 1.0 : -1.0;
        return speed * direction;
    }

    /// <summary>
    /// Helper method to generate the specified number of flyweight class
    /// instances and associate those instances with individual contexts
    /// and a single big resource.
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
    /// <returns>A list containing the requested number of Flyweight class
    /// instances, each attached to the specified "big" resource.</returns>
    FlyweightClassList _Flyweight_GenerateFlyweightClasses(int bigResourceId, int numFlyweights,
        int image_width, int image_height, int display_width, int display_height)
    {
        FlyweightClassList flyweightInstances;

        // Generate the instances of the flyweight class, randomizing the position
        // of each flyweight within the display.
        for (int index = 0; index < numFlyweights; ++index)
        {
            Flyweight_Context context;
            context.OffsetXToImage = index * image_width;
            context.ImageWidth = image_width;
            context.ImageHeight = image_height;
            // Make sure the entire image can be rendered at each position
            context.Position_X = rand() % (display_width - image_width);
            context.Position_Y = rand() % (display_height - image_height);
            // Randomize the initial velocity.
            context.Velocity_X = GenerateVelocity();
            context.Velocity_Y = GenerateVelocity();

            // Create an instance of the Flyweight_Class for the given big
            // resource and with the new context.
            flyweightInstances.push_back(BigResourceManager::CreateFlyweight(bigResourceId, context));
        }
        return flyweightInstances;
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

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
    // ! [Using Flyweight in C++]
    void Flyweight_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Flyweight Exercise" << std::endl;

        // Define the display and image size.
        const int DISPLAY_WIDTH = 80;
        const int DISPLAY_HEIGHT = 20;
        const int IMAGE_WIDTH = 30;
        const int IMAGE_HEIGHT = 5;
        const int NUMFLYWEIGHTS = 5;
        const int NUM_ITERATIONS = 1000;

        int bigResourceId = _Flyweight_GenerateBigResource(NUMFLYWEIGHTS, IMAGE_WIDTH, IMAGE_HEIGHT);
        FlyweightClassList flyweightInstances;
        flyweightInstances = _Flyweight_GenerateFlyweightClasses(bigResourceId, NUMFLYWEIGHTS,
            IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT);

        // Create the "display".
        // We use a list of character arrays so we can write to each
        // character position individually.  In C#, strings are immutable
        // and changing a character in a string is not allowed.
        std::vector<std::vector<char>> displayArea = _Flyweight_GenerateDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);

        // Finally, display the rendered output.
        std::cout << Helpers::formatstring("  The image rendered %d times:", NUMFLYWEIGHTS) << std::endl;
        std::cout << std::endl; // Blank line for iteration count
        _Flyweight_RenderFlyweights(flyweightInstances, displayArea);
        _Flyweight_ShowDisplay(displayArea);

        Helpers::disableinputecho();
        // Now let's have some fun and bounce those images around for a while!
        // (Or until a keypress.)
        int cursorLeft = -1;
        int cursorTop = -1;
        Helpers::getcursorposition(&cursorTop, &cursorLeft);
        if (cursorLeft != -1 && cursorTop != -1)
        {
            cursorTop -= DISPLAY_HEIGHT + 1;
        }
        for (int index = 0; index < NUM_ITERATIONS; ++index)
        {
            if (cursorLeft != -1)
            {
                Helpers::setcursorposition(cursorTop - 1, cursorLeft);
            }
            std::cout << Helpers::formatstring("  %5d/%d iterations [press a key to exit early]", index + 1, NUM_ITERATIONS) << std::endl;
            if (cursorLeft != -1)
            {
                Helpers::setcursorposition(cursorTop, cursorLeft);
            }

            _Flyweight_ClearDisplay(displayArea);
            _Flyweight_MoveFlyweights(flyweightInstances, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            _Flyweight_RenderFlyweights(flyweightInstances, displayArea);
            _Flyweight_ShowDisplay(displayArea);
            Helpers::sleep(16); // 60 frames a second
            if (Helpers::checkforkey())
            {
                Helpers::readkey();
                break;
            }
        }
        Helpers::enableinputecho();

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Flyweight in C++]

} // end namespace
