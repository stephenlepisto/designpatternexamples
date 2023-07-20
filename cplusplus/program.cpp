/// @file
/// @brief
/// Implementation of the main() entry point and the machinery to call all the
/// design pattern example functions.  See @ref mainpage "Main Overview".

#include <functional>
#include <iostream>

#include "helpers/replace.h"
#include "helpers/stringlist.h"
#include "helpers/enablevtmode.h"

#include "Adapter_Exercise.h"
#include "Bridge_Exercise.h"
#include "Command_Exercise.h"
#include "Composite_Exercise.h"
#include "Decorator_Exercise.h"
#include "Facade_Exercise.h"
#include "Flyweight_Exercise.h"
#include "HandlerChain_Exercise.h"
#include "Interpreter_Exercise.h"
#include "Iterator_Exercise.h"
#include "Mediator_Exercise.h"
#include "Memento_Exercise.h"
#include "NullObject_Exercise.h"
#include "Observer_Exercise.h"
#include "Proxy_Exercise.h"
#include "State_Exercise.h"
#include "Strategy_Exercise.h"
#include "Visitor_Exercise.h"

/// <summary>
/// The namespace containing all Design Pattern Examples implemented in C++.
/// </summary>
namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Alias for a function pointer, using C# as inspiration for the name.
    /// </summary>
    typedef std::function<void()> Action;

    /// <summary>
    /// Contains all the top-level Design Pattern Examples to match C#.
    /// </summary>
    class Program
    {
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

        /// <summary>
        /// Alias for a list of Exercise instances.
        /// </summary>
        typedef std::vector<Exercise> ExerciseList;

        /// <summary>
        /// Represents the command line options provided to the program, if any.
        /// </summary>
        struct Options
        {
            /// <summary>
            /// List of names of exercise to run.  If this list is empty, run all
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
                "Runs through a series of exercises showing off design patterns.  If no\n"
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
                Exercise("Command",  [&] { Command_Exercise(); }),
                Exercise("Composite",  [&] { Composite_Exercise(); }),
                Exercise("Decorator",  [&] { Decorator_Exercise(); }),
                Exercise("Facade",  [&] { Facade_Exercise(); }),
                Exercise("Flyweight",  [&] { Flyweight_Exercise(); }),
                Exercise("HandlerChain",  [&] { HandlerChain_Exercise(); }),
                Exercise("Interpreter",  [&] { Interpreter_Exercise(); }),
                Exercise("Iterator",  [&] { Iterator_Exercise(); }),
                Exercise("Mediator",  [&] { Mediator_Exercise(); }),
                Exercise("Memento",  [&] { Memento_Exercise(); }),
                Exercise("NullObject",  [&] { NullObject_Exercise(); }),
                Exercise("Observer",  [&] { Observer_Exercise(); }),
                Exercise("Proxy",  [&] { Proxy_Exercise(); }),
                Exercise("State",  [&] { State_Exercise(); }),
                Exercise("Strategy",  [&] { Strategy_Exercise(); }),
                Exercise("Visitor",  [&] { Visitor_Exercise(); }),
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
