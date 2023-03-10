## @package program
#  Heart of the DesignPatternExamples_python package, which executes all the
#  exercises.  This mirrors the C# and C++ program structures.

import os
import sys

from .adapter import Adapter_Exercise
from .bridge import Bridge_Exercise
from .command import Command_Exercise
from .composite import Composite_Exercise
from .decorator import Decorator_Exercise
from .facade import Facade_Exercise
from .flyweight import Flyweight_Exercise
from .handlerchain import HandlerChain_Exercise
from .interpreter import Interpreter_Exercise
from .iterator import Iterator_Exercise
from .mediator import Mediator_Exercise
from .memento import Memento_Exercise
from .nullobject import NullObject_Exercise
from .observer import Observer_Exercise
from .proxy import Proxy_Exercise
from .state import State_Exercise
from .strategy import Strategy_Exercise
from .visitor import Visitor_Exercise


## Contains all the top-level Design Pattern Examples to match C#.
class Program:

    ##Represents a single exercise or example for a design pattern.
    class Exercise:

        ## Constructor.
        #  @param exercise_name
        #         Name of the exercise.
        #  @param exercise
        #         Method to run
        def __init__(self, exercise_name, exercise):
            self.name = exercise_name
            self.exercise_to_run = exercise

        ## @var name
        #       Name of the exercise.
        #  @var exercise_to_run
        #       Method to call to run the exercise.


    ## Represents the command line options provided to the program, if any.
    class Options:

        ## Constructor.
        def __init__(self):
            self.exercise_names = []

        ## var exercise_names
        #      List of exercise names to run.  If this list is empty, run all
        #      exercises.


    ## Helper method to show usage information for this program.
    #
    # @param exercises
    #        List of Exercise objects for which to show the names.
    def Help(self, exercises: list[Exercise]):
        usage = \
                "{0} by Stephen P. Lepisto\n" + \
                "usage: {0} [--help][-?][options] [exercise_name][[ exercise_name][...]]\n" + \
                "\n"  + \
                "Runs through a series of exercises showing off design patterns.  If no exercise_name\n" + \
                "is given, then run through all exercises.\n" + \
                "\n" + \
                "Options:\n" + \
                "--help, -?\n" + \
                "     This help text.\n"
        
        print(usage.format("DesignPatternExamples_python"))

        print("Exercises available:")
        for exercise in exercises:
            print("  {0}".format(exercise.name))



    ## Helper method to parse the given options and store the results in
    #  the given Options structure.  Displays help if requested and
    #  returns False.
    #
    # @returns
    #     True if options are valid and help was not displayed; otherwise,
    #     returns False.  In this case, False is returned only if help display
    #     is requested (options are not validated).
    def ParseOptions(self, args, options : Options, exercises) -> bool:
        optionsValid = True

        if args:
            for argument in args:
                if argument in ["--help", "-?", "/?"]:
                    self.Help(exercises)
                    optionsValid = False
                    break
                options.exercise_names.append(argument)
        return optionsValid


    ## Run the specified examples.
    #  @param args
    #         Command line arguments.
    def Run(self, args=None):
        exercises = [
            Program.Exercise("Adapter", Adapter_Exercise),
            Program.Exercise("Bridge", Bridge_Exercise),
            Program.Exercise("Composite", Composite_Exercise),
            Program.Exercise("Decorator", Decorator_Exercise),
            Program.Exercise("Facade", Facade_Exercise),
            Program.Exercise("Flyweight", Flyweight_Exercise),
            Program.Exercise("Proxy", Proxy_Exercise),
            Program.Exercise("Visitor", Visitor_Exercise),
            Program.Exercise("Command", Command_Exercise),
            Program.Exercise("HandlerChain", HandlerChain_Exercise),
            Program.Exercise("Interpreter", Interpreter_Exercise),
            Program.Exercise("Iterator", Iterator_Exercise),
            Program.Exercise("Mediator", Mediator_Exercise),
            Program.Exercise("Memento", Memento_Exercise),
            Program.Exercise("NullObject", NullObject_Exercise),
            Program.Exercise("Observer", Observer_Exercise),
            Program.Exercise("State", State_Exercise),
            Program.Exercise("Strategy", Strategy_Exercise),
        ]

        options = Program.Options()
        if self.ParseOptions(args, options, exercises):
            for exercise in exercises:
                if len(options.exercise_names) == 0 or exercise.name in options.exercise_names:
                    exercise.exercise_to_run()

