# Memento Pattern {#memento_pattern}

The Memento design pattern is used to capture the internal state of an
object without exposing the details of that internal state.  At a later
time, the Memento is used to restore the internal state of the object.

The client asks an object for a snapshot of the object's internal state.
This snapshot is in an opaque form.  The client typically caches this
snapshot for later use (such as restoring the state to a known good state
or as part of the process of implementing an undo system).  When the
client wants to restore the object's state, it passed the snapshot back to
the object and the object changes its internal state to match the given
snapshot.

The python pickling mechanism is a form of the Memento pattern, although in
the process of pickling an object, the entire object is saved off, not just
the internal state; however, the effect is the same.

To implement the Memento state, the object whose state is to be saved off
and later restored must be designed to make it easy to save and restore the
state.  The Private Data pattern can facilitate this by storing the state
of the main class in another class.  That data class can then be more
easily converted to some internal state or the data class instance itself
could be stored in the Memento, which is arguably more effective with
classes that have a lot of internal data elements (less copying).  A class
with only a few data elements would be more efficient serializing the data
elements into another form such as strings or binary images.

In the Command pattern, a simplistic undo/redo stack was created that
required remembering commands used to get to a particular state.  To undo
changes to the state, the state was cleared then the commands up to but not
including the command to undo were replayed, rebuilding the state.

Using Mementos, the state can be saved before each command.  To undo a
command, the state saved before that command could be restored.  No need to
replay the commands at all.  This makes for a more efficient undo process.
However, if the state is very large, such as in a paint program, the undo
may have to spool the saved states to disk or provide a combination of
commands and mementos, where the state is saved periodically and the
commands to get to the next save state are remembered and replayed.

# How to Use

The example used here is a snapshot of a text object.  This is then used
to create an undo stack.  In fact, this is the same example as used for
the Command pattern but this example shows how mementos are generally more
efficient than commands for creating an undo stack.

__C++__

@snippet cplusplus/program.cpp Using Memento in C++

__C#__

@snippet csharp/program.cs Using Memento in C#


### See Also
- @ref mainpage "Main page"