
/// @file
/// @brief
/// Implementation of the Visitor_Exercise() function as used in the 
/// @ref visitor_pattern "Visitor pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Visitor_Exercise.h"
#include "Visitor_Visitor_Class.h"
#include "Visitor_Village.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref visitor_pattern "Visitor" design pattern.
    /// 
    /// The Visitor pattern is used to add functionality to a list of
    /// otherwise unchanging element objects by passing a visitor object to
    /// each element object.  Each element object calls the visitor object,
    /// passing itself as an argument.  The visitor object then does
    /// something based on the type of the element.
    /// 
    /// In this exercise, a collection of shop objects is initialized then
    /// an order visitor is created to retrieve an item from one of the shop
    /// objects.  Along the way, shops that don't have the necessary
    /// ingredients use another order visitor to order ingredients from
    /// other shops.  This approach assumes no two shops sell the same
    /// thing.
    /// </summary>
    //! [Using Visitor in C++]
    void Visitor_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Visitor Exercise" << std::endl;

        std::cout << "  Creating Village" << std::endl;
        std::unique_ptr<Visitor_Village> village = std::make_unique<Visitor_Village>();
        village->LoadVillage();

        OrderVisitor visitor(StringList{ "hamburger" });
        std::cout
            << std::format("  Ordering a hamburger from a shop in the {0}",
                village->Name)
            << std::endl;
        // Visit all shops and place an order for a hamburger at the shop
        // that sells them.  We don't know which shop it is and we don't
        // need to know until we receive the order.
        village->Accept(&visitor);
        if (!visitor.ItemsReceived.empty())
        {
            // We are expecting only a single item
            std::cout
                << std::format("  We received a {0} from {1}.",
                    visitor.ItemsReceived[0], visitor.ShopNameReceivedFrom)
                << std::endl;
        }
        else
        {
            std::cout << "  Failed to receive a hamburger" << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    //! [Using Visitor in C++]

} // end namespace
