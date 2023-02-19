// The Visitor pattern is a way of separating data from operations where the
// operations can be applied after the list of data is created all while
// leaving the data and operations as objects.  The visitor pattern works best
// where the number of data classes changes very infrequently.  The data
// classes and associated Visitor class must be engineered to support the
// Visitor pattern.
//
// Probably the best way to think of the Visitor pattern is as a way to apply
// operations to a collection of data classes without changing the data
// classes themselves.  The data classes are set up to support a visitor class
// and from then on can support any visitor that derives from that visitor
// class.
//
// All Visitor classes derive from a known Visitor base class provided by the
// the data class implementation -- natural since the data class
// implementation must support visitors so it must dictate the interface to
// the visitors.
//
// As originally envisioned, the Visitor pattern is a rather clunky pattern.
//
// Here's the first clunky part: An operation is defined as a class derived
// from the Visitor base class.  On that base class are a number of virtual
// methods called visit() that each take a single parameter the type of which
// is one of the derived Element classes.  If there are five derived Element
// classes, there are five versions of the visit() method.  These virtual
// methods do nothing by default.  Each derived visitor class that provides an
// operation must override the appropriate visit() method for the Element type
// that operation is interested in.
//
// Here's the second clunky part: The base Element class must define a pure
// virtual method typically called accept() that accepts the Visitor base
// class.  Then every derived Element class must implement the accept()
// method.  (Technically, the base Element class could have a default
// implementation of visit() but since the visitor pattern needs to apply to
// all elements in the list, every derived Element class must provide an
// implementation anyhow.  The reason for this is explained after the below
// example.)
//
// At least this implementation of Element.accept() is always the same, even
// if it needs to be repeated in every derived Element class:
//     void accept(Visitor* pVisitor)
//     {
//         pVisitor->visit(this);
//     }
//
// Here's the third clunky part: The definitions of the Element base class and
// Visitor base class must occur in the right order to avoid a circular
// dependency.  In C++, it looks like this:
//
//     class Visitor; //  forward declaration
//
//     class ElementBase
//     {
//         public:
//         virtual void accept(Visitor* pVisitor) = 0;
//     };
//
//     // Declare the derived element classes.  Cannot provide implementation
//     // here because we don't know yet what the Visitor class looks like.
//     class ElementDerivedOne : public ElementBase
//     {
//     public:
//         void accept(Visitor* pVisitor);
//     };
//
//     class ElementDerivedTwo : public ElementBase
//     {
//     public:
//         void accept(Visitor* pVisitor);
//     };
//
//
//     // Now that we have the derived element classes, we can make use of them.
//     // Technically, we could use class forwarding here too and move this
//     // declaration to after ElementBase but it makes more sense to define
//     // this here with the derived visitor classes.
//     class Visitor
//     {
//         public:
//         virtual void visit(ElementDerivedOne* pData) { };
//         virtual void visit(ElementDerivedTwo* pData) { };
//     };
//
//
//     // Implement the derived classes here (or declare them here and
//     // implement them somewhere else).
//     class VisitorOperationOne : public Visitor
//     {
//     public:
//         void visit(ElementDerivedOne* pData)
//         {
//             // Interested in ElementDerivedOne
//         }
//
//         void visit(ElementDerivedTwo* pData)
//         {
//             // Also interested in ElementDerivedTwo
//         }
//     };
//
//     class VisitorOperationTwo : public Visitor
//     {
//     public:
//         void visit(ElementDerivedTwo* pData)
//         {
//             // Only interested in ElementDerivedTwo
//         }
//     };
//
//
//     // Now that the Visitor classes and its derivations have been declared or
//     // defined, we can finally implement the accept() method on each derived
//     // Element class.  This can only be done after the Visitor base class is
//     // declared.
//     void ElementDerivedOne::accept(Visitor* pVisitor)
//     {
//         pVisitor->visit(this);
//     }
//
//     void ElementDerivedTwo::accept(Visitor* pVisitor)
//     {
//         pVisitor->visit(this);
//     }
//
//     // Type of the composite element list.
//     typedef std::vector<std::unique_ptr<ElementBase>> ElementBaseList;
//
//
// The above rigamarole is needed because of how polymorphism works in C++.
// Putting the accept() method into the base class won't work because the
// 'this' value will get interpreted as the base class and not the derived
// class (a well-known limitation known as "class slicing" because the derived
// class gets sliced off when determining matches in overloaded methods).
//
// C# is a lot more flexible in terms of declaration by using interfaces.
// Since C# uses a two pass compilation, there is no need for forward
// declarations or interleaved declarations.  This might be made even simpler
// in C# using reflection but that is an advanced topic that greatly obscures
// the example.
//
// Using the visitor pattern looks like this:
// 1. Create list of elements
// 2. Create a visitor object
// 3. For all elements, pass the visitor to each element
//
// Although the visitor pattern was originally defined as an object-oriented
// approach to applying (mostly) arbitrary operations to data objects, it can
// be argued that any mechanism that applies an operation to all or a select
// number of elements in a container is an application of the visitor pattern,
// even if that mechanism uses a function and not an object.  For example, a
// function that takes a list of elements and does something to each element
// is a form of visitor pattern.  In many cases, using a function is generally
// simpler to implement although the function needs to test for the types of
// elements it is visiting rather than letting the language overloading do
// that automatically.
//
// A function is also not as sensitive to changes in the element interface.
// If a new element type is added, the function will never know unless the
// function is explicitly updated to know about the new type -- assuming that
// particular function even needs to know about the new element type.
//
// On the other hand, if a visitor base class was updated with a new visit()
// method for the new element class, all visitors derived from that base class
// must be recompiled even if none of the visitors care about the new data
// type.
//
// Note: The C++ Standard Template Library (STL) has an algorithm called
// for_each().  This applies a user-defined function to every element in the
// container passed to the for_each() function.  This is a version of the
// Visitor pattern, where the visitor is a user-supplied function that is
// called with every element in the container.  The elements have no knowledge
// of this visitor, making for a much more elegant solution than described
// in the C++ example above (the power of C++ templates in action!).
//
// The demonstration example here is a C# version of the big C++ example
// described earlier but taking advantage of C#'s two-pass compilation to
// eliminate the need for forward declarations.
//
// See the Visitor_Element_Classes.cs file for details on the element classes
// that can accept a visitor.

using System;

namespace DesignPatternExamples
{
    /// <summary>
    /// An operation to apply to one or more data elements.  This is the
    /// Visitor.
    /// </summary>
    class VisitorOperationOne : ElementVisitor
    {
        /// <summary>
        /// We want to visit elements of type ElementDerivedOne.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        public override void visit(ElementDerivedOne element)
        {
            Console.WriteLine("  --> {0} received element #{1} (type {2})", GetType().Name, element.InstanceId, element.GetType().Name);
        }

        /// <summary>
        /// We also want to visit elements of type ElementDerivedTwo.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        public override void visit(ElementDerivedTwo element)
        {
            Console.WriteLine("  --> {0} received element #{1} (type {2})", GetType().Name, element.InstanceId, element.GetType().Name);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// An operation to apply to one or more data elements.  This is the
    /// Visitor.
    /// </summary>
    class VisitorOperationTwo : ElementVisitor
    {
        /// <summary>
        /// We only want to visit elements of type ElementDerivedTwo.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        public override void visit(ElementDerivedTwo element)
        {
            Console.WriteLine("  --> {0} received element #{1} (type {2})", GetType().Name, element.InstanceId, element.GetType().Name);
        }
    }
}
