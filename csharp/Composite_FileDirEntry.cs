// Composite design pattern example.  See Composite_IFileDirEntry.cs for details.
//
// This module contains the following:
//  - FileDirEntry, the base class that implements the IFileDirEntry interface.
//  - FileEntry, the class that represents files.  Derives from FileDirEntry.
//  - DirEntry, the class that represents directories.  Derives from FileDirEntry.

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Base class representing a File or Directory entry.
    /// 
    /// Provides default implementations for the IFileDirEntry interface.
    /// </summary>
    class FileDirEntry : IFileDirEntry
    {
        #region IFileDirEntry Members

        /// <summary>
        /// The type of this entry as represented by a value from the FileDirTypes enumeration.
        /// </summary>
        public FileDirTypes FileDirType
        {
            get;
            protected set;
        }

        /// <summary>
        /// The name of this entry.
        /// </summary>
        public string Name
        {
            get;
            protected set;
        }

        /// <summary>
        /// The length in bytes of this entry.  Directory entries are the sum of
        /// the length of all children.
        /// </summary>
        virtual public long Length
        {
            get;
            protected set;
        }

        /// <summary>
        /// When this entry was last modified.
        /// </summary>
        public DateTime WhenModified
        {
            get;
            protected set;
        }

        /// <summary>
        /// The children of this entry.  Is null if the entry can never have
        /// any children (that is, it isn't a container of other entries).
        /// </summary>
        virtual public IFileDirEntry[] Children
        {
            get
            {
                return null;
            }
        }

        #endregion
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a File entry.
    /// 
    /// A File entry cannot have any children but does have an explicit size.
    /// </summary>
    class FileEntry : FileDirEntry
    {
        public FileEntry(string name, long size, DateTime modDate)
        {
            FileDirType = FileDirTypes.File;
            Name = name;
            Length = size;
            WhenModified = modDate;
        }
    }


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
    class DirEntry : FileDirEntry
    {
        List<IFileDirEntry> _children;
        long _length;
        bool _lengthSet;

        /// <summary>
        /// Construct a DirEntry instance.
        /// </summary>
        /// <param name="name">Name of the directory</param>
        /// <param name="modDate">modification date time of the entry</param>
        /// <param name="children">Array of children.  Must not be null but can be empty.</param>
        /// <exception cref="ArgumentNullException">The list of children cannot be null but can be empty.</exception>
        public DirEntry(string name, DateTime modDate, IFileDirEntry[] children)
        {
            if (children == null)
            {
                throw new ArgumentNullException("children", "The list of children cannot be null but can be empty.");
            }
            FileDirType = FileDirTypes.Directory;
            Name = name;
            WhenModified = modDate;
            _children = new List<IFileDirEntry>(children);
        }


        /// <summary>
        /// Retrieve the size of all children of this directory.  The length
        /// is calculated on the first call and cached for subsequent calls.
        /// 
        /// This is an override of the base class to provide different behavior.
        /// </summary>
        public override long Length
        {
            get
            {
                if (!_lengthSet)
                {
                    // Recurse over all children, accumulating their size.
                    foreach(IFileDirEntry entry in Children)
                    {
                        _length += entry.Length;
                    }
                    _lengthSet = true;
                }
                return _length;
            }
        }


        /// <summary>
        /// Retrieve the children of this node.
        /// 
        /// This is an override of the base class and uses a collection of
        /// children entries stored in the DirEntry class so the base
        /// class doesn't need to store it.
        /// </summary>
        public override IFileDirEntry[] Children
        {
            get
            {
                return _children.ToArray();
            }
        }
    }
}
