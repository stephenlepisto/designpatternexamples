## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
#  interface,
#  @ref DesignPatternExamples_python.decorator.decorator_classes.Decorator "Decorator" base class,
#  @ref DesignPatternExamples_python.decorator.decorator_classes.TextElement "TextElement" class,
#  and the concrete decorator classes as used in the @ref decorator_pattern.

from abc import ABC, abstractmethod

#########################################################################
#########################################################################


## Represents an element that can be rendered in text.  All decorators
#  and the core element class implement this interface.
class IRenderElement(ABC):
    ## Render this element as a string.
    #
    #  @returns
    #    A string containing the rendering of the element.
    @abstractmethod
    def Render(self) -> str:
        pass



#########################################################################
#########################################################################


## Represents the base class of all decorators and is responsible for
#  handling the wrapped element being decorated.
class Decorator(IRenderElement):
    
    ## Constructor
    #
    #  @param element
    #         The DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
    #         to be wrapped and decorated.
    def __init__(self, element : IRenderElement) -> None:
        self._wrappedElement = element
        if not self._wrappedElement:
            raise ValueError("The element being decorated cannot be null.")

    ## @var _wrappedElement
    #       Object being decorated by this class instance.


    ## Render the wrapped element with decorations.
    #
    #  @returns
    #    A string containing the rendering of the element.
    def Render(self) -> str:
        return self._wrappedElement.Render()


#########################################################################
#########################################################################


## Represents the WhiteBackground decorator, which changes the background
#  color of the wrapped element to white.
class WhiteBackgroundDecorator(Decorator):
    ##  Constructor that wraps the specified element.
    #
    #  @param element
    #         The DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
    #         to be wrapped and decorated.
    def __init__(self, element: IRenderElement) -> None:
        super().__init__(element)


    # IRenderElement Members

    ## Render the wrapped element with a white background.
    #
    #  @returns
    #     A string containing the decorated rendered element.
    def Render(self) -> str:
        return "\x1b[47m{0}\x1b[49m".format(super().Render())


#########################################################################
#########################################################################


## Represents the Underline decorator, which underlines the wrapped
#  content.
class UnderlineDecorator(Decorator):
    ## Constructor that wraps the specified element.
    #
    #  @param element
    #         The DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
    #         to be wrapped and decorated.
    def __init__(self, element : IRenderElement) -> None:
        super().__init__(element)

    # IRenderElement Members

    ## Render the wrapped element underlined.
    #
    #  @returns
    #     A string containing the decorated rendered element.
    def Render(self) -> str:
        return "\x1b[4m{0}\x1b[24m".format(super().Render())


#########################################################################
#########################################################################



## Represents the RedForeground decorator, which renders the wrapped
#  content as red text.
class RedForegroundDecorator(Decorator):
    ## Constructor that wraps the specified element.
    #
    #  @param element
    #         The DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
    #         to be wrapped and decorated.
    def __init__(self, element : IRenderElement) -> None:
        super().__init__(element)

    # IRenderElement Members

    ## Render the wrapped element with red text.
    #
    #  @returns
    #     A string containing the decorated rendered element.
    def Render(self) -> str:
        return "\x1b[31m{0}\x1b[39m".format(super().Render())


#########################################################################
#########################################################################


## Represents the core element that can be decorated.  Note that this
#  class implements the
#   @ref DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
#  interface but otherwise has no knowledge of any of the decorators that might
#   be applied.
#  
#  This class wraps a string and does nothing other than return the
#  string.  This way, this class can be decorated because it implements
#  the
#  @ref DesignPatternExamples_python.decorator.decorator_classes.IRenderElement "IRenderElement"
#  interface.
class TextElement(IRenderElement):

    ## Constructor.
    #
    #  @param element
    #         The text to be rendered.
    def __init__(self, element : str) -> None:
        self._elementText = element;
    
    ## @var _elementText
    #       The raw text at the center of all decorators.

    # IRenderElement Members

    ## Render this element as a string.
    #
    #  @returns
    #     A string containing the rendering of the element.
    def Render(self) -> str:
        return self._elementText;
