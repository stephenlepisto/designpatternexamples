/// @file
/// @brief
/// Implementation of the SortStrategy structure and the SortStrategy_Initialize()
/// function, along with the individual strategies,
/// as used in the @ref strategy_pattern.

#include <stdlib.h>
#include <string.h>
#include "Strategy_SortStrategy.h"


/// <summary>
/// Compare the name fields of two EntryInformation objects to determine if
/// the two entries need to be swapped.
/// </summary>
/// <param name="leftEntry">The left EntryInformation object to compare.</param>
/// <param name="rightEntry">The right EntryInformation object to compare.</param>
/// <returns>Returns true if the left object comes after the right object in
/// an ascending order and this would need to be swapped; otherwise, returns
/// false.</returns>
static bool _Compare_Name(const EntryInformation* leftEntry, const EntryInformation* rightEntry)
{
    bool swapEntries = false;

    if (leftEntry != NULL && rightEntry != NULL)
    {
        int result = strcmp(leftEntry->Name, rightEntry->Name);
        swapEntries = result > 0;
    }

    return swapEntries;
}

/// <summary>
/// Compare the age fields of two EntryInformation objects to determine if
/// the two entries need to be swapped.
/// </summary>
/// <param name="leftEntry">The left EntryInformation object to compare.</param>
/// <param name="rightEntry">The right EntryInformation object to compare.</param>
/// <returns>Returns true if the left object comes after the right object in
/// an ascending order and this would need to be swapped; otherwise, returns
/// false.</returns>
static bool _Compare_Age(const EntryInformation* leftEntry, const EntryInformation* rightEntry)
{
    bool swapEntries = false;

    if (leftEntry != NULL && rightEntry != NULL)
    {
        int result = leftEntry->Age - rightEntry->Age;
        swapEntries = result > 0;
    }

    return swapEntries;
}

/// <summary>
/// Compare the height fields of two EntryInformation objects to determine if
/// the two entries need to be swapped.
/// </summary>
/// <param name="leftEntry">The left EntryInformation object to compare.</param>
/// <param name="rightEntry">The right EntryInformation object to compare.</param>
/// <returns>Returns true if the left object comes after the right object in
/// an ascending order and this would need to be swapped; otherwise, returns
/// false.</returns>
static bool _Compare_Height(const EntryInformation* leftEntry, const EntryInformation* rightEntry)
{
    bool swapEntries = false;

    if (leftEntry != NULL && rightEntry != NULL)
    {
        int result = leftEntry->Height - rightEntry->Height;
        swapEntries = result > 0;
    }

    return swapEntries;
}

//=============================================================================
//=============================================================================

/// <summary>
/// Represents a sorting strategy.
/// </summary>
typedef struct
{
    const char* name;                ///< Name of the sorting strategy
    CompareFunction compareFunction; ///< compare function to use for the sorting strategy
} SortStrategyItem;

/// <summary>
/// List of sorting strategies as indexed by a value from the @ref SortOptions
/// enumeration.  Provides the name of the sorting strategy and the compare
/// function to use.
/// </summary>
static SortStrategyItem sortingStrategies[] =
{
    { "ByName"  , _Compare_Name   },
    { "ByAge"   , _Compare_Age    },
    { "ByHeight", _Compare_Height }
};

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize a SortStrategy object with the desired strategy.
/// </summary>
/// <param name="strategy">The SortStrategy object to initialize.</param>
/// <param name="sortOption">A value from the @ref SortOptions enumeration
/// specifying the sorting strategy to use.</param>
/// <param name="reversedSort">True if to reverse the sense of the compare
/// function.</param>
void SortStrategy_Initialize(SortStrategy* strategy, SortOptions sortOption, bool reversedSort)
{
    if (strategy != NULL)
    {
        if (sortOption >= 0 && sortOption < (int)sizeof(sortingStrategies) / sizeof(sortingStrategies[0]))
        {
            strategy->name = sortingStrategies[sortOption].name;
            strategy->compareFunction = sortingStrategies[sortOption].compareFunction;
            strategy->reversedSort = reversedSort;
        }
    }
}
