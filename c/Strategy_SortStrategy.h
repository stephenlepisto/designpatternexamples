/// @file
/// @brief
/// Declaration of the SortStrategy structure and the SortStrategy_Initialize()
/// function as used in the @ref strategy_pattern.

#pragma once
#ifndef __STRATEGY_SORTSTRATEGY_H__
#define __STRATEGY_SORTSTRATEGY_H__

#include <stdbool.h>

/// <summary>
/// Represents an individual with a Name, Age, and Height.
/// </summary>
typedef struct
{
    /// <summary>
    /// Name of this individual.
    /// </summary>
    const char* Name;

    /// <summary>
    /// Age of this individual, in years.
    /// </summary>
    int Age;

    /// <summary>
    /// Height of this individual, in inches.
    /// </summary>
    int Height;
} EntryInformation;


//=============================================================================
//=============================================================================


/// <summary>
/// Represents the difference sorting strategies supported.
/// 
/// These values are used as an index into the @ref sortingStrategies array
/// defined in the Strategy_SortStrategy.c file.
/// </summary>
typedef enum
{
    /// <summary>
    /// Sort alphabetically name in ascending order.
    /// </summary>
    Sort_ByName = 0,

    /// <summary>
    /// Sort numerically by age in ascending order.
    /// </summary>
    Sort_ByAge,

    /// <summary>
    /// Sort numerically by height in ascending order.
    /// </summary>
    Sort_ByHeight,

} SortOptions;

/// <summary>
/// Alias for a function that compares two EntryInformation objects to determine
/// if the left comes before the right.
/// </summary>
typedef bool (*CompareFunction)(const EntryInformation*, const EntryInformation*);

/// <summary>
/// Represents the strategy to use for sorting EntryInformation objects.
/// </summary>
typedef struct
{
    const char* name;                ///< Name of the strategy (for display purposes)
    CompareFunction compareFunction; ///< Compare function that determines the order of two entries
    bool reversedSort;               ///< True if to reverse the order of the sort
} SortStrategy;

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize a SortStrategy object with the desired strategy.
/// </summary>
/// <param name="strategy">The SortStrategy object to initialize.</param>
/// <param name="sortOption">A value from the @ref SortOptions enumeration
/// specifying the sorting strategy to use.</param>
/// <param name="reversedSort">True if to reverse the sense of the compare
/// function.</param>
void SortStrategy_Initialize(SortStrategy* strategy, SortOptions sortOption, bool reversedSort);

#endif // __STRATEGY_SORTSTRATEGY_H__

