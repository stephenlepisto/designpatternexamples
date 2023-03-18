## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.strategy.strategy_showentries_class.Strategy_ShowEntries_Class "Strategy_ShowEntries_Class"
#  class as used in the @ref strategy_pattern.

from .strategy_entryinformation import EntryInformation
from .strategy_isortentries import SortOptions
from .strategy_sortentries_class import Strategy_SortEntries_ClassFactory


## Represents a way of displaying a list of
#  @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
#  objects in a particular order.  The order of sorting is a strategy that can
#  be specified when the class is instantiated.  The sorting strategy can be
#  modified with a flag indicating whether the sort is reversed from
#  normal (in this case, descending instead of ascending).
#
#  In this particular approach, a class with a specific sorting strategy
#  is created.  It can be applied to any number of lists to achieve the
#  specified sorting behavior as the sorting behavior cannot be changed
#  once specified.
#  
#  An alternative implementation would be to pass the choice of sorting
#  strategy to the ShowEntries() method and instantiate the sorting
#  class there.  In this way, the list is sorted and displayed using the
#  specified sorting strategy.  The advantage of this approach is only
#  one instance of the class is needed.  The disadvantage is the need for
#  two additional parameters that must be passed in all the time with the
#  entries to be sorted (there might be places in the program where the
#  sorting strategy is not known or is unavailable from the user).
class Strategy_ShowEntries_Class:

    ## Constructor.
    #
    #  @param sortOption
    #         A value from the
    #         @ref DesignPatternExamples_python.strategy.strategy_isortentries.SortOptions "SortOptions"
    #         enumeration indicating the sorting strategy to use.
    #  @param reversedSort
    #         True if the sort is to be reversed (descending); otherwise,
    #         sort in ascending order.
    def __init__(self, sortOption : SortOptions, reversedSort : bool) -> None:
        self._reversedSort = reversedSort
        self._sortEntries =  Strategy_SortEntries_ClassFactory.Create(sortOption, reversedSort)

    ## @var _sortEntries
    #       The sorting strategy to use as represented by the
    #       @ref DesignPatternExamples_python.strategy.strategy_isortentries.ISortEntries "ISortEntries"
    #       interface.
    #  @var _reversedSort
    #       Whether to reverse the normal order of the sort.
    #       This is remembered here so we can use it when outputting the list.


    ## Display the specified entries in sorted order.  The order of the
    #  sort was established when the Strategy_ShowEntries_Class was instantiated.
    #
    #  @param entries
    #         A list of
    #         @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
    #         objects to sort and display
    def ShowEntries(self, entries : list[EntryInformation]) -> None:
        # Make a local copy of the entries so we don't disturb the original list.
        localEntries = entries.copy()
        self._sortEntries.Sort(localEntries)

        # This is a tabular display, making it easier to follow the sorted data.
        print("    Sort strategy: {0} (order = {1})".format(self._sortEntries.ToString(), "Descending" if self._reversedSort else "Ascending"))
        print("      {0:6} {1:3} {2:3}".format("Name", "Age", "Height"))
        print("      {0:6} {1:3} {2:3}".format("------", "---", "------"))
        for entry in localEntries:
            print("      {0}".format(entry.ToString()))
