/// @file
/// @brief
/// Declaration of the FileDirEntry, FileEntry, DirEntry structures, along with
/// the FileDirEntry_GetFileDirType(), FileDirEntry_GetLength(), FileDirEntry_GetChildren(),
/// FileDirEntry_GetName(), and FileDirEntry_GetWhenModified() functions
/// as used in support of the @ref composite_pattern example.

#pragma once
#ifndef __FILEDIRENTRY_H__
#define __FILEDIRENTRY_H__

#include <stdbool.h>
#include <time.h>

/// <summary>
/// Represents the type of entries allowed in the hierarchy for the
/// Composite design pattern example.
/// </summary>
typedef enum
{
    /// <summary>
    /// Represents a file entry.
    /// </summary>
    FileDirType_File,

    /// <summary>
    /// Represents a directory entry that can contain other FileDirEntry components.
    /// </summary>
    FileDirType_Directory,

    /// <summary>
    /// Represents an unknown type and is considered an error condition.
    /// </summary>
    FileDirType_Unknown = -1
} FileDirTypes;


/// <summary>
/// Structure representing a File (FileEntry) or Directory (DirEntry) entry.
/// This is included as the first element of FileEntry and DirEntry structures.
/// It allows those structures to be cast as a FileDirEntry*.
/// </summary>
typedef struct FileDirEntry
{
    /// <summary>
    /// Value from the @ref FileDirTypes enumeration indicating what type of
    /// entry this is a part of.  Call the FileDirEntry_GetFileDirType() function
    /// to get this value.
    /// </summary>
    FileDirTypes fileDirType;

    /// <summary>
    /// Name of this entry.  Use the FileDirEntry_GetName() function to get
    /// this value.
    /// </summary>
    const char* name;

    /// <summary>
    /// Length of this entry.  For DirEntry objects, this is computed when
    /// getting the length by calling the FileDirEntry_GetLength() function.
    /// </summary>
    long length;

    /// <summary>
    /// Timestamp of when this entry was last "modified".  Use the
    /// FileDirEntry_GetWhenModified() function to get this value.
    /// </summary>
    time_t whenModified;

    /// <summary>
    /// Points to the next entry in a linked list of FileDirEntry objects.
    /// NULL means no more in list.
    /// </summary>
    struct FileDirEntry* next;
} FileDirEntry;


/// <summary>
/// Represents a File entry.
/// 
/// A File entry cannot have any children but does have an explicit size.
/// </summary>
typedef struct
{
    FileDirEntry base; ///< Base FileDirEntry identifying this entry.
} FileEntry;


/// <summary>
/// Represents a Directory entry.
/// 
/// A directory entry contains 0 or more children, which can be a mix of
/// file and directory entries.
/// 
/// A Directory's size is the sum of all children sizes and is computed once
/// on the first call to the FileDirEntry_GetLength() function.
/// </summary>
typedef struct
{
    FileDirEntry base;        ///< Base FileDirEntry identifying this entry.
    FileDirEntry* _children;  ///< Linked list of possible children.  NULL if empty.
    bool _lengthSet;          ///< true if length of all children has been computed;
                              ///< otherwise, false.
} DirEntry;

/// <summary>
/// Get the type of this FileDirEntry object as a value from the @ref FileDirTypes
/// enumeration.
/// </summary>
/// <param name="entry">A FileDirEntry object to examine.</param>
/// <returns>Returns a value from the @ref FileDirTypes enumeration indicating
/// the type of the object.</returns>
FileDirTypes FileDirEntry_GetFileDirType(FileDirEntry* entry);

/// <summary>
/// Get the length of the given FileDirEntry object.  For Files, this is a
/// static value.  For Directories, this is computed once from all the children
/// of the directory and stored internally.
/// </summary>
/// <param name="entry">A FileEntry or DirEntry object for which to get the length.
/// </param>
/// <returns>Returns the length of the given entry.</returns>
long FileDirEntry_GetLength(FileDirEntry* entry);

/// <summary>
/// Retrieve a pointer to the first child of the given FileDirEntry object.  If
/// the entry does not support children or the entry has no children, returns a
/// NULL pointer.
/// </summary>
/// <param name="entry">A FileDirEntry object to examine.</param>
/// <returns>Returns a FileDirEntry* representing the first child in the list;
/// Returns NULL if there are no children or the FileDirEntry object is a
/// FileEntry object that does not support children.</returns>
FileDirEntry* FileDirEntry_GetChildren(FileDirEntry* entry);

/// <summary>
/// Retrieve the name of the given FileDirEntry object.
/// </summary>
/// <param name="entry">FileDirEntry object to examine.</param>
/// <returns>Returns a pointer to the name of the entry.</returns>
const char* FileDirEntry_GetName(FileDirEntry* entry);

/// <summary>
/// Retrieve the last modified time of the given FileDirEntry object.
/// </summary>
/// <param name="entry">FileDirEntry object to examine.</param>
/// <returns>Returns a time_t value representing last modified time of the
/// FileDirEntry object.</returns>
time_t FileDirEntry_GetWhenModified(FileDirEntry* entry);

#endif // __FILEDIRENTRY_H__

