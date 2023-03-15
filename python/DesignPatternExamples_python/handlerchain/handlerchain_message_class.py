## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_message_class.Message "Message"
#  and
#  @ref DesignPatternExamples_python.handlerchain.handlerchain_message_class.MessagePosition "MessagePosition"
#  classes used in the @ref handlerchain_pattern "HandlerChain pattern"

from enum import Enum

## Type of message handled by MessageWindow.
class MessageType(Enum):
    ## Window is asked to close itself, generally sent by the window itself
    #  in response to a button up in a Close region.  Applies only to the
    #  currently selected window.
    Close = 0,

    ## Selects a window based on position.
    ButtonDown = 1,

    ## Take an action on the currently selected window.
    ButtonUp = 2


#========================================================================
#========================================================================
#========================================================================


## Position of the message in global coordinates (same scope of
#  coordinates as windows).  Although this can handle negative coordinates,
#  the example is careful to use only positive coordinates.
class MessagePosition:

    ## Constructor.
    #
    #  @param x
    #         X position to use.
    #  @param y
    #         Y position to use.
    def __init__(self, x : int, y : int) -> None:
        self.X = x
        self.Y = y

    ## @var X
    #       X position.
    #  @var Y
    #       Y position.

    ## Convert this position to a string.
    #
    #  @returns
    #     A string containing a string representation of the position.
    def ToString(self) -> str:
        return "x={0:2},y={1:2}".format(self.X, self.Y)



#========================================================================
#========================================================================
#========================================================================


## Represents a message sent to the windows.  A message contains a type
#  and a position.
class Message:

    ## Constructor.
    #
    #  @param type
    #         Value from the MessageType enumeration indicating the type of
    #         message being created.
    #  @param position
    #         Position of the message, expressed as a MessagePosition object.
    def __init__(self, type : MessageType, position : MessagePosition) -> None:
        self.MessageType = type
        self.Position = position
    
    ## @var MessageType
    ##      Value from the MessageType enumeration indicating the type of this
    #       message.
    # @var Position
    #      Position of message when the message was sent.  In a real system,
    #      this would generally represent the position of a cursor at the time
    #      the message was generated.


    ## Convert this message to a string.
    #
    #  @returns
    #     Returns a string representation of this message.
    def ToString(self) -> str:
        messageTypeAsString = ""
        match (self.MessageType):
            case MessageType.Close:
                messageTypeAsString = "Close"

            case MessageType.ButtonDown:
                messageTypeAsString = "ButtonDown"

            case MessageType.ButtonUp:
                messageTypeAsString = "ButtonUp"

            case _:
                messageTypeAsString = "Unknown message type"

        return "{0} at ({1})".format(messageTypeAsString, self.Position.ToString())

