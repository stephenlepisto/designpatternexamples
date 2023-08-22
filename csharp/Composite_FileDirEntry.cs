/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.FileDirEntry "FileDirEntry" base class,
/// and the @ref DesignPatternExamples_csharp.FileEntry "FileEntry" and classes
/// and the @ref DesignPatternExamples_csharp.DirEntry "DirEntry" classes
/// as used in the @ref composite_pattern "Composite pattern".

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents the type of entries allowed in the hierarchy for the
    /// Composite design pattern example.
    /// </summary>
    public enum FileDirTypes
    {
        /// <summary>
        /// Represents a file entry.
        /// </summary>
        File,

        /// <summary>
        /// Represents a directory entry that can contain other FileDirEntry components.
        /// </summary>
        Directory
    }


    /// <summary>
    /// Base class representing a File or Directory entry.
    /// 
    /// The program treats the File and Directory entries as this base class.
    /// </summary>
    public class FileDirEntry
    {
        /// <summary>
        /// The type of this entry as represented by a value from the FileDirTypes
        /// enumeration.
        /// </summary>
        public virtual FileDirTypes FileDirType
        {
            get;
            protected set;
        }

        /// <summary>
        /// The name of this entry.
        /// </summary>
        public virtual string Name
        {
            get;
            protected set;
        }

        /// <summary>
        /// The length in bytes of this entry.  Directory entries are the sum of
        /// the length of all children.
        /// </summary>
        public virtual long Length
        {
            get;
            protected set;
        }

        /// <summary>
        /// When this entry was last modified.
        /// </summary>
        public virtual DateTime WhenModified
        {
            get;
            protected set;
        }

        /// <summary>
        /// The children of this entry.  Is null if the entry can never have
        /// any children (that is, it isn't a container of other entries).
        /// </summary>
        public virtual FileDirEntry[]? Children
        {
            get
            {
                return null;
            }
        }

        /// <summary>
        /// Default constructor.
        /// </summary>
        public FileDirEntry()
        {
            FileDirType = FileDirTypes.File;
            Name = string.Empty;
            Length = 0;
            WhenModified = DateTime.MinValue;
        }

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
        List<FileDirEntry> _children;
        long _length;
        bool _lengthSet;

        /// <summary>
        /// Construct a DirEntry instance.
        /// </summary>
        /// <param name="name">Name of the directory</param>
        /// <param name="modDate">modification date time of the entry</param>
        /// <param name="children">Array of children.  Must not be null but can be empty.</param>
        /// <exception cref="ArgumentNullException">The list of children cannot be null but can be empty.</exception>
        public DirEntry(string name, DateTime modDate, FileDirEntry[] children)
        {
            if (children == null)
            {
                throw new ArgumentNullException("children", "The list of children cannot be null but can be empty.");
            }
            FileDirType = FileDirTypes.Directory;
            Name = name;
            WhenModified = modDate;
            _children = new List<FileDirEntry>(children);
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
                    foreach(FileDirEntry entry in Children)
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
        public override FileDirEntry[] Children
        {
            get
            {
                return _children.ToArray();
            }
        }
    }
}
