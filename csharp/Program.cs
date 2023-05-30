/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_csharp.Program.Main "Main()"
/// entry point and all the design pattern example functions.
/// See @ref mainpage "Main Overview".

using System;
using System.Collections.Generic;

/// <summary>
/// The namespace containing all Design Pattern Examples implemented in C#.
/// </summary>
namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Contains all the top-level Design Pattern Examples.
    /// </summary>
    class Program
    {
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

        //########################################################################


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
                new Exercise("Adapter", () => { Adapter_Exercise exercise = new Adapter_Exercise(); exercise.Run(); }),
                new Exercise("Bridge", () => { Bridge_Exercise exercise = new Bridge_Exercise(); exercise.Run(); }),
                new Exercise("Composite", () => { Composite_Exercise exercise = new Composite_Exercise(); exercise.Run(); }),
                new Exercise("Decorator", () => { Decorator_Exercise exercise = new Decorator_Exercise(); exercise.Run(); }),
                new Exercise("Facade", () => { Facade_Exercise exercise = new Facade_Exercise(); exercise.Run(); }),
                new Exercise("Flyweight", () => { Flyweight_Exercise exercise = new Flyweight_Exercise(); exercise.Run(); }),
                new Exercise("Proxy", () => { Proxy_Exercise exercise = new Proxy_Exercise(); exercise.Run(); }),
                new Exercise("Visitor", () => { Visitor_Exercise exercise = new Visitor_Exercise(); exercise.Run(); }),
                new Exercise("Command", () => { Command_Exercise exercise = new Command_Exercise(); exercise.Run(); }),
                new Exercise("HandlerChain", () => { HandlerChain_Exercise exercise = new HandlerChain_Exercise(); exercise.Run(); }),
                new Exercise("Interpreter", () => { Interpreter_Exercise exercise = new Interpreter_Exercise(); exercise.Run(); }),
                new Exercise("Iterator", () => { Iterator_Exercise exercise = new Iterator_Exercise(); exercise.Run(); }),
                new Exercise("Mediator", () => { Mediator_Exercise exercise = new Mediator_Exercise(); exercise.Run(); }),
                new Exercise("Memento", () => { Memento_Exercise exercise = new Memento_Exercise(); exercise.Run(); }),
                new Exercise("NullObject", () => { NullObject_Exercise exercise = new NullObject_Exercise(); exercise.Run(); }),
                new Exercise("Observer", () => { Observer_Exercise exercise = new Observer_Exercise(); exercise.Run(); }),
                new Exercise("State", () => { State_Exercise exercise = new State_Exercise(); exercise.Run(); }),
                new Exercise("Strategy", () => { Strategy_Exercise exercise = new Strategy_Exercise(); exercise.Run(); }),
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
