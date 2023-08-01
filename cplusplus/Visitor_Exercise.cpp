
/// @file
/// @brief
/// Implementation of the Visitor_Exercise() function as used in the 
/// @ref visitor_pattern.

#include <iostream>

#include "helpers/formatstring.h"

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
    // ! [Using Visitor in C++]
    void Visitor_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Visitor Exercise" << std::endl;

        std::cout << "  Creating Village" << std::endl;
        std::unique_ptr<Visitor_Village> village = std::make_unique<Visitor_Village>();
        village->LoadVillage();

        OrderVisitor visitor(StringList{ "hamburger" });
        std::cout
            << Helpers::formatstring("  Ordering a hamburger from a shop in the %s",
                village->Name.c_str())
            << std::endl;
        // Visit all shops and place an order for a hamburger at the shop
        // that sells them.  We don't know which shop it is and we don't
        // need to know until we receive the order.
        village->Accept(&visitor);
        if (!visitor.ItemsReceived.empty())
        {
            // We are expecting only a single item
            std::cout
                << Helpers::formatstring("  We received a %s from %s.",
                    visitor.ItemsReceived[0].c_str(),
                    visitor.ShopNameReceivedFrom.c_str())
                << std::endl;
        }
        else
        {
            std::cout << "  Failed to receive a hamburger" << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Visitor in C++]

} // end namespace
