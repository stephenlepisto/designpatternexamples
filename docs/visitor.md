# Visitor Pattern {#visitor_pattern}

@image html visitor_diagram.png "Diagram of the visitor pattern"

The Visitor pattern is a way of separating data from operations where the
operations can be applied after the list of data is created all while
leaving the data and operations as objects.  The visitor pattern works best
where the number of data classes changes very infrequently.  The data
classes and associated Visitor class must be engineered to support the
Visitor pattern.

Probably the best way to think of the Visitor pattern is as a way to apply
operations to a collection of data classes without changing the data
classes themselves.  The data classes are set up to support a visitor class
and from then on can support any visitor that derives from that visitor
class.

All Visitor classes derive from a known Visitor base class provided by the
the data class implementation -- natural since the data class
implementation must support visitors so it must dictate the interface to
the visitors.

As originally envisioned, the Visitor pattern is a rather clunky pattern.

Here's the first clunky part: An operation is defined as a class derived
from the Visitor base class.  On that base class are a number of virtual
methods called `visit()` that each take a single parameter the type of which
is one of the derived Element classes.  If there are five derived Element
classes, there are five versions of the `visit()` method.  These virtual
methods do nothing by default.  Each derived visitor class that provides an
operation must override the appropriate `visit()` method for the Element type
that operation is interested in.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
class ElementOne; // forward declaration
class ElementTwo; // forward declaration

class Visitor
{
public:
    virtual void visit(ElementOne* pData) { };
    virtual void visit(ElementTwo* pData) { };
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here's the second clunky part: The base Element class must define a pure
virtual method typically called `accept()` that accepts the Visitor base
class.  Then every derived Element class must implement the `accept()`
method.  (Technically, the base Element class could have a default
implementation of visit() but since the visitor pattern needs to apply to
all elements in the list, every derived Element class must provide an
implementation anyhow.  The reason for this is explained after the below
example.)

In the following, each of the element classes must provide a definition for the
`accept()` method (required because it is pure virtual in the interface).  To
take advantage of polymorphism to select the right visit() method, the following
`accept()` methods need to be repeated in each Element class so the `this`
pointer is correctly typed to match the correct overloaded visit() methods:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//----------------------------------------------------------
// The Element declaration, which will be visited.
//----------------------------------------------------------

// Each element must implement this interface in order to accept visitors.
class IElementVisitInterface
{
public:
    virtual ~IElementVisitInterface() {}
    virtual void accept(Visitor* pVisitor) = 0;
};

// Declare the element classes, which inherit from the above interface.
// If the class Visitor has been declared (for example, as above) then
// we can provide definitions for the `accept()` method.
//
// However, the Visitor class requires forward declarations to these
// element classes in order to be fully defined.

class ElementOne : public IElementVisitInterface
{
public:
    void accept(Visitor* pVisitor)
    {
        pVisitor->visit(this);
    }
};

class ElementTwo : public IElementVisitInterface
{
public:
    void accept(Visitor* pVisitor)
    {
        pVisitor->visit(this);
    }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Finally, the visitor implementations can be defined now that the Element classes
are defined.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//----------------------------------------------------------
// The Visitor declaration/definition, which will do the visiting.
//----------------------------------------------------------


// The following Visitor definitions could appear in a .h file or in a .cpp
// file, but these definitions must appear after the `class Visitor`
// declaration.

// VisitorOperationOne is interested in two different elements.
class VisitorOperationOne : public Visitor
{
public:
    void visit(ElementOne* pData)
    {
        // Interested in ElementOne
    }

    void visit(ElementTwo* pData)
    {
        // Also interested in ElementTwo
    }
};

// VisitorOperationTwo is interested in only one element.
class VisitorOperationTwo : public Visitor
{
public:
    void visit(ElementTwo* pData)
    {
        // Only interested in ElementTwo
    }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The above rigamarole is needed because of how polymorphism works in C++.
Putting the `accept()` method into the base class won't work because the
'this' value will get interpreted as the base class and not the derived
class (a well-known limitation known as "class slicing" because the derived
class gets sliced off when determining matches in overloaded methods).

C# is a lot more flexible in terms of declaration by using interfaces.
Since C# uses a two pass compilation, there is no need for forward
declarations or interleaved declarations.  This might be made even simpler
in C# using reflection but that is an advanced topic that greatly obscures
the example.

Using the visitor pattern looks like this:
1. Create list of elements
2. Create a visitor object
3. For all elements, pass the visitor to each element

Although the visitor pattern was originally defined as an object-oriented
approach to applying (mostly) arbitrary operations to data objects, it can
be argued that any mechanism that applies an operation to all or a select
number of elements in a container is an application of the visitor pattern,
even if that mechanism uses a function and not an object.  For example, a
function that takes a list of elements and does something to each element
is a form of visitor pattern.  In many cases, using a function is generally
simpler to implement although the function needs to test for the types of
elements it is visiting rather than letting the language overloading do
that automatically.

A function is also not as sensitive to changes in the element interface.
If a new element type is added, the function will never know unless the
function is explicitly updated to know about the new type -- assuming that
particular function even needs to know about the new element type.

On the other hand, if a visitor base class was updated with a new visit()
method for the new element class, all visitors derived from that base class
must be recompiled even if none of the visitors care about the new data
type.

Note: The C++ Standard Template Library (STL) has an algorithm called
for_each().  This applies a user-defined function to every element in the
container passed to the `for_each()` function.  This is a version of the
Visitor pattern, where the visitor is a user-supplied function that is
called with every element in the container.  The elements have no knowledge
of this visitor, making for a much more elegant solution than described
in the C++ example above (the power of C++ templates in action!).

# How to Use

Links to the key Visitor classes and interfaces:

## Visitors that Visit Elements
- @ref DesignPatternExamples_cpp::ElementVisitor "ElementVisitor base class" for visitors (C++)
- @ref DesignPatternExamples_csharp.Visitor "Visitor base class" for visitors (C#)
- @ref DesignPatternExamples_cpp::VisitorOperationOne "VisitorOperationOne class" for visitors (C++)
- @ref DesignPatternExamples_csharp.OrderVisitor "OrderVisitor class" for visitors (C#)

## Elements to be Visited
- @ref DesignPatternExamples_cpp::IElementVisitInterface "IElementVisitInterface interface" for elements that accept visitors (C++)
- @ref DesignPatternExamples_csharp.ISupportVisitors "ISupportVisitors interface" for elements that accept visitors (C#)
- @ref DesignPatternExamples_cpp::ElementDerivedOne "ElementDerivedOne class" (C++)
- @ref DesignPatternExamples_csharp.Visitor_Shop "Visitor_Shop base class for elements" (C#)
- @ref DesignPatternExamples_cpp::ElementDerivedTwo "ElementDerivedTwo class" (C++)

The example provided here shows a C++ and a C# version of the same visitor
pattern.  The C# version takes advantage of C#'s two-pass compilation to
eliminate the need for forward declarations.

__C++__

@snippet cplusplus/program.cpp Using Visitor in C++

__C#__

@snippet csharp/program.cs Using Visitor in C#


### See Also
- @ref mainpage "Main page"
