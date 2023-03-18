## @file
#  @brief
#  Declaration of the
#  @ref DesignPatternExamples_python.strategy.strategy_isortentries.SortOptions "SortOptions"
#  enumeration and the implementation of the
#  @ref DesignPatternExamples_python.strategy.strategy_isortentries.ISortEntries "ISortEntries"
#  interface as used in the @ref strategy_pattern.

from abc import ABC, abstractmethod
from enum import Enum

from .strategy_entryinformation import EntryInformation


##  Identifies the different sorting strategies available.
class SortOptions(Enum):

    ## Sort alphabetically by name in ascending order.
    ByName = 0

    ## Sort numerically by age in ascending order.
    ByAge = 1

    ## Sort numerically by height in ascending order.
    ByHeight = 2


#########################################################################
#########################################################################


## Represents a sorting strategy.
class ISortEntries(ABC):

    ## Sort the specified list of entries in place.
    #
    #  @param entries
    #         A list of EntryInformation objects to be sorted.
    @abstractmethod
    def Sort(self, entries : list[EntryInformation]) -> None:
        pass

    ## Return a string representation of the sorting strategy.
    #
    #  @returns
    #     Returns a string containing the name of the sorting strategy.
    @abstractmethod
    def ToString(self) -> str:
        pass

