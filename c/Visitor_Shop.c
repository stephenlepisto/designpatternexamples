/// @file
/// @brief
/// Implementation of the Visitor_Shop structure's supporting functions,
/// Shop_Create(), Shop_Destroy(), Shop_PlaceOrder(), and Shop_PickupOrder(),
/// as used in the @ref visitor_pattern.

#include <stdio.h>
#include <memory.h>

#include "helpers/dynamicstring.h"

#include "Visitor_Village.h"

/// <summary>
/// Convert a string list to a comma-delimited string.  Useful for
/// displaying the list.
/// </summary>
/// <param name="list">The ConstStringList object containing the strings to be
/// stringized</param>
/// <param name="output">A DynamicString object that returns the resulting
/// string.</param>
/// <returns>Returns true if the operation completed successfully; otherwise,
/// returns false, indicating an out of memory condition (or a NULL argument).
/// </returns>
static bool _StringizeStringList(ConstStringList* list, DynamicString* output)
{
    bool success = false;

    if (list != NULL && output != NULL)
    {
        for (size_t index = 0; index < list->strings_count; index++)
        {
            if (index != 0)
            {
                success = DynamicString_Append(output, ", ");
                if (!success)
                {
                    printf("  Error!  Out of memory condition appending ',' to list of strings being concatenated into a single string!\n");
                    break;
                }
            }
            success = DynamicString_Append(output, list->strings[index]);
            if (!success)
            {
                printf("  Error!  Out of memory condition appending a string to list of strings being concatenated into a single string!\n");
                break;
            }
        }
    }

    return success;
}

/// <summary>
/// Determine if the given Visitor_Shop object sells the specified item.
/// </summary>
/// <param name="shop">The Visitor_Shop to access.</param>
/// <param name="item">The item to look for</param>
/// <returns>Returns true if this shop sells the item; otherwise false.
/// </returns>
static bool Shop_DoesShopSellItem(Visitor_Shop* shop, const char* item)
{
    bool doesSell = false;

    if (shop != NULL)
    {
        int foundIndex = MapOfStrings_Find(&shop->IngredientsForItems, item);
        doesSell = foundIndex != -1;
    }

    return doesSell;
}


/// <summary>
/// Determine if given Visitor_Shop object has the specified item in stock.
/// </summary>
/// <param name="shop">The Visitor_Shop to access.</param>
/// <param name="item">The item to look for</param>
/// <returns>Returns true if the item is in stock; otherwise false.
/// </returns>
static bool Shop_IsItemInStock(Visitor_Shop* shop, const char* item)
{
    bool inStock = false;

    if (shop != NULL && item != NULL)
    {
        int foundIndex = MapOfInt_Find(&shop->Inventory, item);
        if (foundIndex != -1)
        {
            inStock = shop->Inventory.entries[foundIndex].value > 0;
        }
    }

    return inStock;
}


