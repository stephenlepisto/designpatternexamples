
/// @file
/// @brief
/// Implementation of the Strategy_Exercise() function as used in the 
/// @ref strategy_pattern "Strategy pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Strategy_Exercise.h"
#include "Strategy_ShowEntries_Class.h"
#include "Strategy_SortEntries_Classes.h"


namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// List of individuals to play around with in the Strategy exercise.
    /// </summary>
    std::vector<EntryInformation> entries =
    {
        // Name, age, height (in inches)
        EntryInformation("Ronnie", 19, 84),
        EntryInformation("Elaine", 29, 78),
        EntryInformation("Jack", 20, 81),
        EntryInformation("Myra", 35, 71),
        EntryInformation("Fred", 18, 88),
    };

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref strategy_pattern "Strategy" design pattern.
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
    // ! [Using Strategy in C++]
    void Strategy_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Strategy Exercise" << std::endl;

        Strategy_ShowEntries_Class displaySortedByNameAscending(SortOptions::ByName, false);
        displaySortedByNameAscending.ShowEntries(entries);

        Strategy_ShowEntries_Class displaySortedByAgeAscending(SortOptions::ByAge, false);
        displaySortedByAgeAscending.ShowEntries(entries);

        Strategy_ShowEntries_Class displaySortedByHeightDescending(SortOptions::ByHeight, true);
        displaySortedByHeightDescending.ShowEntries(entries);

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Strategy in C++]

} // end namespace
