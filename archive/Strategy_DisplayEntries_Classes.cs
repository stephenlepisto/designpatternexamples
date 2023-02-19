using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    internal interface IDisplayEntries
    {
        void Display(List<EntryInformation> entries);
    }


    class Strategy_DisplayEntries_Base
    {
        DisplayModifierOptions _displayModifierOptions;
        protected Strategy_DisplayEntries_Base(DisplayModifierOptions displayModifierOptions)
        {
            _displayModifierOptions = displayModifierOptions;
        }

        /// <summary>
        /// Format the entry flags into a single string with letters
        /// indicating whether the flag is set or not.  The order, from left
        /// to right is DSHALR (Directory, Sytem, Hidden, Archive, Link, Read-Only).
        /// </summary>
        /// <param name="entryFlags">The collection of entry flags to examine.</param>
        /// <returns>A string containing the entry flags as letters.
        /// A '-' indicates the corresponding flag is not set.</returns>
        private string _FormatEntryFlags(EntryFlags entryFlags)
        {
            // DSHAL--R
            StringBuilder entryFlagsAsString = new StringBuilder();

            string flag = "-";
            if ((entryFlags & EntryFlags.Directory) != 0)
            {
                flag = "D";
            }
            entryFlagsAsString.Append(flag);

            flag = "-";
            if ((entryFlags & EntryFlags.System) != 0)
            {
                flag = "S";
            }
            entryFlagsAsString.Append(flag);

            flag = "-";
            if ((entryFlags & EntryFlags.Hidden) != 0)
            {
                flag = "H";
            }
            entryFlagsAsString.Append(flag);

            flag = "-";
            if ((entryFlags & EntryFlags.Archive) != 0)
            {
                flag = "A";
            }
            entryFlagsAsString.Append(flag);

            flag = "-";
            if ((entryFlags & EntryFlags.ReadOnly) != 0)
            {
                flag = "R";
            }
            entryFlagsAsString.Append(flag);

            return entryFlagsAsString.ToString();
        }

        private string _GetName(EntryInformation entry)
        {
            string name = entry.Name;
            //string name = Path.Combine(entry.DirectoryName, entry.Name);
            if ((entry.EntryFlags & EntryFlags.Directory) != 0)
            {
                name += "/";
            }
            return name;
        }

        private void _DisplayEntry(EntryInformation entry, bool nameOnly, int indentLevel)
        {
            string indentSpaces = new string(' ', indentLevel);
            if (nameOnly)
            {
                Console.WriteLine("{0}{1}", indentSpaces, entry.Name);
            }
            else
            {
                if (nameOnly)
                {
                    string name = _GetName(entry);
                    Console.WriteLine(name);
                }
                else
                {
                    string date = entry.LastModified.ToLocalTime().ToShortDateString();
                    string time = entry.LastModified.ToLocalTime().ToShortTimeString();
                    string entryFlags = _FormatEntryFlags(entry.EntryFlags);
                    ulong size = entry.Size;
                    string name = _GetName(entry);
                    Console.WriteLine("{1,10} {2,8} {3} {4,12:N0} {0}{5}", indentSpaces, date, time, entryFlags, size, name);
                }
            }
        }

        /// <summary>
        /// Determine if the given entry can be displayed based on the
        /// currently establishe display modifier options.
        /// </summary>
        /// <param name="entry">The entry to examine.</param>
        /// <returns>Returns true if the entry can be displayed; otherwise, returns
        /// false indicating the entry should not be displayed.</returns>
        private bool _CanDisplayEntry(EntryInformation entry)
        {
            bool canDisplay = true;

            if ((_displayModifierOptions & DisplayModifierOptions.IncludeHidden) != 0 ||
                (_displayModifierOptions & DisplayModifierOptions.ShowOnlyHidden) != 0)
            {
                if ((entry.EntryFlags & EntryFlags.Hidden) == 0)
                {
                    canDisplay = false;
                }
            }

            if ((_displayModifierOptions & DisplayModifierOptions.IncludeSystem) != 0 ||
                (_displayModifierOptions & DisplayModifierOptions.ShowOnlySystem) != 0)
            {
                if ((entry.EntryFlags & EntryFlags.System) == 0)
                {
                    canDisplay = false;
                }
            }

            if ((_displayModifierOptions & DisplayModifierOptions.ShowOnlyHidden) != 0)
            {
                if ((entry.EntryFlags & EntryFlags.Hidden) == 0)
                {
                    canDisplay = false;
                }
            }

            if ((_displayModifierOptions & DisplayModifierOptions.ShowOnlySystem) != 0)
            {
                if ((entry.EntryFlags & EntryFlags.System) == 0)
                {
                    canDisplay = false;
                }
            }

            return canDisplay;
        }


        /// <summary>
        /// Determine if the specified entry represents a file.
        /// </summary>
        /// <param name="entry">The entry to examine.</param>
        /// <returns>Returns true if the entry is not a directory or a link.</returns>
        private bool _IsFileEntry(EntryInformation entry)
        {
            bool isFile = true;
            
            if ((entry.EntryFlags & EntryFlags.Directory) != 0)
            {
                isFile = false;
            }

            return isFile;
        }


        /// <summary>
        /// Determine if the specified entry represents a directory.
        /// </summary>
        /// <param name="entry">The entry to examine.</param>
        /// <returns>Returns true if the entry is a directory.</returns>
        private bool _IsDirectoryEntry(EntryInformation entry)
        {
            bool isDirectory = false;

            if ((entry.EntryFlags & EntryFlags.Directory) != 0)
            {
                isDirectory = true;
            }

            return isDirectory;
        }

        
        /// <summary>
        /// Display only files from the given list entries, taking into account
        /// the display modifiers.
        /// </summary>
        /// <param name="entries">List of EntryInformation elements describing
        /// files and folders to display</param>
        /// <param name="indentLevel">Number of spaces to print before each entry.</param>
        protected void DisplayFiles(List<EntryInformation> entries, int indentLevel)
        {
            foreach(EntryInformation entry in entries)
            {
                if (_IsFileEntry(entry))
                {
                    if (_CanDisplayEntry(entry))
                    {
                        _DisplayEntry(entry, false, indentLevel);
                        if (entry.Children != null)
                        {
                            DisplayFiles(entry.Children, indentLevel + 2);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Display only directories from the given list entries, taking into
        /// account the display modifiers.
        /// </summary>
        /// <param name="entries">List of EntryInformation elements describing
        /// files and folders to display</param>
        protected void DisplayDirectories(List<EntryInformation> entries, int indentLevel)
        {
            foreach (EntryInformation entry in entries)
            {
                if (_IsDirectoryEntry(entry))
                {
                    if (_CanDisplayEntry(entry))
                    {
                        _DisplayEntry(entry, false, indentLevel);
                        if (entry.Children != null)
                        {
                            DisplayDirectories(entry.Children, indentLevel + 2);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Display files and directories from the given list entries, taking
        /// into account the display modifiers.
        /// </summary>
        /// <param name="entries">List of EntryInformation elements describing
        /// files and folders to display</param>
        /// <param name="namesOnly">If true, display only the names of each entry.</param>
        protected void DisplayAll(List<EntryInformation> entries, bool namesOnly, int indentLevel)
        {
            foreach (EntryInformation entry in entries)
            {
                if (_CanDisplayEntry(entry))
                {
                    _DisplayEntry(entry, false, indentLevel);
                    if (entry.Children != null)
                    {
                        DisplayAll(entry.Children, namesOnly, indentLevel + 2);
                    }
                }
            }
        }
    }

    internal class Strategy_DisplayEntries_All : Strategy_DisplayEntries_Base, IDisplayEntries
    {
        public Strategy_DisplayEntries_All(DisplayModifierOptions displayModifierOptions)
            : base(displayModifierOptions)
        {
        }


        void IDisplayEntries.Display(List<EntryInformation> entries)
        {
            base.DisplayAll(entries, false, 0);
        }
    }


    internal class Strategy_DisplayEntries_OnlyFiles : Strategy_DisplayEntries_Base, IDisplayEntries
    {
        public Strategy_DisplayEntries_OnlyFiles(DisplayModifierOptions displayModifierOptions)
            : base(displayModifierOptions)
        {
        }


        void IDisplayEntries.Display(List<EntryInformation> entries)
        {
            base.DisplayFiles(entries, 0);
        }
    }


    internal class Strategy_DisplayEntries_OnlyDirectories : Strategy_DisplayEntries_Base, IDisplayEntries
    {
        public Strategy_DisplayEntries_OnlyDirectories(DisplayModifierOptions displayModifierOptions)
            : base(displayModifierOptions)
        {
        }


        void IDisplayEntries.Display(List<EntryInformation> entries)
        {
            base.DisplayDirectories(entries, 0);
        }
    }


    internal class Strategy_DisplayEntries_OnlyNames : Strategy_DisplayEntries_Base, IDisplayEntries
    {
        public Strategy_DisplayEntries_OnlyNames(DisplayModifierOptions displayModifierOptions)
            : base(displayModifierOptions)
        {
        }


        void IDisplayEntries.Display(List<EntryInformation> entries)
        {
            base.DisplayAll(entries, true, 0);
        }
    }

    internal static class Strategy_DisplayEntries_ClassFactory
    {
        internal static IDisplayEntries Create(InputOptions options)
        {
            IDisplayEntries displayEntries = null;

            switch(options.DisplayOptions)
            {
                case DisplayOptions.ShowAll:
                    displayEntries = new Strategy_DisplayEntries_All(options.DisplayModifierOptions);
                    break;

                case DisplayOptions.ShowOnlyFiles:
                    displayEntries = new Strategy_DisplayEntries_OnlyFiles(options.DisplayModifierOptions);
                    break;

                case DisplayOptions.ShowOnlyDirectories:
                    displayEntries = new Strategy_DisplayEntries_OnlyDirectories(options.DisplayModifierOptions);
                    break;

                case DisplayOptions.ShowOnlyNames:
                    displayEntries = new Strategy_DisplayEntries_OnlyNames(options.DisplayModifierOptions);
                    break;

                default:
                    {
                        string message = string.Format("Unrecognized display option: {0}", options.DisplayOptions);
                        throw new ApplicationException(message);
                    }
            }

            return displayEntries;
        }
    }
}
