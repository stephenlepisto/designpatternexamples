/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Flyweight_Exercise "Flyweight_Exercise"
/// class used in the @ref flyweight_pattern.

using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref flyweight_pattern in C#.
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
    internal class Flyweight_Exercise
    {
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
        /// <param name="width">Width of each "text" image, in characters.  Minimum
        /// width is 3.</param>
        /// <param name="height">Height of each "text" image, in characters.  Minimum
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

            List<string> image = new List<string>();
            for (int row = 0; row < height; ++row)
            {
                string image_row = "";
                for (int imageIndex = 0; imageIndex < numImages; imageIndex++)
                {
                    if (row == 0 || (row + 1) == height)
                    {
                        // top and bottom row are the same.
                        image_row += "+" + new string('-', width - 2) + "+";
                    }
                    else
                    {
                        // All other rows are each the same -- except that
                        // each image is "numbered" where the background of the
                        // image reflects the number of the image (0, 1, 2, etc.).
                        char c = imageIndex.ToString()[0];
                        image_row += '|' + new string(c, width - 2) + '|';
                    }
                }
                image.Add(image_row);
            }

            int resourceId = BigResourceManager.AddResource(image);
            return resourceId;
        }


        /// <summary>
        /// Generate a display area in which to render the big resource.
        /// </summary>
        /// <param name="width">Width of the display area.</param>
        /// <param name="height">Height of the display area.</param>
        /// <returns>A List of character arrays representing the display area.</returns>
        List<char[]> _Flyweight_GenerateDisplay(int width, int height)
        {
            List<char[]> display = new List<char[]>();

            for (int row = 0; row < height; ++row)
            {
                display.Add(new char[width]);
            }

            _Flyweight_ClearDisplay(display);
            return display;
        }


        /// <summary>
        /// Render the display to the screen.
        /// </summary>
        /// <param name="display">A list of character arrays representing the display.</param>
        void _Flyweight_ShowDisplay(List<char[]> display)
        {
            StringBuilder output = new StringBuilder();
            foreach (char[] row in display)
            {
                output.Append("  ");
                foreach (char col in row)
                {
                    output.Append(col);
                }
                output.Append(Environment.NewLine);
            }
            Console.WriteLine(output);
        }


        /// <summary>
        /// Clear the "display" to a background image, erasing whatever was there before.
        /// </summary>
        /// <param name="display">A list of character arrays representing the display.</param>
        void _Flyweight_ClearDisplay(List<char[]> display)
        {
            foreach (char[] row in display)
            {
                for (int index = 0; index < row.Length; ++index)
                {
                    row[index] = '~';
                }
            }
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
        void _Flyweight_MoveFlyweights(List<Flyweight_Class> flyweightInstances, int display_width, int display_height)
        {
            foreach (Flyweight_Class flyweight in flyweightInstances)
            {
                Flyweight_Context context = flyweight.Context;
                int image_width = flyweight.ImageWidth;
                int image_height = flyweight.ImageHeight;
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
                flyweight.Context = context;
            }
        }


        /// <summary>
        /// Render the image into the display, once for each flyweight instance.
        /// </summary>
        /// <param name="flyweightInstances">List of Flyweight_Class instances to render.</param>
        /// <param name="displayArea">The "display" in which to render.</param>
        void _Flyweight_RenderFlyweights(List<Flyweight_Class> flyweightInstances, List<char[]> displayArea)
        {
            // Render the image into the "display", one image for each instance
            // of the Flyweight class.
            foreach (Flyweight_Class flyweight in flyweightInstances)
            {
                flyweight.Render(displayArea,
                    flyweight.Context.OffsetXToImage,
                    flyweight.ImageWidth,
                    flyweight.ImageHeight,
                    (int)flyweight.Context.Position_X,
                    (int)flyweight.Context.Position_Y);
            }
        }

        /// <summary>
        /// Generate a random velocity, which includes a speed and a direction.
        /// The velocity is 0.2 to 1.0 (in increments of 0.2) and the direction
        /// is either + or -.
        /// </summary>
        /// <returns>Returns the velocity.</returns>
        double GenerateVelocity(Random randomizer)
        {
            double speed = (randomizer.Next(1, 5) / 5.0);
            double direction = ((randomizer.Next(100) > 50) ? 1.0 : -1.0);
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
        /// <returns></returns>
        List<Flyweight_Class> _Flyweight_GenerateFlyweightClasses(int bigResourceId, int numFlyweights,
            int image_width, int image_height, int display_width, int display_height)
        {
            List<Flyweight_Class> flyweightInstances = new List<Flyweight_Class>();

            Random randomizer = new Random();
            // Generate the instances of the flyweight class, randomizing the position
            // of each flyweight within the display.
            for (int index = 0; index < numFlyweights; ++index)
            {
                Flyweight_Context context = new Flyweight_Context();
                context.OffsetXToImage = index * image_width;
                context.ImageWidth = image_width;
                context.ImageHeight = image_height;
                // Make sure the entire image can be rendered at each position
                context.Position_X = randomizer.Next(0, display_width - image_width);
                context.Position_Y = randomizer.Next(0, display_height - image_height);
                // Randomize the initial velocity.
                context.Velocity_X = GenerateVelocity(randomizer);
                context.Velocity_Y = GenerateVelocity(randomizer);

                // Create an instance of the Flyweight_Class for the given big
                // resource and with the new context.
                Flyweight_Class? flyweightInstance = BigResourceManager.CreateFlyweight(bigResourceId, context);
                if (flyweightInstance != null)
                {
                    flyweightInstances.Add(flyweightInstance);
                }
                else
                {
                    Console.WriteLine("  Error!  Failed to find big resource ID {}, which is needed for the flyweight.", bigResourceId);
                }
            }
            return flyweightInstances;
        }

        /// <summary>
        /// Executes the example for the @ref flyweight_pattern in C#.
        /// </summary>
        // ! [Using Flyweight in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Flyweight Exercise");

            // Define the display and image size.
            const int DISPLAY_WIDTH = 80;
            const int DISPLAY_HEIGHT = 20;
            const int IMAGE_WIDTH = 30;
            const int IMAGE_HEIGHT = 5;
            const int NUMFLYWEIGHTS = 5;
            const int NUM_ITERATIONS = 1000;

            int bigResourceId = _Flyweight_GenerateBigResource(NUMFLYWEIGHTS, IMAGE_WIDTH, IMAGE_HEIGHT);
            List<Flyweight_Class> flyweightInstances;
            flyweightInstances = _Flyweight_GenerateFlyweightClasses(bigResourceId, NUMFLYWEIGHTS,
                IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT);

            // Create the "display".
            // We use a list of character arrays so we can write to each
            // character position individually.  In C#, strings are immutable
            // and changing a character in a string is not allowed.
            List<char[]> displayArea = _Flyweight_GenerateDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);

            // Finally, display the rendered output.
            Console.WriteLine("  The image rendered {0} times:", NUMFLYWEIGHTS);
            Console.WriteLine(""); // Blank line for iteration count
            _Flyweight_RenderFlyweights(flyweightInstances, displayArea);
            _Flyweight_ShowDisplay(displayArea);

            // Now let's have some fun and bounce those images around for a while!
            // (Or until a keypress.)
            int cursorLeft = Console.CursorLeft;
            int cursorTop = Console.CursorTop;
            cursorTop -= DISPLAY_HEIGHT + 1;
            for (int index = 0; index < NUM_ITERATIONS; ++index)
            {
                Console.SetCursorPosition(cursorLeft, cursorTop - 1);
                Console.WriteLine("  {0,5}/{1} iterations [press a key to exit early]", index + 1, NUM_ITERATIONS);
                Console.SetCursorPosition(cursorLeft, cursorTop);

                _Flyweight_ClearDisplay(displayArea);
                _Flyweight_MoveFlyweights(flyweightInstances, DISPLAY_WIDTH, DISPLAY_HEIGHT);
                _Flyweight_RenderFlyweights(flyweightInstances, displayArea);
                _Flyweight_ShowDisplay(displayArea);
                System.Threading.Thread.Sleep(16); // 60 frames a second
                if (Console.KeyAvailable)
                {
                    Console.ReadKey();
                    break;
                }
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Flyweight in C#]
    }
}
