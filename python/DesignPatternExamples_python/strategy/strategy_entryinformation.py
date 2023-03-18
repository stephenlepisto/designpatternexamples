## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.strategy.strategy_entryinformation.EntryInformation "EntryInformation"
#  class as used in the @ref strategy_pattern.

##  Represents an individual with a Name, Age, and Height.
class EntryInformation:

    ## Constructor.
    #
    #  @param name
    #         Name of the individual.
    #  @param age
    #         Age of the individual (in years).
    #  @param height
    #         Height of the individual (in inches).
    def __init__(self, name : str, age : int, height : int) -> None:
        self.Name = name
        self.Age = age
        self.Height = height

    ## @var Name
    #       Name of this individual.
    #  @var Age
    #       Age of this individual, in years.
    #  @var Height
    #       Height of this individual, in inches.


    ## Convert the entry into a string.  In this case, a formatted
    #  string where name, age, and height are confined to columns.
    #
    #  @returns
    #     A string representation of this instance.
    def ToString(self) -> str:
        return "{0:6} {1:3} {2:3}\"".format(self.Name, self.Age, self.Height)
