# Null Object Pattern {#nullobject_pattern}

@image html nullobject_diagram.png "Diagram of the Null Object pattern"

The Null Object pattern is used in those places where a default object of
some kind is needed to do nothing.  A Null (or Default) Object is an actual
object that can be called on but does not do anything.  This is not the
same thing as a null reference or pointer, which represents an
uninitialized variable.

A Null Object works only in those places where abstract classes or
interfaces are used to represent all objects of a particular kind.  One of
those kinds can be a Null Object.  So if you have an interface that
represents commands that can be applied to a picture, it may be useful to
create a command that does nothing (in assembly language parlance, a NOP or
No Operation).

The concept of a "do nothing" object can be extended to functions,
typically in situations where pointers to the functions (or delegates) are
stored in dynamic lists to be executed in order.  A function that fits in
the list but otherwise does nothing when called is a Null Object (in this
case, the function is treated as an object).

During initial development of such a system, it is often quite useful to
have a Null Object in place.  Such objects are easy to implement so no bugs
are likely to be present.  Then the rest of the system that actually works
with the commands can be created, using the Null Object as a stand-in for
real commands.

An explicit class representing a Null Object is not always needed.  A class
that does something could be designed to do nothing if created in a certain
way or a flag is set (or cleared) on the class instance.  The idea is there
is an object that does nothing but acts as a stand-in for a real object
that does do something.

For one example, the @ref bridge_pattern example has a Bridge_NullLogger class
that represents a logger that does nothing.  This is a classic case of a null
object.

# How to Use

<table>
<caption>Links to the Null Object classes or functions</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveProcessor "MoveProcessor" class
  <td>@ref DesignPatternExamples_csharp.MoveProcessor "MoveProcessor" class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveProcessor "MoveProcessor" class
  <td>MoveProcessor_ExecuteMoveList() function<br>
      MoveProcessor_ShowMoveList()
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveCommand "MoveCommand" base class
  <td>@ref DesignPatternExamples_csharp::MoveCommand "MoveCommand" base class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommand "MoveCommand" base class
  <td>MoveCommand structure<br>
      MoveCommand_Create()<br>
      MoveCommand_Destroy()
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveCommandNone "MoveCommandNone" (Null Object) class
  <td>@ref DesignPatternExamples_csharp.MoveCommandNone "MoveCommandNone" (Null Object) class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommandNone "MoveCommandNone" (Null Object) class
  <td>MoveCommandNone_Execute() function
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveCommandLeft "MoveCommandLeft" class
  <td>@ref DesignPatternExamples_csharp.MoveCommandLeft "MoveCommandLeft" class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommandLeft "MoveCommandLeft" class
  <td>MoveCommandLeft_Execute() function
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveCommandRight "MoveCommandRight" class
  <td>@ref DesignPatternExamples_csharp.MoveCommandRight "MoveCommandRight" class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommandRight "MoveCommandRight" class
  <td>MoveCommandRight_Execute() function
<tr>
  <td>@ref DesignPatternExamples_cpp::MoveCommandUp "MoveCommandUp" class
  <td>@ref DesignPatternExamples_csharp.MoveCommandUp "MoveCommandUp" class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommandUp "MoveCommandUp" class
  <td>MoveCommandUp_Execute() function
<tr>
  <td>@ref DesignPatternExamples_csharp.MoveCommandDown "MoveCommandDown"
  <td>@ref DesignPatternExamples_csharp.MoveCommandDown "MoveCommandDown" class
  <td>@ref DesignPatternExamples_python.nullobject.null_object.MoveCommandDown "MoveCommandDown" class
  <td>MoveCommandDown_Execute() function
</table>

The somewhat contrived example here parses a string for single letter move
commands, converting them into class objects (C++, C#, Python) or functions (C)
for each command.  For all other characters in the string, a null object or
function is used to represent the move command.  Bad commands are not simply
ignored so as to allow for showing them along with the command class assigned
to execute the command.

This example also uses a form of the @ref command_pattern the
@ref interpreter_pattern.

__C++__

@snippet cplusplus/NullObject_Exercise.cpp Using NullObject in C++

__C#__

@snippet csharp/program.cs Using NullObject in C#

__Python__

@snippet python/DesignPatternExamples_python/nullobject/nullobject_exercise.py Using NullObject in Python

__C__

@snippet c/NullObject_Exercise.c Using NullObject in C

### See Also
- @ref mainpage "Main page"
