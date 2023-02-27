// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>

#include "helpers/replace.h"
#include "helpers/stringlist.h"
#include "helpers/enablevtmode.h"
#include "helpers/sleep.h"
#include "helpers/cursor.h"
#include "helpers/readkey.h"
#include "helpers/checkforkey.h"

#include "Adapter_FrontEndClass.h"
#include "Bridge_Logger.h"
#include "Composite_FileDirEntry.h"
#include "Composite_FileAccess.h"
#include "Decorator_Classes.h"
#include "FacadeSubsystem_Interface.h"
#include "Facade_Interface.h"
#include "Flyweight_Classes.h"
#include "Proxy_Class.h"


namespace DesignPatternExamples_cpp
{

    //typedef void (*Action)(); // Represents a function to be called
    typedef std::function<void()> Action;

    class Program
    {
    private:

    private:
        /// <summary>
        /// Represents a single exercise or example for a design pattern.
        /// </summary>
        struct Exercise
        {
            /// <summary>
            /// Name of the exercise.
            /// </summary>
            std::string name;

            /// <summary>
            /// Method to call to run the exercise.
            /// </summary>
            Action exercise_to_run;


            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="nameOfExercise">Name of the exercise.</param>
            /// <param name="exercise">Method to run (of type void ()(void)).</param>
            Exercise(const char* nameOfExercise, Action exercise)
            {
                name = nameOfExercise;
                exercise_to_run = exercise;
            }
        };

        typedef std::vector<Exercise> ExerciseList;

        /// <summary>
        /// Represents the command line options provided to the program, if any.
        /// </summary>
        struct Options
        {
            /// <summary>
            /// List of exercise names to run.  If this list is empty, run all
            /// exercises.
            /// </summary>
            StringList exercise_names;
        };

    private:
        /// <summary>
        /// Helper method to show usage information for this program.
        /// </summary>
        /// <param name="exercises">List of Exercise objects for which to show the
        /// names.</param>
        void Help(ExerciseList exercises)
        {
            std::string usage =
                "{0} by Stephen P. Lepisto\n"
                "usage: {0} [options] [exercise_name][[ exercise_name][...]]\n"
                "\n"
                "Runs through a series of exercises showing off design patterns.  If no"
                "exercise_name is given, then run through all exercises.\n"
                "\n"
                "Options:\n"
                "--help, -?\n"
                "     This help text.\n"
                "\n"
                ""; // End of string.

            std::string appName = "DesignPatternExamples_cpp";
            std::cout << Helpers::Replace(usage, "{0}", appName.c_str());

            std::cout << std::endl << "Exercises available:" << std::endl;
            for (Exercise exercise : exercises)
            {
                std::cout << "  " << exercise.name << std::endl;
            }
        }

        /// <summary>
        /// Helper method to parse the given options and store the results in
        /// the given Options structure.  Displays help if requested and
        /// returns false.
        /// </summary>
        /// <param name="args">List of arguments passed on the command line.</param>
        /// <param name="exercises">List of Exercise objects to display if
        /// help is needed.</param>
        /// <param name="options">An Options structure to be filled in by command
        /// line parameters.</param>
        /// <returns>true if the command lines were valid and help was not asked.
        /// Otherwise, a command line option was not valid or help was
        /// requested.</returns>
        bool ParseOptions(StringList args, ExerciseList exercises, Options& options)
        {
            bool optionsValid = true;

            options.exercise_names;

            if (args.size() > 0)
            {
                for (std::string argument : args)
                {
                    if (argument == "--help" ||
                        argument == "-?" ||
                        argument == "/?")
                    {
                        Help(exercises);
                        optionsValid = false;
                        break;
                    }
                    options.exercise_names.push_back(argument);
                }
            }

            return optionsValid;
        }

