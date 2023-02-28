#pragma once
#ifndef __VISITOR_ELEMENT_CLASSES_H__
#define __VISITOR_ELEMENT_CLASSES_H__

#include <memory>

namespace DesignPatternExamples_cpp
{
    class ElementVisitor; // forward declaration

    /// <summary>
    /// The interface that all element classes must implement if they are
    /// to participate in the visitor pattern.
    /// </summary>
    struct IElementVisitInterface
    {
        /// <summary>
        /// Alias type to make it easier to read the code.
        /// </summary>
        using unique_ptr_t = std::unique_ptr<IElementVisitInterface>;

        /// <summary>
        /// Virtual destructor (required for interfaces composed of virtual
        /// abstract methods).
        /// </summary>
        virtual ~IElementVisitInterface() { }

        /// <summary>
        /// This method will be called on each element for every visitor.  In
        /// turn, the element (in the implementation of this method) will call
        /// the visitor's visit() method with a reference to itself.
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        virtual void accept(ElementVisitor* visitor) = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Base class for all Element classes.  This base class provides a unique
    /// instance ID to each element and a property to get that ID.
    /// </summary>
    class ElementIdBaseClass
    {
    public:
        /// <summary>
        /// The next Instance ID to assign.
        /// </summary>
        static int _nextInstanceId;

        /// <summary>
        /// The current ID for this instance.
        /// </summary>
        int _instanceId;

        /// <summary>
        /// Default Constructor.
        /// </summary>
        ElementIdBaseClass()
        {
            _instanceId = _nextInstanceId;
            ++_nextInstanceId;
        }

        /// <summary>
        /// Retrieve the current ID for this instance.
        /// </summary>
        int InstanceId()
        {
            return _instanceId;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// One element that might have some specific properties (not needed here
    /// for this visitor pattern example).
    /// </summary>
    class ElementDerivedOne : public ElementIdBaseClass, public IElementVisitInterface
    {
    public:
        /// <summary>
        /// The visitor indirectly calls this method (through polymorphism on
        /// inherited interface).
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void accept(ElementVisitor* visitor);
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Second element that might have some specific properties (not needed
    /// here for this visitor pattern example).
    /// </summary>
    class ElementDerivedTwo : public ElementIdBaseClass, public IElementVisitInterface
    {
    public:
        /// <summary>
        /// The visitor indirectly calls this method (through polymorphism on
        /// inherited interface).
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void accept(ElementVisitor* visitor);
    };


} // end namespace

#endif // __VISITOR_ELEMENT_CLASSES_H__

