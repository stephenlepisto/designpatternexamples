/// @file
/// @brief
/// Declaration of the OrderVisitor structure and its supporting functions,
/// OrderVisitor_Initialize(), OrderVisitor_Clear(), and OrderVisitor_VisitShop(),
/// as used in the @ref visitor_pattern.

#pragma once
#ifndef __VISITOR_ORDERVISITOR_H__
#define __VISITOR_ORDERVISITOR_H__

#include "Visitor_Shop.h"

/// <summary>
/// Represents a visitor used for ordering items from various shops.  The user
/// starts with an instance of this class and a list of what they want to order.
/// 
/// Later, a shop will used this visitor to order ingredients to make a
/// requested item.
/// </summary>
typedef struct OrderVisitor
{
    /// <summary>
    /// Items to be ordered from any shop that sells the item.
    /// </summary>
    ConstStringList ItemsToOrder;

    /// <summary>
    /// List of items received from an order/pickup process.
    /// </summary>
    ConstStringList ItemsReceived;

    /// <summary>
    /// Name of the shop that provided the item(s).  Borrowed pointer.
    /// </summary>
    const char* ShopNameReceivedFrom;
} OrderVisitor;

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize the specified OrderVisitor object.
/// 
/// Alternatively, declare the OrderVisitor instance like this:
/// <example>
/// <code>
/// OrderVisitor map = { 0 };
/// </code>
/// </example>
/// </summary>
/// <param name="visitor">The OrderVisitor object to initialize.</param>
void OrderVisitor_Initialize(OrderVisitor* visitor);

/// <summary>
/// Clear the specified OrderVisitor object, freeing up any memory that it
/// was using.  The resulting object is initialized as if brand new.
/// </summary>
/// <param name="visitor">The OrderVisitor object to clear.</param>
void OrderVisitor_Clear(OrderVisitor* visitor);

/// <summary>
/// Represents a visit to the specified Visitor_Shop with the specified
/// order.
/// </summary>
/// <param name="order">The OrderVisitor object representing what is being ordered
/// from the shop.</param>
/// <param name="shop">The Visitor_Shop that is being visited and, if it carries
/// the ingredients, receives the order.  Otherwise, the shop ignores the visit.
/// </param>
/// <returns>Returns true if the shop was visited (but not necessarily received
/// an order); otherwise, returns false, indicating an out of memory condition
/// (or a NULL argument).</returns>
bool OrderVisitor_VisitShop(OrderVisitor* order, Visitor_Shop* shop);

#endif // __VISITOR_ORDERVISITOR_H__

