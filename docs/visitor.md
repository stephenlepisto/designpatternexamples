# Visitor Pattern {#visitor_pattern}

@image html visitor_diagram.png "Diagram of the visitor pattern"

The Visitor pattern is a way of separating data from operations where the
operations can be applied after the list of data is created all while
leaving the data and operations as objects.  The visitor pattern works best
where the number of data classes changes very infrequently.  This is because
the data classes and associated Visitor class must be engineered to support the
Visitor pattern.

The Visitor pattern is a way to use operations on or with a collection of
data classes without changing the data classes themselves.  The data classes
are set up to support a visitor class and from then on can support any visitor
that derives from that visitor class.

All Visitor classes derive from a known Visitor base class provided by the
data class implementation.  This is a consequence of the fact that the data
class must support visitors so it must dictate the interface to the visitors.

The data can be organized in a flat list or in a hierarchical tree.  The root
of the list or tree is responsible for making sure a given visitor instance
visits all the elements.  At the core of the Visitor pattern are the following
two methods.

The data classes implement an "accept" method like the following (the name
"accept" is convention only):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
class SomeDataType : public ISupportVisitors
{
public:
    void accept(Visitor visitor)
    {
        visitor.VisitSomeDataType(this);
    }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

All data elements, including the root of the data list or tree, inherits from
the ISupportVisitors interface, which declares the `accept()` method and
therefore must be implemented in every data class.  The idea is for the visitor
to be given the concrete class representing a specific data type, so the
visitor can access the data type.

The Visitor implements one or more "visit" methods, one for each data class:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
class SomeVisitor : public VisitorBase
{
public:
    void visitSomeDataType(SomeDataType data)
    {
        // Do something to or with the data object.
    }
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The key to making this work is for all visitors to inherit from one base class
where each of the VisitXXX() methods (one for each data type) does nothing but
can be overridden in the derived class to take some action.  Here is an example
base class for all visitors:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
class VisitorBase
{
public:
    virtual void visitSomeDataType(SomeDataType* data) {}
    virtual void visitSomeOtherDataType(SomeOtherDataType* data) {}
    virtual void visitSomeThirdDataType(SomeThirdDataType* data) {}
    // etc.
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The derived Visitor class would override only the method or methods they are
interested in.

*Note: It is possible to use `visit(SomeDataType* data()`, `visit(SomeOtherDataType* data)()`,
etc., if the programming language being used supports overloaded methods.
Which approach to use is a matter of style and preference.*

Adding new data types requires adding a new VisitXXX() method to the Visitor
base class; this is why the recommendation to use the Visitor pattern only when
the data types are going to change infrequently.

# How to Use

<table>
<caption>Links to the key Visitor classes and interfaces</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
<tr>
<td colspan="3">__Visitors that Visit Elements__
<tr>
  <td>@ref DesignPatternExamples_cpp::Visitor "Visitor" base class
  <td>@ref DesignPatternExamples_csharp.Visitor "Visitor" base class
  <td>@ref DesignPatternExamples_python.visitor.visitor_class.Visitor "Visitor" base class
<tr>
  <td>@ref DesignPatternExamples_cpp::OrderVisitor "OrderVisitor" class
  <td>@ref DesignPatternExamples_csharp.OrderVisitor "OrderVisitor" class
  <td>@ref DesignPatternExamples_python.visitor.visitor_ordervisitor.OrderVisitor "OrderVisitor" class
<tr>
<td colspan="3">__Elements to be Visited__
<tr>
  <td>@ref DesignPatternExamples_cpp::Visitor_Shop "Visitor_Shop" base class
  <td>@ref DesignPatternExamples_csharp.Visitor_Shop "Visitor_Shop" base class
  <td>@ref DesignPatternExamples_python.visitor.visitor_visitor_shop.Visitor_Shop "Visitor_Shop" base class
<tr>
  <td>@ref DesignPatternExamples_cpp::Visitor_Restaurant "Visitor_Restaurant" example class
  <td>@ref DesignPatternExamples_csharp.Visitor_Restaurant "Visitor_Restaurant" example class
  <td>@ref DesignPatternExamples_python.visitor.visitor_element_classes.Visitor_Restaurant "Visitor_Restaurant"
</table>

The example provided here shows a C++, a C#, and a Python version of the same visitor
pattern.

__C++__

@snippet cplusplus/Visitor_Exercise.cpp Using Visitor in C++

__C#__

@snippet csharp/program.cs Using Visitor in C#

__Python__

@snippet python/DesignPatternExamples_python/visitor/visitor_exercise.py Using Visitor in Python

### See Also
- @ref mainpage "Main page"