    public:
        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Adapter design pattern.
        /// 
        /// This example adapts functions that return error codes into a class
        /// object that throws exceptions, which is more fitting of an object-
        /// oriented language.
        /// </summary>
        //! [Using Adapter in C++]
        void Adapter_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Adapter Exercise" << std::endl;
            try
            {
                DataReaderWriter dataReaderWriter("-target BXT");
                
                // Create the data to be written
                uint32_t dataSize = 128;
                std::vector<uint8_t> writeData(dataSize);
                for (uint32_t index = 0; index < dataSize; ++index)
                {
                    writeData[index] = static_cast<uint8_t>(index);
                }
                
                // Display the data to be written
                std::string dataDump =
                    dataReaderWriter.BufferToString(writeData, dataSize, 2);
                std::cout << "  Data written:" << std::endl;
                std::cout << dataDump << std::endl;
                
                // Write the data to the external component
                dataReaderWriter.Write(writeData, dataSize);
                
                // Read the data from the external component
                std::vector<uint8_t> readData = dataReaderWriter.Read(dataSize);
                
                // Display the data read back.  Should be the same as was written.
                dataDump = dataReaderWriter.BufferToString(readData, dataSize, 2);
                std::cout << "  Data read:" << std::endl;
                std::cout << dataDump << std::endl;
            }
            catch (DataReaderWriterInitException& e)
            {
                std::cout << "Error with startup or shutdown! " << e.what()
                          << std::endl;
            }
            catch (DataReaderWriterException& e)
            {
                std::cout << "Error with reading or writing! " << e.what()
                          << std::endl;
            }

            std::cout << "  Done." << std::endl;
        }
        //! [Using Adapter in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Helper function to show an example of writing to a logger.
        /// 
        /// This is called for all types of loggers, showing how the Logger
        /// class hides the details of the underlying implementation.
        /// </summary>
        /// <param name="logger">A Logger instance to log to</param>
        /// <param name="loggerType">The type of the underlying implementation.
        /// </param>
        void _Bridge_Exercise_Demonstrate_Logging(
            Logger& logger, std::string loggerType)
        {
            std::string output;
            output = std::format("Starting \"log to {}\" example", loggerType);
            logger.LogTrace(output);

            logger.LogInfo("An example of an informational line");
            logger.LogError("An example of an error log entry");

            output = std::format("Done with \"log to {}\" example", loggerType);
            logger.LogTrace(output);
        }


        /// <summary>
        /// Example of using the Bridge design pattern.
        /// 
        /// The Bridge pattern is used to allow a program to offer multiple
        /// ways to perform logging without changing how the logging is
        /// used throughout the program.
        ///
        /// In this exercise, note how the calls into the logger are the
        /// same regardless of the logger used.
        /// </summary>
        //! [Using Bridge in C++]
        void Bridge_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Bridge Exercise" << std::endl;

            // Note: Use local contexts to automatically close the various loggers
            // when the loggers go out of scope.
            {
                Logger logger("Bridge.log"); // Logger::LoggerTypes::ToFile type
                std::cout << "  Example of writing to a log file..." << std::endl;
                _Bridge_Exercise_Demonstrate_Logging(logger, "file");
            }

            {
                Logger logger(Logger::LoggerTypes::ToConsole);
                std::cout << "  Example of writing to the console..." << std::endl;
                _Bridge_Exercise_Demonstrate_Logging(logger, "console");
            }

            {
                Logger logger(Logger::LoggerTypes::ToNull);
                std::cout << "  Example of writing to a Null object (no output)..."
                          << std::endl;
                // Note: The resulting log lines will not be shown anywhere.
                _Bridge_Exercise_Demonstrate_Logging(logger, "null");
            }

