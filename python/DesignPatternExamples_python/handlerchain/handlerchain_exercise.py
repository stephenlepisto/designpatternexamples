## @file
# @brief
# Implementation of the HandlerChain_Exercise() function as used in the 
# @ref handlerchain_pattern "HandlerChain pattern".


##  Example of using the @ref handlerchain_pattern "Handle Chain" or Chain of
#   Responsibility design pattern.
#  
#  The Handler Chain pattern is used to support a dynamic list of
#  handlers that are passed the same arguments.  It is kind of the
#  inverse of the Visitor pattern, where the Visitor pattern is a
#  handler that is passed to all objects in a list and the Handler
#  Chain pattern is an object passed to handlers in a list.
# 
#  In this exercise, multiple rectangular regions called
#  MessageWindows embody the handlers and the HandlerChain object
#  passes message objects to each MessageWindow until the message is
#  handled.
##! [Using HandlerChain in Python]
def HandlerChain_Exercise():
    print()
    print("Handler Chain Exercise")

    print("  Done.")
##! [Using HandlerChain in Python]
