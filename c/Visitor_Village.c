/// @file
/// @brief
/// Implementation of the Village structure's support functions,
/// Village_Initialize(), Village_Clear(), Village_Load(), Village_AddShop(),
/// and Village_VisitShop(),
/// as used in the @ref visitor_pattern.

#include <string.h>

#include "Visitor_Village.h"


//-----------------------------------------------------------------------------

/// <summary>
/// Add a Visitor_Shop object to the specified Village.  The Village object
/// takes ownership of the Visitor_Shop object and is responsible for freeing
/// up any memory associated with the shop.
/// </summary>
/// <param name="village">The Village to which to add the shop.</param>
/// <param name="shop">The Visitor_Shop object to add to the village.</param>
/// <returns>Returns true if the shop was added successfully; otherwise, returns
/// false, indicating an out of memory condition (or a NULL argument).</returns>
static bool Village_AddShop(Village* village, Visitor_Shop* shop)
{
    bool added = false;

    if (village != NULL && shop != NULL)
    {
        Visitor_Shop** new_list = NULL;
        if (village->shops == NULL)
        {
            new_list = calloc(1, sizeof(Visitor_Shop*));
        }
        else
        {
            size_t new_count = village->shops_count + 1;
            size_t new_size = new_count * sizeof(Visitor_Shop*);
            new_list = realloc(village->shops, new_size);
        }
        if (new_list != NULL)
        {
            village->shops = new_list;
            village->shops[village->shops_count] = shop;
            village->shops_count++;
            added = true;
        }
    }

    return added;
}

//-----------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
// Village_Initialize()
///////////////////////////////////////////////////////////////////////////////
void Village_Initialize(Village* village)
{
    if (village != NULL)
    {
        village->Name = NULL;
        village->shops = NULL;
        village->shops_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Village_Clear()
///////////////////////////////////////////////////////////////////////////////
void Village_Clear(Village* village)
{
    if (village != NULL)
    {
        for (size_t index = 0; index < village->shops_count; index++)
        {
            Shop_Destroy(village->shops[index]);
        }
        free(village->shops);
        Village_Initialize(village);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Village_Load()
///////////////////////////////////////////////////////////////////////////////
bool Village_Load(Village* village)
{
    static const char* empty_ingredients[] = {NULL};
    bool success = false;

    Visitor_Shop* shop = NULL;
    if (village != NULL)
    {
        village->Name = "Village of Self-Sufficiency";

        shop = Shop_Create("Joe's Burger Joint", "47 Millings Rd.", village);
        if (shop != NULL)
        {
            static const char* hamburger_ingredients[] = {"ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles", NULL};

            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "hamburger", hamburger_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }
    
    if (success)
    {
        shop = Shop_Create("Amelia's Butcher Shop", "12 Klaxon Ave.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "ground beef", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Oxel's Breads and Buns Bakery", "131 Worthington Dr.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "hamburger buns", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Connie's Condiments", "83 Millings Rd.", village);
        if (shop != NULL)
        {
            static const char* ketchup_ingredients[] = {"fresh ketchup", NULL};
            static const char* mustard_ingredients[] = {"fresh mustard", NULL};
            static const char* mayonnaise_ingredients[] = {"fresh mayonnaise", NULL};

            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "ketchup", ketchup_ingredients);
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "mustard", mustard_ingredients);
            }
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "mayonnaise", mayonnaise_ingredients);
            }
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Florence's Vegetables", "32 Main St.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "lettuce", empty_ingredients);
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "tomato", empty_ingredients);
            }
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "lettuce", empty_ingredients);
            }
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "onion", empty_ingredients);
            }
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "cucumber", empty_ingredients);
            }
            if (success)
            {
                success = MapOfStrings_AddArray(&shop->IngredientsForItems, "mustard seed", empty_ingredients);
            }
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Larry's Pickle Emporium", "34 Main St.", village);
        if (shop != NULL)
        {
            static const char* pickles_ingredients[] = { "vinegar", "cucumber", "salt", NULL };

            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "pickles", pickles_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Klyde and Sons Ketchup Makers", "800 Overtown Rd.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "fresh ketchup", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Molly's Mustard Mart", "810 Overtown Rd.", village);
        if (shop != NULL)
        {
            static const char* fresh_mustard_ingredients[] = { "vinegar", "mustard seed", NULL };

            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "fresh mustard", fresh_mustard_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Turk's Mayo Supply", "820 Overtown Rd.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "fresh mayonnaise", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Vinnies' Sour Flavors", "830 Overtown Rd.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "vinegar", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    if (success)
    {
        shop = Shop_Create("Jessie's Salt Works", "920 Overtown Rd.", village);
        if (shop != NULL)
        {
            success = MapOfStrings_AddArray(&shop->IngredientsForItems, "salt", empty_ingredients);
            if (success)
            {
                success = Village_AddShop(village, shop);
            }
            if (!success)
            {
                Shop_Destroy(shop);
                shop = NULL;
            }
        }
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
// Village_VisitShop()
///////////////////////////////////////////////////////////////////////////////
bool Village_VisitShop(Village* village, OrderVisitor* visitor)
{
    bool success = false;

    if (village != NULL && visitor != NULL)
    {
        success = true;
        for (size_t index = 0; index < village->shops_count; index++)
        {
            success = OrderVisitor_VisitShop(visitor, village->shops[index]);
            if (!success)
            {
                break;
            }
        }
    }

    return success;
}
