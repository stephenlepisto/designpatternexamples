## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirEntry "FileDirEntry"
#  base class, and the
#  @ref DesignPatternExamples_python.composite.composite_filedirentry.FileEntry "FileEntry"
#  and @ref DesignPatternExamples_python.composite.composite_filedirentry.DirEntry "DirEntry"
#  classes used in the @ref composite_pattern.

from datetime import datetime
from enum import Enum


## Represents the type of entries allowed in the hierarchy for the
#  Composite design pattern example.
class FileDirTypes(Enum):
    ## Represents a file entry.
    File = 0,

    ## Represents a directory entry that can contain other FileDirEntry components.
    Directory = 1


## Makes it easier to refer to a list of child nodes.
#
#  This is a list of
#  @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirTypes "FileDirTypes"
#  instances.
class FileDirEntryList(list):
    pass


##  Base class representing a File or Directory entry.
class FileDirEntry:
    ## Constructor
    #  @param type
    #         Value from the
    #         @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirTypes "FileDirTypes"
    #         enumeration specifying the type of entry.
    #  @param entryName
    #         Name of the entry.
    #  @param size
    #         Size of the entry.  Can be 0 for directories.
    #  @param modDate
    #         datetime object indicating when this entry was last modified.
    def __init__(self, type = FileDirTypes.File, entryName = "", size = 0, modDate = datetime.now()):
        self._fileDirType = type
        self._name = entryName
        self._length = size
        self._whenModified = modDate

    ## @var _fileDirType
    #       Value from the
    #       @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirTypes "FileDirTypes"
    #       enumeration indicating what type this entry is.
    #  @var _name
    #       Name of this entry
    #  @var _length
    #       Size of this entry.  For directories, this is the calculated size
    #       of all children (calculated when Length() is called for the first
    #       time)
    #  @var _whenModified
    #       A datetime object indicating when this entry was last modified.
    #       For the @ref composite_pattern example, this is the time the object
    #       was created.

    ## The type of this entry as represented by a value from the
    #  @ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirTypes "FileDirTypes"
    #  enumeration.
    def  FileDirType(self) -> FileDirTypes:
        return self._fileDirType

    ## The name of this entry.
    def Name(self) -> str:
        return self._name

    ## The length in bytes of this entry.  Directory entries are the sum of
    #  the length of all children.
    def Length(self) -> int:
       return self._length

    ## When this entry was last modified.
    def WhenModified(self) -> datetime:
       return self._whenModified

    ## The children of this entry.  Is None if the entry can never have
    #  any children (that is, it isn't a container of other entries).
    def Children(self) -> None:
       return None


#########################################################################
#########################################################################

## Represents a File entry.
#  
#  A File entry cannot have any children but does have an explicit size.
class FileEntry(FileDirEntry):
    ## Constructor
    #
    #  @param entryName
    #         Name of the entry.
    #  @param size
    #         Size of the entry.  Can be 0 for directories.
    #  @param modDate
    #         datetime object indicating when this entry was last modified.
    def __init__(self, entryName : str, size : int, modDate : datetime):
        super().__init__(type=FileDirTypes.File, entryName=entryName, size=size, modDate=modDate)


#########################################################################
#########################################################################


## Represents a Directory entry.
#  
#  A directory entry contains 0 or more children, which can be a mix of
#  file and directory entries.
#  
#  A Directory's size is the sum of all children sizes.
class DirEntry(FileDirEntry):
    ## Construct a DirEntry instance.
    #
    #  @param entryName
    #         Name of the directory
    #  @param modDate
    #         modification date time of the entry
    #  @param children
    #         Array of children.  Can be empty.
    def __init__(self, entryName: str, modDate: datetime, children : FileDirEntryList):
        super().__init__(type=FileDirTypes.Directory, entryName=entryName, modDate=modDate)
        self._children = children # type: FileDirEntryList
        self._lengthSet = False  # type: bool

    ## @var _children
    #       Children of this directory
    ## @var _lengthSet
    #       True if the length has already been computed for this directory;
    #       otherwise, False.


    ## Retrieve the size of all children of this directory.  The length
    #  is calculated on the first call and cached for subsequent calls.
    #  
    #  This is an override of the base class to provide different behavior.
    def Length(self):
        if not self._lengthSet:
            # Recurse over all children, accumulating their size.
            for child in self._children:
                self._length += child.Length()
            self._lengthSet = True
        return self._length


    ## Retrieve the children of this node.
    #  
    #  This is an override of the base class and uses a collection of
    #  children entries stored in the DirEntry class so the base
    #  class doesn't need to store it.
    def Children(self) -> FileDirEntryList:
        return self._children
