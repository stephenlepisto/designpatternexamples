# Flyweight Pattern {#flyweight_pattern}

@image html flyweight_diagram.png "Diagram of the flyweight pattern"

The flyweight pattern is used to represent some resource that can be shared
multiple times.  The flyweight class contains just enough information to
identify the resource and some context in which the instance of each
flyweight class is used.  Instances of flyweight classes are always
obtained through a class factory that is provided with the context
information as a parameter.

The intent is to represent the shared resource with a small, lightweight
class instance that can be used many times without incurring large
memory penalties that might occur if the shared resource was actually
duplicated many times.

An early form of flyweight class is a handle to a resource.  The handle
was typically a 32-bit value and could be easily shared and passed around
with minimal impact to the system.  The drawback is context information
could not be easily attached to the handle.

The contents of a flyweight class typically consists of a handle to the
resource and some context information.  The context information is provided
by the caller to the flyweight factory to be inserted into a new instance
of the flyweight class.

## How to Use

Links to the Flyweight_Class and BigResource class description:
- @ref DesignPatternExamples_cpp::Flyweight_Class "Flyweight_Class class" (C++)
- @ref DesignPatternExamples_csharp.Flyweight_Class "Flyweight_Class class" (C#)
- @ref DesignPatternExamples_cpp::BigResource "BigResource class" (C++)
- @ref DesignPatternExamples_csharp::BigResource "BigResource class" (C#)

This example uses an image as the "big" resource.  The flyweight class
represents a position for that image as the context.  The flyweight class
also contains velocity information for moving the flyweight instance
around a display.  Of course, everything is in text but it's the thought
that counts.

__C++__

@snippet cplusplus/program.cpp Using Flyweight in C++

__C#__

@snippet csharp/program.cs Using Flyweight in C#


### See Also
- @ref mainpage "Main page"
