## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_village.Visitor_Village "Visitor_Village"
#  class as used in the @ref visitor_pattern.

from .visitor_class import Visitor
from .visitor_element_classes import *

## Represents a collection of shops that can be visited.
#  
#  This class works as the container of all objects that can be visited.
#  All visits start in this container.
class Visitor_Village:

    ## @name Properties
    #  @{

    ## Property getter for the name of this village: `value = o.Name`
    @property
    def Name(self) -> str:
        return self._name

    ## Property setter for the name of this village: `o.Name = value`
    @Name.setter
    def Name(self, value) -> None:
        self._name = value

    ## @}


    ## Constructor
    def __init__(self) -> None:
        self._shops = [] # type: list[Visitor_Shop]
        self._name = ""
    
    ## @var _shops
    #       List of shops in this village (filled in by the
    #       @ref DesignPatternExamples_python.visitor.visitor_village.Visitor_Village.LoadVillage "LoadVillage()"
    #       method)
    #  @var _name
    #       Name of this village (set by the
    #       @ref DesignPatternExamples_python.visitor.visitor_village.Visitor_Village.LoadVillage "LoadVillage()"
    #       method)

    ## Load the village.  Defines all the shops that can be visited, what each
    #  shop sells, and what each shop needs to make what it sells.
    def LoadVillage(self) -> None:
        self._name = "Village of Self-Sufficiency"

        self._shops.append(Visitor_Restaurant())
        shop = self._shops[-1]
        shop.Name = "Joe's Burger Joint"
        shop.Address = "47 Millings Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "hamburger": [ "ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles" ]
            }

        self._shops.append(Visitor_Butcher())
        shop = self._shops[-1]
        shop.Name = "Amelia's Butcher Shop"
        shop.Address = "12 Klaxon Ave."
        shop.Village = self
        shop.IngredientsForItems = {
                "ground beef" : []
            }

        self._shops.append(Visitor_Baker())
        shop = self._shops[-1]
        shop.Name = "Oxel's Breads and Buns Bakery"
        shop.Address = "131 Worthington Dr."
        shop.Village = self
        shop.IngredientsForItems = {
                "hamburger buns" : []
            }

        self._shops.append(Visitor_CondimentGrocer())
        shop = self._shops[-1]
        shop.Name = "Connie's Condiments"
        shop.Address = "83 Millings Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "ketchup" : [ "fresh ketchup" ],
                "mustard" : [ "fresh mustard" ],
                "mayonnaise" : [ "fresh mayonnaise" ]
            }

        self._shops.append(Visitor_VegetableGrocer())
        shop = self._shops[-1]
        shop.Name = "Florence's Vegetables"
        shop.Address = "32 Main St."
        shop.Village = self
        shop.IngredientsForItems = {
                "lettuce" : [],
                "tomato" : [],
                "onion" : [],
                "cucumber" : [],
                "mustard seed" : []
            }

        self._shops.append(Visitor_PickleGrocer())
        shop = self._shops[-1]
        shop.Name = "Larry's Pickle Emporium"
        shop.Address = "34 Main St."
        shop.Village = self
        shop.IngredientsForItems = {
                "pickles" : [ "vinegar", "cucumber", "salt" ]
            }

        self._shops.append(Visitor_Maker())
        shop = self._shops[-1]
        shop.Name = "Klyde and Sons Ketchup Makers"
        shop.Address = "800 Overtown Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "fresh ketchup" : []
            }

        self._shops.append(Visitor_Maker())
        shop = self._shops[-1]
        shop.Name = "Molly's Mustard Mart"
        shop.Address = "810 Overtown Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "fresh mustard" : [ "vinegar", "mustard seed" ]
            }

        self._shops.append(Visitor_Maker())
        shop = self._shops[-1]
        shop.Name = "Turk's Mayo Supply"
        shop.Address = "820 Overtown Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "fresh mayonnaise" : []
            }

        self._shops.append(Visitor_Maker())
        shop = self._shops[-1]
        shop.Name = "Vinnies' Sour Flavors"
        shop.Address = "830 Overtown Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "vinegar" : []
            }

        self._shops.append(Visitor_Maker())
        shop = self._shops[-1]
        shop.Name = "Jessie's Salt Works"
        shop.Address = "920 Overtown Rd."
        shop.Village = self
        shop.IngredientsForItems = {
                "salt" : []
            }

    ## Accept a visitor and send them around to all the shops.
    def Accept(self, visitor : Visitor) -> None:
        for shop in self._shops:
            shop.Accept(visitor)
