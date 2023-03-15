## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.handlerchain.handlerchain_exercise.HandlerChain_Exercise "HandlerChain_Exercise"()
# function as used in the @ref handlerchain_pattern.

from .handlerchain_class import HandlerChain
from .handlerchain_messagewindow_class import MessageWindow, MessageWindowFactory
from .handlerchain_message_class import Message, MessagePosition, MessageType

## Helper method to construct a list of windows.  Messages will be passed 
#  to these windows via the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain "HandlerChain"
#  object.
#
#  @param handlerChain
#         The
#         @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain "HandlerChain"
#         object that receives the new windows.
def _HandlerChain_ConstructWindowChain(handlerChain : HandlerChain) -> None:
    # Note: This creates each window and adds the new window to the given
    # HandlerChain object.
    #
    # This example doesn't care about each individual window so the
    # return value is ignored.
    MessageWindowFactory.CreateWindow("Window 1", 0, 0, 10, 10, handlerChain)
    MessageWindowFactory.CreateWindow("Window 2", 20, 0, 5, 5, handlerChain)
    MessageWindowFactory.CreateWindow("Window 3", 30, 10, 15, 15, handlerChain)



## Example of using the @ref handlerchain_pattern or Chain of
#  Responsibility Pattern.
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

# ! [Using HandlerChain in Python]
def HandlerChain_Exercise():
    print()
    print("Handler Chain Exercise")

    # Construct a handler chain and populate with windows that can
    # handle messages.
    handlerChain = HandlerChain()
    _HandlerChain_ConstructWindowChain(handlerChain)

    print("  Handler Chain at start:")
    print(handlerChain.ToString())

    # Now pass messages to the windows.

    print("  Select Window 2")
    handlerChain.SendMessage(Message(MessageType.ButtonDown, MessagePosition(22, 1)))
    handlerChain.SendMessage(Message(MessageType.ButtonUp, MessagePosition(22, 1)))
    print("  Current handler chain:")
    print(handlerChain.ToString())

    print("  Select Window 3")
    handlerChain.SendMessage(Message(MessageType.ButtonDown, MessagePosition(35, 11)))
    handlerChain.SendMessage(Message(MessageType.ButtonUp, MessagePosition(35, 11)))
    print("  Current handler chain:")
    print(handlerChain.ToString())

    print("  Select Window 1")
    handlerChain.SendMessage(Message(MessageType.ButtonDown, MessagePosition(4, 4)))
    handlerChain.SendMessage(Message(MessageType.ButtonUp, MessagePosition(4, 4)))
    print("  Current handler chain:")
    print(handlerChain.ToString())

    print("  Close Window 2")
    handlerChain.SendMessage(Message(MessageType.ButtonDown, MessagePosition(24, 0)))
    handlerChain.SendMessage(Message(MessageType.ButtonUp, MessagePosition(24, 0)))
    print("  Current handler chain:")
    print(handlerChain.ToString())

    print("  Done.")
# ! [Using HandlerChain in Python]
