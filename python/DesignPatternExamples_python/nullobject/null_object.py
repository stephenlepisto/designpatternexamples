## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.nullobject.null_object.MoveProcessor "MoveProcessor"
#  class and the
#  @ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand"
#  base class, along with the various MoveXX classes used in the
#  @ref nullobject_pattern.

from abc import ABC, abstractmethod

## Base class that represents a move command.  A move command has a name
#  and the command character that represents the command in the initial
#  string of movement commands.
#  
#  Yes, this is a variation of the @ref command_pattern.
#  
#  In this example, a move command, when executed, prints "move xxx" on
#  the current line.  When displayed, the move command shows the command
#  character followed by the name of the command.
class MoveCommand(ABC):

    ## Constructor
    #
    #  @param command
    #         The character that represents the command in the original move list.
    #  @param commandName
    #         The name of the command (for display purposes).
    def __init__(self, command : str, commandName : str) -> None:
        self._name = commandName
        self._command = command

    ## @var _name
    #        Name of the command.
    #  @var _command
    #       The command for controlling movement.


    ## Display the move command and its name followed by a newline.
    #  This can be overridden as necessary in derived class.
    def Show(self) -> None:
        print("    '{0}' -> {1}".format(self._command, self._name))


    ## Execute the command.  Derived classes must implement this.
    @abstractmethod
    def Execute(self) -> None:
        pass


#########################################################################
#########################################################################


## Represents the Move Left command.
class MoveCommandLeft(MoveCommand):
    ## Constructor.
    #
    #  @param command
    #         The character representing the move in the original move list.
    def __init__(self, command : str) -> None:
        super().__init__(command, "Left")


    ## Executes the move left command.
    def Execute(self) -> None:
        print("move left", end="")


#########################################################################
#########################################################################


## Represents the Move Right command.
class MoveCommandRight(MoveCommand):
    ## Constructor.
    #
    #  @param command
    #         The character representing the move in the original move list.
    def __init__(self, command : str) -> None:
        super().__init__(command, "Right")


    ## Executes the move right command.
    def Execute(self):
        print("move right", end="")


#########################################################################
#########################################################################


## Represents the Move Up command.
class MoveCommandUp(MoveCommand):
    ##  Constructor.
    #
    #  @param command
    #         The character representing the move in the original move list.
    def __init__(self, command : str) -> None :
       super().__init__(command, "Up")


    ## Executes the move up command.
    def Execute(self) -> None:
        print("move up", end="")


#########################################################################
#########################################################################


## Represents the Move Down command.
class MoveCommandDown(MoveCommand):
    ## Constructor.
    #
    #  @param command
    #         The character representing the move in the original move list.
    def __init__(self, command : str) -> None:
       super().__init__(command, "Down")


    ## Executes the move down command.
    def Execute(self) -> None:
        print("move down", end="")


#########################################################################
#########################################################################


## Represents the Do Nothing command.  This is the Null Object for this
#  exercise.
class MoveCommandNone(MoveCommand):
    ##  Constructor.
    #
    #  @param command
    #     The character representing the move in the original move list.
    def __init__(self, command: str) -> None:
       super().__init__(command, "None")


    ## Does nothing when executed (this is the Null Object, after all).
    def Execute(self) -> str:
        pass


#########################################################################
#########################################################################


## Represents the processor that translates the move list into a list of
#  MoveCommand objects then either displays them or executes them.
#  
#  This classes uses a parser to convert the single letter characters from
#  a string into a list of actions (instances of the
#  @ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand"
#  class).  This list of actions is then executed to perform the operations.
#  
#  This process of executing the list of operations is an example of the
#  @ref command_pattern.  This is also an example of the
#  @ref interpreter_pattern, where the actions are the tokens to be
#  interpreted.
class MoveProcessor:

   #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Private methods.

    ## Helper method to convert a list of single letter commands into a
    #  list of
    #  @ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand"
    #  objects.
    #  
    #  This method recognizes 'L', 'R', 'U', and 'D' (case-insensitive).
    #  All other characters default to the "Do Nothing" (Null Object) command.
    #
    #  @param moveList
    #         A string containing a list of single letter commands to be parsed.
    #  @returns
    #     Returns a list of MoveCommand objects.
    def _ParseMoves(self, moveList : str) -> list[MoveCommand]:
        commands = [] # type: list[MoveCommand]
        for index in range(0, len(moveList)):
            commandChar = moveList[index].upper()
            moveCommand = None

            match (commandChar):
                case 'U':
                    moveCommand = MoveCommandUp(commandChar)

                case 'D':
                    moveCommand = MoveCommandDown(commandChar)

                case 'L':
                    moveCommand = MoveCommandLeft(commandChar)

                case 'R':
                    moveCommand = MoveCommandRight(commandChar)

                case _:
                    # Everything else is a "do nothing" command.
                    moveCommand = MoveCommandNone(commandChar)

            commands.append(moveCommand);

        return commands;


    ## Helper method to execute all the given commands.
    #
    #  In this implementation, the
    #  @ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand"
    #  object prints the command as "&lt;move xxx&gt; " on the current line. 
    #  When all commands have been printed, a new line is printed to move to
    #  the next line. The "Do Nothing" command doesn't print anything, leaving
    #  only the empty &lt;&gt;.
    #
    #  @param commands
    #         A list of
    #         @ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand"
    #         objects to "execute".
    def _ExecuteMoves(self, commands : list[MoveCommand]) -> None:
        for command in commands:
            print("<", end="")
            command.Execute()
            print("> ", end="")
        print()


    ## Display the command character and name of the command for each
    #  command in the given list of commands.
    #
    #  @param commands
    #         The list of MoveCommand objects to display.
    def _ShowMoves(self, commands : list[MoveCommand]) -> None:
        for command in commands:
            command.Show()
            

    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Public methods.

    ## Parse and execute the given list of move commands, where each
    #  command is represents by a single character.
    #  
    #  Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
    #  characters are assigned a "Do Nothing" (Null Object) command.
    #
    #  @param moveList
    #         A string of characters to parse and execute.
    def ExecuteMoveList(self, moveList: str) -> None:
        commands = self._ParseMoves(moveList)
        self._ExecuteMoves(commands)


    ## Parse and display the given list of move commands, where each
    #  command is represents by a single character.
    #  
    #  Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
    #  characters are assigned a "Do Nothing" (Null Object) command.
    #
    #  @param moveList
    #         A string of characters to parse and display.
    def ShowMoveList(self, moveList : str) -> None:
        commands = self._ParseMoves(moveList)
        self._ShowMoves(commands)
