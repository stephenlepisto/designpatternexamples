## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory"
#  class as used in the @ref strategy_pattern.

from audioop import reverse
from tkinter import Entry
from .strategy_isortentries import ISortEntries, SortOptions
from .strategy_entryinformation import EntryInformation


## Strategy for sorting the names in ascending (or descending) order.
class Strategy_SortEntries_ByName(ISortEntries):

    #  <summary>
    #  Constructor.
    #  </summary>
    #  @param reversedSort">true if to sort in descending order; otherwise,
    #  sort in ascending order.
    def __init__(self, reversedSort : bool) -> None:
        self._reversedSort = reversedSort

    ## @var _reversedSort
    #       Controls order of sort: true for descending, false for ascending.


    ## Sort the specified list of entries in place.  A list is used here
    #  so we can leverage the List's sorting capability, although this
    #  will sort the entries in place.
    #
    #  This implementation sorts by name in ascending (or descending) order.
    #
    #  @param entries
    #         The list of
    #         @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
    #         objects to sort.
    def Sort(self, entries : list[EntryInformation]) -> None:
        entries.sort(reverse=self._reversedSort, key=lambda entry : entry.Name)


    ## Return a stringized version of this class.
    #  We are really only looking for the name of the class.
    def ToString(self) -> str:
        return "Strategy_SortEntries_ByName"


#########################################################################
#########################################################################


## Strategy for sorting the ages in ascending (or descending) order.
class Strategy_SortEntries_ByAge(ISortEntries):

    ## Constructor.
    #
    #  @param reversedSort
    #         True if to sort in descending order; otherwise, sort in
    #         ascending order.
    def __init__(self, reversedSort : bool) -> None:
        self._reversedSort = reversedSort

    ## @var _reversedSort
    #       Controls order of sort: true for descending, false for ascending.


    ## Sort the specified list of entries in place.  A list is used here
    #  so we can leverage the List's sorting capability, although this
    #  will sort the entries in place.
    #
    #  This implementation sorts by age in ascending (or descending) order.
    #
    #  @param entries
    #         The list of
    #         @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
    #         objects to sort.
    def Sort(self, entries : list[EntryInformation]) -> None:
        entries.sort(reverse=self._reversedSort, key=lambda entry : entry.Age)


    ## Return a stringized version of this class.
    #  We are really only looking for the name of the class.
    def ToString(self) -> str:
        return "Strategy_SortEntries_ByAge"


#########################################################################
#########################################################################


## Strategy for sorting the heights in ascending (or descending) order.
class Strategy_SortEntries_ByHeight(ISortEntries):

    ## Constructor.
    #
    #  @param reversedSort
    #         True if to sort in descending order; otherwise, sort in
    #         ascending order.
    def __init__(self, reversedSort : bool) -> None:
        self._reversedSort = reversedSort

    ## @var _reversedSort
    #       Controls order of sort: true for descending, false for ascending.


    ## Sort the specified list of entries in place.  A list is used here
    #  so we can leverage the List's sorting capability, although this
    #  will sort the entries in place.
    #
    #  This implementation sorts by height in ascending (or descending) order.
    #
    #  @param entries
    #         The list of
    #         @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
    #         objects to sort.
    def Sort(self, entries : list[EntryInformation]) -> None:
        entries.sort(reverse=self._reversedSort, key=lambda entry : entry.Height)


    ## Return a stringized version of this class.
    #  We are really only looking for the name of the class.
    def ToString(self) -> str:
        return "Strategy_SortEntries_ByHeight"


## Holds the class factory for the sorting strategies.
class Strategy_SortEntries_ClassFactory:

    ## Convert a
    #  @ref DesignPatternExamples_python.strategy.strategy_isortentries.SortOptions "SortOptions"
    #  enumeration to a string.
    #
    #  @param sortOption
    #         A value from the
    #         @ref DesignPatternExamples_python.strategy.strategy_isortentries.SortOptions "SortOptions"
    #         enumeration.
    #  @returns
    #     A string representation of the value.
    def _SortOptionToString(sortOption : SortOptions) -> str:
        optionAsString = ""

        match sortOption:
            case SortOptions.ByName:
                optionAsString = "ByName"

            case SortOptions.ByAge:
                optionAsString = "ByAge"

            case SortOptions.ByHeight:
                optionAsString = "ByHeight"

            case _:
                optionAsString = "Unknown {0}".format(int(sortOption))

        return optionAsString


    ## Generate an instance of a sorting strategy based on the given
    #  sorting option and reversed sort flag.  A new instance of the
    #  sorting strategy is created each time this method is called.
    #
    #  @param sortOption
    #         A value from the
    #         @ref DesignPatternExamples_python.strategy.strategy_isortentries.SortOptions "SortOptions"
    #         enumeration indicating the sorting strategy to use.
    #  @param reversedSort
    #         True if the sort should be descending; otherwise False for an
    #         ascending sort.
    #  @returns
    #     Returns an
    #     @ref DesignPatternExamples_python.strategy.strategy_isortentries.ISortEntries "ISortEntries"
    #     object representing the requested sorting strategy.
    def Create(sortOption : SortOptions, reversedSort : bool) -> ISortEntries:
        sortEntries = None # type: ISortEntries

        match sortOption:
            case SortOptions.ByName:
                sortEntries = Strategy_SortEntries_ByName(reversedSort)

            case SortOptions.ByAge:
                sortEntries = Strategy_SortEntries_ByAge(reversedSort)

            case SortOptions.ByHeight:
                sortEntries = Strategy_SortEntries_ByHeight(reversedSort)

            case _:
                message = "Unrecognized sort option: {0}".format(Strategy_SortEntries_ClassFactory._SortOptionToString(sortOption))
                raise ValueError(message)

        return sortEntries
