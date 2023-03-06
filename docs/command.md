# Command Pattern {#command_pattern}

@image html command_diagram.png "Diagram of the command pattern"

The Command pattern is used to associate an object with an operation that
is deferred to at later time for execution.  The command itself is an object
that contains the target of the command (known as the receiver) along with the
operation to perform on the target.  This means the command object can be
treated like any other object, even putting it into a list.

A common application for the Command pattern is an undo buffer.  Another
application is a batch processor.

At its heart, a Command object takes two parameters: The object to work on
and an operation to use.  The operation is typically a function pointer
(in C++) or a delegate (in C#).  A Command object can hold additional
parameters if the associated operation requires additional parameters.

When invoked, the Command object calls the operation with the receiver
object and whatever additional parameters that might be required.  The
invocation is typically a single method called `execute()` so all Command
objects look the same to the entity doing the invocation of the Commands.

It is typical for the Command objects to be created by one entity and
passed to another entity for invocation.

# How to Use

Links to the Command classes descriptions:
- (high level) @ref DesignPatternExamples_cpp::Command "Command class" for operations to do/undo (C++)
- (high level) @ref DesignPatternExamples_csharp.Command "Command class" for operations to do/undo (C#)
- (high level) @ref DesignPatternExamples_cpp::Command_TextObject "Command_TextObject class" representing what is being changed (C++)
- (high level) @ref DesignPatternExamples_csharp.Command_TextObject "Command_TextObject class" representing what is being changed (C#)

For example, a program that supports undo would work like this (this is
a simplistic undo):
1. Define all operations as functions that takes a single receiver (of the
   command) to operate on, along with any necessary additional parameters.
2. Any time an operation other than Undo is invoked by the user:
   1. Create a Command object with the function for that operation along
      with the receiver on which the function applies
   2. Store the Command object in the undo container
   3. Invoke the Command object just created
3. Repeat step 2 until the user selects Undo.
4. Perform the Undo:
   1. If there are any commands to undo then
   2.   Completely reset the receiver that all commands are applied to
   3.   Remove the last Command object from the undo container, if any
   4.   For all Command objects in the undo container, invoke each Command
        in order (oldest to newest) on the receiver.  This puts the receiver
        back into the state it was in before the last command was applied.

This example implements the above algorithm.  A Command_TextObject instance
representing the target of the commands.  The commands themselves are stored in
a Command instance.  A simple stack is used to remember the commands in the
order in which they are applied.  After several commands are applied, the
commands are undone in reverse order.

*Note: In C++, a std::vector<> is used instead of a std::stack<> because there
is no way to iterate over the contents of a stack.*

__C++__

@snippet cplusplus/program.cpp Using Command in C++

__C#__

@snippet csharp/program.cs Using Command in C#


### See Also
- @ref mainpage "Main page"
