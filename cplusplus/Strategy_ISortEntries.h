/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::ISortEntries "ISortEntries"
/// interface as used in the @ref strategy_pattern "Strategy pattern".

#pragma once
#ifndef __STRATEGY_ISORTENTRIES_H__
#define __STRATEGY_ISORTENTRIES_H__

#include <memory>
#include <vector>
#include <string>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Identifies the different sorting strategies available.
    /// </summary>
    enum SortOptions
    {
        /// <summary>
        /// Sort alphabetically name in ascending order.
        /// </summary>
        ByName,

        /// <summary>
        /// Sort numerically by age in ascending order.
        /// </summary>
        ByAge,

        /// <summary>
        /// Sort numerically by height in ascending order.
        /// </summary>
        ByHeight,
    };


    //########################################################################
    //########################################################################


    struct EntryInformation; // forward reference

    /// <summary>
    /// Represents a sorting strategy.
    /// </summary>
    struct ISortEntries
    {
        /// <summary>
        /// Alias to make it easier to work with a shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<ISortEntries>;

        /// <summary>
        /// Required virtual destructor for interfaces in C++.
        /// </summary>
        virtual ~ISortEntries() {}

        /// <summary>
        /// Sort the specified list of entries in place.
        /// </summary>
        /// <param name="entries">A list of EntryInformation objects to be sorted.</param>
        virtual void Sort(std::vector<EntryInformation>& entries) = 0;

        /// <summary>
        /// Return a string representation of the sorting strategy.
        /// </summary>
        /// <returns>Returns a string containing the name of the sorting strategy.</returns>
        virtual std::string ToString() = 0;
    };

} // end namespace

#endif // __STRATEGY_ISORTENTRIES_H__

