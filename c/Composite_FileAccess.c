/// @file
/// @brief
/// Implementation of the Composite_FileAccess_GetEntry() function along with
/// the static file/directory list used in the example for the
/// @ref composite_pattern.

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helpers/datetime.h"
#include "helpers/replace.h"
#include "helpers/split.h"
#include "helpers/strdup.h"

#include "Composite_FileDirEntry.h"
#include "Composite_FileAccess.h"

/// <summary>
/// The root of the constructed file/directory tree.
/// </summary>
static FileDirEntry* _root = NULL;


/// <summary>
/// Create a new FileEntry object with the specified properties.
/// </summary>
/// <param name="name">Name of the file entry.</param>
/// <param name="length">Length of the file entry.</param>
/// <param name="whenModified">Timestamp for when this file entry was last
/// modified.</param>
/// <returns>Returns a FileEntry object cast as a FileDirEntry pointer.
/// Returns NULL for out of memory error.</returns>
FileDirEntry* _NewFileEntry(const char* name, long length, time_t whenModified)
{
    FileEntry* fileEntry = calloc(1, sizeof(FileEntry));
    if (fileEntry != NULL)
    {
        fileEntry->base.name = name;
        fileEntry->base.length = length;
        fileEntry->base.whenModified = whenModified;
        fileEntry->base.fileDirType = FileDirType_File;
    }

    return (FileDirEntry*)fileEntry;
}

/// <summary>
/// Create a new DirEntry object with the specified properties.
/// </summary>
/// <param name="name">Name of the directory entry.</param>
/// <param name="whenModified">Timestamp for when this directory entry was last
/// modified.</param>
/// <returns>Returns a DirEntry object.  Returns NULL for out of memory error.</returns>
DirEntry* _NewDirEntry(const char* name, time_t whenModified)
{
    DirEntry* dirEntry = calloc(1, sizeof(DirEntry));
    if (dirEntry != NULL)
    {
        dirEntry->base.name = name;
        dirEntry->base.whenModified = whenModified;
        dirEntry->base.fileDirType = FileDirType_Directory;
    }

    return dirEntry;
}

/// <summary>
/// Add a child to the given DirEntry object.
/// </summary>
/// <param name="dirEntry">The DirEntry to which to add the child.</param>
/// <param name="child">The FileDirEntry object to add as a child.</param>
void _AddChild(DirEntry* dirEntry, FileDirEntry* child)
{
    if (dirEntry != NULL && child != NULL)
    {
        if (dirEntry->_children == NULL)
        {
            dirEntry->_children = child;
        }
        else
        {
            FileDirEntry* nextChild = dirEntry->_children;
            while (nextChild->next != NULL)
            {
                nextChild = nextChild->next;
            }
            nextChild->next = child;
        }
    }
}

/// <summary>
/// Destroy a file/directory tree given its root.  Each element of the
/// hierarchical tree needs to be freed.  After this function returns, the
/// root pointer is no longer valid.
/// </summary>
/// <param name="root">A FileDirEntry object representing the root of the tree
/// to destroy.</param>
static void _DestroyTree(FileDirEntry* root)
{
    if (root != NULL)
    {
        if (root->fileDirType == FileDirType_Directory)
        {
            DirEntry* dirEntry = (DirEntry*)root;
            _DestroyTree(dirEntry->_children);
        }
        free(root);
    }
}

/// <summary>
/// Construct a file/directory tree with a predefined set of files and
/// directories.  If there are any out of memory conditions, the entire
/// root built to that point is freed, leaving the program in the same state
/// as before this function was called.
/// </summary>
static void _ConstructTree(void)
{
    if (_root == NULL)
    {
        time_t now = datetime_now();
        DirEntry* dirEntry = _NewDirEntry("root", now);
        if (dirEntry == NULL)
        {
            return;
        }
        _root = (FileDirEntry*)dirEntry;

        FileDirEntry* fileEntry = _NewFileEntry("FileA.txt", 101, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(dirEntry, fileEntry);

        fileEntry = _NewFileEntry("FileB.txt", 102, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(dirEntry, fileEntry);

        fileEntry = _NewFileEntry("FileC.txt", 103, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(dirEntry, fileEntry);

        DirEntry* subDirEntry = _NewDirEntry("subdir1", now);
        if (subDirEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(dirEntry, (FileDirEntry*)subDirEntry);

        fileEntry = _NewFileEntry("FileD.txt", 104, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(subDirEntry, fileEntry);

        fileEntry = _NewFileEntry("FileE.txt", 105, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(subDirEntry, fileEntry);

        DirEntry* subsubDirEntry = _NewDirEntry("subdir2", now);
        if (subsubDirEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(subDirEntry, (FileDirEntry*)subsubDirEntry);


        fileEntry = _NewFileEntry("FileF.txt", 106, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(subsubDirEntry, fileEntry);

        fileEntry = _NewFileEntry("FileG.txt", 107, now);
        if (fileEntry == NULL)
        {
            _DestroyTree(_root);
            return;
        }
        _AddChild(subsubDirEntry, fileEntry);
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/// <summary>
/// Search the file/directory "tree" for an entry that matches the given file
/// "path".  The file path is a slash-separated list of directory names ending
/// in either a directory name or a file name.
/// </summary>
/// <param name="path">The path to the file or directory to retrieve.  This
/// will be altered.</param>
/// <returns>Returns a FileDirEntry* representing the desired file or directory.
/// Returns NULL if the entry could not be found.</returns>
static FileDirEntry* _FindEntry(char* path)
{
    _ConstructTree();

    FileDirEntry* root = _root;
    if (root != NULL)
    {
        SplitList pathComponents = { 0 };
        split(path, "/", &pathComponents);
        if (pathComponents.strings_count > 0)
        {
            size_t numComponents = pathComponents.strings_count;
            for (size_t index = 0; index < numComponents; index++)
            {
                const char* rootName = FileDirEntry_GetName(root);
                if (strcmp(rootName, pathComponents.strings[index]) != 0)
                {
                    // Mismatch in path to this entry, bad path
                    root = NULL;
                    break;
                }

                if ((index + 1) >= numComponents)
                {
                    // Reached end of path so we found what was asked for.
                    break;
                }

                // Still haven't reached end of specified path, look at
                // the current root for children.

                FileDirEntry* child = FileDirEntry_GetChildren(root);
                if (child == NULL)
                {
                    // Path included leaf in the middle, bad path
                    break;
                }

                root = NULL; // Assume we won't find anything
                // Look ahead in the path for a matching child.
                const char* childComponent = pathComponents.strings[index + 1];
                while (child != NULL)
                {
                    const char* childName = FileDirEntry_GetName(child);
                    if (strcmp(childName, childComponent) == 0)
                    {
                        root = child;
                        break;
                    }
                    child = child->next;
                }

                if (root == NULL)
                {
                    // Couldn't find matching child, bad path
                    break;
                }
            }
        }
        SplitList_Clear(&pathComponents);
    }

    return root;
}

///////////////////////////////////////////////////////////////////////////////
// Composite_FileAccess_GetEntry()
///////////////////////////////////////////////////////////////////////////////
FileDirEntry* Composite_FileAccess_GetEntry(const char* path)
{
    FileDirEntry* foundEntry = NULL;

    if (path != NULL)
    {
        // _FindEntry() modifies the path string so create duplicate to work with.
        char* filepath = STRDUP(path);
        if (filepath != NULL)
        {
            replace_chr(filepath, '\\', '/');
            foundEntry = _FindEntry(filepath);

            free(filepath);
        }
    }

    return foundEntry;
}
