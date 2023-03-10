## @package program
#  Heart of the DesignPatternExamples_python package, which executes all the
#  exercises.  This mirrors the C# and C++ program structures.

import os
import sys


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


    ###########################################################################
    ###########################################################################
    

    ## Example of using the Adapter design pattern.
    # 
    # This example adapts functions that return error codes into a class object
    # that throws exceptions, which is more fitting of an object-oriented
    # language.
    ##! [Using Adapter in Python]
    def Adapter_Exercise(self):
        print()
        print("Adapter Exercise")

        print("  Done.")
    ##! [Using Adapter in Python]


    ###########################################################################
    ###########################################################################
    

    ## Example of using the Bridge design pattern.
    # 
    # The Bridge pattern is used to allow a program to offer multiple
    # ways to perform logging without changing how the logging is
    # used throughout the program.
    #
    # In this exercise, note how the calls into the logger are the
    # same regardless of the logger used.
    ##! [Using Bridge in Python]
    def Bridge_Exercise(self):
        print()
        print("Bridge Exercise")

        print("  Done.")
    ##! [Using Bridge in Python]


    ###########################################################################
    ###########################################################################
    

    ## Example of using the Composite design pattern.
    # 
    #  The Composite pattern is used when a collection of objects is to
    #  be formed in a hierarchical form where each object needs to be
    #  treated like any other object but some objects can contain other
    #  objects.
    # 
    #  This example uses a file structure of file and directories to
    #  represent each object type.
    ##! [Using Composite in Python]
    def Composite_Exercise(self):
        print()
        print("Composite Exercise")

        print("  Done.")
    ##! [Using Composite in Python]


    ###########################################################################
    ###########################################################################


    ## Example of using the Decorator design pattern.
    #  
    #  The Decorator pattern is used when a class instance at run time needs
    #  to have its behavior altered.  This is supported by providing wrapper
    #  classes called decorators that take instances of the IRenderElement
    #  interface.  All elements look the same and can therefore recursively
    #  wrap other decorators.  The base element never wraps anything and
    #  decorators must ultimately wrap a non-decorator class to be of any
    #  use.
    ##! [Using Decorator in Python]
    def Decorator_Exercise(self):
        print()
        print("Decorator Exercise")

        print("  Done.")
    ##! [Using Decorator in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Facade design pattern.
    #  
    #  The Facade pattern is used when a simplified version of an
    #  interface on a complicated sub-system is needed in situations
    #  where the whole complicated sub-system does not need to be
    #  exposed.
    #  
    #  In this example, the complicated subsystem is a representation of
    #  a device network complete with scan chains, device idcodes, and device
    #  devices that can be selected and deselected.  The Facade exposed
    #  by this complex network exposes only the scan chain, getting
    #  device idcodes based on an index into those scan chains, resetting
    #  the scan chains and selecting a device to appear in the scan
    #  chain.
    ##! [Using Facade in Python]
    def Facade_Exercise(self):
        print()
        print("Facade Exercise")

        print("  Done.")
    ##! [Using Facade in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Flyweight design pattern.
    #  
    #  The Flyweight pattern is used when a large object needs to be
    #  represented by a much lighter weight class, possibly multiple
    #  instances of said light-weight class.
    #  
    #  In this example, a large object is represented by a so-called "big
    #  resource" or image (a two-dimensional array of text characters).
    #  Flyweight classes that represent position and velocity are
    #  attached to the big resource image so they all share the same image
    #  but have different positions and velocities.  The image is rendered
    #  to a display area through the Flyweight class.  The Flyweight
    #  class instances then have their positions updated, bouncing off the
    #  edges of the display area 60 times a second.  This continues for
    #  1000 iterations or until a key is pressed.
    ##! [Using Flyweight in Python]
    def Flyweight_Exercise(self):
        print()
        print("Flyweight Exercise")

        print("  Done.")
    ##! [Using Flyweight in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Proxy design pattern.
    #  
    #  The Proxy pattern is used when a large or expensive object cannot be
    #  represented directly in the program, typically because the object is
    #  in another process or even another system altogether.
    #  
    #  In this exercise, a Proxy class implements the same interface as the
    #  Real class, making the Proxy class look like the Real class.  Calls
    #  made on the Proxy class are passed to the Real class where the work
    #  is actually done (in this case, a munged string with the text
    #  "Real class received 'xxxx'".
    #  
    #  The only difference in output here is one additional line for the
    #  first call showing the real class being instantiated.  The subsequent
    #  calls do not show this line.
    ##! [Using Proxy in Python]
    def Proxy_Exercise(self):
        print()
        print("Proxy Exercise")

        print("  Done.")
    ##! [Using Proxy in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Visitor design pattern.
    #  
    #  The Visitor pattern is used to add functionality to a list of
    #  otherwise unchanging element objects by passing a visitor object to
    #  each element object.  Each element object calls the visitor object,
    #  passing itself as an argument.  The visitor object then does
    #  something based on the type of the element.
    #  
    #  In this exercise, a collection of shop objects is initialized then
    #  an order visitor is created to retrieve an item from one of the shop
    #  objects.  Along the way, shops that don't have the necessary
    #  ingredients use another order visitor to order ingredients from
    #  other shops.  This approach assumes no two shops sell the same
    #  thing.
    ##! [Using Visitor in Python]
    def Visitor_Exercise(self):
        print()
        print("Visitor Exercise")

        print("  Done.")
    ##! [Using Visitor in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Command design pattern.
    #  
    #  The Command pattern is used to encapsulate an operation or command
    #  associated with an object so that the command can be applied to
    #  the object at a later time.
    #  
    #  In this exercise, an undo list is implemented using Commands that
    #  associate commands defined in this file with a text object.  The
    #  commands are applied to the text object in succession then
    #  effectively undone.
    ##! [Using Command in Python]
    def Command_Exercise(self):
        print()
        print("Command Exercise")

        print("  Done.")
    ##! [Using Command in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Handle Chain or Chain of Responsibility design
    #  pattern.
    #  
    #  The Handler Chain pattern is used to support a dynamic list of
    #  handlers that are passed the same arguments.  It is kind of the
    #  inverse of the Visitor pattern, where the Visitor pattern is a
    #  handler that is passed to all objects in a list and the Handler
    #  Chain pattern is an object passed to handlers in a list.
    # 
    #  In this exercise, multiple rectangular regions called
    #  MessageWindows embody the handlers and the HandlerChain object
    #  passes message objects to each MessageWindow until the message is
    #  handled.
    ##! [Using HandlerChain in Python]
    def HandlerChain_Exercise(self):
        print()
        print("Handler Chain Exercise")

        print("  Done.")
    ##! [Using HandlerChain in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Interpreter design pattern.
    #  
    #  The interpreter is instantiated then fed a series of arrays 
    #  containing integer tokens.  Each token represents a single word or
    #  punctuation mark.  The interpreter converts that array of tokens
    #  to an actual sentence by interpreting the meaning of the tokens.
    #  
    #  This is a very simple interpreter that handles the first token in
    #  a special way and supports punctuation.  It is an example of a
    #  linear interpreter where tokens can appear in any order (it's up
    #  to the creator of the token list to make sure the outcome makes
    #  any sense).
    #  
    #  The output shows the token list followed by the sentence produced
    #  from the tokens.
    ##! [Using Interpreter in Python]
    def Interpreter_Exercise(self):
        print()
        print("Interpreter Exercise")

        print("  Done.")
    ##! [Using Interpreter in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Iterator design pattern.
    #  
    #  A custom container is instantiated (it already contains harcoded data
    #  to iterate over).  The custom container can then deliver three
    #  iterators, each providing a different aspect of the hardcoded data.
    #  
    #  The output shows the output from each iterator.
    ##! [Using Iterator in Python]
    def Iterator_Exercise(self):
        print()
        print("Iterator Exercise")

        print("  Done.")
    ##! [Using Iterator in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Mediator design pattern.
    #  
    #  A mediator is instantiated then populated with users and groups.
    #  Users are added to some of the groups.
    #  
    #  A series of operations are then performed through the mediator.
    #  The output shows the results of each operation.  Note that all
    #  operations are done using user and group names, with no knowledge
    #  of the actual lists of users and groups.  The mediator hides all
    #  the details.
    ##! [Using Mediator in Python]
    def Mediator_Exercise(self):
        print()
        print("Mediator Exercise")

        print("  Done.")
    ##! [Using Mediator in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Memento design pattern.
    #  
    #  In this exercise, the Memento pattern is used to take snapshots of
    #  a text object so as to form an undo list of changes to the text
    #  object.  Undoing an operation means restoring a snapshot of the
    #  text object.
    #  
    #  The undo list is implemented as a stack of memento objects that
    #  each represent a snapshot of the text object taken before each
    #  operation is applied.  After all operations are applied, the
    #  mementos are used to restore the text object in reverse order,
    #  effectively undoing each operation in turn.
    #  
    #  Compare this to the Command_Exercise() and note that the steps
    #  taken there are identical to here (except for method names, of
    #  course).  The difference lies in how operations are executed
    #  and undone.  Mementos make the undo process much cleaner and
    #  faster since operations do not need to be applied repeatedly to
    #  get the text object into a specific state.  Specifically,
    #  compare Command_Undo() with Memento_Undo().  Also note the
    #  differences in the "Memento_ApplyXXOperation()" methods, which
    #  more cleanly separate the save from the operation.
    ##! [Using Memento in Python]
    def Memento_Exercise(self):
        print()
        print("Memento Exercise")

        print("  Done.")
    ##! [Using Memento in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Null Object design pattern.
    #  
    #  The Null Object pattern is where an object or function acts as a
    #  stand-in for real commands but otherwise does nothing.
    #  
    #  In this exercise, movement commands are presented as characters in
    #  a string, with the characters 'u', 'd', 'l', and 'r' representing
    #  the moves "up", "down", "left", and "right", respectively.  To
    #  keep the processing of this string simple, all other characters in
    #  the string are assigned a Null Object ("Do Nothing") version of
    #  the move command.
    #  
    #  This example displays the commands after parsing and then
    #  "executes" commands, which consists of printing the commands out.
    #  
    #  This example highlights the Null Object pattern while utilizing
    #  the Command and Interpreter patterns.
    ##! [Using NullObject in Python]
    def NullObject_Exercise(self):
        print()
        print("Null Object Exercise")

        print("  Done.")
    ##! [Using NullObject in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Observer design pattern.
    #  
    #  The Observer pattern allows for one or more observers to react to
    #  changes in a Subject entity.
    #  
    #  In this exercise, a number producer (the Subject) updates an internal
    #  value every time the Update() method is called.  Three different
    #  observers are attached to the number producer and print out the
    #  current value in different formats whenever the number is changed.
    #  
    #  Note: Interfaces are used throughout this example.  For example, to
    #  subscribe to the number producer, the IEventNotifications interface
    #  must be obtained from the number producer.  The number producer is
    #  represented to the observers with the INumberProducer interface and
    #  the observers are represented to the number producer with the
    #  IObserverNumberChanged interface.  This highlights a common way to
    #  implement a "pull" style observer without having too much knowledge
    #  about the Subject.
    ##! [Using Observer in Python]
    def Observer_Exercise(self):
        print()
        print("Observer Exercise")

        print("  Done.")
    ##! [Using Observer in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the State design pattern.
    #  
    #  The State pattern alters the behavior of the class hierarchy based
    #  on some state.  This is the basis of a Finite State Machine.
    #  
    #  In this exercise, the State class is a filter that parses text to
    #  remove C++-style line and block comments.  It needs to be smart
    #  enough to ignore comment characters inside quotes.
    #  
    #  The filtering process starts with creating the context that drives
    #  the state machine.  Internal classes are provided for each state.
    ##! [Using State in Python]
    def State_Exercise(self):
        print()
        print("State Exercise")

        print("  Done.")
    ##! [Using State in Python]


    ###########################################################################
    ###########################################################################


    ##  Example of using the Strategy design pattern.
    #  
    #  The Strategy pattern provides a way to easily assign different
    #  algorithms to a class instance that can be changed at the time the
    #  class is created.
    #  
    #  In this exercise, the Strategy_ShowEntries_Class instance sorts
    #  and displays a list of EntryInformation elements.  Three different
    #  sorting strategies are provided (Name, Age, Height) and an option
    #  to reverse the normal order of the sort.
    #! [Using Strategy in Python]
    def Strategy_Exercise(self):
        print()
        print("Strategy Exercise")

        print("  Done.")
    ##! [Using Strategy in Python]


    ###########################################################################
    ###########################################################################


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
            Program.Exercise("Adapter", self.Adapter_Exercise),
            Program.Exercise("Bridge", self.Bridge_Exercise),
            Program.Exercise("Composite", self.Composite_Exercise),
            Program.Exercise("Decorator", self.Decorator_Exercise),
            Program.Exercise("Facade", self.Facade_Exercise),
            Program.Exercise("Flyweight", self.Flyweight_Exercise),
            Program.Exercise("Proxy", self.Proxy_Exercise),
            Program.Exercise("Visitor", self.Visitor_Exercise),
            Program.Exercise("Command", self.Command_Exercise),
            Program.Exercise("HandlerChain", self.HandlerChain_Exercise),
            Program.Exercise("Interpreter", self.Interpreter_Exercise),
            Program.Exercise("Iterator", self.Iterator_Exercise),
            Program.Exercise("Mediator", self.Mediator_Exercise),
            Program.Exercise("Memento", self.Memento_Exercise),
            Program.Exercise("NullObject", self.NullObject_Exercise),
            Program.Exercise("Observer", self.Observer_Exercise),
            Program.Exercise("State", self.State_Exercise),
            Program.Exercise("Strategy", self.Strategy_Exercise),
        ]

        options = Program.Options()
        if self.ParseOptions(args, options, exercises):
            for exercise in exercises:
                if len(options.exercise_names) == 0 or exercise.name in options.exercise_names:
                    exercise.exercise_to_run()

