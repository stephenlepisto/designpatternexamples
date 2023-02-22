using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    internal interface IFetchEntries
    {
        List<EntryInformation> Fetch();
    }

    internal class FetchEntries_Base
    {
        string[] _pathnames;
        bool _recurseDirectories;

        protected FetchEntries_Base(string[] pathnames, bool recurseDirectories)
        {
            _pathnames = pathnames;
            _recurseDirectories = recurseDirectories;
        }


        EntryFlags _TranslateFileAttributesToEntryFlags(FileAttributes fileAttributes)
        {
            EntryFlags entryFlags = 0;

            if ((fileAttributes & FileAttributes.Directory) != 0)
            {
                entryFlags |= EntryFlags.Directory;
            }

            if ((fileAttributes & FileAttributes.Hidden) != 0)
            {
                entryFlags |= EntryFlags.Hidden;
            }

            if ((fileAttributes & FileAttributes.System) != 0)
            {
                entryFlags |= EntryFlags.System;
            }

            if ((fileAttributes & FileAttributes.ReadOnly) != 0)
            {
                entryFlags |= EntryFlags.ReadOnly;
            }

            if ((fileAttributes & FileAttributes.Archive) != 0)
            {
                entryFlags |= EntryFlags.Archive;
            }

            return entryFlags;
        }

        private EntryInformation _GetFileEntryInformation(string pathname)
        {
            EntryInformation entry = new EntryInformation();

            FileInfo fileinfo = new FileInfo(pathname);

            entry.EntryFlags = _TranslateFileAttributesToEntryFlags(fileinfo.Attributes);
            entry.Size = (ulong)fileinfo.Length;
            entry.Name = fileinfo.Name;
            entry.DirectoryName = fileinfo.DirectoryName;
            entry.LastModified = fileinfo.LastWriteTime;
            entry.WhenCreated = fileinfo.CreationTime;
            entry.LastAccess = fileinfo.LastAccessTime;
            return entry;
        }

        private EntryInformation _GetDirectoryEntryInformation(string pathname)
        {
            EntryInformation entry = new EntryInformation();

            DirectoryInfo dirinfo = new DirectoryInfo(pathname);

            entry.EntryFlags = _TranslateFileAttributesToEntryFlags(dirinfo.Attributes);
            entry.Name = dirinfo.Name;
            entry.DirectoryName = Path.GetDirectoryName(dirinfo.FullName);
            entry.Size = 0;
            entry.LastModified = dirinfo.LastWriteTime;
            entry.LastAccess = dirinfo.LastAccessTime;
            entry.WhenCreated = dirinfo.CreationTime;

            return entry;
        }

        private EntryInformation _GetEntryInformation(string pathname)
        {
            EntryInformation entry = null;

            if (File.Exists(pathname))
            {
                entry = _GetFileEntryInformation(pathname);
            }
            else
            {
                entry = _GetDirectoryEntryInformation(pathname);
            }

            return entry;
        }

        private ulong _CalculateSize(List<EntryInformation> entries)
        {
            ulong size = 0;

            foreach(EntryInformation entry in entries)
            {
                size += entry.Size;
            }
            return size;
        }

        /// <summary>
        /// Read all applicable entries from the given path.
        /// 
        /// The path is expected to be [<dir>\]<file>, where <file> is the name
        /// of a file or a search pattern for folder or file names.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="addFiles"></param>
        /// <param name="addDirectories"></param>
        /// <returns></returns>
        private List<EntryInformation> _ReadOnePathOfEntries(string path, bool addFiles, bool addDirectories)
        {
            List<EntryInformation> entries = new List<EntryInformation>();

            IEnumerable<string> entryEnumerable;

            string basePath = Path.GetDirectoryName(path);
            string searchPattern = Path.GetFileName(path);
            if (String.IsNullOrEmpty(basePath))
            {
                basePath = ".";
            }
            if (!Directory.Exists(basePath))
            {
                string message = string.Format("The folder '{0}' does not exist.  Cannot search in it.", basePath);
                throw new ApplicationException(message);
            }
            if (String.IsNullOrEmpty(searchPattern))
            {
                searchPattern = "*";
            }

            // Read all files and folder names that match the given pattern, optionally recursing
            // through all directories.
            entryEnumerable = Directory.EnumerateFileSystemEntries(basePath, searchPattern);
            foreach(string entryName in entryEnumerable)
            {
                EntryInformation entry = _GetEntryInformation(entryName);
                entries.Add(entry);
                if (_recurseDirectories)
                {
                    if ((entry.EntryFlags & EntryFlags.Directory) != 0)
                    {
                        entry.Children = _ReadOnePathOfEntries(Path.Combine(entry.DirectoryName, entry.Name, "*"), addFiles, addDirectories);
                        entry.Size = _CalculateSize(entry.Children);
                    }
                }
            }

            return entries;
        }


        protected List<EntryInformation> ReadEntries(bool addFiles, bool addDirectories)
        {
            List<EntryInformation> entries = new List<EntryInformation>();

            foreach(string path in _pathnames)
            {
                List<EntryInformation> localEntries = _ReadOnePathOfEntries(path, addFiles, addDirectories);
                if (localEntries.Count > 0)
                {
                    entries.AddRange(localEntries);
                }
            }

            return entries;
        }
    }

    internal class FetchEntries_All : FetchEntries_Base, IFetchEntries
    {
        internal FetchEntries_All(string[] pathnames, bool recurseDirectories)
            : base(pathnames, recurseDirectories)
        {

        }

        List<EntryInformation> IFetchEntries.Fetch()
        {
            return base.ReadEntries(true, true);
        }
    }

    internal class FetchEntries_FilesOnly : FetchEntries_Base, IFetchEntries
    {
        internal FetchEntries_FilesOnly(string[] pathnames, bool recurseDirectories)
            : base(pathnames, recurseDirectories)
        {

        }

        List<EntryInformation> IFetchEntries.Fetch()
        {
            return base.ReadEntries(true, false);
        }
    }

    internal class FetchEntries_DirectoriesOnly : FetchEntries_Base, IFetchEntries
    {
        internal FetchEntries_DirectoriesOnly(string[] pathnames, bool recurseDirectories)
            : base(pathnames, recurseDirectories)
        {

        }

        List<EntryInformation> IFetchEntries.Fetch()
        {
            return base.ReadEntries(false, true);
        }
    }

    internal static class Strategy_FetchEntries_ClassFactory
    {
        internal static IFetchEntries Create(InputOptions options)
        {
            IFetchEntries fetchEntries = null;

            switch(options.FetchOptions)
            {
                case FetchOptions.FetchAll:
                    fetchEntries = new FetchEntries_All(options.Pathnames, options.RecurseDirectories);
                    break;

                case FetchOptions.FetchOnlyFiles:
                    fetchEntries = new FetchEntries_FilesOnly(options.Pathnames, options.RecurseDirectories);
                    break;

                case FetchOptions.FetchOnlyDirectories:
                    fetchEntries = new FetchEntries_DirectoriesOnly(options.Pathnames, options.RecurseDirectories);
                    break;

                default:
                    {
                        string message = string.Format("Unrecognized fetch option: {0}", options.FetchOptions);
                        throw new ApplicationException(message);
                    }
            }

            return fetchEntries;
        }
    }
}
