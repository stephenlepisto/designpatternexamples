## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.observer.observer_class.ObserverForDecimal "ObserverForDecimal",
#  @ref DesignPatternExamples_python.observer.observer_class.ObserverForHexaDecimal "ObserverForHexaDecimal",
#  and
#  @ref DesignPatternExamples_python.observer.observer_class.ObserverForBinary "ObserverForBinary"
#  classes as used in the @ref observer_pattern.

from .observersubject_numberproducer import IObserverNumberChanged, INumberProducer


## Represents an observer that prints out the current number from the
#  Subject in decimal.
class ObserverForDecimal(IObserverNumberChanged):

    ## Constructor.
    #
    #  @param numberProducer
    #         A number producer as represented by an
    #         @ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer"
    #         interface.  Cannot be null.
    def __init__(self, numberProducer : INumberProducer) -> None:
        if not numberProducer:
            raise ValueError("The ObserverForDecimal constructor requires a valid INumberProducer object.")
        self._numberProducer = numberProducer

    ## @var _numberProducer
    #       The number producer from which to get the current number.


    ## Called whenever the number is changed in the number producer.
    #  This observer instance must first be subscribed to the number
    #  producer to receive calls on this method.
    #
    #  In this example, this notification handler prints out the current
    #  number in decimal.
    def NumberChanged(self) -> None:
        number = self._numberProducer.FetchNumber()
        print("    Decimal    : {0}".format(number))


#########################################################################
#########################################################################


## Represents an observer that prints out the current number from the
#  Subject in hexadecimal.
class ObserverForHexaDecimal(IObserverNumberChanged):

    ## Constructor.
    #
    #  @param numberProducer
    #         A number producer as represented by an
    #         @ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer"
    #         interface.  Cannot be null.
    def __init__(self, numberProducer : INumberProducer) -> None:
        if not numberProducer:
            raise ValueError("The ObserverForHexaDecimal constructor requires a valid INumberProducer object.")
        self._numberProducer = numberProducer

    ## @var _numberProducer
    #       The number producer from which to get the current number.


    ## Called whenever the number is changed in the number producer.
    #  This observer instance must first be subscribed to the number
    #  producer to receive calls on this method.
    #
    #  In this example, this notification handler prints out the current
    #  number in hexadecimal using C++'s std::format to make the conversion.
    def NumberChanged(self) -> None:
        number = self._numberProducer.FetchNumber()
        print("    Hexadecimal: {0:#08X}".format(number))


#########################################################################
#########################################################################


## Represents an observer that prints out the current number from the
#  Subject in binary.
class ObserverForBinary(IObserverNumberChanged):

    ## Constructor.
    #
    #  @param numberProducer
    #         A number producer as represented by an
    #         @ref DesignPatternExamples_python.observer.observersubject_numberproducer.INumberProducer "INumberProducer"
    #         interface.  Cannot be null.
    def __init__(self, numberProducer : INumberProducer) -> None:
        if not numberProducer:
            raise ValueError("The ObserverForBinary constructor requires a valid INumberProducer object.")
        self._numberProducer = numberProducer

    ## @var _numberProducer
    #       The number producer from which to get the current number.


    ## Called whenever the number is changed in the number producer.
    #  This observer instance must first be subscribed to the number
    #  producer to receive calls on this method.
    #
    #  In this example, this notification handler prints out the current
    #  number in binary, using C++'s std::format() to make the conversion.
    def NumberChanged(self) -> None:
        number = self._numberProducer.FetchNumber()
        print("    Binary     : {0:#032b}".format(number))
