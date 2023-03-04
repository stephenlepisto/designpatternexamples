/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.EntryInformation "EntryInformation"
/// and @ref DesignPatternExamples_csharp.Strategy_ShowEntries_Class "Strategy_ShowEntries_Class"
/// classes used in the @ref strategy_pattern "Strategy pattern".

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents an individual with a Name, Age, and Height.
    /// </summary>
    public class EntryInformation
    {
        /// <summary>
        /// Name of this individual.
        /// </summary>
        public string Name;

        /// <summary>
        /// Age of this individual, in years.
        /// </summary>
        public int Age;

        /// <summary>
        /// Height of this individual, in inches.
        /// </summary>
        public int Height;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of the individual.</param>
        /// <param name="age">Age of the individual (in years).</param>
        /// <param name="height">Height of the individual (in inches).</param>
        public EntryInformation(string name, int age, int height)
        {
            Name = name;
            Age = age;
            Height = height;
        }


        /// <summary>
        /// Convert the entry into a string.  In this case, a formatted
        /// string where name, age, and height are confined to columns.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return String.Format("{0,6} {1,3} {2,3}\"", Name, Age, Height);
        }
    }


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
    public class Strategy_ShowEntries_Class
    {
        /// <summary>
        /// Identifies the different sorting strategies available.
        /// </summary>
        public enum SortOptions
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
        }


        /// <summary>
        /// The sorting strategy to use.
        /// </summary>
        ISortEntries _sortEntries;

        /// <summary>
        /// Whether to reverse the normal order of the sort.
        /// </summary>
        /// <remarks>
        /// This is remembered here so we can use it when outputting the list.
        /// </remarks>
        bool _reversedSort;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="sortOption">A value from the SortOptions enumeration indicating the sorting
        /// strategy to use.</param>
        /// <param name="reversedSort">true if the sort is to be reversed (descending); otherwise,
        /// sort in ascending order.</param>
        public Strategy_ShowEntries_Class(SortOptions sortOption, bool reversedSort)
        {
            _reversedSort = reversedSort;
            // Create the sorting strategy to use.
            _sortEntries = Strategy_SortEntries_ClassFactory.Create(sortOption, reversedSort);

        }

        /// <summary>
        /// Display the specified entries in sorted order.  The order of the
        /// sort was established when the Strategy_ShowEntries_Class was instantiated.
        /// </summary>
        /// <param name="entries">A list of EntryInformation objects to sort and display</param>
        public void ShowEntries(EntryInformation[] entries)
        {
            // Make a local copy of the entries so we can sort them using the
            // List class's sorting capabilities; otherwise, we would have to
            // write our own sorting algorithms to work on an array.
            List<EntryInformation> localEntries = new List<EntryInformation>(entries);
            _sortEntries.Sort(localEntries);

            // This is a tabular display, making it easier to follow the sorted data.
            Console.WriteLine("    Sort strategy: {0} (order = {1})", _sortEntries, _reversedSort ? "Descending" : "Ascending");
            Console.WriteLine("      {0,6} {1,3} {2,3}", "Name", "Age", "Height");
            Console.WriteLine("      {0,6} {1,3} {2,3}", "------", "---", "------");
            foreach(EntryInformation entry in localEntries)
            {
                Console.WriteLine("      {0}", entry);
            }
        }
    }
}
