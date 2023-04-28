/// @file
/// @brief
/// Implementation of the OrderVisitor structure's supporting functions,
/// OrderVisitor_Initialize(), OrderVisitor_Clear(), and OrderVisitor_VisitShop(),
/// as used in the @ref visitor_pattern.

#include "Visitor_OrderVisitor.h"

///////////////////////////////////////////////////////////////////////////////
// OrderVisitor_VisitShop()
///////////////////////////////////////////////////////////////////////////////
void OrderVisitor_Initialize(OrderVisitor* visitor)
{
    if (visitor != NULL)
    {
        ConstStringList_Initialize(&visitor->ItemsToOrder);
        ConstStringList_Initialize(&visitor->ItemsReceived);
        visitor->ShopNameReceivedFrom = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// OrderVisitor_VisitShop()
///////////////////////////////////////////////////////////////////////////////
void OrderVisitor_Clear(OrderVisitor* visitor)
{
    if (visitor != NULL)
    {
        ConstStringList_Clear(&visitor->ItemsToOrder);
        ConstStringList_Clear(&visitor->ItemsReceived);
        OrderVisitor_Initialize(visitor);
    }
}

///////////////////////////////////////////////////////////////////////////////
// OrderVisitor_VisitShop()
///////////////////////////////////////////////////////////////////////////////
bool OrderVisitor_VisitShop(OrderVisitor* order, Visitor_Shop* shop)
{
    bool success = false;

    if (shop != NULL)
    {
        success = true;
        PlaceOrderReponse shopResponse = Shop_PlaceOrder(shop, &order->ItemsToOrder);
        if (shopResponse == PlaceOrderResponse_OrderAccepted)
        {
            success = Shop_PickupOrder(shop, &order->ItemsToOrder, &order->ItemsReceived);
            if (success)
            {
                order->ShopNameReceivedFrom = shop->Name;
            }
        }
    }

    return success;
}


