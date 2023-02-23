#pragma once
// Composite design pattern example.
//
// A composite design is for a hierarchical list of items where some items are
// containers for additional items.  The root of the list is always a container.
// The hierarchical list is a composite of all the node types in the list.
//
// A common example of this is a file/directory structure.  A directory contains
// entries that can be a file or another directory.  The root of the structure
// is a directory.
//
// This example uses a file/directory approach, although the files and directories
// are hardcoded examples.  Each entry, be it a file or a directory, is represented
// by the IFileDirEntry interface.  Each entry has a name, a length, and a date
// when it was last modified.  For directories, the length is the sum of all child
// files and directories contained within.
//
// The type of the entry is determined by the IFileDirEntry.FileDirType property.
// If the entry is a directory, then it might have child entries in the
// IFileDirEntry.Children property.
//
// Note: In a flat list, getting to any entry is straightforward: just provide
// the index to the entry.  For hierarchical lists, however, a "path" must be
// provided to get to any entry.  This "path" describes all the entries that
// must be passed through to get to the desired entry, starting with the root
// entry.
//
// For example, a container called "root" contains a child entry called
// "itemcontainer1" that is also a container.  The "itemcontainer1" entry
// contains an entry called "item2" that is not a container.  The "path" to
// the "item2" entry must pass through "root" and "itemcontainer1".  This "path"
// can be written in any number of ways with a common approach separating the
// names of each entry by '/' like this: "/root/itemcontainer1/item2".  This
// should look familiar as it is very much like a file path in an operating
// system with a hierarchical file structure.
#ifndef __COMPOSITE_IFILEENTRY_H__
#define __COMPOSITE_IFILEENTRY_H__

#include <string>
#include <memory>
#include <vector>
#include "helpers/DateTime.h"
using Helpers::DateTime;

namespace DesignPatternExamples_cpp
{
    /// <summary>
    /// Represents the type of entries allowed in the hierarchy for the
    /// Composite design pattern example.
    /// </summary>
    enum FileDirTypes
    {
        /// <summary>
        /// Represents a file entry.
        /// </summary>
        File,

        /// <summary>
        /// Represents a directory entry that can contain other IFIleDirEntry components.
        /// </summary>
        Directory
    };

    struct IFileDirEntry; // forward declaration

    /// <summary>
    /// Makes it easier to refer to a list of child nodes.
    /// </summary>
    typedef std::vector<std::shared_ptr<IFileDirEntry>> IFileDirEntryList;

    /// <summary>
    /// Represents a file or directory entry.
    /// </summary>
    struct IFileDirEntry
    {
        virtual ~IFileDirEntry() {}

        /// <summary>
        /// A value from the <seealso cref="FileDirTypes"/> enumeration
        /// indicating the type of this entry.
        /// </summary>
        virtual FileDirTypes FileDirType() = 0;

        /// <summary>
        /// The name of this entry.
        /// </summary>
        virtual std::string Name() = 0;

        /// <summary>
        /// The number of bytes representing the size of this entry.  For directories,
        /// represents the cumulative total of all child entries.
        /// </summary>
        virtual long Length() = 0;

        /// <summary>
        /// When this entry was last modified.
        /// </summary>
        virtual DateTime WhenModified() = 0;

        /// <summary>
        /// Return a (possibly empty) array of all immediate children of this entry.
        /// </summary>
        virtual IFileDirEntryList Children() = 0;
    };

} // end namespace

#endif // __COMPOSITE_IFILEENTRY_H__

