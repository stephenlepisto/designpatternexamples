/// @file
/// @brief
/// Implementation of the Strategy_Exercise() function as used in the
/// @ref strategy_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Strategy_SortStrategy.h"

#include "Strategy_Exercise.h"


//-----------------------------------------------------------------------------

/// <summary>
/// Sort the list of EntryInformation objects using the sorting strategy
/// given in the SortStrategy object.
///
/// Note: This function actually sorts the given indices and not the entries
/// themselves.  The entries are treated as immutable.
/// </summary>
/// <param name="entries">A list of EntryInformation objects to sort.</param>
/// <param name="numEntries">The number of entries in the `entries` and `sortIndices` lists.</param>
/// <param name="sortIndices">A list of indices into the `entries` list to be sorted.
/// This list is altered as a result of the sorting process.</param>
/// <param name="sortStrategy">A SortStrategy object describing the sorting
/// strategy to be used.  The key part of this object is the comparison function
/// used to compare two entries to determine if they need to be swapped.</param>
static void Sort_Entries(const EntryInformation* entries, size_t numEntries, int* sortIndices, SortStrategy* sortStrategy)
{
    if (entries != NULL && sortIndices != NULL && sortStrategy != NULL)
    {
        for (size_t leftIndex = 0; leftIndex < numEntries - 1; leftIndex++)
        {
            for (size_t rightIndex = leftIndex + 1; rightIndex < numEntries; rightIndex++)
            {
                bool swapEntries = sortStrategy->compareFunction(&entries[sortIndices[leftIndex]], &entries[sortIndices[rightIndex]]);
                if (sortStrategy->reversedSort)
                {
                    swapEntries = !swapEntries;
                }
                if (swapEntries)
                {
                    int tempIndex = sortIndices[leftIndex];
                    sortIndices[leftIndex] = sortIndices[rightIndex];
                    sortIndices[rightIndex] = tempIndex;
                }
            }
        }
    }
}

/// <summary>
/// Display the list of EntryInformation objects that have (presumably) been
/// sorted with the given SortStrategy object.
///
/// Note: Must use the contents of the given indices to access the entries in
/// the correct (sorted) order.
/// </summary>
/// <param name="entries">A list of EntryInformation objects that were sorted.</param>
/// <param name="numEntries">The number of entries in the `entries` and `sortIndices` lists.</param>
/// <param name="sortIndices">A list of indices into the `entries` list giving the
/// order of the sorted entries.</param>
/// <param name="sortStrategy">A SortStrategy object describing the sorting
/// strategy that was used.</param>
static void Display_Entries(const EntryInformation* entries, size_t numEntries, int* sortIndices, SortStrategy* sortStrategy)
{
    if (entries != NULL && sortIndices != NULL)
    {
        // This is a tabular display, making it easier to follow the sorted data.
        printf("    Sort strategy: %s (order = %s)\n", sortStrategy->name, sortStrategy->reversedSort ? "Descending" : "Ascending");
        printf("      %-6s %3s %3s\n", "Name", "Age", "Height");
        printf("      %6s %3s %3s\n", "------", "---", "------");
        for (size_t index = 0; index < numEntries; index++)
        {
            const EntryInformation* entry = &entries[sortIndices[index]];
            printf("      %-6s %3d %3d\"\n", entry->Name, entry->Age, entry->Height);
        }
    }
}

//=============================================================================
//=============================================================================
/// <summary>
/// List of individuals to play around with in the Strategy exercise.
/// </summary>
static EntryInformation entries[] =
{
    // Name, age, height (in inches)
    { "Ronnie", 19, 84 },
    { "Elaine", 29, 71 },
    { "Jack", 20, 81 },
    { "Myra", 35, 78 },
    { "Fred", 18, 88 },
};


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref strategy_pattern.
///
/// The Strategy pattern provides a way to easily assign different
/// algorithms to a function that can be changed at the time the function is
/// called.
///
/// In this exercise, the Sort_Entries() is given a sorting strategy via the
/// SortStrategy structure, which is initialized with the appropriate options
/// based on the value from the @ref SortOptions enumeration.
///
/// The Display_Entries() function is given the same strategy object to display
/// the results of the sort.
///
/// Three different sorting strategies are provided (Name, Age, Height) and an
/// option to reverse the normal order of the sort.
/// </summary>
// ! [Using Strategy in C]
void Strategy_Exercise(void)
{
    printf("\nStrategy Exercise\n");

    size_t numEntries = sizeof(entries) / sizeof(entries[0]);
    int* sortIndices = malloc(numEntries * sizeof(int)); // These are sortable indices into entries
    if (sortIndices != NULL)
    {
        for (int index = 0; index < (int)numEntries; index++)
        {
            sortIndices[index] = index;
        }

        SortStrategy sortStrategy = { 0 };

        SortStrategy_Initialize(&sortStrategy, Sort_ByName, false);
        Sort_Entries(entries, numEntries, sortIndices, &sortStrategy);
        Display_Entries(entries, numEntries, sortIndices, &sortStrategy);

        SortStrategy_Initialize(&sortStrategy, Sort_ByAge, false);
        Sort_Entries(entries, numEntries, sortIndices, &sortStrategy);
        Display_Entries(entries, numEntries, sortIndices, &sortStrategy);

        SortStrategy_Initialize(&sortStrategy, Sort_ByHeight, true);
        Sort_Entries(entries, numEntries, sortIndices, &sortStrategy);
        Display_Entries(entries, numEntries, sortIndices, &sortStrategy);

        free(sortIndices);
    }
    else
    {
        printf("  Error!  Out of memory creating array of indices to sort on!\n");
    }

    printf("  Done.\n");
}
// ! [Using Strategy in C]
