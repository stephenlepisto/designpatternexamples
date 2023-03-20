## @file
#  @brief
#  Implementation of the @ref DesignPatternExamples_python.command.command_exercise.Command_Exercise "Command_Exercise"()
#  function as used in the @ref command_pattern.

from .command_classes import Command_TextObject, Command

##  The list of commands applied.
_commandUndoList = []  # type; [Command]

## Save the given command on the undo list then execute the command on
#  the given text object.
#
#  @param text
#         The @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
#         on which to apply the command.
#  @param command
#         The Command object to apply to the text object.
def Command_Save_And_Execute(text : Command_TextObject, command : Command):
    _commandUndoList.append(command)
    command.Execute()


## An operation to search and replace text in a
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#
#  @param source
#         The Command_TextObject to affect.
#  @param searchPattern
#         What to look for in the
#         @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#  @param replaceText
#         What to replace the searchPattern with.
def Command_Operation_Replace(source : Command_TextObject, searchPattern : str, replaceText : str) -> None:
    source.Text = source.Text.replace(searchPattern, replaceText)


## An operation to reverse the characters in the given
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#
#  @param source
#         The @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
#         to affect.
def Command_Operation_Reverse(source : Command_TextObject):
    text_in_list = [c for c in source.Text]
    text_in_list.reverse()
    output = "".join(text_in_list)
    source.Text = output


## Perform an undo on the given
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject",
#  using the commands in the "global" undo list.  If the undo list is empty, nothing happens.
# 
#  @param text
#         The @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
#         to affect.
def Command_Undo(text : Command_TextObject) -> None:
    if _commandUndoList:
        # Reset the text to the starting point.
        text.Reset()

        # Get rid of the last command applied and remember it.
        lastCommand = _commandUndoList.pop(len(_commandUndoList) - 1)

        # Now apply all remaining commands to the text in order
        # (oldest to newest).
        for command in _commandUndoList:
            command.Execute()

        # Show off what we (un)did.
        print("    undoing command {0:<31}==> \"{1}\"".format(lastCommand.ToString(), text.ToString()))


## Helper function to create a @ref DesignPatternExamples_python.command.command_classes.Command "Command"
#  object that replaces text in the given
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject",
#  adds the command to the undo list and then applies the command
#  to the @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#  Finally, it shows off what was done.
#
#  @param text
#         The @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
#         to affect.
#  @param searchPattern
#         What to look for in the @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#  @param replaceText
#         What to replace the `searchPattern` with.
def Command_ApplyReplaceCommand(text : Command_TextObject, searchPattern : str, replaceText : str) -> None:
    command = Command(text, "Replace", Command_Operation_Replace, searchPattern, replaceText)
    Command_Save_And_Execute(text, command)
    print("    command {0:<31}==> \"{1}\"".format(command.ToString(), text.ToString()))


## Helper function to create a @ref DesignPatternExamples_python.command.command_classes.Command "Command"
#  object that reverses the order of the characters in the given
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject",
#  adds the command to the undo list and then applies the command to the
#  @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject".
#  Finally, it shows what was done.
# 
#  @param text
#         The @ref DesignPatternExamples_python.command.command_classes.Command_TextObject "Command_TextObject"
#         to affect.
def Command_ApplyReverseCommand(text : Command_TextObject) -> None:
    command = Command(text, "Reverse", Command_Operation_Reverse)
    Command_Save_And_Execute(text, command)
    print("    command {0:<31}==> \"{1}\"".format(command.ToString(), text.ToString()))


##  Example of using the @ref command_pattern.
#  
#  The Command pattern is used to encapsulate an operation or command
#  associated with an object so that the command can be applied to
#  the object at a later time.
#  
#  In this exercise, an undo list is implemented using instances of the
#  @ref DesignPatternExamples_python.command.command_classes.Command "Command"
#  class that associate commands defined in this file with a text object.  The
#  commands are applied to the text object in succession then effectively undone.

# ! [Using Command in Python]
def Command_Exercise():
    print()
    print("Command Exercise")

    # The base text object to work from.
    text = Command_TextObject("This is a line of text on which to experiment.")

    print("  Starting text: \"{0}\"".format(text.ToString()))

    # Apply four operations to the text.
    Command_ApplyReplaceCommand(text, "text", "painting")
    Command_ApplyReplaceCommand(text, "on", "off")
    Command_ApplyReverseCommand(text)
    Command_ApplyReplaceCommand(text, "i", "!")

    print("  Now perform undo until back to original")

    # Now undo the four operations.
    Command_Undo(text)
    Command_Undo(text)
    Command_Undo(text)
    Command_Undo(text)

    print("  Final text   : \"{0}\"".format(text.ToString()))

    print("  Done.")
# ! [Using Command in Python]