/// <summary>
/// Add the specified item to the given Visitor_Shop object's inventory.
/// </summary>
/// <param name="shop">The Visitor_Shop to access.</param>
/// <param name="item">The item to add</param>
/// <returns>Returns true if the item was added successfully; otherwise,
/// returns false, indicating an out of memory condition (or a NULL argument).
/// </returns>
static bool Shop_AddItemToInventory(Visitor_Shop* shop, const char* item)
{
    bool success = false;

    if (shop != NULL && item != NULL)
    {
        int foundIndex = MapOfInt_Find(&shop->Inventory, item);
        if (foundIndex != -1)
        {
            shop->Inventory.entries[foundIndex].value++;
            success = true;
        }
        else
        {
            success = MapOfInt_Add(&shop->Inventory, item, 1);
            if (!success)
            {
                printf("  Error!  Out of memory condition adding an item to a shop's inventory!\n");
            }
        }
    }

    return success;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
// Shop_Create()
///////////////////////////////////////////////////////////////////////////////
Visitor_Shop* Shop_Create(const char* name, const char* address, struct Village* village)
{
    Visitor_Shop* shop = NULL;

    if (name != NULL && address != NULL && village != NULL)
    {
        shop = calloc(1, sizeof(Visitor_Shop));
        if (shop != NULL)
        {
            shop->Name = name;
            shop->Address = address;
            shop->Village = village;
            MapOfStrings_Initialize(&shop->IngredientsForItems);
            MapOfInt_Initialize(&shop->Inventory);
        }
    }

    return shop;
}

///////////////////////////////////////////////////////////////////////////////
// Shop_Destroy()
///////////////////////////////////////////////////////////////////////////////
void Shop_Destroy(Visitor_Shop* shop)
{
    if (shop != NULL)
    {
        MapOfStrings_Clear(&shop->IngredientsForItems);
        MapOfInt_Clear(&shop->Inventory);
    }
}



///////////////////////////////////////////////////////////////////////////////
// Shop_PlaceOrder()
///////////////////////////////////////////////////////////////////////////////
PlaceOrderReponse Shop_PlaceOrder(Visitor_Shop* shop, ConstStringList* itemsToOrder)
{
    PlaceOrderReponse response = PlaceOrderResponse_Error;

    if (itemsToOrder != NULL && shop != NULL)
    {
        ConstStringList outOfStockItems = { 0 };
        ConstStringList itemsInThisShop = { 0 };

        bool success = false;

        for (size_t index = 0; index < itemsToOrder->strings_count; index++)
        {
            const char* item = itemsToOrder->strings[index];
            if (Shop_DoesShopSellItem(shop, item))
            {
                if (!Shop_IsItemInStock(shop, item))
                {
                    success = ConstStringList_AddString(&outOfStockItems, item);
                    if (!success)
                    {
                        printf("  Error!  Out of memory condition adding ingredient to out of stock item list!\n");
                        break;
                    }
                }
                success = ConstStringList_AddString(&itemsInThisShop, item);
                if (!success)
                {
                    printf("  Error!  Out of memory condition adding ingredient to local list of items sold by a store!\n");
                    break;
                }
            }
        }

        if (success)
        {
            if (itemsInThisShop.strings_count != 0)
            {
                DynamicString output = { 0 };
                success = _StringizeStringList(&itemsInThisShop, &output);
                if (success)
                {
                    printf("  %s: Received an order for %s.\n",
                        shop->Name, output.string);
                    response = PlaceOrderResponse_OrderAccepted;
                }
                DynamicString_Clear(&output);
            }
            else
            {
                response = PlaceOrderResponse_OrderIgnored;
            }

        }

        if (success)
        {
            if (outOfStockItems.strings_count != 0)
            {
                for (size_t index = 0; index < outOfStockItems.strings_count; index++)
                {
                    const char* ingredient = outOfStockItems.strings[index];
                    int ingredientIndex = MapOfStrings_Find(&shop->IngredientsForItems, ingredient);
                    if (ingredientIndex != -1 && shop->IngredientsForItems.entries[ingredientIndex].value->strings_count != 0)
                    {
                        printf("  %s:   %s out of stock, ordering ingredients to make more...\n",
                                shop->Name, ingredient);
                        OrderVisitor visitor = { 0 };
                        success = ConstStringList_AddStrings(&visitor.ItemsToOrder, shop->IngredientsForItems.entries[ingredientIndex].value->strings, shop->IngredientsForItems.entries[ingredientIndex].value->strings_count);
                        if (!success)
                        {
                            printf("  Error!  Out of memory creating order for out of stock items!\n");
                            break;
                        }
                        success = Village_VisitShop(shop->Village, &visitor);
                        if (!success)
                        {
                            printf("  Error! Failed to visit shops for out of stock items, probably an out of memory condition!\n");
                            break;
                        }
                    }
                    else
                    {
                        // The ordered item has no ingredients so the
                        // ordered item will be magically added to inventory
                        printf("  %s:   %s out of stock, making...\n",
                                shop->Name, ingredient);
                    }
                    success = Shop_AddItemToInventory(shop, ingredient);
                    if (!success)
                    {
                        break;
                    }
                }
            }
        }
        if (!success)
        {
            response = PlaceOrderResponse_Error;
        }

        ConstStringList_Clear(&outOfStockItems);
        ConstStringList_Clear(&itemsInThisShop);
    }

    return response;
}


///////////////////////////////////////////////////////////////////////////////
// Shop_PickupOrder()
///////////////////////////////////////////////////////////////////////////////
bool Shop_PickupOrder(Visitor_Shop* shop, ConstStringList* items, ConstStringList* itemsToBePickedUp)
{
    bool success = false;

    if (items != NULL && itemsToBePickedUp  != NULL && shop != NULL)
    {
        ConstStringList_Clear(itemsToBePickedUp);
        for (size_t index = 0; index < items->strings_count; index++)
        {
            const char* item = items->strings[index];
            // If this shop sells the item and the item is in stock then
            if (Shop_DoesShopSellItem(shop, item))
            {
                if (Shop_IsItemInStock(shop, item))
                {
                    success = ConstStringList_AddString(itemsToBePickedUp, item);
                    if (!success)
                    {
                        printf("  Error!  Out of memory adding item to list of items to be picked up!\n");
                        break;
                    }
                }
                else
                {
                    printf("  Error!  %s: Item %s is not in the inventory when it should be.\n",
                            shop->Name, item);
                }
            }
        }

        if (itemsToBePickedUp->strings_count != 0)
        {
            // Reduce inventory for the ordered items
            DynamicString output = { 0 };
            success = _StringizeStringList(itemsToBePickedUp, &output);
            if (success)
            {
                for (size_t index = 0; index < itemsToBePickedUp->strings_count; index++)
                {
                    const char* itemToBePickedUp = itemsToBePickedUp->strings[index];
                    int inventoryIndex = MapOfInt_Find(&shop->Inventory, itemToBePickedUp);
                    if (inventoryIndex != -1)
                    {
                        shop->Inventory.entries[inventoryIndex].value--;
                    }
                }
                printf("  %s: Order picked up for %s.\n", shop->Name, output.string);
            }
            DynamicString_Clear(&output);
        }

    }
    return success;
}
