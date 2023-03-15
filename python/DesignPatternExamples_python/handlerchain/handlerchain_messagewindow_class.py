## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindow "MessageWindow"
#  and
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.WindowRectangle "WindowRectangle"
#  classes, along with the static class
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindowFactory "MessageWindowFactory"
#  used in the @ref handlerchain_pattern "HandlerChain pattern"

from .handlerchain_message_class import MessageType, Message, MessagePosition
from .handlerchain_class import IMessageHandler, HandlerChain

## Represents a rectangular region, with upper left and lower right coordinates.
#  
#  For this example, the minimum width of a rectangle is 4 x 4.
class WindowRectangle:
    ## Minimum width of a window (to accommodate a close box).
    MINIMUM_WIDTH = 4
    ## Minimum height of a window (to accommodate a close box).
    MINIMUM_HEIGHT = 4

    #  <summary>
    #  Constructor.
    #  </summary>
    #  @param x">X coordinate of upper left corner.
    #  @param y">Y coordinate of upper left corner.
    #  @param width">Width of rectangle.
    #  @param height">Height of rectangle.
    def __init__(self, x : int, y : int, width : int, height : int) -> None:
        width = max([width, WindowRectangle.MINIMUM_WIDTH])
        height = max([height, WindowRectangle.MINIMUM_HEIGHT])
        self.Left = x;
        self.Top = y;
        self.Right = x + width;
        self.Bottom = y + height;
    
    ## @var Left
    #       X position of the upper left corner of the window rectangle.
    #  @var Top
    #       Y position of the upper left corner of the window rectangle.
    ## @var Right
    #       X position of the lower right corner of the window rectangle.
    #  @var Bottom
    #       Y position of the lower right corner of the window rectangle.


    ## Determine if the given point is in the rectangle.
    #
    #  @param  point
    #         Point to examine.
    #  @returns
    #     Return true if the point is in the rectangle.
    def PointInside(self, point : MessagePosition) -> bool:
        isInside = False

        if point.X >= self.Left and point.X < self.Right and \
           point.Y >= self.Top and point.Y < self.Bottom:
            isInside = True

        return isInside;


    ## Convert this rectangle to a string.
    #
    #  @returns
    #    Returns a representation of this rectangle.
    def ToString(self) -> str:
        return "x1={0:2}, y1={1:2}, x2={2:2}, y2={3:2}".format(
            self.Left, self.Top, self.Right, self.Bottom)


#========================================================================
#========================================================================
#========================================================================

