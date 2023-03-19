## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.visitor.visitor_exercise.Visitor_Exercise "Visitor_Exercise"()
#  function as used in the @ref visitor_pattern.

from .visitor_village import Visitor_Village
from .visitor_ordervisitor import OrderVisitor

##  Example of using the @ref visitor_pattern.
#  
#  The Visitor pattern is used to add functionality to a list of
#  otherwise unchanging element objects by passing a visitor object to
#  each element object.  Each element object calls the visitor object,
#  passing itself as an argument.  The visitor object then does
#  something based on the type of the element.
#  
#  In this exercise, a collection of shop objects is initialized then
#  an order visitor is created to retrieve an item from one of the shop
#  objects.  Along the way, shops that don't have the necessary
#  ingredients use another order visitor to order ingredients from
#  other shops.  This approach assumes no two shops sell the same
#  thing.

# ! [Using Visitor in Python]
def Visitor_Exercise():
    print()
    print("Visitor Exercise")

    print("  Creating Village")
    village = Visitor_Village()
    village.LoadVillage()

    visitor = OrderVisitor([ "hamburger" ])
    print("  Ordering a hamburger from a shop in the {0}".format(village.Name))

    # Visit all shops and place an order for a hamburger at the shop
    # that sells them.  We don't know which shop it is and we don't
    # need to know until we receive the order.
    village.Accept(visitor)
    if visitor.ItemsReceived:
        # We are expecting only a single item
        print("  We received a {0} from {1}.".format(visitor.ItemsReceived[0], visitor.ShopNameReceivedFrom))
    else:
        print("  Failed to receive a {0}".format(visitor.ItemsToOrder[0]))

    print("  Done.")
# ! [Using Visitor in Python]
