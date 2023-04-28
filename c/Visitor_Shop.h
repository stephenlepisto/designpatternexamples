/// @file
/// @brief
/// Declaration of the Visitor_Shop structure and its supporting functions,
/// Shop_Create(), Shop_Destroy(), Shop_PlaceOrder(), and Shop_PickupOrder(),
/// as used in the @ref visitor_pattern.

#pragma once
#ifndef __VISITOR_SHOP_H__
#define __VISITOR_SHOP_H__

#include "helpers/mapofstrings.h"
#include "helpers/mapofint.h"

struct OrderVisitor; // forward declaration

/// <summary>
/// Represents the possible responses from the Shop_PlaceOrder() function.
/// </summary>
typedef enum
{
    PlaceOrderResponse_OrderAccepted, ///< Order was accepted
    PlaceOrderResponse_OrderIgnored,  ///< Order was ignored
    PlaceOrderResponse_Error          ///< There was an error placing the order, likely an out of memory condition.
} PlaceOrderReponse;

/// <summary>
/// Represents a shop in the village that can be visited.
/// </summary>
typedef struct
{
    const char* Name;                ///< Name of shop.  Borrowed pointer.
    const char* Address;             ///< Address of shop.  Borrowed pointer.
    struct Village* Village;         ///< Village this shop is in.  Borrowed pointer.
    MapOfStrings IngredientsForItems;///< Maps ingredient to list of items need for ingredient
    MapOfInt Inventory;              ///< Maps ingredient to number of that ingredient in the shop
} Visitor_Shop;

//-----------------------------------------------------------------------------

/// <summary>
/// Creates a new instance of a Visitor_Shop structure, and initializes it
/// with the given name, address, and Village object.
/// </summary>
/// <param name="name">The name of the shop.</param>
/// <param name="address">The address of the shop.</param>
/// <param name="village">The Village in which this shop exists.</param>
/// <returns>Returns a Visitor_Shop object if successful; otherwise, returns
/// NULL, indicating an out of memory condition (or NULL arguments).</returns>
Visitor_Shop* Shop_Create(const char* name, const char* address, struct Village* village);

/// <summary>
/// Destroy an instance of the Visitor_Shop structure, freeing up any memory
/// that may have been allocated to the shop.  After this function returns,
/// the pointer to the Visitor_Shop is no longer valid.
/// </summary>
/// <param name="shop">The Visitor_Shop object to destroy.</param>
void Shop_Destroy(Visitor_Shop* shop);


/// <summary>
/// Visit the specified Visitor_Shop object to try to place an order as described
/// in the OrderVisitor object.
/// </summary>
/// <param name="shop">The Visitor_Shop object to visit.  The shop might not
/// carry the requested ingredients, in which case, the visit is ignored.</param>
/// <param name="itemsToOrder">A ConstStringList object containing a list of the
/// ingredients to order.</param>
/// <returns>Returns a value from the @ref PlaceOrderReponse enumeration
/// indicating whether the order was accepted, ignored, or there was an error
/// fulfilling the order (typically an out of memory condition).</returns>
PlaceOrderReponse Shop_PlaceOrder(Visitor_Shop* shop, ConstStringList* itemsToOrder);

/// <summary>
/// Pick up the items sold by this shop (assumes the items were ordered
/// already).  Basically, this reduces the inventory for the given items
/// that are sold by this shop.
/// </summary>
/// <param name="shop">The Visitor_Shop object to visit.  The shop might not
/// carry the requested ingredients, in which case, the visit is ignored.</param>
/// <param name="items">Items that were ordered, some of which may be
/// sold by this shop.</param>
/// <param name="itemsToBePickedUp">List to be filled in with the item names
/// that were picked up.</param>
/// <returns>Returns true if the order was picked up successfully; otherwise,
/// returns false, indicating an out of memory condition (or a NULL argument).
/// </returns>
bool Shop_PickupOrder(Visitor_Shop* shop, ConstStringList* items, ConstStringList* itemsToBePickedUp);

#endif // __VISITOR_SHOP_H__

