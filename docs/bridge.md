# Bridge Pattern{#bridge_pattern}

@image html bridge_diagram.png "Diagram of the bridge pattern"

The Bridge design pattern is used to separate the implementation from the
abstract interface presented to the caller.  This is also colloquially
known as the "pimpl" pattern, since the abstract interface forwards all
method calls to an underlying implementation via a "pointer to the
implementation" or "pimpl".

The Bridge pattern separates the abstraction from the implementation so
that both abstraction and, more importantly, implementation can vary
without affecting the other side of the bridge.  The Bridge pattern is not
limited to a single class with one or more implementations.  The abstract
side can have a hierarchy of classes inheriting from a base abstraction.
The implementation side can also have a parallel hierarchy of inherited
classes.

The key idea is the caller is presented with an abstract class that knows
how to create a specific implementation based on input from the caller.
The definition of the implementation is completely hidden from the caller,
who sees only the abstract class.

That abstract class must be a class since it must contain some kind of
reference to the underlying implementation.

## How to Use

<table>
<caption>Links to the Logger classes (interfaces, functions)</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::Logger "Logger" class
  <td>@ref DesignPatternExamples_csharp.Logger "Logger" class
  <td>@ref DesignPatternExamples_python.bridge.bridge_logger.Logger "Logger" class
  <td>ILogger interface<br>
  CreateLogger()<br>
  DestroyLogger()<br>
</table>

In this example, the Logger class is what the program uses for all logging.
The program logs information at various levels of granularity to some
output.  The program doesn't care where the logged output ends up.

The Logger abstract class can make use of three different implementations
of loggers: File, Console, Null.  Each of these loggers implements the
ILogger interface so the Logger object doesn't have to care about the
implementation details.  And the user of the Logger class has no idea of
how the Logger class does what it does, only that it provides the same
methods regardless of the actual implementation.

In this way, the Logger class is the bridge between the program and the
logger implementations.

Note: The Bridge_NullLogger class is an example of the Null Object pattern.

An alternative implementation would use a class factory method to take
the LoggerType and optional parameter as arguments and return an actual
implementation represented by the ILogger class.  This eliminates the need
for a bridge class altogether and completely hides any details of the
implementation.  In other words, the interface itself is the "bridge".

Basically, the use of an interface and a class factory can hide any
implementation and it works in any programming language that supports the
idea of a base class or interface.

__C++__

@snippet cplusplus/Bridge_Exercise.cpp Using Bridge in C++

__C#__

@snippet csharp/program.cs Using Bridge in C#

__Python__

@snippet python/DesignPatternExamples_python/bridge/bridge_exercise.py Using Bridge in Python

__C__

@snippet c/bridge_exercise.c Using Bridge in C


### See Also
- @ref mainpage "Main Page"
