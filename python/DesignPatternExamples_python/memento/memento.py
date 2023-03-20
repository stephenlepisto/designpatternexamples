## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.memento.memento.Memento_TextObject "Memento_TextObject"
# and (private)
# @ref DesignPatternExamples_python.memento.memento.Memento_TextObject.Memento "Memento"
# class, along with
# @ref DesignPatternExamples_python.memento.memento.IMemento "IMemento"
# interface implemented on the Memento class, as used in the @ref memento_pattern.

from abc import ABC, abstractmethod


## Represents a single memento, a single snapshot of the state of the
#  @ref DesignPatternExamples_python.memento.memento.Memento_TextObject "Memento_TextObject"
#  class as represented by the private class,
#  @ref DesignPatternExamples_python.memento.memento.Memento_TextObject.Memento "Memento".
class IMemento(ABC):
    ## Property getter for the name of the memento (snapshot): `value = o.Name`.
    #  Useful for displaying a list of mementos in an undo list.  In this case,
    #  the name of each memento is the operation that triggered the creation of
    #  the memento.
    @abstractmethod
    @property
    def Name(self) -> str:
        pass


#########################################################################
#########################################################################


##  Container for a string.  Need to use a class that allows the text to
#  be changed while the container (this class) remains constant.  This
#  way, operations can be applied to the text and the container's contents
#  change but not the container (strings are immutable in C#; this dances
#  around that problem).
class Memento_TextObject:
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    # Inner class Memento

    ## Represents a single memento (snapshot) of the text state before
    #  an operation is applied.  The operation becomes the name of the
    #  memento for display purposes.
    class Memento(IMemento):
        ## Constructor.
        #
        #  @param name
        #         The name of the memento to create.
        #  @param text
        #         The data to be saved in the memento
        def __init__(self, name : str, text : str) -> None:
            self._name = name
            self._text = text

        ## @var _name
        #       The name of this memento (really just the name of the operation
        #       that triggered the need for this memento).
        ## @var _text
        #       The snapshot of the text data as stored in the
        #       @ref DesignPatternExamples_python.memento.memento.Memento_TextObject "Memento_TextObject"
        #       class instance.


        ## Property getter for the saved text in this memento: `value = o.Text`.
        #  This is accessible only by the
        #  @ref DesignPatternExamples_python.memento.memento.Memento_TextObject "Memento_TextObject"
        #  class since it is the only entity that knows what to do with the
        #  text during an undo.
        @property
        def Text(self) -> str:
            return self._text

        ## Property getter for the name of this memento: `value = o.Name`.
        #  This is seen as the operation that triggered the need for the
        #  memento.
        @property
        def Name(self) -> str:
            return self._name

    # End of Inner class Memento
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    #++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    ## @name Properties
    #  @{

    ## Property getter for the text in this TextObject: `value = o.Text`.
    @property
    def Text(self) -> str:
        return self._text


    ## Property setter for the text in this TextObject: `o.Text = value`
    @Text.setter
    def Text(self, value : str) -> None:
        self._text = value;

    ## @}

    ## Constructs a text object with an initial string.
    #
    #  @param text
    #         The initial string for the text object.
    def __init__(self, text : str) -> None:
        self._text = text;

    ## @var _text
    #       The text that can change in this
    #       @ref DesignPatternExamples_python.memento.memento.Memento_TextObject "Memento_TextObject"
    #       class.

    ## Returns an
    #  @ref DesignPatternExamples_python.memento.memento.IMemento "IMemento"
    #  object containing a snapshot of the text stored in this class instance.
    #
    #  @param operationName
    #         Name of the memento (the operation associated with this memento).
    def GetMemento(self, operationName : str) -> IMemento:
        return Memento_TextObject.Memento(operationName, self._text)


    ## Sets the text in this class instance to the snapshot stored in the
    #  given IMemento object (which is assumed to be from this class).
    #
    #  @param memento
    #         The IMemento object to restore to.
    def RestoreMemento(self, memento : IMemento) -> None:
        if memento:
            self._text = memento.Text


    ## Converts the Memento_TextObject to a string (makes it easier to
    #  use the class in string formatting).
    #
    #  @returns
    #     Returns the text stored in the text object.
    def ToString(self) -> str:
        return self._text;

