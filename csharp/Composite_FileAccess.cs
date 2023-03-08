/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Composite_FileAccess "Composite_FileAccess"
/// static class as used in the @ref composite_pattern "Composite pattern".
///
/// This module contains the hardcoded example of a file/directory hierarchy.
/// The example code calls Composite_FileAccess.GetEntry() with the path of
/// of the file or directory.  GetEntry() returns a FileDirEntry presenting
/// the requested entry, with possible children (if the entry is a directory).
///
/// To simplify the example, the files and directories are hardcoded into a
/// composite list so that GetEntry() only needs to return the entry from the
/// composite list once it is found.

using System;
using System.IO;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Static class containing functions for accessing a hardcoded "file" and
    /// "directory" hierarchy.
    /// </summary>
    public static class Composite_FileAccess
    {
        // The hardcoded hierarchy representing a file/directory structure.
        // Note: This is the Composite pattern in action.
        static FileDirEntry rootEntry =
            new DirEntry("root", DateTime.Now, new FileDirEntry[] {
                new FileEntry("FileA.txt", 101, DateTime.Now),
                new FileEntry("FileB.txt", 102, DateTime.Now),
                new FileEntry("FileC.txt", 103, DateTime.Now),
                new DirEntry("subdir1", DateTime.Now, new FileDirEntry[] {
                    new FileEntry("FileD.txt", 104, DateTime.Now),
                    new FileEntry("FileE.txt", 105, DateTime.Now),
                    new DirEntry("subdir2", DateTime.Now, new FileDirEntry[] {
                        new FileEntry("FileF.txt", 106, DateTime.Now),
                        new FileEntry("FileG.txt", 107, DateTime.Now)
                    }),
                }),
            });


        /// <summary>
        /// Helper method to search the static data list for the specified
        /// file/dir entry.
        /// </summary>
        /// <param name="filepath">A "path" specifying the entry to find, with each
        /// component separated by '/'.</param>
        /// <returns>Returns a FileDirEntry object for the requested object;
        /// otherwise, returns null, indicating the entry was not found.</returns>
        private static FileDirEntry _FindEntry(string filepath)
        {
            FileDirEntry root = rootEntry;

            string[] pathComponents = filepath.Split('/');
            int numComponents = pathComponents.Length;
            for (int index = 0; index < numComponents; ++index)
            {
                if (root.Name != pathComponents[index])
                {
                    // Mismatch in path to this entry, bad path
                    root = null;
                    break;
                }
                if (index + 1 >= numComponents)
                {
                    // Reached end of path so we found what was asked for.
                    break;
                }

                // Still haven't reached end of specified path, look at
                // the current root for children.

                FileDirEntry[] children = root.Children;
                if (children == null)
                {
                    // Path included leaf in the middle, bad path
                    root = null;
                    break;
                }

                root = null; // Assume we won't find matching child
                // Look ahead in the path for a matching child.
                string childComponent = pathComponents[index + 1];
                foreach (FileDirEntry child in children)
                {
                    if (childComponent == child.Name)
                    {
                        root = child;
                        break;
                    }
                }
                if (root == null)
                {
                    // Couldn't find matching child, bad path
                    break;
                }
            }

            // Root is either a valid file/directory entry that matches the
            // requested path or it is null, indicating the entry could not be
            // found.
            return root;
        }

        
        /// <summary>
        /// Return a FileDirEntry object representing the specified file "path"
        /// in an internal list of data entries that is organized in a file/
        /// directory structure.
        /// </summary>
        /// <param name="filepath">A "path" specifying the entry to find, with each
        /// component separated by '/'.</param>
        /// <returns>Returns a FileDirEntry object representing the specified file entry.
        /// </returns>
        /// <exception cref="FIleNotFoundException">The specified file entry was not found.</exception>
        public static FileDirEntry GetEntry(string filepath)
        {
            filepath = filepath.Replace('\\', '/');
            FileDirEntry filedirEntry = _FindEntry(filepath);

            if (filedirEntry == null)
            {
                string msg = String.Format("Unable to find '{0}'", filepath);
                throw new FileNotFoundException(msg);
            }

            return filedirEntry;
        }
    }
}
