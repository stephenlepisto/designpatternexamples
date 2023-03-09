/// @file
/// @brief
/// Declaration of the
/// @ref DesignPatternExamples_cpp::Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory"
/// class and implementation of the various StrategyXXX classes that implement
/// the @ref DesignPatternExamples_cpp::ISortEntries "ISortEntries" interface
/// as used in the @ref strategy_pattern "Strategy pattern".

#pragma once
#ifndef __STRATEGY_SORTENTRIES_CLASSES_H__
#define __STRATEGY_SORTENTRIES_CLASSES_H__

#include <algorithm>
#include <exception>

#include "Strategy_ISortEntries.h"
#include "Strategy_EntryInformation.h"

namespace DesignPatternExamples_cpp
{


    /// <summary>
    /// Strategy for sorting the names in ascending (or descending) order.
    /// </summary>
    class Strategy_SortEntries_ByName : public ISortEntries
    {
    private:
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        Strategy_SortEntries_ByName(bool reversedSort)
            : _reversedSort(reversedSort)
        {
        }


        /// <summary>
        /// Sort the specified list of entries in place.  A list is used here
        /// so we can leverage the List's sorting capability, although this
        /// will sort the entries in place.
        /// </summary>
        /// <param name="entries">The list of EntryInformation objects to sort.</param>
        /// <remarks>
        /// This implementation sorts by name in ascending (or descending) order.
        /// </remarks>
        void Sort(std::vector<EntryInformation>& entries)
        {
            // C++ lambda can "import" only local variables so copy the class
            // variable to a local variable.
            bool reversedSort = _reversedSort;

            // Take advantage of C++'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            std::sort(std::begin(entries), std::end(entries),
                [reversedSort](EntryInformation& first, EntryInformation& second)
                {
                    return reversedSort  ? (first.Name > second.Name) : (first.Name < second.Name);
                });
        }


        std::string ToString()
        {
            std::string function(__FUNCTION__);
            return function.substr(0, function.rfind("::"));
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Strategy for sorting the ages in ascending (or descending) order.
    /// </summary>
    class Strategy_SortEntries_ByAge : public ISortEntries
    {
    private:
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        Strategy_SortEntries_ByAge(bool reversedSort)
            : _reversedSort(reversedSort)
        {
        }


        /// <summary>
        /// Sort the specified list of entries in place.  A list is used here
        /// so we can leverage the List's sorting capability, although this
        /// will sort the entries in place.
        /// </summary>
        /// <param name="entries">The list of EntryInformation objects to sort.</param>
        /// <remarks>
        /// This implementation sorts by age in ascending (or descending) order.
        /// </remarks>
        void Sort(std::vector<EntryInformation>& entries)
        {
            // C++ lambda can "import" only local variables so copy the class
            // variable to a local variable.
            bool reversedSort = _reversedSort;

            // Take advantage of C++'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            std::sort(std::begin(entries), std::end(entries),
                [reversedSort](EntryInformation& first, EntryInformation& second)
                {
                    return reversedSort ? (first.Age > second.Age) : (first.Age < second.Age);
                });
        }


        std::string ToString()
        {
            std::string function(__FUNCTION__);
            return function.substr(0, function.rfind("::"));
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Strategy for sorting the heights in ascending (or descending) order.
    /// </summary>
    class Strategy_SortEntries_ByHeight : public ISortEntries
    {
    private:
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        Strategy_SortEntries_ByHeight(bool reversedSort)
            : _reversedSort(reversedSort)
        {
        }


        /// <summary>
        /// Sort the specified list of entries in place.  A list is used here
        /// so we can leverage the List's sorting capability, although this
        /// will sort the entries in place.
        /// </summary>
        /// <param name="entries">The list of EntryInformation objects to sort.</param>
        /// <remarks>
        /// This implementation sorts by height in ascending (or descending) order.
        /// </remarks>
        void Sort(std::vector<EntryInformation>& entries)
        {
            // C++ lambda can "import" only local variables so copy the class
            // variable to a local variable.
            bool reversedSort = _reversedSort;

            // Take advantage of C++'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            std::sort(std::begin(entries), std::end(entries),
                [reversedSort](EntryInformation& first, EntryInformation& second)
                {
                    return reversedSort ? (first.Height > second.Height) : (first.Height < second.Height);
                });
        }


        std::string ToString()
        {
            std::string function(__FUNCTION__);
            return function.substr(0,function.rfind("::"));
        }
    };


    /// <summary>
    /// Holds the class constructor for the sorting strategies.
    /// </summary>
    class Strategy_SortEntries_ClassFactory
    {
    public:
        /// <summary>
        /// Generate an instance of a sorting strategy based on the given
        /// sorting option and reversed sort flag.  A new instance of the
        /// sorting strategy is created each time this method is called.
        /// </summary>
        /// <param name="sortOption">A value from the
        /// Strategy_ShowEntries_Class.SortOptions enumeration indicating
        /// the sorting strategy to use.</param>
        /// <param name="reversedSort">true if the sort should be descending;
        /// otherwise false for an ascending sort.</param>
        /// <returns>Returns an ISortEntries object representing the requested sorting strategy.</returns>
        /// <exception cref="ApplicationException">The sorting option was not recognized.</exception>
        static ISortEntries::shared_ptr_t Create(SortOptions sortOption, bool reversedSort);
    };

} // end namespace

#endif // __STRATEGY_SORTENTRIES_CLASSES_H__

