## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.strategy.strategy_exercise.Strategy_Exercise "Strategy_Exercise"()
#  function as used in the @ref strategy_pattern.

from .strategy_entryinformation import EntryInformation
from .strategy_showentries_class import Strategy_ShowEntries_Class
from .strategy_isortentries import SortOptions


## List of individuals to play around with in the Strategy exercise.
entries = [
    # Name, age, height (in inches)
    EntryInformation("Ronnie", 19, 84),
    EntryInformation("Elaine", 29, 71),
    EntryInformation("Jack", 20, 81),
    EntryInformation("Myra", 35, 78),
    EntryInformation("Fred", 18, 88),
]

##  Example of using the @ref strategy_pattern.
#  
#  The Strategy pattern provides a way to easily assign different
#  algorithms to a class instance that can be changed at the time the
#  class is created.
#  
#  In this exercise, the Strategy_ShowEntries_Class instance sorts
#  and displays a list of EntryInformation elements.  Three different
#  sorting strategies are provided (Name, Age, Height) and an option
#  to reverse the normal order of the sort.

# ! [Using Strategy in Python]
def Strategy_Exercise():
    print()
    print("Strategy Exercise")

    displaySortedByNameAscending = Strategy_ShowEntries_Class(SortOptions.ByName, False)
    displaySortedByNameAscending.ShowEntries(entries)

    displaySortedByAgeAscending = Strategy_ShowEntries_Class(SortOptions.ByAge, False)
    displaySortedByAgeAscending.ShowEntries(entries)

    displaySortedByHeightDescending  = Strategy_ShowEntries_Class(SortOptions.ByHeight, True)
    displaySortedByHeightDescending.ShowEntries(entries)

    print("  Done.")
# ! [Using Strategy in Python]
