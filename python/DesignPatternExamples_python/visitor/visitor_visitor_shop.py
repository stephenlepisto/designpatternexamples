## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_visitor_shop.Visitor_Shop "Visitor_Shop"
#  class as used in the @ref visitor_pattern.

from abc import ABC, abstractmethod
from typing import TypeAlias

Visitor_Village : TypeAlias = "Visitor_Village"

#from .visitor_village import Visitor_Village
from .visitor_ordervisitor import OrderVisitor
from .visitor_class import Visitor

## Base class that all shops must implement.
#  
#  Technically, all the work is done in this base class but we still need
#  to differentiate between different shop types for the visitors.
class Visitor_Shop(ABC):

    ## Default Constructor
    def __init__(self) -> None:
        self.shopName = ""
        self.shopAddress = ""
        self.village = None # type: Visitor_Village
        self.ingredientsForItems = {} # type: dict[str, list[str]]
        self.Inventory = {} # type: dict[str, int]

    ## @var shopName
    #       Name of this shop
    #  @var shopAddress
    #       address of this shop
    #  @var village
    #       The Visitor_Village object this shop is in
    #  @var ingredientsForItems
    #       Map of ingredients required for inventory items.
    #  @var Inventory
    #       Inventory for this shop, keyed by ingredient name and holding the
    #       the count of each ingredient

    ## Get the name of the shop.
    #
    #  @returns
    #     A string containing the name of this shop.
    def Name(self) -> str:
        return self.shopName

    ## Set the name of the shop.
    def SetName(self, name : str) -> None:
        self.shopName = name

    ## Address of the shop (could be a structure but a simple string is
    #  sufficient for this example).
    #
    #  @returns
    #     A string containing the address of this shop.
    def Address(self) -> str:
        return self.shopAddress

    ## Set the address of this shop
    def SetAddress(self, address : str) -> None:
        self.shopAddress = address

    ## Get the Village that contains this shop.
    #
    #  @returns
    #     The Visitor_Village representing the village this shop is in.
    def Village(self)  -> Visitor_Village:
        return self.village

    ## Set the village that contains this shop
    def SetVillage(self, v : Visitor_Village) -> None:
        self.village = v

    ## Get the ingredients needed for each item sold by the shop.
    #
    #  @returns
    #     A list of inventory items mapped to a list of ingredients needed for
    #     each item.
    def IngredientsForItems(self) -> dict[str, list[str]]:
        return self.ingredientsForItems

    ## Set the ingredients needed for each item sold by the shop.
    #  Also, the keys are what the shop sells.  The ingredient list could
    #  be empty if this shop is the origin of the item used as the key.
    def SetIngredientsForItems(self, ingredients : dict[str, list[str]]) -> None:
        self.ingredientsForItems = ingredients

    #-------------------------------------------------------------------

    ## Determine if this shop sells the specified item.
    #
    #  @param item
    #         The item to look for
    #  @returns
    #     Returns true if this shop sells the item; otherwise false.
    def DoesShopSellItem(self, item : str) -> bool:
        return item in self.ingredientsForItems

    ## Determine if this shop has the specified item in stock.
    #
    #  @param item
    #         The item to look for
    #  @returns
    #     Returns true if the item is in stock; otherwise false.
    def IsItemInStock(self, item : str) -> bool:
        return item in self.Inventory and self.Inventory[item] > 0


    ## Add the specified item to this shop's inventory.
    #
    #  @param item
    #     The item to add
    def AddItemToInventory(self, item : str) -> None:
        if not item in self.Inventory:
            self.Inventory[item] = 1
        else:
            self.Inventory[item] += 1


    ## Convert a string list to a comma-delimited string.  Useful for
    #  displaying the list.
    #
    #  @param items
    #         List to be stringized
    #  @returns
    #     Returns a string containing the comma-delimited contents of the list.
    def StringizeList(self, items : list[str]) -> str:
        return ", ".join(items)


    ## Place an order for the specified items.  If the inventory is empty,
    #  replenish the inventory by visiting other shops for the missing
    #  ingredients.
    #  
    #  Call PickupOrder() to receive the order and reduce the inventory.
    #
    #  @param items
    #         List of items to order.
    #  @returns
    #     Returns True if the order was placed; otherwise, returns False
    #     (shop doesn't sell the items).
    def PlaceOrder(self, items : list[str]) -> bool:
        orderPlaced = False
        outOfStockItems = []  # type: list[str]
        itemsInThisShop = []  # type: list[str]

        for item in items:
            if self.DoesShopSellItem(item):
                if not self.IsItemInStock(item):
                    outOfStockItems.append(item)
                itemsInThisShop.append(item)

        if itemsInThisShop:
            print("  {0}: Received an order for {1}.".format(
                    self.Name(), self.StringizeList(itemsInThisShop)))
            orderPlaced = True

        if outOfStockItems:
            for itemToOrder in outOfStockItems:
                if self.ingredientsForItems[itemToOrder]:
                    print("  {0}:   {1} out of stock, ordering ingredients to make more...".format(
                            self.Name(), itemToOrder))
                    visitor = OrderVisitor(self.ingredientsForItems[itemToOrder])
                    self.village.Accept(visitor)
                else:
                    # The ordered item has no ingredients so the
                    # ordered item will be magically added to inventory
                    print("  {0}:   {1} out of stock, making...".format(
                            self.Name(), itemToOrder))
                self.AddItemToInventory(itemToOrder)
        return orderPlaced


    ## Pick up the items sold by this shop (assumes the items were ordered
    #  already).  Basically, this reduces the inventory for the given items
    #  that are sold by this shop.
    #
    #  @param items
    #         Items that were ordered, some of which may be sold by this shop.
    #  @param itemsToBePickedUp
    #         List to be filled in with the item names that were picked up.
    def PickupOrder(self, items : list[str], itemsToBePickedUp : list[str]) -> None:
        itemsToBePickedUp.clear()
        for item in items:
            # If this shop sells the item and the item is in stock then
            if self.DoesShopSellItem(item):
                if self.IsItemInStock(item):
                    itemsToBePickedUp.append(item)
                else:
                    print("  Error!  {0}: Item {1} is not in the inventory when it should be.".format(
                            self.Name(), item))

        if itemsToBePickedUp:
            # Reduce inventory for the ordered items
            output = self.StringizeList(itemsToBePickedUp)
            for itemToBePickedUp in itemsToBePickedUp:
                self.Inventory[itemToBePickedUp] -= 1
            print("  {0}: Order picked up for {1}.".format(self.Name(), output))


    ## The visitor will call this method on each element it wants to visit.
    # 
    #  @param visitor
    #         The visitor as represented by the
    #         Visitor
    #         base class
    @abstractmethod
    def Accept(self, visitor : Visitor) -> None:
        pass

