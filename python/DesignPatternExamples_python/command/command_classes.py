## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
# and @ref DesignPatternExamples_python.command.command_classes.Command "Command"
# classes used in the @ref command_pattern.

## Container for a string.  Need to use a class that allows the text to
#  be changed while the container (this class) remains constant.  This
#  way, operations can be applied to the text and the container's contents
#  change but not the container (strings are immutable in Python this dances
#  around that problem).
class Command_TextObject:

    ## Constructs a text object with an initial string.
    #
    #  @param text
    #         The initial string for the text object.
    def __init__(self, text : str):
        self._text = text
        self._startingText = text

    ## @var _startingText
    #       Starting string text so we can reset the text to a known point.
    ## @var _text
    #       The text that can change.


    ## Gets the text in this TextObject.
    def Text(self) -> str:
        return self._text

    ## Sets the text in this TextObject.
    def SetText(self, value : str):
        self._text = value

    ## Resets the TextObject to the starting string.
    def Reset(self):
        self._text = self._startingText

    ## Returns the TextObject to a string.
    #
    #  @returns
    #     Returns the text stored in the text object.
    def ToString(self) -> str:
        return self._text



## Represents an operation that can be applied to a TextObject.
#  This class can handle two kinds of operations, one that takes no
#  additional parameters and one that takes two additional string
#  parameters.
# 
#  In a real program, the commands would be represented by an interface
#  and concrete classes for each type of operation (based on additional
#  parameters) would be used.  This requires the calling entity to
#  instantiate the appropriate concrete class as opposed to letting the Python
#  constructor figure out the correct operation based on the number of extra
#  parameters provided for the operation.  Or the calling entity could use a
#  class factory to create the concrete classes.
#  
#  For Python, this Command class is made somewhat more general case simply
#  because there can only be one `__init__()` method (constructor).  So the
#  number of extra parameters passed after the function determine whether the
#  function takes zero or two parameters.  The code assumes the two-parameter
#  function if there are exactly two extra arguments given to the constructor;
#  otherwise, a no-parameter function is assumed.
class Command:

    ## Constructor for a command that applies an operation to a TextObject, where the
    #  operation takes zero or two parameters.
    #
    #  @param source
    #         The TextObject to apply the operation to.
    #  @param commandName
    #         Easy-to-read name of the command.
    #  @param operation
    #         The two parameter operation to apply to the TextObject.
    #  @param arguments
    #         Zero or two arguments that are passed to the operation
    def __init__(self, source : Command_TextObject, commandName : str, operation, *arguments) -> None:
        self._receiver = source
        self._commandName = commandName
        self._argument1 = None
        self._argument2 = None
        self._two_parameter_operation = None
        self._no_parameter_operation = None
        if len(arguments) == 2:
            self._argument1 = arguments[0]
            self._argument2 = arguments[1]
            self._two_parameter_operation = operation
        else:
            self._no_parameter_operation = operation


    ## @var _receiver
    #       The receiver of the command.
    ## @var _commandName
    #       Easy-to-read command name.
    ## @var _two_parameter_operation
    #       Two parameter operation to apply to the receiver.
    ## @var _no_parameter_operation
    #       No parameter operation to apply to the receiver.
    ## @var _argument1
    #       The first argument to the two-parameter operation.
    ## @var _argument2
    #       The second argument to the two-parameter operation.


    ## Execute the command on the TextObject.
    def Execute(self):
        if self._two_parameter_operation:
            self._two_parameter_operation(self._receiver, self._argument1, self._argument2)
        else:
            self._no_parameter_operation(self._receiver)

    ## Return this command as a string representation.
    #
    #  @returns
    #     A string containing the representation of the command.
    def ToString(self) -> str:
        output = "<NO COMMAND>"
        if self._two_parameter_operation:
            output = "{0} \"{1}\" with \"{2}\"".format(self._commandName, self._argument1, self._argument2)
        elif self._no_parameter_operation:
            output = self._commandName
        return output
