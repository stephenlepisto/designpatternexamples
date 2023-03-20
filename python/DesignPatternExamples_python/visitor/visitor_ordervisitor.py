## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_ordervisitor.OrderVisitor "OrderVisitor"
#  class as used in the @ref visitor_pattern.

from .visitor_class import Visitor

## A visitor used for ordering items from various shops.  The user starts
#  with an instance of this class and a list of what they want to order.
#  
#  A shop will also use this visitor to order ingredients from other shops in
#  order to make a requested item.
class OrderVisitor(Visitor):

    ## Constructor
    #
    #  @param itemsToOrder
    #         List of items to order.
    def __init__(self, itemsToOrder : list[str]) -> None:
        self.ItemsToOrder = itemsToOrder
        self.ItemsReceived = [] # type: list[str]
        self.ShopNameReceivedFrom = ""

    ## @var ItemsToOrder
    #       Items to be ordered from any shop that sells the item.
    #  @var ItemsReceived
    #       List of items received from an order/pickup process.
    #  @var ShopNameReceivedFrom
    #       Name of the shop that provided the item(s).


    ## Helper method to handle a visitor, since all visitors are handled in
    #  the same way in this collection of visitor.  A shop will receive an
    #  order.  If the shop accepts the order, the order is picked up and the
    #  name of the shop is remembered.  The results of the visit are
    #  accumulated in the ItemsReceived list.
    #
    #  @param shop
    #         A shop that implements the
    #         @ref DesignPatternExamples_python.visitor.visitor_visitor_shop.Visitor_Shop "Visitor_Shop"
    #         base class.
    def _HandleVisitor(self, shop) -> None:
        if shop:
            if hasattr(shop, "PlaceOrder") and shop.PlaceOrder(self.ItemsToOrder):
                if hasattr(shop, "PickupOrder"):
                    shop.PickupOrder(self.ItemsToOrder, self.ItemsReceived)
                    self.ShopNameReceivedFrom = shop.Name

    def VisitBaker(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitButcher(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitPickleGrocer(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitCondimentGrocer(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitVegetableGrocer(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitMaker(self, shop) -> None:
        self._HandleVisitor(shop)

    def VisitRestaurant(self, shop) -> None:
        self._HandleVisitor(shop)
