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

<table>
<caption>Links to the Flyweight classes</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
<tr>
  <td>@ref DesignPatternExamples_cpp::Flyweight_Class "Flyweight_Class" class
  <td>@ref DesignPatternExamples_csharp.Flyweight_Class "Flyweight_Class" class
  <td>@ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class" class
<tr>
  <td>@ref DesignPatternExamples_cpp::Flyweight_Context "Flyweight_Context" struct
  <td>@ref DesignPatternExamples_csharp.Flyweight_Context "Flyweight_Context" struct
  <td>@ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Context "Flyweight_Context" class
<tr>
  <td>@ref DesignPatternExamples_cpp::BigResource "BigResource" class
  <td>@ref DesignPatternExamples_csharp::BigResource "BigResource" class
  <td>@ref DesignPatternExamples_python.flyweight.flyweight_classes.BigResource "BigResource" class
<tr>
  <td>@ref DesignPatternExamples_cpp::BigResourceManager "BigResourceManager" class
  <td>@ref DesignPatternExamples_csharp.BigResourceManager "BigResourceManager" class
  <td>@ref DesignPatternExamples_python.flyweight.flyweight_classes.BigResourceManager "BigResourceManager" class
</table>

This example uses an image as the "big" resource.  The image is composed of a
set of smaller images, all the same size, and all arranged in a single
horizontal row.  Each smaller image is associated with one Flyweight class
instance and the smaller image's background is the number of the Flyweight
class instance.  For example, for 3 flyweight instances:

```
+----------------------------++----------------------------++----------------------------+
|0000000000000000000000000000||1111111111111111111111111111||2222222222222222222222222222|
|0000000000000000000000000000||1111111111111111111111111111||2222222222222222222222222222|
|0000000000000000000000000000||1111111111111111111111111111||2222222222222222222222222222|
+----------------------------++----------------------------++----------------------------+
```

The flyweight class represents a position for that image as the context, along
with an offset into the big resource to the left edge of that flyweight class
instance's image.  The flyweight class also contains velocity information for
moving the flyweight instance around a display.  Of course, everything is in
text but it's the thought that counts.

Example output:

```
Flyweight Exercise
  The image rendered 5 times:
     39/1000 iterations [press a key to exit early]
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+----------------------------+~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|0000000000000000000000000000|~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|0000000000000000000000000000|~~
  ~~~~~~+----------------------------+~~~~~~~~~~~~|0000000000000000000000000000|~~
  ~~~~~~|1111111111111111111111111111|~~~~~~~~~~~~+----------------------------+~~
  ~~~~~~|1111111111111111111111111111|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~~~~~|1111111111111111111111111111|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~+----------------------------+---+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~|222222222222222222222222+----------------------------+~~~~~~~~~~~~~~~~~~~~~~~
  ~~|222222222222222222222222|4444444444444444444444444444|~~~~~~~~~~~~~~~~~~~~~~~
  ~~|222222222222222222222222|4444444444444444444444444444|------------+~~~~~~~~~~
  ~~+------------------------|4444444444444444444444444444|333333333333|~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~+----------------------------+333333333333|~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|3333333333333333333333333333|~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+----------------------------+~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Done.
```

__C++__

@snippet cplusplus/Flyweight_Exercise.cpp Using Flyweight in C++

__C#__

@snippet csharp/program.cs Using Flyweight in C#

__Python__

@snippet python/DesignPatternExamples_python/flyweight/flyweight_exercise.py Using Flyweight in Python

### See Also
- @ref mainpage "Main page"
