using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPatternExamples_csharp
{
    class Program
    {
        //########################################################################
        //########################################################################


        /// <summary>
        /// Example of using the Adapter design pattern.
        /// 
        /// This example adapts functions that return error codes into a class object
        /// that throws exceptions, which is more fitting of an object-oriented
        /// language.
        /// </summary>
        //! [Using Adapter in C#]
        void Adapter_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Adapter Exercise");
            try
            {
                // Will call Dispose() automatically when exiting the using block
                using (var dataReaderWriter = new DataReaderWriter("-target BXT"))
                {
                    // Create the data to be written
                    uint dataSize = 128;
                    byte[] writeData = new byte[dataSize];
                    for (int index = 0; index < dataSize; ++index)
                    {
                        writeData[index] = (byte)index;
                    }

                    // Display the data to be written
                    string dataDump = dataReaderWriter.BufferToString(writeData, dataSize, 2);
                    Console.WriteLine("  Data written:{0}{1}", Environment.NewLine, dataDump);

                    // Write the data to the external component
                    dataReaderWriter.Write(writeData, dataSize);

                    // Read the data from the external component
                    byte[] readData = dataReaderWriter.Read(dataSize);

                    // Display the data read back.  Should be the same as was written.
                    dataDump = dataReaderWriter.BufferToString(readData, dataSize, 2);
                    Console.WriteLine("  Data read:{0}{1}", Environment.NewLine, dataDump);
                }

            }
            catch(DataReaderWriterInitException e)
            {
                Console.WriteLine("Error with startup or shutdown! {0}", e.Message);
            }
            catch(DataReaderWriterException e)
            {
                Console.WriteLine("Error with reading or writing! {0}", e.Message);
            }
            Console.WriteLine("  Done.");
        }
        //! [Using Adapter in C#]


        //########################################################################
        //########################################################################


        /// <summary>
        /// Helper function to show an example of writing to a logger.
        /// 
        /// This is called for all types of loggers, showing how the Logger
        /// class hides the details of the underlying implementation.
        /// </summary>
        /// <param name="logger">A Logger instance to log to</param>
        /// <param name="loggerType">The type of the underlying implementation.</param>
        void _Bridge_Exercise_Demonstrate_Logging(Logger logger, string loggerType)
        {
            logger.LogTrace(String.Format("Starting log to {0} example", loggerType));
            logger.LogInfo("An example of an informational line");
            logger.LogError("An example of an error log entry");
            logger.LogTrace(String.Format("Done with log to {0} example", loggerType));
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
        //! [Using Bridge in C#]
        void Bridge_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Bridge Exercise");
            using (Logger logger = new Logger(Logger.LoggerTypes.ToFile, "Bridge.log"))
            {
                Console.WriteLine("  Example of writing to a log file...");
                _Bridge_Exercise_Demonstrate_Logging(logger, "file");
            }

            using (Logger logger = new Logger(Logger.LoggerTypes.ToConsole))
            {
                Console.WriteLine("  Example of writing to the console...");
                _Bridge_Exercise_Demonstrate_Logging(logger, "console");
            }

            using (Logger logger = new Logger(Logger.LoggerTypes.ToNull))
            {
                Console.WriteLine("  Example of writing to a Null object (no output)...");
                // Note: The resulting log lines will not be shown anywhere.
                _Bridge_Exercise_Demonstrate_Logging(logger, "null");
            }
            Console.WriteLine("  Done.");
        }
        //! [Using Bridge in C#]


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
        string Composite_Exercise_FormatEntry(FileDirEntry entry, int depth)
        {
            const int NAME_PADDING_SIZE = 20;
            StringBuilder output = new StringBuilder();
            string spaces = new string(' ', depth * 2);
            output.AppendFormat("{0}{1}", spaces, entry.Name);
            int padding = NAME_PADDING_SIZE - entry.Name.Length - (depth * 2);
            if (entry.FileDirType == FileDirTypes.Directory)
            {
                output.Append("/");
                padding--;
            }
            output.AppendFormat("{0}", new string(' ', padding));
            output.AppendFormat("{0,4}", entry.Length);
            output.AppendFormat("  {0}", entry.WhenModified.ToString());
            output.AppendFormat("{0}", Environment.NewLine);

            FileDirEntry[] children = entry.Children;
            if (children != null)
            {
                for (int index = 0; index < children.Length; ++index)
                {
                    output.AppendFormat(Composite_Exercise_FormatEntry(children[index], depth + 1));
                }
            }

            return output.ToString();
        }


        /// <summary>
        /// Recursively display the contents of the hierarchical list of objects
        /// starting with the given object.
        /// </summary>
        /// <param name="entry"></param>
        void Composite_Exercise_ShowEntry(FileDirEntry entry)
        {
            string output = Composite_Exercise_FormatEntry(entry, 2);
            Console.WriteLine(output);
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
        //! [Using Composite in C#]
        void Composite_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Composite Exercise");
            try
            {
                string filepath = "root";
                FileDirEntry rootEntry = Composite_FileAccess.GetEntry(filepath);
                Console.WriteLine("  Showing object '{0}'", filepath);
                Composite_Exercise_ShowEntry(rootEntry);

                filepath = "root/subdir1/FileD.txt";
                rootEntry = Composite_FileAccess.GetEntry(filepath);
                Console.WriteLine("  Showing object '{0}'", filepath);
                Composite_Exercise_ShowEntry(rootEntry);
            }
            catch(System.IO.FileNotFoundException e)
            {
                Console.WriteLine("{0}: {1}", e.GetType().Name, e.Message);
            }
            Console.WriteLine("  Done.");
        }
        //! [Using Composite in C#]


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
        //! [Using Decorator in C#]
        void Decorator_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Decorator Exercise");
            IRenderElement baseElement = new TextElement("This is raw text");

            // Wrap the base element in three decorators.
            IRenderElement wrappedElement =
                new WhiteBackgroundDecorator(
                    new UnderlineDecorator(
                        new RedForegroundDecorator(baseElement)));

            // Now render the elements to the console.
            Console.WriteLine("  base Text element: \"{0}\"", baseElement.Render());
            Console.WriteLine("  Decorated element: \"{0}\"", wrappedElement.Render());
            Console.WriteLine("  Done.");
        }
        //! [Using Decorator in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// Helper method to present a formatted list of idcodes for a particular
        /// device chain.  The output is on a single line.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain being displayed.</param>
        /// <param name="idcodes">Array of 32-bit idcodes to be printed in hex.</param>
        void _Facade_ShowIdCodes(int chainIndex, uint[] idcodes)
        {
            Console.Write("    On chain {0}, idcodes = [ ", chainIndex);
            foreach (uint idcode in idcodes)
            {
                Console.Write("0x{0:X} ", idcode);
            }
            Console.WriteLine("]");
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
        //! [Using Facade in C#]
        void Facade_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Facade Exercise");

            IDeviceNetworkHighLevel deviceChainFacade = Facade_ComplicatedSubSystemFactory.CreateHighLevelInstance();
            int numChains = deviceChainFacade.NumChains;
            Console.WriteLine("  Showing idcodes of devices after a device reset (expect one device on each chain)...");
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade.DisableDevicesInDeviceChain(chainIndex);
                uint[] idcodes = deviceChainFacade.GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }

            Console.WriteLine("  Showing idcodes of devices after selecting all devices...");
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade.EnableDevicesInDeviceChain(chainIndex, 0xffffffff);
                uint[] idcodes = deviceChainFacade.GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }
            Console.WriteLine("  Done.");
        }
        //! [Using Facade in C#]

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

            List<string> image = new List<string>();
            for (int row = 0; row < height; ++row)
            {
                string image_row;
                if (row == 0 || (row + 1) == height)
                {
                    // top and bottom row are the same.
                    image_row = "+" + new string('-', width - 2) + "+";
                }
                else
                {
                    // All other rows are each the same.
                    image_row = '|' + new string('0', width - 2) + '|';
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
            foreach(char[] row in display)
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
            foreach(Flyweight_Class flyweight in flyweightInstances)
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
                // Make sure the entire image can be rendered at each position
                context.Position_X = randomizer.Next(0, display_width - image_width);
                context.Position_Y = randomizer.Next(0, display_height - image_height);
                // Randomize the initial velocity.
                context.Velocity_X = GenerateVelocity(randomizer);
                context.Velocity_Y = GenerateVelocity(randomizer);

                // Create an instance of the Flyweight_Class for the given big
                // resource and with the new context.
                Flyweight_Class flyweightInstance = BigResourceManager.CreateFlyweight(bigResourceId, context);
                flyweightInstances.Add(flyweightInstance);
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
        //! [Using Flyweight in C#]
        void Flyweight_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Flyweight Exercise");

            // Define the display and image size.
            const int DISPLAY_WIDTH  = 80;
            const int DISPLAY_HEIGHT = 20;
            const int IMAGE_WIDTH = 30;
            const int IMAGE_HEIGHT = 5;
            const int NUMFLYWEIGHTS = 5;
            const int NUM_ITERATIONS = 1000;

            int bigResourceId = _Flyweight_GenerateBigResource(IMAGE_WIDTH, IMAGE_HEIGHT);
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
        //! [Using Flyweight in C#]

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
        //! [Using Proxy in C#]
        void Proxy_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Proxy Exercise");

            Console.WriteLine("  Getting proxy object...");
            IWorkByProxy proxyObject = Proxy_Classes_Container.CreateProxy();

            Console.WriteLine("  Calling Dowork() on proxy...");
            string output = proxyObject.DoWork("Initial call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);

            Console.WriteLine("  Calling Dowork() on proxy...");
            output = proxyObject.DoWork("Second call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);

            Console.WriteLine("  Calling Dowork() on proxy...");
            output = proxyObject.DoWork("Third call");
            Console.WriteLine("  Output from proxy = \"{0}\"", output);
            Console.WriteLine("  Done.");
        }
        //! [Using Proxy in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// Example of using the Visitor design pattern.
        /// 
        /// The Visitor pattern is used to add functionality to a list of
        /// otherwise unchanging element objects by passing a visitor object to
        /// each element object.  Each element object calls the visitor object,
        /// passing itself as an argument.  The visitor object then does
        /// something based on the type of the element.
        /// 
        /// In this exercise, a collection of shop objects is initialized then
        /// an order visitor is created to retrieve an item from one of the shop
        /// objects.  Along the way, shops that don't have the necessary
        /// ingredients use another order visitor to order ingredients from
        /// other shops.  This approach assumes no two shops sell the same
        /// thing.
        /// </summary>
        //! [Using Visitor in C#]
        void Visitor_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Visitor Exercise");

            Console.WriteLine("  Creating Village");
            Village village = new Village();
            village.LoadVillage();

            OrderVisitor visitor = new OrderVisitor(new string[] { "hamburger"} );
            Console.WriteLine("  Ordering a hamburger from a shop in the {0}", village.Name);
            // Visit all shops and place an order for a hamburger at the shop
            // that sells them.  We don't know which shop it is and we don't
            // need to know until we receive the order.
            village.Accept(visitor);
            if (visitor.ItemsReceived.Count > 0)
            {
                // We are expecting only a single item
                Console.WriteLine("  We received a {0} from {1}.",
                    visitor.ItemsReceived[0], visitor.ShopNameReceivedFrom);
            }
            else
            {
                Console.WriteLine("  Failed to receive a hamburger");
            }

            Console.WriteLine("  Done.");
        }
        //! [Using Visitor in C#]


        //########################################################################
        //########################################################################


        /// <summary>
        /// The list of commands applied.
        /// </summary>
        Stack<Command> _commandUndoList;

        /// <summary>
        /// Save the given command on the undo list then execute the command on
        /// the given text object.
        /// </summary>
        /// <param name="text">The Command_TextObject on which to apply the command.</param>
        /// <param name="command">The Command object to apply to the text object.</param>
        void Command_Save_And_Execute(Command_TextObject text, Command command)
        {
            _commandUndoList.Push(command);
            command.Execute();
        }

        /// <summary>
        /// An operation to search and replace text in a Command_TextObject.
        /// </summary>
        /// <param name="source">The Command_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Command_Operation_Replace(Command_TextObject source, string searchPattern, string replaceText)
        {
            source.Text = source.Text.Replace(searchPattern, replaceText);
        }

        /// <summary>
        /// An operation to reverse the characters in the given Command_TextObject.
        /// </summary>
        /// <param name="source">The Command_TextObject to affect.</param>
        void Command_Operation_Reverse(Command_TextObject source)
        {
            StringBuilder output = new StringBuilder();
            string text = source.Text;
            for (int index = 0; index < text.Length; ++index)
            {
                output.Append(text[text.Length - 1 - index]);
            }
            source.Text = output.ToString();
        }

        /// <summary>
        /// Perform an undo on the given Command_TextObject, using the commands in the
        /// "global" undo list.  If the undo list is empty, nothing happens.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Command_Undo(Command_TextObject text)
        {
            if (_commandUndoList.Count > 0)
            {
                // Reset the text to the starting point.
                text.Reset();
                
                // Get rid of the last command applied and remember it.
                Command lastCommand = _commandUndoList.Pop();

                // Now apply all remaining commands to the text in order.
                foreach (Command command in _commandUndoList)
                {
                    command.Execute();
                }

                // Show off what we (un)did.
                Console.WriteLine("    undoing command {0,-31}: \"{1}\"", lastCommand, text);
            }
        }

        /// <summary>
        /// Helper function to create a Command object that replaces text in the given
        /// Command_TextObject, adds the command to the undo list and then applies the command
        /// to the Command_TextObject.  Finally, it shows off what was done.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Command_ApplyReplaceCommand(Command_TextObject text, string searchPattern, string replaceText)
        {
            Command command = new Command(text, "Replace", Command_Operation_Replace, searchPattern, replaceText);
            Command_Save_And_Execute(text, command);
            Console.WriteLine("    command {0,-31}: \"{1}\"", command, text);
        }


        /// <summary>
        /// Helper function to create a Command object that reverses the order of
        /// the characters in the given Command_TextObject, adds the command to the undo
        /// list and then applies the command to the Command_TextObject.  Finally, it shows
        /// what was done.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Command_ApplyReverseCommand(Command_TextObject text)
        {
            Command command = new Command(text, "Reverse", Command_Operation_Reverse);
            Command_Save_And_Execute(text, command);
            Console.WriteLine("    command {0,-31}: \"{1}\"", command, text);
        }


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
        //! [Using Command in C#]
        void Command_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Command Exercise");

            // Start with a fresh undo list.
            _commandUndoList = new Stack<Command>();

            // The base text object to work from.
            Command_TextObject text = new Command_TextObject("This is a line of text on which to experiment.");

            Console.WriteLine("  Starting text: \"{0}\"", text);

            // Apply four operations to the text.
            Command_ApplyReplaceCommand(text, "text", "painting");
            Command_ApplyReplaceCommand(text, "on", "off");
            Command_ApplyReverseCommand(text);
            Command_ApplyReplaceCommand(text, "i", "!");

            Console.WriteLine("  Now perform undo until back to original");

            // Now undo the four operations.
            Command_Undo(text);
            Command_Undo(text);
            Command_Undo(text);
            Command_Undo(text);

            Console.WriteLine("  Final text   : \"{0}\"", text);

            Console.WriteLine("  Done.");
        }
        //! [Using Command in C#]

        //########################################################################
        //########################################################################

        /// <summary>
        /// Helper method to construct a list of windows.  Messages will be passed 
        /// to these windows via the HandlerChain object.
        /// </summary>
        /// <param name="handlerChain">The HandlerChain object that receives the
        /// new windows.</param>
        void _HandlerChain_ConstructWindowChain(HandlerChain handlerChain)
        {
            // Note: This creates each window and adds the new window to the given
            // HandlerChain object.
            //
            // This example doesn't care about each individual window so the
            // return value is ignored.
            MessageWindow.CreateWindow("Window 1", 0, 0, 10, 10, handlerChain);
            MessageWindow.CreateWindow("Window 2", 20, 0, 5, 5, handlerChain);
            MessageWindow.CreateWindow("Window 3", 30, 10, 15, 15, handlerChain);
        }

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
        //! [Using HandlerChain in C#]
        void HandlerChain_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Handler Chain Exercise");

            // Construct a handler chain and populate with windows that can
            // handle messages.
            HandlerChain handlerChain = new HandlerChain();
            _HandlerChain_ConstructWindowChain(handlerChain);

            Console.WriteLine("  Handler Chain at start:");
            Console.WriteLine(handlerChain);

            // Now pass messages to the windows.

            Console.WriteLine("  Select Window 2");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(22, 1)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(22, 1)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Select Window 3");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(35, 11)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(35, 11)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Select Window 1");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(4, 4)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(4, 4)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Close Window 2");
            handlerChain.SendMessage(new Message(MessageType.ButtonDown, new MessagePosition(24, 0)));
            handlerChain.SendMessage(new Message(MessageType.ButtonUp, new MessagePosition(24, 0)));
            Console.WriteLine("  Current handler chain:");
            Console.WriteLine(handlerChain);

            Console.WriteLine("  Done.");
        }
        //! [Using HandlerChain in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// Helper method to convert a list of ints to a string representation.
        /// </summary>
        /// <param name="tokens">Array of ints to work with.</param>
        /// <returns>A string representation of the integer list.</returns>
        string _TokensToString(int[] tokens)
        {
            StringBuilder output = new StringBuilder();

            output.Append("[");
            for (int index = 0; index < tokens.Length; ++index)
            {
                output.AppendFormat("{0,3}", tokens[index]);
                if (index + 1 < tokens.Length)
                {
                    output.Append(", ");
                }
            }
            output.Append("]");
            return output.ToString();
        }


        /// <summary>
        /// A list of pre-defined token lists.  Each token list represents
        /// a single sentence constructed from the 40 most common words in
        /// the English language.  I don't use all 40 words, though; that
        /// would be silly.
        /// </summary>
        static int[][] _sentenceTokenLists = new int[][] {
            new int[] { 39, 18, 17, 27, 2, 7, 101 }, // "What do you say to that?"
            new int[] { 32, 17, 1, 0, 34, 2, 1, 37, 101 }, // "Will you be the one to be there?"
            new int[] { 36, 17, 8, 5, 32, 2, 18, 7, 101 }, // "Would you have a will to do that?"
            new int[] { 11, 12, 17, 9, 36, 12, 1, 6, 20, 100 }, // "For not you I would not be in this."
            new int[] { 26, 27, 7, 21, 36, 17, 27, 10, 101 }, // "We say that but would you say it?"
            new int[] { 23, 28, 32, 26, 32, 18, 10, 100 } // "By her will we will do it."
        };

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
        //! [Using Interpreter in C#]
        void Interpreter_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Interpreter Exercise");

            Interpreter_Class interpreter = new Interpreter_Class();

            for (int sentenceIndex = 0; sentenceIndex < _sentenceTokenLists.Length; ++sentenceIndex)
            {
                int[] tokenList = _sentenceTokenLists[sentenceIndex];

                string tokensAsString = _TokensToString(tokenList);

                string sentence = interpreter.Interpret(tokenList);

                // 50 is a magic number corresponding to the longest token list
                // expressed as a string.  Derived empirically.  It makes the
                // output easier to, er, interpret.
                Console.WriteLine("  {0,-50} ==> \"{1}\"", tokensAsString, sentence);
            }
            Console.WriteLine("  Done.");
        }
        //! [Using Interpreter in C#]

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
        //! [Using Iterator in C#]
        void Iterator_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Iterator Exercise");

            // For this example, the class already has built into it the data
            // to be iterated over.
            IteratorContainer_Class items = new IteratorContainer_Class();

            Console.WriteLine("  Iterating over keys only:");
            var keyIterator = items.GetKeys();
            for (string item = keyIterator.Next(); item != null; item = keyIterator.Next())
            {
                Console.WriteLine("    {0}", item);
            }

            Console.WriteLine("  Iterating over values only:");
            var valueIterator = items.GetValues();
            for (string item = valueIterator.Next(); item != null; item = valueIterator.Next())
            {
                Console.WriteLine("    {0}", item);
            }

            Console.WriteLine("  Iterating over all items:");
            var itemIterator = items.GetItems();
            for (ItemPair item = itemIterator.Next(); item != null; item = itemIterator.Next())
            {
                Console.WriteLine("    {0} = {1}", item.Key, item.Value);
            }

            Console.WriteLine("  Done.");
        }
        //! [Using Iterator in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// Helper method to convert a list of strings to a comma-delimited
        /// list in a single string.
        /// </summary>
        /// <param name="items">The list of strings to convert.</param>
        /// <returns>A string contaiing a comma-delimited format of strings.</returns>
        string _StringListToCommaArray(string[] items)
        {
            StringBuilder output = new StringBuilder();
            for (int index = 0; index < items.Length; ++index)
            {
                if (index != 0)
                {
                    output.Append(", ");
                }
                output.Append(items[index]);
            }
            return output.ToString();
        }

        /// <summary>
        /// Helper method to add a number of users to the Users list.
        /// </summary>
        /// <param name="mediator">The mediator object that owns the list of users.</param>
        void Mediator_SetupUsers(UserGroupMediator mediator)
        {
            mediator.AddUser("Stephen");
            mediator.AddUser("Gladys");
            mediator.AddUser("Marvin");
            mediator.AddUser("Arthur");
        }

        /// <summary>
        /// Helper method to add a number of groups to the Groups list and
        /// then add users to the groups.  Note that everything here is done
        /// with names.
        /// </summary>
        /// <param name="mediator">The mediator object that owns the list of groups.</param>
        void Mediator_SetupGroups(UserGroupMediator mediator)
        {
            mediator.AddGroup("admins");
            mediator.AddGroup("Users");
            mediator.AddGroup("Power Users");

            mediator.AddUserToGroup("Marvin", "admins");
            mediator.AddUserToGroup("Arthur", "admins");
            mediator.AddUserToGroup("Stephen", "Users");
            mediator.AddUserToGroup("Gladys", "Users");
            mediator.AddUserToGroup("Arthur", "Power Users");
            mediator.AddUserToGroup("Marvin", "Power Users");
        }

        /// <summary>
        /// Example of using the Mediator design pattern.
        /// 
        /// A mediator is instantiated then populated with users and groups.
        /// Users are added to some of the groups.
        /// 
        /// A series of operations are then performed through the mediator.
        /// The output shows the results of each operation.  Note that all
        /// operations are done using user and group names, with no knowledge
        /// of the actual lists of users and groups.  The medaitor hides all
        /// the details.
        /// </summary>
        //! [Using Mediator in C#]
        void Mediator_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Mediator Exercise");
            UserGroupMediator mediator = new UserGroupMediator();

            Mediator_SetupUsers(mediator);
            Mediator_SetupGroups(mediator);

            Console.WriteLine("  Operation 1: Show all groups");
            Console.WriteLine("    All groups: {0}", _StringListToCommaArray(mediator.GetAllGroups()));

            Console.WriteLine("  Operation 2: Show all users");
            Console.WriteLine("    All users : {0}", _StringListToCommaArray(mediator.GetAllUsers()));

            Console.WriteLine("  Operation 3: Determine if a user is a member of a specific group.");
            string userName = "Arthur";
            string groupName = "admins";
            Console.Write("    Is user '{0}' in the '{1}' group?", userName, groupName);
            Console.WriteLine("  {0}", mediator.IsUserInGroup(userName, groupName) ? "Yes": "No");

            Console.WriteLine("  Operation 4: Show all users in a specific group.");
            groupName = "Users";
            string[] userNames = mediator.GetUsersInGroup(groupName);
            Console.WriteLine("    All users in '{0}' group: {1}", groupName, _StringListToCommaArray(userNames));

            Console.WriteLine("  Operation 5: Show all groups containing a specific user.");
            userName = "Marvin";
            string[] groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("    All groups with user '{0}': {1}", userName, _StringListToCommaArray(groupNames));

            Console.WriteLine("  Operation 6: Remove a user from a group.");
            userName = "Marvin";
            groupName = "Power Users";
            mediator.RemoveUserFromGroup(userName, groupName);
            Console.WriteLine("    Removed user '{0}' from group '{1}'", userName, groupName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      All groups with user '{0}': {1}", userName, _StringListToCommaArray(groupNames));

            Console.WriteLine("  Operation 7: Add a user to a group.");
            groupName = "Users";
            Console.WriteLine("    Adding user '{0}' to group '{1}'.", userName, groupName);
            mediator.AddUserToGroup(userName, groupName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      All groups with user '{0}': {1}", userName, _StringListToCommaArray(groupNames));

            Console.WriteLine("  Operation 8: Remove a user from all groups.");
            userName = "Arthur";
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("    Removing user '{0}' from all groups.", userName);
            Console.WriteLine("      Start: all groups with user '{0}': {1}", userName, _StringListToCommaArray(groupNames));
            Console.WriteLine("      Removing...");
            mediator.RemoveUserFromAllGroups(userName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      End: all groups with user '{0}': {1}", userName, _StringListToCommaArray(groupNames));

            Console.WriteLine("  Operation 9: Remove a user (also removes the user from all groups).");
            userName = "Marvin";
            Console.WriteLine("    Removing user '{0}'.", userName);
            mediator.RemoveUser(userName);
            Console.WriteLine("      All users : {0}", _StringListToCommaArray(mediator.GetAllUsers()));
            groupNames = mediator.GetAllGroups();
            foreach(string name in groupNames)
            {
                userNames = mediator.GetUsersInGroup(name);
                Console.WriteLine("      Users in group '{0}': {1}", name, _StringListToCommaArray(userNames));
            }

            Console.WriteLine("  Done.");
        }
        //! [Using Mediator in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// The list of memento objects that form a series of snapshots in time
        /// of a Memento_TextObject.
        /// </summary>
        Stack<IMemento> _mementoUndoList;

        /// <summary>
        /// Take a snapshot of the given text object associated with the name of
        /// given operation.
        /// </summary>
        /// <param name="text">The Memento_TextObject to take a snapshot of.</param>
        /// <param name="operation">A string describing the operation that will
        /// be applied after the snapshot is taken.</param>
        void Memento_SaveForUndo(Memento_TextObject text, string operation)
        {
            IMemento memento = text.GetMemento(operation);
            _mementoUndoList.Push(memento);
        }


        /// <summary>
        /// An operation to search and replace text in a Memento_TextObject.
        /// </summary>
        /// <param name="source">The Memento_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Memento_Operation_Replace(Memento_TextObject source, string searchPattern, string replaceText)
        {
            source.Text = source.Text.Replace(searchPattern, replaceText);
        }

        /// <summary>
        /// An operation to reverse the characters in the given Memento_TextObject.
        /// </summary>
        /// <param name="source">The Memento_TextObject to affect.</param>
        void Memento_Operation_Reverse(Memento_TextObject source)
        {
            StringBuilder output = new StringBuilder();
            string text = source.Text;
            for (int index = 0; index < text.Length; ++index)
            {
                output.Append(text[text.Length - 1 - index]);
            }
            source.Text = output.ToString();
        }

        /// <summary>
        /// Perform an undo on the given Command_TextObject, using the mementos in the
        /// "global" undo list.  If the undo list is empty, nothing happens.
        /// </summary>
        /// <param name="text">The Command_TextObject to affect.</param>
        void Memento_Undo(Memento_TextObject text)
        {
            if (_mementoUndoList.Count > 0)
            {
                IMemento lastMemento = _mementoUndoList.Pop();
                text.RestoreMemento(lastMemento);

                // Show off what we (un)did.
                Console.WriteLine("    undoing operation {0,-31}: \"{1}\"", lastMemento.Name, text);
            }
        }

        /// <summary>
        /// Helper function to replace a pattern with another string in the
        /// given Memento_TextObject after adding a snapshot of the text
        /// object to the undo list.  Finally, it shows off what was done.
        /// </summary>
        /// <param name="text">The Memento_TextObject to affect.</param>
        /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
        /// <param name="replaceText">What to replace the searchPattern with.</param>
        void Memento_ApplyReplaceOperation(Memento_TextObject text, string searchPattern, string replaceText)
        {
            string operationName = String.Format("Replace '{0}' with '{1}'", searchPattern, replaceText);
            Memento_SaveForUndo(text, operationName);
            Memento_Operation_Replace(text, searchPattern, replaceText);
            Console.WriteLine("    operation {0,-31}: \"{1}\"", operationName, text);
        }


        /// <summary>
        /// Helper function to reverse the order of the characters in the
        /// given Memento_TextObject after adding a snapshot of the text
        /// object to an undo list.  Finally, it shows what was done.
        /// </summary>
        /// <param name="text">The Memento_TextObject to affect.</param>
        void Memento_ApplyReverseOperation(Memento_TextObject text)
        {
            string operationName = "Reverse";
            Memento_SaveForUndo(text, operationName);
            Memento_Operation_Reverse(text);
            Console.WriteLine("    operation {0,-31}: \"{1}\"", operationName, text);
        }

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
        //! [Using Memento in C#]
        void Memento_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Memento Exercise");

            // Start with a fresh undo list.
            _mementoUndoList = new Stack<IMemento>();

            // The base text object to work from.
            Memento_TextObject text = new Memento_TextObject("This is a line of text on which to experiment.");

            Console.WriteLine("  Starting text: \"{0}\"", text);

            // Apply four operations to the text.
            Memento_ApplyReplaceOperation(text, "text", "painting");
            Memento_ApplyReplaceOperation(text, "on", "off");
            Memento_ApplyReverseOperation(text);
            Memento_ApplyReplaceOperation(text, "i", "!");

            Console.WriteLine("  Now perform undo until back to original");

            // Now undo the four operations.
            Memento_Undo(text);
            Memento_Undo(text);
            Memento_Undo(text);
            Memento_Undo(text);

            Console.WriteLine("  Final text   : \"{0}\"", text);

            Console.WriteLine("  Done.");
        }
        //! [Using Memento in C#]

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
        //! [Using NullObject in C#]
        void NullObject_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Null Object Exercise");

            MoveProcessor moveProcessor = new MoveProcessor();

            // A stream of recognized and unrecognized move commands.  The
            // unrecognized commands do nothing.
            string moveString = "ur#ld!lr";
            Console.WriteLine("  Showing the move commands:");
            moveProcessor.ShowMoveList(moveString);

            Console.WriteLine("  Executing the move commands:");
            Console.Write("    {0} -> ", moveString);
            moveProcessor.ExecuteMoveList(moveString);

            Console.WriteLine("  Done.");
        }
        //! [Using NullObject in C#]

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
        //! [Using Observer in C#]
        void Observer_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Observer Exercise");

            ObserverSubject_NumberProducer numberProducer = new ObserverSubject_NumberProducer();

            // The number producer is passed to the observers so the observers
            // can get the number to display.  The observers only see the
            // INumberProducer interface, to minimize knowledge about the
            // Subject.
            ObserverForDecimal observerDecimal = new ObserverForDecimal(numberProducer);
            ObserverForHexaDecimal observerHexadecimal = new ObserverForHexaDecimal(numberProducer);
            ObserverForBinary observerBinary = new ObserverForBinary(numberProducer);

            // Tell the number producer about the observers who are notified
            // whenever the value changes.
            IEventNotifications eventNotifier = numberProducer as IEventNotifications;
            eventNotifier.SubscribeToNumberChanged(observerDecimal);
            eventNotifier.SubscribeToNumberChanged(observerHexadecimal);
            eventNotifier.SubscribeToNumberChanged(observerBinary);

            // Call the number producer's Update() method a number of times.
            // The observers automatically print out the current value in
            // different bases.
            for (int index = 0; index < 10; ++index)
            {
                Console.WriteLine("  Update {0} on number producer.  Results from observers:", index);
                numberProducer.Update();
            }

            // When done, remove the observers from the number producer.
            // It's always good to clean up after ourselves.
            eventNotifier.UnsubscribeFromNumberChanged(observerDecimal);
            eventNotifier.UnsubscribeFromNumberChanged(observerHexadecimal);
            eventNotifier.UnsubscribeFromNumberChanged(observerBinary);

            Console.WriteLine("  Done.");
        }
        //! [Using Observer in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// Helper method to display text from the State exercise.  Text is
        /// displayed with line numbers.
        /// </summary>
        /// <param name="textToDisplay">Text to display.</param>
        void _State_DisplayText(string textToDisplay)
        {
            string[] lines = textToDisplay.Split('\n');
            int lineNumber = 1;
            foreach(string line in lines)
            {
                Console.WriteLine("    {0,2}) {1}", lineNumber, line);
                ++lineNumber;
            }
        }


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
        //! [Using State in C#]
        void State_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("State Exercise");

            StateContext_Class filterContext = new StateContext_Class();
            string textToFilter = "//########################################################################\n" +
                                  "//########################################################################\n" +
                                  "// A comment.  /* A nested comment */\n" + 
                                  "\n" +
                                  "void State_Exercise() // An exercise in state machines\n" +
                                  "{\n" +
                                  "    char character = '\\\"';\n" +
                                  "    Console.WriteLine();\n" +
                                  "    Console.WriteLine(\"\\\"State\\\" /*Exercise*/\");\n" +
                                  "\n" +
                                  "    StateContext_Class filterContext = new StateContext_Class();\n" +
                                  "\n" +
                                  "    Console.WriteLine(\"\\t\\tDone. //(No, really)//\");\n" +
                                  "}";

            Console.WriteLine("  Text to filter:");
            _State_DisplayText(textToFilter);

            Console.WriteLine("  Filtering text...");
            string filteredText = filterContext.RemoveComments(textToFilter);

            Console.WriteLine("  Filtered text:");
            _State_DisplayText(filteredText);

            Console.WriteLine("  Done.");
        }
        //! [Using State in C#]


        //########################################################################
        //########################################################################

        /// <summary>
        /// List of individuals to play around with in the Strategy exercise.
        /// </summary>
        EntryInformation[] entries =
        {
            // Name, age, height (in inches)
            new EntryInformation("Ronnie", 19, 84),
            new EntryInformation("Elaine", 29, 78),
            new EntryInformation("Jack", 20, 81),
            new EntryInformation("Myra", 35, 71),
            new EntryInformation("Fred", 18, 88),
        };

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
        //! [Using Strategy in C#]
        void Strategy_Exercise()
        {
            Console.WriteLine();
            Console.WriteLine("Strategy Exercise");

            Strategy_ShowEntries_Class displaySortedByNameAscending;
            displaySortedByNameAscending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByName, false);
            displaySortedByNameAscending.ShowEntries(entries);

            Strategy_ShowEntries_Class displaySortedByAgeAscending;
            displaySortedByAgeAscending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByAge, false);
            displaySortedByAgeAscending.ShowEntries(entries);

            Strategy_ShowEntries_Class displaySortedByHeightDescending;
            displaySortedByHeightDescending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByHeight, true);
            displaySortedByHeightDescending.ShowEntries(entries);

            Console.WriteLine("  Done.");
        }
        //! [Using Strategy in C#]

        //########################################################################
        //########################################################################

        /// <summary>
        /// Represents a single exercise or example for a design pattern.
        /// </summary>
        struct Exercise
        {
            /// <summary>
            /// Name of the exercise.
            /// </summary>
            public string name;

            /// <summary>
            /// Method to call to run the exercise.
            /// </summary>
            public Action exercise_to_run;


            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="nameOfExercise">Name of the exercise.</param>
            /// <param name="exercise">Method to run (of type void ()(void)).</param>
            public Exercise(string nameOfExercise, Action exercise)
            {
                name = nameOfExercise;
                exercise_to_run = exercise;
            }
        }

        /// <summary>
        /// Represents the command line options provided to the program, if any.
        /// </summary>
        internal struct Options
        {
            /// <summary>
            /// List of exercise names to run.  If this list is empty, run all
            /// exercises.
            /// </summary>
            public List<string> exercise_names;
        }



        /// <summary>
        /// Helper method to show usage information for this program.
        /// </summary>
        /// <param name="exercises">List of Exercise objects for which to show the names.</param>
        void Help(Exercise[] exercises)
        {
            string usage =
                "{0} by Stephen P. Lepisto\n" +
                "usage: {0} [--help][-?][options] [exercise_name][[ exercise_name][...]]\n" +
                "\n" +
                "Runs through a series of exercises showing off design patterns.  If no exercise_name\n" +
                "is given, then run through all exercises.\n" +
                "\n" +
                "Options:\n" +
                "--help, -?\n" +
                "     This help text.\n" +
                "\n" +
                ""; // End of string.

            string appName = System.IO.Path.GetFileNameWithoutExtension(AppDomain.CurrentDomain.FriendlyName);
            Console.Write(usage, appName);

            Console.WriteLine("\nExercises available:");
            foreach (Exercise exercise in exercises)
            {
                Console.WriteLine("  {0}", exercise.name);
            }
        }

        /// <summary>
        /// Helper method to parse the given options and store the results in
        /// the given Options structure.  Displays help if requested and
        /// returns false.
        /// </summary>
        /// <param name="args">List of arguments passed on the command line.</param>
        /// <param name="exercises">List of Exercise objects to display if help is needed.</param>
        /// <param name="options">An Options structure to be filled in by command line parameters.</param>
        /// <returns>true if the command lines were valid and help was not asked.  Otherwise,
        /// a command line option was not valid or help was requested.</returns>
        bool ParseOptions(string[] args, Exercise[] exercises, ref Options options)
        {
            bool optionsValid = true;

            options.exercise_names = new List<string>();

            if (args.Length > 0)
            {
                foreach (string argument in args)
                {
                    string arg = argument;
                    if (string.Compare(arg, "--help") == 0 ||
                        string.Compare(arg, "-?") == 0 ||
                        string.Compare(arg, "/?") == 0)
                    {
                        Help(exercises);
                        optionsValid = false;
                        break;
                    }
                    options.exercise_names.Add(arg);
                }
            }

            return optionsValid;
        }


        /// <summary>
        /// Run the specified examples.
        /// </summary>
        /// <param name="args">Command line arguments.</param>
        void Run(string[] args)
        {
            Exercise[] exercises = new Exercise[]
            {
                new Exercise("Adapter", Adapter_Exercise),
                new Exercise("Bridge", Bridge_Exercise),
                new Exercise("Composite", Composite_Exercise),
                new Exercise("Decorator", Decorator_Exercise),
                new Exercise("Facade", Facade_Exercise),
                new Exercise("Flyweight", Flyweight_Exercise),
                new Exercise("Proxy", Proxy_Exercise),
                new Exercise("Visitor", Visitor_Exercise),
                new Exercise("Command", Command_Exercise),
                new Exercise("HandlerChain", HandlerChain_Exercise),
                new Exercise("Interpreter", Interpreter_Exercise),
                new Exercise("Iterator", Iterator_Exercise),
                new Exercise("Mediator", Mediator_Exercise),
                new Exercise("Memento", Memento_Exercise),
                new Exercise("NullObject", NullObject_Exercise),
                new Exercise("Observer", Observer_Exercise),
                new Exercise("State", State_Exercise),
                new Exercise("Strategy", Strategy_Exercise),
            };

            Options options = new Options();
            if (ParseOptions(args, exercises, ref options))
            {
                foreach (Exercise exercise in exercises)
                {
                    if (options.exercise_names.Count == 0 ||
                        options.exercise_names.FindIndex((string option_name) =>
                            String.Compare(option_name, exercise.name, true) == 0) != -1)
                    {
                        exercise.exercise_to_run();
                    }
                }
            }
        }


        //########################################################################
        //########################################################################

        /// <summary>
        /// Main entry point into this example program.
        /// </summary>
        /// <param name="args">Command line arguments.</param>
        static void Main(string[] args)
        {
            // Enable the virtual terminal processing mode for the life of this
            // program.
            using (EnableVTModeForWindowsConsole o = new EnableVTModeForWindowsConsole())
            {
                Program prog = new Program();
                prog.Run(args);
            }
        }
    }
}
