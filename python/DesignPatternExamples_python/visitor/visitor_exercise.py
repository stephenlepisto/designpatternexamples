## @file
# @brief
# Implementation of the Visitor_Exercise() function as used in the 
# @ref visitor_pattern "Visitor pattern".


##  Example of using the @ref visitor_pattern "Visitor" design pattern.
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

    print("  Done.")
# ! [Using Visitor in Python]
