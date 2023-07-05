/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Strategy_ShowEntries_Class "Strategy_ShowEntries_Class"
/// classes used in the @ref strategy_pattern.

#pragma once
#ifndef __STRATEGY_SHOWENTRIES_H__
#define __STRATEGY_SHOWENTRIES_H__

#include "Strategy_SortEntries_Classes.h"

namespace DesignPatternExamples_cpp
{


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a way of displaying a list of EntryInformation objects in
    /// a particular order.  The order of sorting is a strategy that can be
    /// specified when the class is instantiated.  The sorting strategy can be
    /// modified with a flag indicating whether the sort is reversed from
    /// normal (in this case, descending instead of ascending).
    /// </summary>
    /// <remarks>
    /// In this particular approach, a class with a specific sorting strategy
    /// is created.  It can be applied to any number of lists to achieve the
    /// specified sorting behavior as the sorting behavior cannot be changed
    /// once specified.
    /// 
    /// An alternative implementation would be to pass the choice of sorting
    /// strategy to the ShowEntries() method and instantiate the sorting
    /// class there.  In this way, the list is sorted and displayed using the
    /// specified sorting strategy.  The advantage of this approach is only
    /// one instance of the class is needed.  The disadvantage is the need for
    /// two additional parameters that must be passed in all the time with the
    /// entries to be sorted (there might be places in the program where the
    /// sorting strategy is not known or is unavailable from the user).
    /// </remarks>
    class Strategy_ShowEntries_Class
    {
    private:
        /// <summary>
        /// The sorting strategy to use.
        /// </summary>
        ISortEntries::shared_ptr_t _sortEntries;

        /// <summary>
        /// Whether to reverse the normal order of the sort.
        /// </summary>
        /// <remarks>
        /// This is remembered here so we can use it when outputting the list.
        /// </remarks>
        bool _reversedSort;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="sortOption">A value from the SortOptions enumeration indicating the sorting
        /// strategy to use.</param>
        /// <param name="reversedSort">true if the sort is to be reversed (descending); otherwise,
        /// sort in ascending order.</param>
        Strategy_ShowEntries_Class(SortOptions sortOption, bool reversedSort)
        {
            _reversedSort = reversedSort;
            // Create the sorting strategy to use.
            _sortEntries = Strategy_SortEntries_ClassFactory::Create(sortOption, reversedSort);

        }

        /// <summary>
        /// Display the specified entries in sorted order.  The order of the
        /// sort was established when the Strategy_ShowEntries_Class was instantiated.
        /// </summary>
        /// <param name="entries">A list of EntryInformation objects to sort and display</param>
        void ShowEntries(const std::vector<EntryInformation>& entries)
        {
            // Make a local copy of the entries so we don't disturb the original list.
            std::vector<EntryInformation> localEntries(entries);
            _sortEntries->Sort(localEntries);

            // This is a tabular display, making it easier to follow the sorted data.
            std::cout
                << std::format("    Sort strategy: {0} (order = {1})", _sortEntries->ToString(), _reversedSort ? "Descending" : "Ascending")
                << std::endl;
            std::cout
                << std::format("      {0:6} {1:3} {2:3}", "Name", "Age", "Height")
                << std::endl;
            std::cout
                << std::format("      {0:6} {1:3} {2:3}", "------", "---", "------")
                << std::endl;
            for(EntryInformation& entry : localEntries)
            {
                std::cout
                    << std::format("      {0}", entry.ToString())
                    << std::endl;
            }
        }
    };


} // end namespace

#endif // __STRATEGY_SHOWENTRIES_H__

