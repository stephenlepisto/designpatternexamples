#pragma once
#ifndef __VISITOR_VISITOR_CLASS_H__
#define __VISITOR_VISITOR_CLASS_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20
#include <iostream>
#include <memory>

#include "Visitor_Element_classes.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// All visitors must implement this base class and then override one or
    /// more of the visit() methods, depending on which element type the
    /// visitor class is interested in.
    /// 
    /// For every new element class added, a new visit() method needs to be
    /// added to this base class and then all visitor classes must be rebuilt.
    /// There is no way around this as the Element and Visitor classes are
    /// closely intertwined at least at the interface level.
    /// </summary>
    class ElementVisitor
    {
    public:
        /// <summary>
        /// Perform an operation on ElementDerivedOne types.
        /// </summary>
        /// <param name="element">The element to affect.</param>
        virtual void visit(ElementDerivedOne* element) { element; }

        /// <summary>
        /// Perform an operation on ElementDerivedTwo types.
        /// </summary>
        /// <param name="element">The element to affect.</param>
        virtual void visit(ElementDerivedTwo* element) { element; }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// An operation to apply to one or more data elements.  This is the
    /// Visitor.
    /// </summary>
    class VisitorOperationOne : public ElementVisitor
    {
    public:
        /// <summary>
        /// Alias type to make it easier to read the code.
        /// </summary>
        using unique_ptr_t = std::unique_ptr<VisitorOperationOne>;

        /// <summary>
        /// We want to visit elements of type ElementDerivedOne.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        void visit(ElementDerivedOne* element)
        {
            if (element != nullptr)
            {
                std::cout << std::format("  --> {0} received element #{1} (type {2})",
                    "VisitorOperationOne", element->InstanceId(), "ElementDerivedOne")
                    << std::endl;
            }
        }

        /// <summary>
        /// We also want to visit elements of type ElementDerivedTwo.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        void visit(ElementDerivedTwo* element)
        {
            if (element != nullptr)
            {
                std::cout << std::format("  --> {0} received element #{1} (type {2})",
                    "VisitorOperationOne", element->InstanceId(), "ElementDerivedTwo")
                    << std::endl;
            }
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// An operation to apply to one or more data elements.  This is the
    /// Visitor.
    /// </summary>
    class VisitorOperationTwo : public ElementVisitor
    {
    public:
        /// <summary>
        /// Alias type to make it easier to read the code.
        /// </summary>
        using unique_ptr_t = std::unique_ptr<VisitorOperationTwo>;

        /// <summary>
        /// We only want to visit elements of type ElementDerivedTwo.
        /// </summary>
        /// <param name="element">The desired element to visit.</param>
        void visit(ElementDerivedTwo* element)
        {
            if (element != nullptr)
            {
                std::cout << std::format("  --> {0} received element #{1} (type {2})",
                    "VisitorOperationTwo", element->InstanceId(), "ElementDerivedTwo")
                    << std::endl;
            }
        }
    };

} // end namespace

#endif // __VISITOR_VISITOR_CLASS_H__

