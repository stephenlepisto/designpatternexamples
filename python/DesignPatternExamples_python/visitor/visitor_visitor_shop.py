## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_visitor_shop.Visitor_Shop "Visitor_Shop"
#  class as used in the @ref visitor_pattern.

from abc import ABC, abstractmethod
from typing import TypeAlias

Visitor_Village : TypeAlias = "Visitor_Village"

from .visitor_ordervisitor import OrderVisitor
from .visitor_class import Visitor

##-----------------------------------------------------------------------------

## Determine if the two string lists have the same contents.
#  
#  @param left
#         A StringList to compare.
#  @param right
#         Another StringList to compare.
# 
# @Returns
# Returns True if the contents of the `left` list matches what
# is in the `Right` list, regardless of actual order.
def are_list_contents_the_same(left: list, right: list):
    matched = False
    if len(left) == len(right):
        matched = True
        for left_item in left:
            if left_item not in right:
                matched = False
                break
    return matched

##-----------------------------------------------------------------------------

## Base class that all shops must implement.
#  
#  Technically, all the work is done in this base class but we still need
#  to differentiate between different shop types for the visitors.
class Visitor_Shop(ABC):

    ## @name Properties
    #  @{

    ## Property getter for the name of the shop: `value = o.Name`
    #
    #  @returns
    #     A string containing the name of this shop.
    @property
    def Name(self) -> str:
        return self._shopName

    ## Property setter for the name of the shop: `o.Name = value`
    @Name.setter
    def Name(self, name : str) -> None:
        self._shopName = name

    ## Property getter for the address of the shop: `value = o.Address`.
    #  This could be a structure but a simple string is sufficient for this
    #  example.
    #
    #  @returns
    #     A string containing the address of this shop.
    @property
    def Address(self) -> str:
        return self._shopAddress

    ## Property setter for the address of this shop: `o.Address = value`.
    @Address.setter
    def Address(self, address : str) -> None:
        self._shopAddress = address

    ## Property getter for the Village that contains this shop: `value = o.Village`
    #
    #  @returns
    #     The Visitor_Village representing the village this shop is in.
    @property
    def Village(self)  -> Visitor_Village:
        return self._village

    ## Property setter for the village that contains this shop: `o.Village = value`
    @Village.setter
    def Village(self, v : Visitor_Village) -> None:
        self._village = v

    ## Property getter for the ingredients needed for each item sold by the shop:
    #  `value = o.IngredientsForItems`
    #
    #  @returns
    #     A list of inventory items mapped to a list of ingredients needed for
    #     each item.
    @property
    def IngredientsForItems(self) -> dict[str, list[str]]:
        return self._ingredientsForItems

    ## Property setter for the ingredients needed for each item sold by the shop:
    #  `o.IngredientsForItems = value`.
    #  Also, the keys are what the shop sells.  The ingredient list could
    #  be empty if this shop is the origin of the item used as the key.
    @IngredientsForItems.setter
    def IngredientsForItems(self, ingredients : dict[str, list[str]]) -> None:
        self._ingredientsForItems = ingredients

    ## Property getter for the inventory maintained by the shop: `value = o.Inventory`
    @property
    def Inventory(self) -> dict[str, int]:
        return self._inventory
    ## @}


    ## Default Constructor
    def __init__(self) -> None:
        self._shopName = ""
        self._shopAddress = ""
        self._village = None # type: Visitor_Village
        self._ingredientsForItems = {} # type: dict[str, list[str]]
        self._inventory = {} # type: dict[str, int]

    ## @var _shopName
    #       Name of this shop
    #  @var _shopAddress
    #       address of this shop
    #  @var _village
    #       The Visitor_Village object this shop is in
    #  @var _ingredientsForItems
    #       Map of ingredients required for inventory items.
    #  @var _inventory
    #       Inventory for this shop, keyed by ingredient name and holding the
    #       the count of each ingredient

    #-------------------------------------------------------------------

    ## Determine if this shop sells the specified item.
    #
    #  @param item
    #         The item to look for
    #  @returns
    #     Returns true if this shop sells the item; otherwise false.
    def DoesShopSellItem(self, item : str) -> bool:
        return item in self._ingredientsForItems

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
                    self.Name, self.StringizeList(itemsInThisShop)))
            orderPlaced = True

        if outOfStockItems:
            for itemToOrder in outOfStockItems:
                if self._ingredientsForItems[itemToOrder]:
                    print("  {0}:   {1} out of stock, ordering ingredients to make more...".format(
                            self.Name, itemToOrder))
                    visitor = OrderVisitor(self._ingredientsForItems[itemToOrder])
                    self._village.Accept(visitor)
                    if are_list_contents_the_same(visitor.ItemsReceived, self._ingredientsForItems[itemToOrder]):
                        # verify the ingredients received matches the ingredients
                        # needed. Only then add 1 to the inventory.
                        self.AddItemToInventory(itemToOrder)
                else:
                    # The ordered item has no ingredients so the
                    # ordered item will be magically added to inventory
                    print("  {0}:   {1} out of stock, making...".format(
                            self.Name, itemToOrder))
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
    #         The list may contain items from other stores.
    def PickupOrder(self, items : list[str], itemsToBePickedUp : list[str]) -> None:
        for item in items:
            # If this shop sells the item and the item is in stock then
            if self.DoesShopSellItem(item):
                if self.IsItemInStock(item):
                    itemsToBePickedUp.append(item)
                else:
                    print("  Error!  {0}: Item {1} is not in the inventory when it should be.".format(
                            self.Name, item))

        if itemsToBePickedUp:
            itemsReceivedFromThisShop = []
            # Reduce inventory for the ordered items
            for itemToBePickedUp in itemsToBePickedUp:
                if self.DoesShopSellItem(itemToBePickedUp):
                     self.Inventory[itemToBePickedUp] -= 1
                     itemsReceivedFromThisShop.append(itemToBePickedUp)
            output = self.StringizeList(itemsReceivedFromThisShop)
            print("  {0}: Order picked up for {1}.".format(self.Name, output))


    ## The visitor will call this method on each element it wants to visit.
    # 
    #  @param visitor
    #         The visitor as represented by the
    #         Visitor
    #         base class
    @abstractmethod
    def Accept(self, visitor : Visitor) -> None:
        pass

