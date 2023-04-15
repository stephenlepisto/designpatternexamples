# Decorator Pattern {#decorator_pattern}

@image html decorator_diagram.png "Diagram of the decorator pattern"

The decorator pattern provides a way to extend capabilities to an instance
of a class without altering the original class.  The intention is to extend
the capabilities at runtime, providing a dynamic and potentially user-driven
level of extension.  This is done by having the decorators provide the same
interface as the object being decorated.  that way, the decorators can wrap
the object or other decorators and still look like the same kind of object
to the calling entity.

This kind of architecture requires cooperation among all the decorators and
classes being decorated by having each class implement the same abstract
interface (again, so all the classes look the same to each other).  The
decorators then wrap any object with the same abstract interface.  The 
ability of decorators being able to wrap other decorators automatically
builds a kind of nested hierarchy, similar to a Composite pattern except
that the decorators don't typically support multiple children in a single
decorator.

Since each decorator looks like any other decorator (of the same kind),
the decorators need to be designed to work in pretty much any order,
with the core or concrete class taking whatever parameters it needs to be
instantiated (by definition, the concrete class does not take a decorator;
decorators are applied to the concrete class by wrapping the concrete class).

# How to Use

<table>
<caption>Links to the Decorator classes</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::IRenderElement "IRenderElement" interface
  <td>@ref DesignPatternExamples_csharp.IRenderElement "IRenderElement" interface
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement" interface
  <td>Not Applicable
<tr>
  <td>@ref DesignPatternExamples_cpp::TextElement "TextElement" class
  <td>@ref DesignPatternExamples_csharp.TextElement "TextElement" class
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.TextElement "TextElement" class
  <td>DynamicString structure
<tr>
  <td>@ref DesignPatternExamples_cpp::Decorator "Decorator" base class
  <td>@ref DesignPatternExamples_csharp.Decorator "Decorator" base class
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.Decorator "Decorator" base class
  <td>_Decorate() function
<tr>
  <td>@ref DesignPatternExamples_cpp::WhiteBackgroundDecorator "WhiteBackgroundDecorator" derived class
  <td>@ref DesignPatternExamples_csharp.WhiteBackgroundDecorator "WhiteBackgroundDecorator" derived class
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.WhiteBackgroundDecorator "WhiteBackgroundDecorator" derived class
  <td>WhiteBackgroundDecorator() function
<tr>
  <td>@ref DesignPatternExamples_cpp::UnderlineDecorator "UnderlineDecorator" derived class
  <td>@ref DesignPatternExamples_csharp.UnderlineDecorator "UnderlineDecorator" derived class
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.UnderlineDecorator "UnderlineDecorator" derived class
  <td>UnderlineDecorator() function
<tr>
  <td>@ref DesignPatternExamples_cpp::RedForegroundDecorator "RedForegroundDecorator" derived class
  <td>@ref DesignPatternExamples_csharp.RedForegroundDecorator "RedForegroundDecorator" derived class
  <td>@ref DesignPatternExamples_python.decorator.decorator_classes.RedForegroundDecorator "RedForegroundDecorator" derived class
  <td>RedForegroundDecorator() function
</table>

In this example, the concrete class is called TextElement and up to three
decorators can be applied (WhiteBackgroundDecorator, UnderlineDecorator, and
ReadForegroundDecorator).  Decorators should ideally be designed to be applied
in any order, as is the case here.  If an order is required, the documentation
that comes with the decorators would explain it.  All decorators implement a base
class that manages the wrapped elements (and implements the IRenderElement
interface) and the TextElement class just implements the IRenderElement
interface.

__C++__

@snippet cplusplus/Decorator_Exercise.cpp Using Decorator in C++

__C#__

@snippet csharp/program.cs Using Decorator in C#

__Python__

@snippet python/DesignPatternExamples_python/decorator/decorator_exercise.py Using Decorator in Python

__C__

@snippet c/decorator_exercise.c Using Decorator in C


### See Also
- @ref mainpage "Main page"
