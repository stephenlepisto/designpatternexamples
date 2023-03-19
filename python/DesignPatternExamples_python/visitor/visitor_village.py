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

    ## Constructor
    def __init__(self) -> None:
        self.shops = [] # type: list[Visitor_Shop]
        self.Name = ""
    
    ## @var shops
    #       List of shops in this village (filled in by the
    #       @ref DesignPatternExamples_python.visitor.visitor_village.Visitor_Village.LoadVillage "LoadVillage()"
    #       method)
    #  @var Name
    #       Name of this village (set by the
    #       @ref DesignPatternExamples_python.visitor.visitor_village.Visitor_Village.LoadVillage "LoadVillage()"
    #       method)

    ## Load the village.  Defines all the shops that can be visited, what each
    #  shop sells, and what each shop needs to make what it sells.
    def LoadVillage(self) -> None:
        self.Name = "Village of Self-Sufficiency"

        self.shops.append(Visitor_Restaurant())
        shop = self.shops[-1]
        shop.SetName("Joe's Burger Joint")
        shop.SetAddress("47 Millings Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "hamburger": [ "ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles" ]
            })

        self.shops.append(Visitor_Butcher())
        shop = self.shops[-1]
        shop.SetName("Amelia's Butcher Shop")
        shop.SetAddress("12 Klaxon Ave.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "ground beef" : []
            })

        self.shops.append(Visitor_Baker())
        shop = self.shops[-1]
        shop.SetName("Oxel's Breads and Buns Bakery")
        shop.SetAddress("131 Worthington Dr.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "hamburger buns" : []
            })

        self.shops.append(Visitor_CondimentGrocer())
        shop = self.shops[-1]
        shop.SetName("Connie's Condiments")
        shop.SetAddress("83 Millings Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "ketchup" : [ "fresh ketchup" ],
                "mustard" : [ "fresh mustard" ],
                "mayonnaise" : [ "fresh mayonnaise" ]
            })

        self.shops.append(Visitor_VegetableGrocer())
        shop = self.shops[-1]
        shop.SetName("Florence's Vegetables")
        shop.SetAddress("32 Main St.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "lettuce" : [],
                "tomato" : [],
                "onion" : [],
                "cucumber" : [],
                "mustard seed" : []
            })

        self.shops.append(Visitor_PickleGrocer())
        shop = self.shops[-1]
        shop.SetName("Larry's Pickle Emporium")
        shop.SetAddress("34 Main St.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "pickles" : [ "vinegar", "cucumber", "salt" ]
            })

        self.shops.append(Visitor_Maker())
        shop = self.shops[-1]
        shop.SetName("Klyde and Sons Ketchup Makers")
        shop.SetAddress("800 Overtown Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "fresh ketchup" : []
            })

        self.shops.append(Visitor_Maker())
        shop = self.shops[-1]
        shop.SetName("Molly's Mustard Mart")
        shop.SetAddress("810 Overtown Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "fresh mustard" : [ "vinegar", "mustard seed" ]
            })

        self.shops.append(Visitor_Maker())
        shop = self.shops[-1]
        shop.SetName("Turk's Mayo Supply")
        shop.SetAddress("820 Overtown Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "fresh mayonnaise" : []
            })

        self.shops.append(Visitor_Maker())
        shop = self.shops[-1]
        shop.SetName("Vinnies' Sour Flavors")
        shop.SetAddress("830 Overtown Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "vinegar" : []
            })

        self.shops.append(Visitor_Maker())
        shop = self.shops[-1]
        shop.SetName("Jessie's Salt Works")
        shop.SetAddress("920 Overtown Rd.")
        shop.SetVillage(self)
        shop.SetIngredientsForItems({
                "salt" : []
            })

    ## Accept a visitor and send them around to all the shops.
    def Accept(self, visitor : Visitor) -> None:
        for shop in self.shops:
            shop.Accept(visitor)
