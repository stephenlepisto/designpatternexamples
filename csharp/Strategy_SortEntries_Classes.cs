/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.ISortEntries "ISortEntries" interface
/// and the various StrategyXXX classes that implement the interface as used in
/// the @ref strategy_pattern "Strategy pattern".

// The Strategy pattern is used when a choice of multiple different but
// related algorithms can be made at startup time.  The implementation of each
// related algorithm exposes the same interface so as to hide the details of
// implementation from the calling program.
//
// This module holds the sorting strategies used on a list of EntryInformation
// objects.

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a sorting strategy.
    /// </summary>
    internal interface ISortEntries
    {
        /// <summary>
        /// Sort the specified list of entries in place.  A list is used here
        /// so we can leverage the List's sorting capability, although this
        /// will sort the entries in place.
        /// </summary>
        /// <param name="entries">A list of EntryInformation objects to be sorted.</param>
        void Sort(List<EntryInformation> entries);
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Strategy for sorting the names in ascending (or descending) order.
    /// </summary>
    internal class Strategy_SortEntries_ByName : ISortEntries
    {
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        public Strategy_SortEntries_ByName(bool reversedSort)
        {
            _reversedSort = reversedSort;
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
        public void Sort(List<EntryInformation> entries)
        {
            // Take advantage of C#'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            entries.Sort(delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.Name.CompareTo(left.Name) : left.Name.CompareTo(right.Name);
            });
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Strategy for sorting the ages in ascending (or descending) order.
    /// </summary>
    internal class Strategy_SortEntries_ByAge : ISortEntries
    {
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        public Strategy_SortEntries_ByAge(bool reversedSort)
        {
            _reversedSort = reversedSort;
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
        public void Sort(List<EntryInformation> entries)
        {
            // Take advantage of C#'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            entries.Sort(delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.Age.CompareTo(left.Age) : left.Age.CompareTo(right.Age);
            });
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Strategy for sorting the heights in ascending (or descending) order.
    /// </summary>
    internal class Strategy_SortEntries_ByHeight : ISortEntries
    {
        /// <summary>
        /// Controls order of sort: true for descending, false for ascending.
        /// </summary>
        bool _reversedSort;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="reversedSort">true if to sort in descending order; otherwise,
        /// sort in ascending order.</param>
        public Strategy_SortEntries_ByHeight(bool reversedSort)
        {
            _reversedSort = reversedSort;
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
        public void Sort(List<EntryInformation> entries)
        {
            // Take advantage of C#'s lambda/anonymous function capability
            // to specify the sorting criteria so we don't have to define a
            // separate method for this.  This is where lambdas really shine.
            entries.Sort(delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.Height.CompareTo(left.Height) : left.Height.CompareTo(right.Height);
            });
        }
    }


    /// <summary>
    /// Class constructor for the sorting strategies.
    /// </summary>
    internal static class Strategy_SortEntries_ClassFactory
    {
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
        internal static ISortEntries Create(Strategy_ShowEntries_Class.SortOptions sortOption, bool reversedSort)
        {
            ISortEntries sortEntries = null;

            switch(sortOption)
            {
                case Strategy_ShowEntries_Class.SortOptions.ByName:
                    sortEntries = new Strategy_SortEntries_ByName(reversedSort);
                    break;

                case Strategy_ShowEntries_Class.SortOptions.ByAge:
                    sortEntries = new Strategy_SortEntries_ByAge(reversedSort);
                    break;

                case Strategy_ShowEntries_Class.SortOptions.ByHeight:
                    sortEntries = new Strategy_SortEntries_ByHeight(reversedSort);
                    break;

                default:
                    {
                        string message = string.Format("Unrecognized sort option: {0}", sortOption);
                        throw new ApplicationException(message);
                    }
            }

            return sortEntries;
        }
    }
}
