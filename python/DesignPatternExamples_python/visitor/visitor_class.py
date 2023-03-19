## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_class.Visitor "Visitor"
#  class as used in the @ref visitor_pattern.


## All visitors must implement this base class and then override one or
#  more of the VisitXXX() methods, depending on which shop type the
#  visitor class is interested in.
#  
#  For every new shop class added, a new VisitXXX() method needs to be
#  added to this base class and then all visitor classes must be rebuilt.
#  There is no way around this as the
#  @ref DesignPatternExamples_python.visitor.visitor_visitor_shop.Visitor_Shop "Visitor_Shop"
#  and Visitor classes are closely intertwined -- at least at the interface
#  level.
class Visitor:
    ## Let the visitor visit a Visitor_Restaurant shop.
    #
    #  @param shop
    #         The specific restaurant being visited.
    def VisitRestaurant(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_Butcher shop.
    #
    #  @param shop
    #         The specific butcher shop being visited.
    def VisitButcher(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_Baker shop.
    #
    #  @param shop
    #         The specific baker shop being visited.
    def VisitBaker(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_VegetableGrocer shop.
    #
    #  @param shop
    #         The specific vegetable grocer being visited.
    def VisitVegetableGrocer(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_CondimentGrocer shop.
    #
    #  @param shop
    #         The specific condiment grocer being visited.
    def VisitCondimentGrocer(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_PickleGrocer shop.
    #
    #  @param shop
    #         The specific pickle grocer being visited.
    def VisitPickleGrocer(shop) -> None:
        pass

    ## Let the visitor visit a Visitor_Maker shop.
    #
    #  @param shop
    #         The specific maker shop being visited.
    def VisitMaker(shop) -> None:
        pass