## Represents a rectangular region that can handle messages directed to that
#  region.
#
#  Note: The
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.IMessageHandler "IMessageHandler"
#  interface is an example of a @ref facade_pattern, where the complexity of
#  the MessageWindow is exposed only through a few methods to a system that
#  only needs to deal with those few methods.
class MessageWindow(IMessageHandler):

    ## Size of QUIT region in the upper right corner of the region.
    CLOSE_WIDTH = 2
    ## Size of QUIT region in the upper right corner of the region.
    CLOSE_HEIGHT = 2


    ## Determine if the specified point is in this MessageWindow's region.
    #
    #  @param position
    #         The global coordinate to examine.
    #  @returns
    #     Returns true if the point is contained within the MessageWindow's region.
    def _PointInWindow(self, position : MessagePosition) -> bool:
        return self._windowBox.PointInside(position)


    ## Determine if the specified point is in this MessageWindow's "close"
    #  region.
    #
    #  @param position
    #         The point to examine.
    #  @returns
    #     Returns true if the point is contained within the MessageWindow's
    #  "close" region.
    def _PointInCloseBox(self, position : MessagePosition):
        return self._closeBox.PointInside(position)


    ## Constructor.
    #
    #  @param windowId
    #         Unique ID of the window to use.
    #  @param title
    #         Title of the window.
    #  @param x
    #         Global x position of the upper left corner of the window's region.
    #  @param y
    #         Global y position of the upper left corner of the window's region.
    #  @param width
    #         Width of the window's region.
    #  @param height
    #         Height of the window's region.
    #  @param handlerChain
    #         A HandlerChain object that will be used for removal of this
    #         window when it is closed.
    def __init__(self, windowId : int, title : str, x : int, y : int, width : int, height : int, handlerChain : HandlerChain) -> None:
        self._windowId = windowId
        self._title = title
        self._windowBox = WindowRectangle(x, y, width, height)
        self._closeBox = WindowRectangle(self._windowBox.Right - MessageWindow.CLOSE_WIDTH,
                                         self._windowBox.Top,
                                         MessageWindow.CLOSE_WIDTH,
                                         MessageWindow.CLOSE_HEIGHT)
        self._handlerChain = handlerChain
        self._selected = False
        # Construct our lookup table for message handlers.
        self._messageHandlers = {
            MessageType.ButtonDown : MessageWindowHandlers._HandleButtonDownMessage,
            MessageType.ButtonUp : MessageWindowHandlers._HandleButtonUpMessage,
            MessageType.Close : MessageWindowHandlers._HandleCloseMessage
        }

    ## @var _messageHandlers
    #       Maps a message type to a handler method of type MessageHandler.
    #  @var _windowId
    #       Unique ID of this window.
    #  @var _title
    #       Title/Name of this window.
    #  @var _windowBox
    #       Position of this window in global coordinates.
    #  @var _closeBox
    #       Position of the close window within the window box, although the
    #       coordinates are also global coordinates to eliminate the need to
    #       convert between window and global coordinates.
    # @var _selected
    #      Whether this window has been selected (a button click occurred
    #      within the window).
    # @var _handlerChain
    #      The HandlerChain to which this window belongs (as an
    #      @ref DesignPatternExamples_python.handlerchain.handlerchain_class.IMessageHandler "IMessageHandler"
    #      object).


    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Implementation of the IMessageHandler interface.
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ## Returns the ID of the message handler.
    def ID(self) -> int:
        return self._windowId;


    ## Processes a message.
    #
    #  The message types are mapped to handlers in the MessageWindow
    #  constructor and stored in the `_messageHandlers` dictionary.
    #
    #  @param message
    #         The Message object to process.
    #  @returns
    #     Returns true if the message was handled and no further windows should
    #  be notified; otherwise return false to allow the message to be passed to
    #  subsequent windows.
    def ProcessMessage(self, message : Message) -> bool:
        messageProcessed = False
        if message.MessageType in self._messageHandlers:
            handler = self._messageHandlers[message.MessageType]
            messageProcessed = handler(self, message)
        return messageProcessed;


    ## Convert this handler to a string.
    #
    #  @returns
    #     Returns a string representation of the message handler.
    def ToString(self) -> str:
        return "[id={0:2}] \"{1}\" ({2}), selected={3}".format(
            self.ID(), self._title, self._windowBox.ToString(), self._selected)


##############################################################################
##############################################################################
##############################################################################


## Represents a class factory for instances of the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindow "MessageWindow"
#  class.
#
#  Call `MessageWindowFactory.CreateWindow()`.
class MessageWindowFactory:
    ## Used for assigning a unique ID to each created window.
    _nextWindowId = 1 # type: int

    ## Creates an instance of the
    #  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindow "MessageWindow"
    #  class with the specified attributes and adds the new instance to the given
    #  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain "HandlerChain"
    #  object.
    #
    #  Each MessageWindow instance is assigned a unique ID, which is required by
    #  the
    #  @ref DesignPatternExamples_python.handlerchain.handlerchain_class.HandlerChain "HandlerChain"
    #  object.
    # 
    #  @param title
    #         Title of the MessageWindow.
    #  @param x
    #         X position of the upper left corner of the window's region.
    #  @param y
    #         Y position of the upper left corner of the window's region.
    #  @param width
    #         Width of the window's region.
    #  @param height
    #         Height of the window's region.
    #  @param handlerChain
    #         A HandlerChain object that will be given the window.
    #  
    #  @returns
    #     Returns the newly created
    #     @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindow "MessageWindow"
    #     object.
    def CreateWindow(title : str, x : int, y : int, width : int, height : int, handlerChain : HandlerChain) -> MessageWindow:
        window = MessageWindow(MessageWindowFactory._nextWindowId, title, x, y,
            width, height, handlerChain)
        MessageWindowFactory._nextWindowId += 1

        if handlerChain:
            handlerChain.AddHandler(window)
        return window