            std::cout << "  Done." << std::endl;
        }
        //! [Using Bridge in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Format the specified entry for display.
        /// 
        /// This is a recursive call.
        /// </summary>
        /// <param name="entry">The FileDirEntry object to format</param>
        /// <param name="depth">The current recursion depth.  This is used as
        /// leading space.</param>
        /// <returns>A string containing the formatted text for the given entry.</returns>
        std::string Composite_Exercise_FormatEntry(FileDirEntry* entry, int depth)
        {
            const int NAME_PADDING_SIZE = 20;
            std::string output = "";
            std::string spaces(depth * 2, ' ');
            output.append(std::format("{0}{1}", spaces, entry->Name()));
            size_t padding = NAME_PADDING_SIZE - entry->Name().size()  - (depth * 2);
            if (entry->FileDirType() == FileDirTypes::Directory)
            {
                output.append("/");
                padding--;
            }
            output.append(std::string(padding, ' '));
            output.append(std::format("{0:4}", entry->Length()));
            output.append(std::format("  {0}", entry->WhenModified().ToString()));
            output.append("\n");

            FileDirEntryList children = entry->Children();
            if (!children.empty())
            {
                for (int index = 0; index < children.size(); ++index)
                {
                    output.append(Composite_Exercise_FormatEntry(children[index].get(), depth + 1));
                }
            }

            return output;
        }


        /// <summary>
        /// Recursively display the contents of the hierarchical list of objects
        /// starting with the given object.
        /// </summary>
        /// <param name="entry">The file entry to display</param>
        void Composite_Exercise_ShowEntry(FileDirEntry* entry)
        {
            std::string output = Composite_Exercise_FormatEntry(entry, 2);
            std::cout << output << std::endl;
        }


        /// <summary>
        /// Example of using the Composite design pattern.
        /// 
        /// The Composite pattern is used when a collection of objects is to
        /// be formed in a hierarchical form where each object needs to be
        /// treated like any other object but some objects can contain other
        /// objects.
        /// 
        /// This example uses a file structure of file and directories to
        /// represent each object type.
        /// </summary>
        //! [Using Composite in C++]
        void Composite_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Composite Exercise" << std::endl;

            try
            {
                std::string filepath = "root";
                FileDirEntry* rootEntry = Composite_FileAccess::GetEntry(filepath);
                std::cout << "  Showing object '" << filepath << "'" << std::endl;
                Composite_Exercise_ShowEntry(rootEntry);

                filepath = "root/subdir1/FileD.txt";
                rootEntry = Composite_FileAccess::GetEntry(filepath);
                std::cout << "  Showing object '" << filepath << "'" << std::endl;
                Composite_Exercise_ShowEntry(rootEntry);
            }
            catch (std::filesystem::filesystem_error& e)
            {
                std::cout << "Error! filesystem_error: " << e.what() << std::endl;
            }

            std::cout << "  Done." << std::endl;
        }
        //! [Using Composite in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Decorator design pattern.
        /// 
        /// The Decorator pattern is used when a class instance at run time needs
        /// to have its behavior altered.  This is supported by providing wrapper
        /// classes called decorators that take instances of the IRenderElement
        /// interface.  All elements look the same and can therefore recursively
        /// wrap other decorators.  The base element never wraps anything and
        /// decorators must ultimately wrap a non-decorator class to be of any
        /// use.
        /// </summary>
        //! [Using Decorator in C++]
        void Decorator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Decorator Exercise" << std::endl;

            IRenderElement::shared_ptr_t baseElement;
            baseElement = std::make_shared<TextElement>("This is raw text");

            // Wrap the base element in three decorators.
            IRenderElement::shared_ptr_t wrappedElement =
                std::make_shared<WhiteBackgroundDecorator>(
                    std::make_shared<UnderlineDecorator>(
                        std::make_shared<RedForegroundDecorator>(baseElement)));

            // Now render the elements to the console.
            std::cout
                << std::format("  base Text element: \"{0}\"", baseElement->Render())
                << std::endl;
            std::cout
                << std::format("  Decorated element: \"{0}\"", wrappedElement->Render())
                << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Decorator in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Helper method to present a formatted list of idcodes for a particular
        /// device chain.  The output is on a single line.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain being displayed.</param>
        /// <param name="idcodes">Array of 32-bit idcodes to be printed in hex.</param>
        void _Facade_ShowIdCodes(int chainIndex, const std::vector<uint32_t>& idcodes)
        {
            std::cout << std::format("    On chain {0}, idcodes = [ ", chainIndex);
            for(uint32_t idcode : idcodes)
            {
                std::cout << std::format("0x{0:X} ", idcode);
            }
            std::cout << "]" << std::endl;
        }


        /// <summary>
        /// Example of using the Facade design pattern.
        /// 
        /// The Facade pattern is used when a simplified version of an
        /// interface on a complicated sub-system is needed in situations
        /// where the whole complicated sub-system does not need to be
        /// exposed.
        /// 
        /// In this example, the complicated subsystem is a representation of
        /// a device network complete with scan chains, device idcodes, and device
        /// devices that can be selected and deselected.  The Facade exposed
        /// by this complex network exposes only the scan chain, getting
        /// device idcodes based on an index into those scan chains, resetting
        /// the scan chains and selecting a device to appear in the scan
        /// chain.
        /// </summary>
        //! [Using Facade in C++]
        void Facade_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Facade Exercise" << std::endl;

            IDeviceNetworkHighLevel* deviceChainFacade = CreateHighLevelInstance();
            int numChains = deviceChainFacade->NumChains();
            std::cout
                << "  Showing idcodes of devices after a device reset (expect one device on each chain)..."
                << std::endl;
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade->DisableDevicesInDeviceChain(chainIndex);
                std::vector<uint32_t> idcodes = deviceChainFacade->GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }

            std::cout << "  Showing idcodes of devices after selecting all devices..."
                << std::endl;
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade->EnableDevicesInDeviceChain(chainIndex, 0xffffffff);
                std::vector<uint32_t> idcodes = deviceChainFacade->GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }

            std::cout << "  Done." << std::endl;
        }
        //! [Using Facade in C++]


        //########################################################################
        //########################################################################



        /// <summary>
        /// Generate a big resource, in this case, a text "image" of the specified
        /// width and height.  The image is a box.
        /// </summary>
        /// <param name="width">Width of the "text" image, in characters.  Minimum
        /// width is 3.</param>
        /// <param name="height">Height of the "text" image, in characters.  Minimum
        /// height is 3.</param>
        /// <returns>An index to the generated index in the BigResourceManager.</returns>
        int _Flyweight_GenerateBigResource(int width, int height)
        {
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
                std::string image_row;
                if (row == 0 || (row + 1) == height)
                {
                    // top and bottom row are the same.
                    image_row = std::format("+{0}+", std::string((size_t)width - 2, '-'));
                }
                else
                {
                    // All other rows are each the same.
                    image_row = std::format("|{0}|", std::string((size_t)width - 2, '0'));
                }
                image.push_back(image_row);
            }

            int resourceId = BigResourceManager::AddResource(image);
            return resourceId;
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
        /// Clear the "display" to a background image, erasing whatever was there before.
        /// </summary>
        /// <param name="display">A list of character arrays representing the display.</param>
        void _Flyweight_ClearDisplay(std::vector<std::vector<char>>& display)
        {
            for(std::vector<char>& row : display)
            {
                for (size_t index = 0; index < row.size(); ++index)
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
                Flyweight_Context context = (*flyweightIter)->Context();
                (*flyweightIter)->Render(displayArea,
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

        /// <summary>
        /// Example of using the Flyweight design pattern.
        /// 
        /// The Flyweight pattern is used when a large object needs to be
        /// represented by a much lighter weight class, possibly multiple
        /// instances of said light-weight class.
        /// 
        /// In this example, a large object is represented by a so-called "big
        /// resource" or image (a two-dimensional array of text characters).
        /// Flyweight classes that represent position and velocity are
        /// attached to the big resource image so they all share the same image
        /// but have different positions and velocities.  The image is rendered
        /// to a display area through the Flyweight class.  The Flyweight
        /// class instances then have their positions updated, bouncing off the
        /// edges of the display area 60 times a second.  This continues for
        /// 1000 iterations or until a key is pressed.
        /// </summary>
        //! [Using Flyweight in C++]
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

            int bigResourceId = _Flyweight_GenerateBigResource(IMAGE_WIDTH, IMAGE_HEIGHT);
            FlyweightClassList flyweightInstances;
            flyweightInstances = _Flyweight_GenerateFlyweightClasses(bigResourceId, NUMFLYWEIGHTS,
                IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT);

            // Create the "display".
            // We use a list of character arrays so we can write to each
            // character position individually.  In C#, strings are immutable
            // and changing a character in a string is not allowed.
            std::vector<std::vector<char>> displayArea = _Flyweight_GenerateDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);

            // Finally, display the rendered output.
            std::cout << std::format("  The image rendered {0} times:", NUMFLYWEIGHTS) << std::endl;
            std::cout << std::endl; // Blank line for iteration count
            _Flyweight_RenderFlyweights(flyweightInstances, displayArea);
            _Flyweight_ShowDisplay(displayArea);

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
                std::cout << std::format("  {0:5}/{1} iterations [press a key to exit early]", index + 1, NUM_ITERATIONS) << std::endl;
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

            std::cout << "  Done." << std::endl;
        }
        //! [Using Flyweight in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Proxy design pattern.
        /// 
        /// The Proxy pattern is used when a large or expensive object cannot be
        /// represented directly in the program, typically because the object is
        /// in another process or even another system altogether.
        /// 
        /// In this exercise, a Proxy class implements the same interface as the
        /// Real class, making the Proxy class look like the Real class.  Calls
        /// made on the Proxy class are passed to the Real class where the work
        /// is actually done (in this case, a munged string with the text
        /// "Real class received 'xxxx'".
        /// 
        /// The only difference in output here is one additional line for the
        /// first call showing the real class being instantiated.  The subsequent
        /// calls do not show this line.
        /// </summary>
        //! [Using Proxy in C++]
        void Proxy_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Proxy Exercise" << std::endl;

            std::cout << "  Getting proxy object..." << std::endl;
            std::unique_ptr<IWorkByProxy> proxyObject = Proxy_Classes_Container::CreateProxy();

            std::cout << "  Calling Dowork() on proxy..." << std::endl;
            std::string output = proxyObject->DoWork("Initial call");
            std::cout << std::format("  Output from proxy = \"{0}\"", output) << std::endl;

            std::cout << "  Calling Dowork() on proxy..." << std::endl;
            output = proxyObject->DoWork("Second call");
            std::cout << std::format("  Output from proxy = \"{0}\"", output) << std::endl;

            std::cout << "  Calling Dowork() on proxy..." << std::endl;
            output = proxyObject->DoWork("Third call");
            std::cout << std::format("  Output from proxy = \"{0}\"", output) << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Proxy in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Visitor design pattern.
        /// 
        /// The Visitor pattern is used to add functionality to a list of
        /// otherwise unchanging element objects by passing a function to each
        /// element object.  Each element object calls the function, passing
        /// itself to the function.  The visiting function then does something
        /// based on the type of the element.
        /// 
        /// In this exercise, a list of element objects is created then two
        /// visitors are created.  The visitors represent possible operations
        /// that can be done on the element types.  In this exercise, the
        /// operations just print out what was received.
        /// </summary>
        //! [Using Visitor in C++]
        void Visitor_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Visitor Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Visitor in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Command design pattern.
        /// 
        /// The Command pattern is used to encapsulate an operation or command
        /// associated with an object so that the command can be applied to
        /// the object at a later time.
        /// 
        /// In this exercise, an undo list is implemented using Commands that
        /// associate commands defined in this file with a text object.  The
        /// commands are applied to the text object in succession then
        /// effectively undone.
        /// </summary>
        //! [Using Command in C++]
        void Command_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Command Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Command in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Handle Chain or Chain of Responsibility design
        /// pattern.
        /// 
        /// The Handler Chain pattern is used to support a dynamic list of
        /// handlers that are passed the same arguments.  It is kind of the
        /// inverse of the Visitor pattern, where the Visitor pattern is a
        /// handler that is passed to all objects in a list and the Handler
        /// Chain pattern is an object passed to handlers in a list.
        ///
        /// In this exercise, multiple rectangular regions called
        /// MessageWindows embody the handlers and the HandlerChain object
        /// passes message objects to each MessageWindow until the message is
        /// handled.
        /// </summary>
        //! [Using HandlerChain in C++]
        void HandlerChain_Exercise()
        {
            std::cout << std::endl;
            std::cout << "HandlerChain Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using HandlerChain in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Interpreter design pattern.
        /// 
        /// The interpreter is instantiated then fed a series of arrays 
        /// containing integer tokens.  Each token represents a single word or
        /// punctuation mark.  The interpreter converts that array of tokens
        /// to an actual sentence by interpreting the meaning of the tokens.
        /// 
        /// This is a very simple interpreter that handles the first token in
        /// a special way and supports punctuation.  It is an example of a
        /// linear interpreter where tokens can appear in any order (it's up
        /// to the creator of the token list to make sure the outcome makes
        /// any sense).
        /// 
        /// The output shows the token list followed by the sentence produced
        /// from the tokens.
        /// </summary>
        //! [Using Interpreter in C++]
        void Interpreter_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Interpreter Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Interpreter in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Iterator design pattern.
        /// 
        /// A custom container is instantiated (it already contains harcoded data
        /// to iterate over).  The custom container can then deliver three
        /// iterators, each providing a different aspect of the hardcoded data.
        /// 
        /// The output shows the output from each iterator.
        /// </summary>
        //! [Using Iterator in C++]
        void Iterator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Iterator Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Iterator in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Mediator design pattern.
        /// 
        /// A mediator is instantiated then populated with users and groups.
        /// Users are added to some of the groups.
        /// 
        /// A series of operations are then performed through the mediator.
        /// The output shows the results of each operation.  Note that all
        /// operations are done using user and group names, with no knowledge
        /// of the actual lists of users and groups.  The mediator hides all
        /// the details.
        /// </summary>
        //! [Using Mediator in C++]
        void Mediator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Mediator Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Mediator in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Memento design pattern.
        /// 
        /// In this exercise, the Memento pattern is used to take snapshots of
        /// a text object so as to form an undo list of changes to the text
        /// object.  Undoing an operation means restoring a snapshot of the
        /// text object.
        /// 
        /// The undo list is implemented as a stack of memento objects that
        /// each represent a snapshot of the text object taken before each
        /// operation is applied.  After all operations are applied, the
        /// mementos are used to restore the text object in reverse order,
        /// effectively undoing each operation in turn.
        /// 
        /// Compare this to the Command_Exercise() and note that the steps
        /// taken there are identical to here (except for method names, of
        /// course).  The difference lies in how operations are executed
        /// and undone.  Mementos make the undo process much cleaner and
        /// faster since operations do not need to be applied repeatedly to
        /// get the text object into a specific state.  Specifically,
        /// compare Command_Undo() with Memento_Undo().  Also note the
        /// differences in the "Memento_ApplyXXOperation()" methods, which
        /// more cleanly separate the save from the operation.
        /// </summary>
        //! [Using Memento in C++]
        void Memento_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Memento Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Memento in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Null Object design pattern.
        /// 
        /// The Null Object pattern is where an object or function acts as a
        /// stand-in for real commands but otherwise does nothing.
        /// 
        /// In this exercise, movement commands are presented as characters in
        /// a string, with the characters 'u', 'd', 'l', and 'r' representing
        /// the moves "up", "down", "left", and "right", respectively.  To
        /// keep the processing of this string simple, all other characters in
        /// the string are assigned a Null Object ("Do Nothing") version of
        /// the move command.
        /// 
        /// This example displays the commands after parsing and then
        /// "executes" commands, which consists of printing the commands out.
        /// 
        /// This example highlights the Null Object pattern while utilizing
        /// the Command and Interpreter patterns.
        /// </summary>
        //! [Using NullObject in C++]
        void NullObject_Exercise()
        {
            std::cout << std::endl;
            std::cout << "NullObject Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using NullObject in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Observer design pattern.
        /// 
        /// The Observer pattern allows for one or more observers to react to
        /// changes in a Subject entity.
        /// 
        /// In this exercise, a number producer (the Subject) updates an internal
        /// value every time the Update() method is called.  Three different
        /// observers are attached to the number producer and print out the
        /// current value in different formats whenever the number is changed.
        /// 
        /// Note: Interfaces are used throughout this example.  For example, to
        /// subscribe to the number producer, the IEventNotifications interface
        /// must be obtained from the number producer.  The number producer is
        /// represented to the observers with the INumberProducer interface and
        /// the observers are represented to the number producer with the
        /// IObserverNumberChanged interface.  This highlights a common way to
        /// implement a "pull" style observer without having too much knowledge
        /// about the Subject.
        /// </summary>
        //! [Using Observer in C++]
        void Observer_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Observer Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Observer in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the State design pattern.
        /// 
        /// The State pattern alters the behavior of the class hierarchy based
        /// on some state.  This is the basis of a Finite State Machine.
        /// 
        /// In this exercise, the State class is a filter that parses text to
        /// remove C++-style line and block comments.  It needs to be smart
        /// enough to ignore comment characters inside quotes.
        /// 
        /// The filtering process starts with creating the context that drives
        /// the state machine.  Internal classes are provided for each state.
        /// </summary>
        //! [Using State in C++]
        void State_Exercise()
        {
            std::cout << std::endl;
            std::cout << "State Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using State in C++]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Strategy design pattern.
        /// 
        /// The Strategy pattern provides a way to easily assign different
        /// algorithms to a class instance that can be changed at the time the
        /// class is created.
        /// 
        /// In this exercise, the Strategy_ShowEntries_Class instance sorts
        /// and displays a list of EntryInformation elements.  Three different
        /// sorting strategies are provided (Name, Age, Height) and an option
        /// to reverse the normal order of the sort.
        /// </summary>
        //! [Using Strategy in C++]
        void Strategy_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Strategy Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }
        //! [Using Strategy in C++]


        //########################################################################
        //########################################################################

    public:

        /// <summary>
        /// Run the specified examples.
        /// </summary>
        /// <param name="args">Command line arguments.</param>
        void Run(StringList args)
        {
            ExerciseList exercises
            {
                // We use a lambda here that auto-binds to the "this" pointer ("[&]")
                // for this object so as to avoid complicated declarations and
                // bindings to class methods.
                Exercise("Adapter", [&] { Adapter_Exercise(); }),
                Exercise("Bridge",  [&] { Bridge_Exercise(); }),
                Exercise("Composite",  [&] { Composite_Exercise(); }),
                Exercise("Decorator",  [&] { Decorator_Exercise(); }),
                Exercise("Facade",  [&] { Facade_Exercise(); }),
                Exercise("Flyweight",  [&] { Flyweight_Exercise(); }),
                Exercise("Proxy",  [&] { Proxy_Exercise(); }),
                Exercise("Visitor",  [&] { Visitor_Exercise(); }),
                Exercise("Command",  [&] { Command_Exercise(); }),
                Exercise("HandlerChain",  [&] { HandlerChain_Exercise(); }),
                Exercise("Interpreter",  [&] { Interpreter_Exercise(); }),
                Exercise("Iterator",  [&] { Iterator_Exercise(); }),
                Exercise("Mediator",  [&] { Mediator_Exercise(); }),
                Exercise("Memento",  [&] { Memento_Exercise(); }),
                Exercise("NullObject",  [&] { NullObject_Exercise(); }),
                Exercise("Observer",  [&] { Observer_Exercise(); }),
                Exercise("State",  [&] { State_Exercise(); }),
                Exercise("Strategy",  [&] { Strategy_Exercise(); }),
            };

            Options options;
            if (ParseOptions(args, exercises, options))
            {
                for (Exercise exercise : exercises)
                {
                    bool runExercise = options.exercise_names.empty();
                    if (!runExercise)
                    {
                        auto foundIter = std::find(
                            std::begin(options.exercise_names),
                            std::end(options.exercise_names),
                            exercise.name);
                        runExercise = (foundIter != std::end(options.exercise_names));
                    }
                    if (runExercise)
                    {
                        exercise.exercise_to_run();
                    }
                }
            }
        }
    };

} // end namespace

//########################################################################
//########################################################################


/// <summary>
/// Main entry point into this example program.
/// </summary>
/// <param name="argc">Number of command line arguments + 1 (the first argument
/// is the name of the program).</param>
/// <param name="argv">Pointer to a list of zero-terminated strings containing
/// the command line arguments.</param>
int main(int argc, char** argv)
{
    Helpers::enableVTMode();

    srand(static_cast<unsigned int>(time(nullptr)));
    DesignPatternExamples_cpp::Program prog;
    StringList args;
    for (int argIndex = 1; argIndex < argc; ++argIndex)
    {
        args.push_back(std::string(argv[argIndex]));
    }

    prog.Run(args);

    return EXIT_SUCCESS;
}
