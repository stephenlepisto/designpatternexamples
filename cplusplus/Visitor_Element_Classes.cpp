/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Visitor_Shop "Visitor_Shop"
/// base class used in the @ref visitor_pattern

#include <iostream>
#include <sstream>

#include "helpers/formatstring.h"
#include "helpers/stringlist.h"

#include "Visitor_Element_Classes.h"
#include "Visitor_Visitor_Class.h"
#include "Visitor_Village.h"

namespace { // Anonymous

    /// <summary>
    /// Determine if the two string lists have the same contents.
    /// </summary>
    /// <param name="left">A StringList to compare.</param>
    /// <param name="right">Another StringList to compare.</param>
    /// <returns>Returns true if the contents of the `left` list matches what
    /// is in the `right` list, regardless of actual order.</returns>
    bool are_vector_contents_the_same(StringList& left, StringList& right)
    {
        bool match = left.size() == right.size();

        if (match)
        {
            for (StringList::iterator leftIter = std::begin(left);
                leftIter != std::end(left);
                leftIter++)
            {
                if (std::find(std::begin(right), std::end(right), *leftIter) == std::end(right))
                {
                    match = false;
                    break;
                }
            }
        }

        return match;
    }
}

namespace DesignPatternExamples_cpp
{
    bool Visitor_Shop::DoesShopSellItem(std::string item)
    {
        return ingredientsForItems.contains(item);
    }


    bool Visitor_Shop::IsItemInStock(std::string item)
    {
        return Inventory.contains(item) && Inventory[item] > 0;
    }

    
    void Visitor_Shop::AddItemToInventory(std::string item)
    {
        if (!Inventory.contains(item))
        {
            Inventory.insert(std::pair(item, 1));
        }
        else
        {
            Inventory[item]++;
        }
    }


    std::string Visitor_Shop::StringizeList(StringList items)
    {
        std::ostringstream output;

        for (std::string& item : items)
        {
            if (output.tellp() != 0)
            {
                output << ", ";
            }
            output << item;
        }
        return output.str();
    }


    bool Visitor_Shop::PlaceOrder(StringList items)
    {
        bool orderPlaced = false;
        StringList outOfStockItems;
        StringList itemsInThisShop;

        for (std::string& item : items)
        {
            if (DoesShopSellItem(item))
            {
                if (!IsItemInStock(item))
                {
                    outOfStockItems.push_back(item);
                }
                itemsInThisShop.push_back(item);
            }
        }

        if (!itemsInThisShop.empty())
        {
            std::cout
                << Helpers::formatstring("  %s: Received an order for %s.",
                    Name().c_str(), StringizeList(itemsInThisShop).c_str())
                << std::endl;
            orderPlaced = true;
        }
        if (!outOfStockItems.empty())
        {
            for (std::string& itemToOrder : outOfStockItems)
            {
                if (!ingredientsForItems[itemToOrder].empty())
                {
                    std::cout
                        << Helpers::formatstring("  %s:   %s out of stock, ordering ingredients to make more...",
                            Name().c_str(), itemToOrder.c_str())
                        << std::endl;
                    OrderVisitor visitor(ingredientsForItems[itemToOrder]);
                    village->Accept(&visitor);
                    if (are_vector_contents_the_same(visitor.ItemsReceived, ingredientsForItems[itemToOrder]))
                    {
                        // verify the ingredients received matches the ingredients needed.
                        // only then add 1 to the inventory.
                        AddItemToInventory(itemToOrder);
                    }
                    else
                    {
                        std::cout
                            << Helpers::formatstring("  %s:  Error! Ordered %s but only received %s.",
                                Name().c_str(), StringizeList(ingredientsForItems[itemToOrder]).c_str(),
                                StringizeList(visitor.ItemsReceived).c_str())
                            << std::endl;
                    }
                }
                else
                {
                    // The ordered item has no ingredients so the
                    // ordered item will be magically added to inventory
                    std::cout
                        << Helpers::formatstring("  %s:   %s out of stock, making...",
                            Name().c_str(), itemToOrder.c_str())
                        << std::endl;
                    AddItemToInventory(itemToOrder);
                }
            }
        }
        return orderPlaced;
    }


    void Visitor_Shop::PickupOrder(StringList items, StringList& itemsToBePickedUp)
    {
        for (std::string& item : items)
        {
            // If this shop sells the item and the item is in stock then
            if (DoesShopSellItem(item))
            {
                if (IsItemInStock(item))
                {
                    itemsToBePickedUp.push_back(item);
                }
                else
                {
                    std::cout
                        << Helpers::formatstring("  Error!  %s: Item %s is not in the inventory when it should be.",
                            Name().c_str(), item.c_str())
                        << std::endl;
                }
            }
        }

        if (!itemsToBePickedUp.empty())
        {
            StringList itemsReceivedFromThisShop;
            // Reduce inventory for the ordered items
            for (std::string& itemToBePickedUp : itemsToBePickedUp)
            {
                if (DoesShopSellItem(itemToBePickedUp))
                {
                    Inventory[itemToBePickedUp]--;
                    itemsReceivedFromThisShop.push_back(itemToBePickedUp);
                }
            }

            std::string output = StringizeList(itemsReceivedFromThisShop);
            std::cout
                << Helpers::formatstring("  %s: Order picked up for %s.", Name().c_str(), output.c_str())
                << std::endl;
        }
    }

} // end namespace
