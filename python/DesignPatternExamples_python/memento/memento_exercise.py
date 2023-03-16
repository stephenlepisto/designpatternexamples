## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.memento.memento_exercise.Memento_Exercise "Memento_Exercise"()
# function as used in the @ref memento_pattern.

from io import StringIO

from .memento import IMemento, Memento_TextObject

## The list of memento objects that form a series of snapshots in time
#  of a Memento_TextObject.
_mementoUndoList = [] # type: list[IMemento]

## Take a snapshot of the given text object associated with the name of
#  given operation.
#
#  @param text
#         The Memento_TextObject to take a snapshot of.
#  @param operation
#         A string describing the operation that will be applied after the
#         snapshot is taken.
def Memento_SaveForUndo(text : Memento_TextObject, operation : str) -> None:
    memento = text.GetMemento(operation)
    _mementoUndoList.append(memento)


## An operation to search and replace text in a Memento_TextObject.
#
#  @param source
#         The Memento_TextObject to affect.
#  @param searchPattern
#         What to look for in the Memento_TextObject.
#  @param replaceText
#         What to replace the searchPattern with.
def Memento_Operation_Replace(source : Memento_TextObject, searchPattern : str, replaceText : str) -> None:
    source.SetText(source.Text().replace(searchPattern, replaceText))


## An operation to reverse the characters in the given Memento_TextObject.
#
#  @param source
#         The Memento_TextObject to affect.
def Memento_Operation_Reverse(source : Memento_TextObject) -> None:
    output = StringIO()
    text = source.Text()
    textLength = len(text)
    for index in range(0, textLength):
        output.write(text[textLength - 1 - index])
    source.SetText(output.getvalue())


## Perform an undo on the given Command_TextObject, using the mementos in the
#  "global" undo list.  If the undo list is empty, nothing happens.
#
#  @param text
#         The Command_TextObject to affect.
def Memento_Undo(text : Memento_TextObject) -> None:
    if _mementoUndoList:
        lastMemento = _mementoUndoList.pop()
        text.RestoreMemento(lastMemento)

        # Show off what we (un)did.
        print("    undoing operation {0:<31}: \"{1}\"".format(lastMemento.Name(), text.ToString()))


## Helper function to replace a pattern with another string in the
#  given Memento_TextObject after adding a snapshot of the text
#  object to the undo list.  Finally, it shows off what was done.
#
#  @param text
#         The Memento_TextObject to affect.
#  @param searchPattern
#         What to look for in the Memento_TextObject.
#  @param replaceText
#         What to replace the searchPattern with.
def Memento_ApplyReplaceOperation(text : Memento_TextObject, searchPattern : str, replaceText : str) -> None:
    operationName = "Replace '{0}' with '{1}'".format(searchPattern, replaceText)
    Memento_SaveForUndo(text, operationName)
    Memento_Operation_Replace(text, searchPattern, replaceText)
    print("    operation {0:<31}: \"{1}\"".format(operationName, text.ToString()))


## Helper function to reverse the order of the characters in the
#  given Memento_TextObject after adding a snapshot of the text
#  object to an undo list.  Finally, it shows what was done.
#
#  @param text
#         The Memento_TextObject to affect.
def Memento_ApplyReverseOperation(text : Memento_TextObject) -> None:
    operationName = "Reverse"
    Memento_SaveForUndo(text, operationName)
    Memento_Operation_Reverse(text)
    print("    operation {0:<31}: \"{1}\"".format(operationName, text.ToString()))


## Example of using the @ref memento_pattern.
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

# ! [Using Memento in Python]
def Memento_Exercise():
    print()
    print("Memento Exercise")

    # Start with a fresh undo list.
    _mementoUndoList.clear()

    # The base text object to work from.
    text = Memento_TextObject("This is a line of text on which to experiment.")

    print("  Starting text: \"{0}\"".format(text.ToString()))

    # Apply four operations to the text.
    Memento_ApplyReplaceOperation(text, "text", "painting")
    Memento_ApplyReplaceOperation(text, "on", "off")
    Memento_ApplyReverseOperation(text)
    Memento_ApplyReplaceOperation(text, "i", "!")

    print("  Now perform undo until back to original")

    # Now undo the four operations.
    Memento_Undo(text)
    Memento_Undo(text)
    Memento_Undo(text)
    Memento_Undo(text)

    print("  Final text   : \"{0}\"".format(text.ToString()))

    print("  Done.")
# ! [Using Memento in Python]
