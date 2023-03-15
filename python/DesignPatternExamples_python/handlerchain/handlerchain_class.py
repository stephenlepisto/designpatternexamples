## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.IMessageHandler "IMessageHandler"
#  interface and the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain "HandlerChain"
#  class used in the @ref handlerchain_pattern "HandlerChain pattern"

from abc import ABC, abstractmethod
from threading import Lock
from io import StringIO

from .handlerchain_message_class import Message

## Represents a handler in a chain of handlers.  All objects that participate
#  in the HandlerChain class must implement this interface.
class IMessageHandler(ABC):
    ## ID of the window.  This is used to uniquely identify a #  window in the
    #  collection.
    def ID(self) -> int:
        pass

    ## Called with a message on each window.
    #
    #  @param message
    #         Message object representing the message to process.
    #  @returns
    #     Returns True if the message was processed and the message should not
    #     be passed to subsequent windows.  Returns False to indicate the
    #     message should be passed to subsequent windows.
    def ProcessMessage(self, message : Message) -> bool:
        pass

    ## Convert the handler to a string.
    #
    #  @returns
    #     Returns a representation of the handler.
    def ToString(self) -> str:
        pass


#========================================================================
#========================================================================
#========================================================================


## Represents a list of handlers that all implement the IMessageHandler
#  interface.  This list can be dynamically updated and each element in
#  the list is passed messages for processing.
class HandlerChain:

    ## Constructor
    def __init__(self) -> None:
        self._messageHandlers = [] # type: list[IMessageHandler]
        self._messageHandlersLock = Lock()

    ## @var _messageHandlers
    #       The list of message handlers.
    ## @var _messageHandlersLock
    #       Lock object used to lock access to the message handlers list for
    #       multi-threaded support.


    ## Send a message to each of the handlers in the list, protected by
    #  a multi-threading lock.
    #
    #  @param message
    #         The Message object to send to each handler.
    def SendMessage(self, message : Message):
        # We make a copy of the handlers so our processing of handlers
        # is not impacted by updates to the master handler list.
        copyof_MessageHandlers = None
        with self._messageHandlersLock:
            copyof_MessageHandlers = self._messageHandlers.copy()

        for window in copyof_MessageHandlers:
            if window.ProcessMessage(message):
                break


    ## Add an instance of the IMessageHandler interface to end of the
    #  list of handlers, protected by
    #  a multi-threading lock.
    #  
    #  If a message handler is already in the list, it is not added again.
    #
    #  @param window
    #         The IMessageHandler object to add.
    def AddHandler(self,  window : IMessageHandler) -> None:
        with self._messageHandlersLock:
            existsInList = False
            for handler in self._messageHandlers:
                if window.ID() == handler.ID():
                    existsInList = True
                    break
            if not existsInList:
                self._messageHandlers.append(window)


    ## Remove an instance of the IMessageHandler interface from the list,
    #  protected by a multi-threading lock.
    #  
    #  If the message handler is not in the list, the request to remove
    #  is ignored.
    #
    #  @param window
    #         The window to remove
    def RemoveHandler(self, window : IMessageHandler) -> None:
        with self._messageHandlersLock:
            foundWindow = None
            for handler in self._messageHandlers:
                if window.ID() == handler.ID():
                    foundWindow = window
                    break
            if foundWindow:
                self._messageHandlers.remove(foundWindow)


    ## Convert this HandlerChain to a string, protected by a multi-threading
    #  lock.
    #
    #  @returns
    #     Returns a string representation of this HandlerChain and all the
    #     handlers it contains.
    def ToString(self) -> str:
        output = StringIO()

        copyof_MessageHandlers = None
        with self._messageHandlersLock:
            copyof_MessageHandlers = self._messageHandlers.copy()

        for window in copyof_MessageHandlers:
            output.write("    {0}\n".format(window.ToString()))
        return output.getvalue()
