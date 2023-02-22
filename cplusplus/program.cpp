#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdint.h>

#include "helpers/replace.h"
#include "helpers/stringlist.h"

#include "Adapter_FrontEndClass.h"
#include "Bridge_Logger.h"

namespace DesignPatternExamples
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

            std::string appName = "DesignPatternExamples";
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
        void Adapter_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Adapter Exercise" << std::endl;
            try
            {
                DataReaderWriter dataReaderWriter("-target BXT");
                uint32_t dataSize = 128;
                std::vector<uint8_t> writeData(dataSize);
                for (uint32_t index = 0; index < dataSize; ++index)
                {
                    writeData[index] = static_cast<uint8_t>(index);
                }
                std::string dataDump =
                    dataReaderWriter.BufferToString(writeData, dataSize, 2);
                std::cout << "  Data written:" << std::endl;
                std::cout << dataDump;
                dataReaderWriter.Write(writeData, dataSize);

                std::vector<uint8_t> readData = dataReaderWriter.Read(dataSize);
                dataDump = dataReaderWriter.BufferToString(readData, dataSize, 2);
                std::cout << "  Data read:" << std::endl;
                std::cout << dataDump;
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
            std::ostringstream output;
            output << "Starting \"log to " << loggerType << "\" example";
            logger.LogTrace(output.str());

            logger.LogInfo("An example of an informational line");
            logger.LogError("An example of an error log entry");

            output.str(std::string()); // Clear stream contents so we can reuse.
            output << "Done with \"log to " << loggerType << "\" example";
            logger.LogTrace(output.str());
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


        //########################################################################
        //########################################################################


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
        void Composite_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Composite Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Decorator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Decorator Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


        //########################################################################
        //########################################################################


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
        void Facade_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Facade Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


        //########################################################################
        //########################################################################


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
        void Flyweight_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Flyweight Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Proxy_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Proxy Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Visitor_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Visitor Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Command_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Command Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void HandlerChain_Exercise()
        {
            std::cout << std::endl;
            std::cout << "HandlerChain Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Interpreter_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Interpreter Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Iterator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Iterator Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Mediator_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Mediator Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Memento_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Memento Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void NullObject_Exercise()
        {
            std::cout << std::endl;
            std::cout << "NullObject Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Observer_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Observer Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void State_Exercise()
        {
            std::cout << std::endl;
            std::cout << "State Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
        void Strategy_Exercise()
        {
            std::cout << std::endl;
            std::cout << "Strategy Exercise" << std::endl;

            std::cout << "  Done." << std::endl;
        }


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
    DesignPatternExamples::Program prog;
    StringList args;
    for (int argIndex = 1; argIndex < argc; ++argIndex)
    {
        args.push_back(std::string(argv[argIndex]));
    }

    prog.Run(args);

    return EXIT_SUCCESS;
}
