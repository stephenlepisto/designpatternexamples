/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Visitor_Shop "Visitor_Shop"
/// base class used in the @ref visitor_pattern

#pragma once
#ifndef __VISITOR_SHOP_H__
#define __VISITOR_SHOP_H__

#include <string>
#include <memory>

#include "helpers/mapofstrings.h"


namespace DesignPatternExamples_cpp
{
    class Visitor_Village; // forward declaration
    class Visitor; // forward declaration

    /// <summary>
    /// Base class that all shops must implement.
    /// 
    /// Technically, all the work is done in this base class but we still need
    /// to differentiate between different shop types for the visitors.
    /// </summary>
    class Visitor_Shop
    {
    public:
        /// <summary>
        /// Alias to make it easier to refer to a unique instance of this class.
        /// </summary>
        using unique_ptr_t = std::unique_ptr<Visitor_Shop>;

    private:
        std::string shopName;
        std::string shopAddress;
        Visitor_Village* village;
        MapOfStrings ingredientsForItems;

    public:
        /// <summary>
        /// Inventory for this shop.
        /// </summary>
        std::map<std::string, int> Inventory;

        //-------------------------------------------------------------------

        /// <summary>
        /// Default Constructor
        /// </summary>
        Visitor_Shop()
            : village(nullptr)
        { }

        /// <summary>
        /// Virtual destructor.
        /// </summary>
        virtual ~Visitor_Shop() { }

        /// <summary>
        /// Name of the shop.
        /// </summary>
        std::string Name() { return shopName; }
        void SetName(std::string name) { shopName = name; }

        /// <summary>
        /// Address of the shop (could be a structure but a simple string is
        /// sufficient for this example).
        /// </summary>
        std::string Address() { return shopAddress; }
        void SetAddress(std::string address) { shopAddress = address; }

        /// <summary>
        /// The Village that contains this shop.
        /// </summary>
        Visitor_Village* Village() { return village; }
        void SetVillage(Visitor_Village* v) { village = v; }

        /// <summary>
        /// Specifies the ingredients needed for each item sold by the shop.
        /// Also, the keys are what the shop sells.  The ingredient list could
        /// be empty if this shop is the origin of the item used as the key.
        /// </summary>
        const MapOfStrings& IngredientsForItems() { return ingredientsForItems; }
        void SetIngredientsForItems(const MapOfStrings& ingredients) { ingredientsForItems = ingredients; }

        //-------------------------------------------------------------------

        /// <summary>
        /// Determine if this shop sells the specified item.
        /// </summary>
        /// <param name="item">The item to look for</param>
        /// <returns>Returns true if this shop sells the item; otherwise false.
        /// </returns>
        bool DoesShopSellItem(std::string item);

        /// <summary>
        /// Determine if this shop has the specified item in stock.
        /// </summary>
        /// <param name="item">The item to look for</param>
        /// <returns>Returns true if the item is in stock; otherwise false.
        /// </returns>
        bool IsItemInStock(std::string item);

        /// <summary>
        /// Add the specified item to this shop's inventory.
        /// </summary>
        /// <param name="item">The item to add</param>
        void AddItemToInventory(std::string item);

        /// <summary>
        /// Convert a string list to a comma-delimited string.  Useful for
        /// displaying the list.
        /// </summary>
        /// <param name="items">List to be stringized</param>
        /// <returns>Returns a string containing the comma-delimited contents
        /// of the list.</returns>
        std::string StringizeList(StringList items);

        /// <summary>
        /// Place an order for the specified items.  If the inventory is empty,
        /// replenish the inventory by visiting other shops for the missing
        /// ingredients.
        /// 
        /// Call PickupOrder() to receive the order and reduce the inventory.
        /// </summary>
        /// <param name="items">List of items to order.</param>
        /// <returns>Returns true if the order was placed; otherwise, returns
        /// false (shop doesn't sell the items).</returns>
        bool PlaceOrder(StringList items);

        /// <summary>
        /// Pick up the items sold by this shop (assumes the items were ordered
        /// already).  Basically, this reduces the inventory for the given items
        /// that are sold by this shop.
        /// </summary>
        /// <param name="items">Items that were ordered, some of which may be
        /// sold by this shop.</param>
        /// <param name="itemsToBePickedUp">List to be filled in with the
        /// item names that were picked up.</param>
        void PickupOrder(StringList items, StringList& itemsToBePickedUp);

        /// <summary>
        /// The visitor will call this method on each element it wants to
        /// visit.
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        virtual void Accept(Visitor* visitor) = 0;
    };

} // end namespace


#endif // __VISITOR_SHOP_H__

