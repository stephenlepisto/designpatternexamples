/// @file
/// @brief
/// Implementation of the Visitor_Exercise() function as used in the
/// @ref visitor_pattern.

#include <stdio.h>

#include "Visitor_Village.h"

#include "Visitor_Exercise.h"

//=============================================================================
//=============================================================================



//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref visitor_pattern.
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
// ! [Using Visitor in C]
void Visitor_Exercise(void)
{
    printf("\nVisitor Exercise\n");

    printf("  Creating Village\n");

    Village village;
    Village_Initialize(&village);
    bool success = Village_Load(&village);
    if (success)
    {
        OrderVisitor visitor;
        OrderVisitor_Initialize(&visitor);
        success = ConstStringList_AddString(&visitor.ItemsToOrder, "hamburger");
        if (success)
        {
            printf("  Ordering a hamburger from a shop in the %s\n", village.Name);
            // Visit all shops and place an order for a hamburger at the shop
            // that sells them.  We don't know which shop it is and we don't
            // need to know until we receive the order.
            success = Village_VisitShop(&village, &visitor);
            if (success)
            {
                if (visitor.ItemsReceived.strings_count != 0)
                {
                    // We are expecting only a single item
                    printf("  We received a %s from %s.\n",
                            visitor.ItemsReceived.strings[0],
                        visitor.ShopNameReceivedFrom);
                }
                else
                {
                    printf("  Failed to receive a hamburger\n");
                }

            }
        }
        else
        {
            printf("  Error!  Out of memory condition adding item to list of things to order!\n");
        }
        OrderVisitor_Clear(&visitor);

    }
    else
    {
        printf("  Error!  Out of memory loading the village!\n");
    }

    Village_Clear(&village);

    printf("  Done.\n");
}
// ! [Using Visitor in C]