##############################################################################
##############################################################################
##############################################################################


## Contains the various message handlers that operate on
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_messagewindow_class.MessageWindow "MessageWindow"
#  class instances.
#
#  All message handlers are "static" functions within the class.  The class
#  simply provides a scope for the message handlers.
#
#  These are in a separate class than MessageWindow because the Python type
#  hints cannot resolve MessageWindow type hint from within the MessageWindow
#  class.
class MessageWindowHandlers:
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # The message handlers.
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # To add a new message handler:
    #  - Add a new message type to the MessageTypes enumeration.
    #  - Add a new handler method here for the new message type.
    #  - Update MessageWindow constructor to add a mapping from the
    #    new message type to the new handler method.

    ## Helper method to handle the ButtonDown message.
    #
    #  @param window
    #         The window that is handling the message
    #  @param message
    #         A Message object describing the ButtonDown message.
    #  @returns
    #     Always returns False even if the message was handled (allows other
    #     windows to select/deselect themselves).
    def _HandleButtonDownMessage(window : MessageWindow, message : Message) -> bool:
        # Note: we are not saying we handled the message here since
        # we want other windows to get the button down message as
        # well so they can select or deselect themselves.
        messageProcessed = False

        if window._PointInWindow(message.Position):
            if not window._selected:
                window._selected = True
                print("  --> Button Down in \"{0}\", window selected".format(window._title))
        else:
            if window._selected:
                window._selected = False
                print("  --> Button Down not in \"{0}\", window deselected".format(window._title))

        return messageProcessed


    ## Helper method to handle the ButtonUp message.
    #
    #  @param window
    #         The window that is handling the message
    #  @param message
    #         A Message object describing the ButtonUp message.
    #  @returns
    #     Returns True if the message was handled; otherwise, returns False
    #     indicating the message was not handled.
    def _HandleButtonUpMessage(window : MessageWindow, message : Message) -> bool:
        messageProcessed = False
        if window._selected:
            if window._PointInWindow(message.Position):
                # The Button Up is in the same window as Button Down so
                # we will handle this message and let no other window see
                # it.
                messageProcessed = True
                if window._PointInCloseBox(message.Position):
                    print("  --> Button Up in \"{0}\" close box, sending Close message".format(window._title))
                    window._handlerChain.SendMessage(Message(MessageType.Close, message.Position))
                else:
                    print("  --> Button Up in \"{0}\", no further action taken".format(window._title))

        return messageProcessed


    ## Helper method to handle the Close message.
    #
    #  @param window
    #         The window that is handling the message
    #  @param message
    #         A Message object describing the Close message.
    #  @returns
    #     Returns True if the message was handled; otherwise, returns False
    #     indicating the message was not handled.
    def _HandleCloseMessage(window : MessageWindow, message : Message) -> bool:
        messageProcessed = False
        if window._selected:
            print("  --> Close in \"{0}\", removing window from handler chain".format(window._title))

            # This window is being closed.  We are handling the message
            # so no other window needs to see it.
            messageProcessed = True
            window._handlerChain.RemoveHandler(window)
            window._selected = False
        else:
            print("  --> Close seen in \"{0}\" but this window is not selected, ignoring".format(window._title))

        return messageProcessed

