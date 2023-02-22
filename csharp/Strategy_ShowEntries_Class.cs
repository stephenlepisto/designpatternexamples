// The Strategy pattern is used when a choice of multiple different but
// related algorithms can be made at run time.  The implementation of each
// related algorithm exposes the same interface so as to hide the details of
// implementation from the calling program.
//
// In a more general form, a "Strategy" is nothing more than a class
// implementation hidden behind an abstract interface.  This allows the
// implementation to be changed without affecting the caller.  The Strategy
// pattern takes this one step further to allow entire algorithms to be
// hidden behind the interface and then swap in different instances of the
// interface to change the algorithm being used at run time.
//
// Typically a Strategy pattern implementation specifies the algorithm at the
// time the program starts up or is configured.  It can also be configured at
// the time a class representing the functionality is instantiated.  The
// algorithm to use is generally selected by the user based on some input.
// Once set, the algorithm selected does not change until reconfigured or the
// user selects another algorithm.
//
// The value of a Strategy pattern is the ability to create a basic
// infrastructure for the program and then allow the user to alter the
// behavior of that infrastructure using options.  Also, additional strategies
// for each option can be added without changing the basic infrastructure or
// affecting any other strategy.  The drawback is now the functionality of the
// program is spread out across many different classes and it can be quite
// difficult following the flow of execution, especially if a strategy can
// itself have its own set of strategies.
//
// The only tricky part of making use of the Strategy pattern is figuring out
// what the interface should be for all possible algorithms for a given
// situation.  The simplest approach to solving this is to determine what must
// the algorithm provide to the caller to allow the caller to get work done
// then defining an interface that provides that functionality.  Then create
// the implementation of algorithms that satisfies the required functionality.
//
// For example, a program such as dir or ls can list files and folders in a
// variety of formats.  This program has one feature: display information
// about files and folders.  This feature can be broken down into two
// components:
//   1) Fetch information about files/folders
//   2) Display the fetched in information about the files/folders
//
// To fetch the information about files and folders, there are several
// options:
//   - with no arguments, look at all files and folders in the current folder
//   - Specify matching files/folders (can include wildcards)
//   - Specify with a wildcard the files/folders to look at
//   - Recurse through all folders for all files/folders
//   - Recurse through all folders for all matching files/folders
//
// Each of these can be represented by a strategy for reading information
// about files/folders.  That is, an interface can be defined that returns a
// list of files/folders given a pattern.  Then specific implementations of
// the interface can deal with matching files and recursing through folders.
//
// The same approach can be taken with displaying the information:
//   - Display all information about files/folders in sorted order
//   - Display only the names of files/folders in sorted order
//   - Display only the names of files in sorted order
//   - Display only the names of folders in sorted order
//
// Each of these display options could be a strategy.  Define an interface
// that takes a list of information about files/folders and display all or
// some of the information in the given order. 
//
// The "in sorted order" suggests a third strategy is needed: How to sort the
// list of files/folders.  For example, sort by name, length, type, date, with
// an option to reverse the order.
//
// So the ls program works like this (based on input parameters, including
// default parameters):
//   1. Select and use a strategy to read in information about files/folders.
//   2. Select and use a strategy to sort the list of information about
//      files/folders
//   3. Select and use a strategy to display the sorted list of information
//      about files/folders.
//
// With this approach, the pseudo-code for the ls program can look like this:
//   1. Create instance of file fetch interface based on input parameters
//   2. Create instance of sorting interface based on input parameters
//   3. Create instance of display interface based on input parameters
//   4. Get list of files using file fetch interface
//   5. Sort list of files using sorting interface
//   6. Display list of files using display interface
//   7. Done.
//
// All the really hard stuff happens inside the implementation of each
// strategy.  And additional implementations of each strategy can be added
// later on without affecting the above pseudo-code.
//
// As interesting as the above file lister example would be, it would be just
// a bit too long as an example (like a 1000 lines long).  So in a
// considerably simpler example with only one strategy, a list of individuals
// with Name, Age, and Height are sorted in some order based on a selected
// strategy.  The list of individuals is then shown in the sorted order.
// The sort has a modification where the order can be reversed from ascending
// to descending.
//
// Note: It is strongly advised not to use the word "Strategy" when naming the
// interfaces.  That name is too generic.  Name the interfaces based on what
// the interfaces are used for and that includes the methods exposed through
// the interface.  The only reason I'm using "Strategy" in this example is
// to help group the public classes into the patterns being demonstrated.

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
