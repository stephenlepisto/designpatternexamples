## @file
#  @brief
#  Implementation of the various Visitor_XXX shop classes as used in the
#  @ref visitor_pattern.

from .visitor_visitor_shop import Visitor_Shop


## Represent a restaurant shop.
class Visitor_Restaurant(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitRestaurant"):
            visitor.VisitRestaurant(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a butcher shop.
class Visitor_Butcher(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitButcher"):
            visitor.VisitButcher(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a baker shop.
class Visitor_Baker(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitBaker"):
            visitor.VisitBaker(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a vegetable grocer.
class Visitor_VegetableGrocer(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitVegetableGrocer"):
            visitor.VisitVegetableGrocer(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a condiment grocer.
class Visitor_CondimentGrocer(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitCondimentGrocer"):
            visitor.VisitCondimentGrocer(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a pickle grocer.
class Visitor_PickleGrocer(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitPickleGrocer"):
            visitor.VisitPickleGrocer(self)


#-------------------------------------------------------------------------
#-------------------------------------------------------------------------


## Represent a maker (of things).
class Visitor_Maker(Visitor_Shop):

    ## Handle visitors to this class.
    #
    #  @param visitor
    #         The visitor
    def Accept(self, visitor) -> None:
        if visitor and hasattr(visitor, "VisitMaker"):
            visitor.VisitMaker(self)
