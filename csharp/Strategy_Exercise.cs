/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Strategy_Exercise "Strategy_Exercise"
/// class used in the @ref strategy_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref strategy_pattern in C#.
    /// 
    /// The Strategy pattern provides a way to easily assign different
    /// algorithms to a class instance that can be changed at the time the
    /// class is created.
    /// 
    /// In this exercise, the Strategy_ShowEntries_Class instance sorts
    /// and displays a list of EntryInformation elements.  Three different
    /// sorting strategies are provided (Name, Age, Height) and an option
    /// to reverse the normal order of the sort.
    /// </summary>
    internal class Strategy_Exercise
    {
        /// <summary>
        /// List of individuals to play around with in the Strategy exercise.
        /// </summary>
        EntryInformation[] entries =
        {
            // Name, age, height (in inches)
            new EntryInformation("Ronnie", 19, 84),
            new EntryInformation("Elaine", 29, 71),
            new EntryInformation("Jack", 20, 81),
            new EntryInformation("Myra", 35, 78),
            new EntryInformation("Fred", 18, 88),
        };

        /// <summary>
        /// Executes the example for the @ref strategy_pattern in C#.
        /// </summary>
        // ! [Using Strategy in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Strategy Exercise");

            Strategy_ShowEntries_Class displaySortedByNameAscending;
            displaySortedByNameAscending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByName, false);
            displaySortedByNameAscending.ShowEntries(entries);

            Strategy_ShowEntries_Class displaySortedByAgeAscending;
            displaySortedByAgeAscending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByAge, false);
            displaySortedByAgeAscending.ShowEntries(entries);

            Strategy_ShowEntries_Class displaySortedByHeightDescending;
            displaySortedByHeightDescending = new Strategy_ShowEntries_Class(Strategy_ShowEntries_Class.SortOptions.ByHeight, true);
            displaySortedByHeightDescending.ShowEntries(entries);

            Console.WriteLine("  Done.");
        }
        // ! [Using Strategy in C#]
    }
}
