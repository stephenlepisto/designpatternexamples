#pragma once
#ifndef __COMPOSITE_FILEDIRENTRY_H__
#define __COMPOSITE_FILEDIRENTRY_H__

#include <string>
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
        /// Represents a directory entry that can contain other FileDirEntry components.
        /// </summary>
        Directory
    };

    class FileDirEntry; // forward declaration

    /// <summary>
    /// Makes it easier to refer to a list of child nodes.
    /// </summary>
    typedef std::vector<std::shared_ptr<FileDirEntry>> FileDirEntryList;

    /// <summary>
    /// Base class representing a File or Directory entry.
    /// </summary>
    class FileDirEntry
    {
    protected:
        FileDirTypes fileDirType;
        std::string name;
        long length;
        DateTime whenModified;

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        FileDirEntry()
            : fileDirType(FileDirTypes::File)
            , length(0)
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="type">Value from the FileDirTypes enumeration specifying
        /// the type of entry.</param>
        /// <param name="entryName">Name of the entry.</param>
        /// <param name="size">Size of the entry.  Can be 0 for directories.</param>
        /// <param name="modDate">DateTime object indicating when this entry was
        /// last modified.</param>
        FileDirEntry(FileDirTypes type, std::string entryName, long size, DateTime modDate)
            : fileDirType(type)
            , name(entryName)
            , length(size)
            , whenModified(modDate)
        {
        }

        /// <summary>
        /// The type of this entry as represented by a value from the FileDirTypes enumeration.
        /// </summary>
        virtual FileDirTypes FileDirType() { return fileDirType; }

        /// <summary>
        /// The name of this entry.
        /// </summary>
        virtual std::string Name() { return name; }

        /// <summary>
        /// The length in bytes of this entry.  Directory entries are the sum of
        /// the length of all children.
        /// </summary>
        virtual long Length() { return length; }

        /// <summary>
        /// When this entry was last modified.
        /// </summary>
        virtual DateTime WhenModified() { return whenModified; }

        /// <summary>
        /// The children of this entry.  Is empty if the entry can never have
        /// any children (that is, it isn't a container of other entries).
        /// </summary>
        virtual FileDirEntryList Children() { return FileDirEntryList(); }
    };


    //########################################################################
    //########################################################################

    /// <summary>
    /// Represents a File entry.
    /// 
    /// A File entry cannot have any children but does have an explicit size.
    /// </summary>
    class FileEntry : public FileDirEntry
    {
    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="entryName">Name of the entry.</param>
        /// <param name="size">Size of the entry.  Can be 0 for directories.</param>
        /// <param name="modDate">DateTime object indicating when this entry was
        /// last modified.</param>
        FileEntry(std::string entryName, long size, DateTime modDate)
            : FileDirEntry(FileDirTypes::File, entryName, size, modDate)
        {
        }
    };



    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a Directory entry.
    /// 
    /// A directory entry contains 0 or more children, which can be a mix of
    /// file and directory entries.
    /// 
    /// A Directory's size is the sum of all children sizes.
    /// </summary>
    class DirEntry : public FileDirEntry
    {
    public:
        FileDirEntryList _children;
        bool _lengthSet;

        /// <summary>
        /// Construct a DirEntry instance.
        /// </summary>
        /// <param name="entryName">Name of the directory</param>
        /// <param name="modDate">modification date time of the entry</param>
        /// <param name="children">Array of children.  Can be empty.</param>
        DirEntry(std::string entryName, DateTime modDate, FileDirEntryList children)
            : FileDirEntry(FileDirTypes::Directory, entryName, 0, modDate)
            , _children(children)
            , _lengthSet(false)
        {
        }


        /// <summary>
        /// Retrieve the size of all children of this directory.  The length
        /// is calculated on the first call and cached for subsequent calls.
        /// 
        /// This is an override of the base class to provide different behavior.
        /// </summary>
        long Length()
        {
            if (!_lengthSet)
            {
                // Recurse over all children, accumulating their size.
                for (FileDirEntryList::iterator entryIter = std::begin(_children);
                    entryIter != std::end(_children);
                    entryIter++)
                {
                    length += (*entryIter)->Length();
                }
                _lengthSet = true;
            }
            return length;
        }


        /// <summary>
        /// Retrieve the children of this node.
        /// 
        /// This is an override of the base class and uses a collection of
        /// children entries stored in the DirEntry class so the base
        /// class doesn't need to store it.
        /// </summary>
        FileDirEntryList Children()
        {
            return _children;
        }
    };

} // end namespace

#endif //__COMPOSITE_FILEDIRENTRY_H__

