/// @file
/// @brief
/// Implementation of the main() entry point and the machinery to call all the
/// design pattern example functions.  See @ref mainpage "Main Overview".

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "helpers/enablevtmode.h"
#include "helpers/stringlist.h"

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
/// Alias for a function pointer, using C# as inspiration for the name.
/// </summary>
typedef void(*Action)();

/// <summary>
/// Represents a single exercise or example for a design pattern.
/// </summary>
typedef struct _Exercise
{
    /// <summary>
    /// Name of the exercise.
    /// </summary>
    const char* name;

    /// <summary>
    /// Function to call to run the exercise.
    /// </summary>
    Action exercise_to_run;
} Exercise;

/// <summary>
/// Alias for an array of Exercise objects.
/// </summary>
typedef Exercise ExerciseList[];


/// <summary>
/// Represents the command line options provided to the program, if any.
/// </summary>
typedef struct _Options
{
    /// <summary>
    /// List of names of exercise to run.  If this list is empty, run all
    /// exercises.
    /// </summary>
    StringList exercise_names;
} Options;


/// <summary>
/// Helper function to show usage information for this program.
/// </summary>
/// <param name="exercises">List of Exercise objects to display if
/// help is needed.  The list is expected to be terminated by a NULL pointer for
/// the exercise name.</param>
static void Help(ExerciseList exercises)
{
    const char* usage =
        "DesignPatternExamples_c by Stephen P. Lepisto\n"
        "usage: DesignPatternExamples_c [options] [exercise_name][[ exercise_name][...]]\n"
        "\n"
        "Runs through a series of exercises showing off design patterns.  If no\n"
        "exercise_name is given, then run through all exercises.\n"
        "\n"
        "Options:\n"
        "--help, -?\n"
        "     This help text.\n"
        "\n"
        ""; // End of string.

    printf(usage);

    printf("Exercises available:\n");
    for (size_t index = 0; exercises[index].name != NULL; index++)
    {
        printf("  %s\n", exercises[index].name);
    }
}

/// <summary>
/// Helper function to parse the given options and store the results in
/// the given Options structure.  Displays help if requested and
/// returns false.
/// </summary>
/// <param name="argc">Number of command line arguments + 1 (the first argument
/// is the name of the program).</param>
/// <param name="argv">Pointer to a list of zero-terminated strings containing
/// the command line arguments.</param>
/// <param name="options">An Options structure to be filled in by command
/// line parameters.</param>
/// <param name="exercises">List of Exercise objects to display if
/// help is needed.  The list is expected to be terminated by a NULL pointer for
/// the exercise name.</param>
/// <returns>true if the command lines were valid and help was not asked.
/// Otherwise, a command line option was not valid or help was
/// requested.</returns>
static bool ParseOptions(int argc, char** argv, Options* options, ExerciseList exercises)
{
    bool optionsValid = true;

    if (options == NULL)
    {
        printf("Error!  ParseOptions() requires non-NULL pointer to the Options structure.\n");
        return false;
    }

    if (argc > 1)
    {
        for (int index = 1; index < argc; index++)
        {
            if (strcmp(argv[index], "--help") == 0 ||
                strcmp(argv[index], "-?") == 0 ||
                strcmp(argv[index], "/?") == 0)
            {
                Help(exercises);
                optionsValid = false;
                break;
            }
            if (!StringList_AddString(&options->exercise_names, argv[index]))
            {
                printf("Error!  Out of memory storing exercise name in the Options structure.");
                return false;
            }
        }
    }

    return optionsValid;
}


//########################################################################
//########################################################################

ExerciseList exercises =
    {
        {"Adapter", Adapter_Exercise},
        {"Bridge", Bridge_Exercise},
        {"Command", Command_Exercise},
        {"Composite", Composite_Exercise},
        {"Decorator", Decorator_Exercise},
        {"Facade", Facade_Exercise},
        {"Flyweight", Flyweight_Exercise},
        {"HandlerChain", HandlerChain_Exercise},
        {"Interpreter", Interpreter_Exercise},
        {"Iterator", Iterator_Exercise},
        {"Mediator", Mediator_Exercise},
        {"Memento", Memento_Exercise},
        {"NullObject", NullObject_Exercise},
        {"Observer", Observer_Exercise},
        {"Proxy", Proxy_Exercise},
        {"State", State_Exercise},
        {"Strategy", Strategy_Exercise},
        {"Visitor", Visitor_Exercise},
        {NULL, NULL}};

/// <summary>
/// Main entry point into this example program.
/// </summary>
/// <param name="argc">Number of command line arguments + 1 (the first argument
/// is the name of the program).</param>
/// <param name="argv">Pointer to a list of zero-terminated strings containing
/// the command line arguments.</param>
int main(int argc, char** argv)
{
    enableVTMode();
    srand((unsigned int)(time(NULL)));
    Options options = { 0 };
    StringList_Initialize(&options.exercise_names);

    if (ParseOptions(argc, argv, &options, exercises))
    {
        for (int index = 0; exercises[index].name != NULL; index++)
        {
            bool runExercise = (options.exercise_names.strings_count == 0);
            if (!runExercise)
            {
                runExercise = (StringList_Find(&options.exercise_names, exercises[index].name) != -1);
            }
            if (runExercise)
            {
                exercises[index].exercise_to_run();
            }
        }
    }
    StringList_Clear(&options.exercise_names);

    return EXIT_SUCCESS;
}
