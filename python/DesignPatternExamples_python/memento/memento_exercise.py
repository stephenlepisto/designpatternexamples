## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.memento.memento_exercise.Memento_Exercise "Memento_Exercise"()
# function as used in the @ref memento_pattern.


##  Example of using the @ref memento_pattern.
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

    print("  Done.")
# ! [Using Memento in Python]
