/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Visitor "Visitor" base class
/// and the various shop classes used in the @ref visitor_pattern

#pragma once
#ifndef __VISITOR_ELEMENT_CLASSES_H__
#define __VISITOR_ELEMENT_CLASSES_H__

#include <string>
#include <map>
#include <memory>

#include "helpers/stringlist.h"

#include "Visitor_Shop.h"

namespace DesignPatternExamples_cpp
{
    class Visitor_Restaurant; // forward declaration
    class Visitor_Butcher; // forward declaration
    class Visitor_Baker; // forward declaration
    class Visitor_VegetableGrocer; // forward declaration
    class Visitor_CondimentGrocer; // forward declaration
    class Visitor_PickleGrocer; // forward declaration
    class Visitor_Maker; // forward declaration

    /// <summary>
    /// All visitors must implement this base class and then override one or
    /// more of the VisitXXX() methods, depending on which shop type the
    /// visitor class is interested in.
    ///
    /// For every new shop class added, a new VisitXXX() method needs to be
    /// added to this base class and then all visitor classes must be rebuilt.
    /// There is no way around this as the Visitor_Shop and Visitor classes are
    /// closely intertwined -- at least at the interface level.
    /// </summary>
    class Visitor
    {
    public:
        /// <summary>
        /// Let the visitor visit a Visitor_Restaurant shop.
        /// </summary>
        /// <param name="shop">The specific restaurant being visited.</param>
        virtual void VisitRestaurant(Visitor_Restaurant* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_Butcher shop.
        /// </summary>
        /// <param name="shop">The specific butcher shop being visited.</param>
        virtual void VisitButcher(Visitor_Butcher* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_Baker shop.
        /// </summary>
        /// <param name="shop">The specific baker shop being visited.</param>
        virtual void VisitBaker(Visitor_Baker* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_VegetableGrocer shop.
        /// </summary>
        /// <param name="shop">The specific vegetable grocer being visited.</param>
        virtual void VisitVegetableGrocer(Visitor_VegetableGrocer* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_CondimentGrocer shop.
        /// </summary>
        /// <param name="shop">The specific condiment grocer being visited.</param>
        virtual void VisitCondimentGrocer(Visitor_CondimentGrocer* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_PickleGrocer shop.
        /// </summary>
        /// <param name="shop">The specific pickle grocer being visited.</param>
        virtual void VisitPickleGrocer(Visitor_PickleGrocer* shop) { (void)shop; /* unused */  }

        /// <summary>
        /// Let the visitor visit a Visitor_Maker shop.
        /// </summary>
        /// <param name="shop">The specific maker shop being visited.</param>
        virtual void VisitMaker(Visitor_Maker* shop) { (void)shop; /* unused */  }
    };



    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a restaurant shop.
    /// </summary>
    class Visitor_Restaurant : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitRestaurant(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a butcher shop.
    /// </summary>
    class Visitor_Butcher : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitButcher(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a baker shop.
    /// </summary>
    class Visitor_Baker : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitBaker(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a vegetable grocer.
    /// </summary>
    class Visitor_VegetableGrocer : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitVegetableGrocer(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a condiment grocer.
    /// </summary>
    class Visitor_CondimentGrocer : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitCondimentGrocer(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a pickle grocer.
    /// </summary>
    class Visitor_PickleGrocer : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitPickleGrocer(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a maker (of things).
    /// </summary>
    class Visitor_Maker : public Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        void Accept(Visitor* visitor)
        {
            if (visitor != nullptr)
            {
                visitor->VisitMaker(this);
            }
        }
    };


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------



} // end namespace

#endif // __VISITOR_ELEMENT_CLASSES_H__
