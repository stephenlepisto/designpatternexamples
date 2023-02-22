// The Strategy pattern is used when a choice of multiple different but
// related algorithms can be made at startup time.  The implementation of each
// related algorithm exposes the same interface so as to hide the details of
// implementaiton from the calling program.
//
// In a more general form, a "Strategy" is nothing more than a class
// implementation hidden behind an abstract interface.  This allows the
// implementation to be changed without affecting the caller.  The Strategy
// pattern takes this one step further to allow entire algorithms to be
// hidden behind the interface and then swap in different instances of the
// interface to change the algorithm being used.
//
// Typically a Strategy pattern implementation specifies the algorithm at the
// time the program starts up or is configured.  The algorithm selected could
// also be selected by the user based on some input.  Once set, the algorithm
// selected does not change until reconfigured or the user selects another
// algorithm.
//
// The only tricky part of making use of the Strategy pattern is figuring out
// what the interface should be for all possible algorithms for a given
// situation.  The simplest approach to solving this is what must the
// algorithm provide to the caller to allow the caller to get work done then
// defining an interface that provides that functionality.  Then create the
// implementation of algorithms that satisfies the required functionality.
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
// The "in sorted order" suggests a third strategy is needed: how to sort the
// list of files/folders.  Sort by name, length, type, date, with an option to
// reverse the order.
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
// later on without affecting the above psuedo-code.
//
// Note: It is strongly advised not to use the word "Strategy" when naming the
// interfaces.  That name is too generic.  Name the interfaces based on what
// the interfaces are used for and that includes the methods exposed through
// the interface.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    [Flags]
    public enum EntryFlags
    {
        Directory = 1 << 0, // If set is directory, else is file
        System = 1 << 1,    // If set is system file
        Hidden = 1 << 2,    // If set is hidden file
        Archive = 1 << 3,   // If set archive flag is set
        ReadOnly = 1 << 4,  // If set is read only
    }


    internal class EntryInformation
    {
        public string DirectoryName;
        public string Name;
        public DateTime LastModified;
        public DateTime WhenCreated;
        public DateTime LastAccess;
        public ulong Size;
        public EntryFlags EntryFlags;
        public List<EntryInformation> Children;
    }

    public enum FetchOptions
    {
        FetchAll,             // Get files and folders
        FetchOnlyFiles,       // get only filenames
        FetchOnlyDirectories, // get only directory names
    }

    public enum SortOptions
    {
        ByName,          // Sort alphabetically by name (ascending)
        ByLastModified,  // Sort using last modified timestamp (old to new)
        ByWhenCreated,   // Sort using when created timestamp (old to new)
        ByLastAccess,    // Sort using last access timestamp (old to new)
        BySize           // Sort using size (small to large)
    }

    public enum DisplayOptions
    {
        ShowAll,
        ShowOnlyFiles,
        ShowOnlyDirectories,
        ShowOnlyNames,
    }

    [Flags]
    public enum DisplayModifierOptions
    {
        None = 0,
        IncludeHidden = 1 << 0,
        IncludeSystem = 1 << 1,
        ShowOnlyHidden = 1 << 2,
        ShowOnlySystem = 1 << 3
    }

    public class InputOptions
    {
        /// <summary>
        /// Paths to one or more files or directories.  If a directory is
        /// specified, list all files in the directory.
        /// </summary>
        public string[] Pathnames;
        public FetchOptions FetchOptions;
        public bool RecurseDirectories;
        public SortOptions SortOptions;
        public bool ReverseSort;
        public DisplayOptions DisplayOptions;
        public DisplayModifierOptions DisplayModifierOptions;

        /// <summary>
        /// Constructor to establish default input options.
        /// </summary>
        public InputOptions()
        {
            Pathnames = new string[] { "." };
            FetchOptions = FetchOptions.FetchAll;
            RecurseDirectories = false;
            SortOptions = SortOptions.ByName;
            ReverseSort = false;
            DisplayOptions = DisplayOptions.ShowAll;
            DisplayModifierOptions = DisplayModifierOptions.None;
        }
    }


    public class Strategy_Class
    {
        public void ShowFileList(InputOptions inputOptions)
        {
            IFetchEntries fetchEntries = Strategy_FetchEntries_ClassFactory.Create(inputOptions);
            ISortEntries sortEntries = Strategy_SortEntries_ClassFactory.Create(inputOptions);
            IDisplayEntries displayEntries = Strategy_DisplayEntries_ClassFactory.Create(inputOptions);

            List<EntryInformation> entries = fetchEntries.Fetch();
            sortEntries.Sort(entries);
            displayEntries.Display(entries);
        }
    }
}
