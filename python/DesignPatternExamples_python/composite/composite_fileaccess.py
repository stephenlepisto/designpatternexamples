## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.composite.composite_fileaccess.Composite_FileAccess "Composite_FileAccess",
#  class used in the @ref composite_pattern.

from .composite_filedirentry import FileDirEntry, FileDirEntryList, FileEntry, DirEntry
from datetime import datetime

## Class containing static functions for accessing a hardcoded "file" and
#  "directory" hierarchy.
#
#  Entries are declared like this:
#  @snippet python/DesignPatternExamples_python/composite/composite_fileaccess.py Python Composite_FileAccess directory tree
class Composite_FileAccess:
    ## List of all "files" and "directories" used in the @ref command_pattern
    #  example.

    # ! [Python Composite_FileAccess directory tree]
    _rootEntry =  \
            DirEntry("root", datetime.now(), [ \
                FileEntry("FileA.txt", 101, datetime.now()),
                FileEntry("FileB.txt", 102, datetime.now()),
                FileEntry("FileC.txt", 103, datetime.now()),
                DirEntry("subdir1", datetime.now(), [ \
                    FileEntry("FileD.txt", 104, datetime.now()),
                    FileEntry("FileE.txt", 105, datetime.now()),
                    DirEntry("subdir2", datetime.now(), [ \
                        FileEntry("FileF.txt", 106, datetime.now()),
                        FileEntry("FileG.txt", 107, datetime.now())
                    ]),
                ]),
            ])
    # ! [Python Composite_FileAccess directory tree]


    ## Helper method to search the static data list for the specified file/dir
    #  entry.
    #
    #  @param filepath
    #         A "path" specifying the entry to find, with each component
    #         separated by '/'.
    #  @returns
    #     Returns the found entry otherwise, returns None.
    def _FindEntry(filepath : str) -> FileDirEntry:
        root = Composite_FileAccess._rootEntry # type: FileDirEntry
        found = False

        pathComponents = filepath.split('/')
        numComponents = len(pathComponents)
        for index in range(0, numComponents):
            found = False
            if root.Name() != pathComponents[index]:
                # Mismatch in path to this entry, bad path
                root = None
                break

            if index + 1 >= numComponents:
                # Reached end of path so we found what was asked for.
                found = True
                break

            # Still haven't reached end of specified path, look at
            # the current root for children.

            children = root.Children() # type: FileDirEntryList
            if not children:
                # Path included leaf in the middle, bad path
                found = False
                break

            root = None # assume we won't find anything
            # Look ahead in the path for a matching child.
            childComponent = pathComponents[index + 1] # type: str
            for child in children:
                if childComponent == child.Name():
                    root = child
                    found = True
                    break
            if not found:
                # Couldn't find matching child, bad path
                break
        return root


    ## Retrieve a
    #  @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirEntry "FileDirEntry"
    #  object representing the specified file "path" in an internal list of
    #  data entries that is organized in a file/directory structure.
    #
    #  @param filepath
    #         A "path" specifying the entry to find, with each component
    #         separated by '/'.
    #  @returns
    #     Returns a
    #     @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirEntry "FileDirEntry"
    #     object representing the specified file entry.
    def GetEntry(filepath : str) -> FileDirEntry:
        filepath = filepath.replace('\\', '/')
        fileDirEntry = Composite_FileAccess._FindEntry(filepath)
        if not fileDirEntry:
            raise FileNotFoundError(2, "Unable to find entry", filepath)

        return fileDirEntry
