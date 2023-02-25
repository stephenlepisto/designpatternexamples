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
with the core class taking whatever parameters it needs to (by definition,
the core class does not take a decorator; decorators are applied to the
core class by wrapping the core class).

# How to Use

In this example, the core class is called TextElement and up to three
decorators can be applied (BodyElement, ParagraphElement, and
EmphasisElement).  Decorators should ideally be designed to be applied
in any order but as this example shows, there is often a specific order
for the decorators to be used.  This order would be specified in the
documentation.  All decorators and the TextElement class implement the
IRenderElement interface.

Frequently the decorator pattern is combined with the Composite pattern
so that wrapped elements can contain child elements that are each wrapped
by one or more decorators (basically, the classes that participate in the
Composite pattern also support decorators).  This example does not show this
particular implementation.

__C++__

@snippet cplusplus/program.cpp Using Decorator in C++

__C#__

@snippet csharp/program.cs Using Decorator in C#


### See Also
- @ref mainpage "Main page"
