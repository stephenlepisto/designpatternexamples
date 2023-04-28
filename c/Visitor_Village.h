/// @file
/// @brief
/// Declaration of the Village structure and its supporting functions,
/// Village_Initialize(), Village_Clear(), Village_Load(), Village_AddShop(),
/// and Village_VisitShop(),
/// as used in the @ref visitor_pattern.

#pragma once
#ifndef __VISITOR_VILLAGE_H__
#define __VISITOR_VILLAGE_H__

#include "Visitor_OrderVisitor.h"


/// <summary>
/// Represents a collection of shops that can be visited.
/// </summary>
typedef struct Village
{
    const char* Name;      ///< Name of the village
    Visitor_Shop** shops;  ///< List of shops in this village.
    size_t shops_count;    ///< Number of shops in the `shops` list.
} Village;


/// <summary>
/// Initialize the specified Village object.
/// </summary>
/// <param name="village">The Village object to initialize.</param>
void Village_Initialize(Village* village);

/// <summary>
/// Clear the specified Village object, releasing any allocated memory
/// associated with the village and its contents.  The Village object is left
/// in an newly-initialized state.
/// </summary>
/// <param name="village">The Village object to clear.</param>
void Village_Clear(Village* village);

/// <summary>
/// Set up the specified Village object with all the shops that can be visited.
/// </summary>
/// <param name="village">The Village object to load.</param>
/// <returns>Returns true if the Village object was loaded successfully;
/// otherwise, returns false, indicating an out of memory condition (or a NULL
/// argument).</returns>
bool Village_Load(Village* village);

/// <summary>
/// Visit all shops in the given Village object to find the ingredients specified
/// in the OrderVisitor object.
/// </summary>
/// <param name="village">The Village object whose shops are to be visited.</param>
/// <param name="visitor">The OrderVisitor object describing what is being
/// ordered.</param>
/// <returns>Returns true if the order was placed successfully; otherwise,
/// returns false, indicating an out of memory condition (or a NULL argument).
/// </returns>
bool Village_VisitShop(Village* village, OrderVisitor* visitor);

#endif // __VISITOR_VILLAGE_H__
