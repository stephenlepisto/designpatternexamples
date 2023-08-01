/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::OrderVisitor "OrderVisitor" class
/// used in the @ref visitor_pattern

#pragma once
#ifndef __VISITOR_VISITOR_CLASS_H__
#define __VISITOR_VISITOR_CLASS_H__

#include "helpers/stringlist.h"

#include "Visitor_Element_Classes.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// A visitor used for ordering items from various shops.  The user starts
    /// with an instance of this class and a list of what they want to order.
    ///
    /// A shop will used this visitor to order ingredients to make a requested
    /// item.
    /// </summary>
    class OrderVisitor : public Visitor
    {
    protected:
        /// <summary>
        /// Items to be ordered from any shop that sells the item.
        /// </summary>
        StringList ItemsToOrder;

    public:
        /// <summary>
        /// List of items received from an order/pickup process.
        /// </summary>
        StringList ItemsReceived;

        /// <summary>
        /// Name of the shop that provided the item(s).
        /// </summary>
        std::string ShopNameReceivedFrom;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="itemsToOrder">List of items to order.</param>
        OrderVisitor(StringList itemsToOrder)
            : ItemsToOrder(itemsToOrder)
        {
        }

        void VisitBaker(Visitor_Baker* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitButcher(Visitor_Butcher* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitPickleGrocer(Visitor_PickleGrocer* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitCondimentGrocer(Visitor_CondimentGrocer* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitVegetableGrocer(Visitor_VegetableGrocer* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitMaker(Visitor_Maker* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }

        void VisitRestaurant(Visitor_Restaurant* shop) override
        {
            if (shop != nullptr)
            {
                if (shop->PlaceOrder(ItemsToOrder))
                {
                    shop->PickupOrder(ItemsToOrder, ItemsReceived);
                    ShopNameReceivedFrom = shop->Name();
                }
            }
        }
    };

} // end namespace

#endif // __VISITOR_VISITOR_CLASS_H__
