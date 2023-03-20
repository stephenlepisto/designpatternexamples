## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.composite.composite_exercise.Composite_Exercise "Composite_Exercise"()
# function as used in the @ref composite_pattern.

from io import StringIO

from .composite_filedirentry import FileDirEntry, FileDirTypes, FileDirEntryList
from .composite_fileaccess import Composite_FileAccess

## Format the specified entry for display.
#  
#  This is a recursive call.
#
#  @param entry
#         The FileDirEntry object to format
#  @param depth
#         The current recursion depth.  This is used as leading space.
#  @returns
#    A string containing the formatted text for the given entry.
def Composite_Exercise_FormatEntry(entry : FileDirEntry, depth : int) -> str:
    NAME_PADDING_SIZE = 20
    output = StringIO()
    spaces = ' ' * (depth * 2)
    output.write("{0}{1}".format(spaces, entry.Name))
    padding = NAME_PADDING_SIZE - len(entry.Name) - (depth * 2)
    if entry.FileDirType == FileDirTypes.Directory:
        output.write("/")
        padding -= 1
    output.write(' ' * padding)
    output.write("{0:4}".format(entry.Length))
    output.write("  {0}".format(entry.WhenModified.strftime("%m/%d/%Y %I:%M:%S %p")))
    output.write("\n")

    children = entry.Children
    if children:
        for index in range(0, len(children)):
            output.write(Composite_Exercise_FormatEntry(children[index], depth + 1))

    return output.getvalue()



## Recursively display the contents of the hierarchical list of objects
#  starting with the given object.
#
#  @param entry
#         The file entry to display
def Composite_Exercise_ShowEntry(entry : FileDirEntry) -> None:
    output = Composite_Exercise_FormatEntry(entry, 2)
    print(output)


## Example of using the @ref composite_pattern.
# 
#  The Composite pattern is used when a collection of objects is to
#  be formed in a hierarchical form where each object needs to be
#  treated like any other object but some objects can contain other
#  objects.
# 
#  This example uses a file structure of file and directories to
#  represent each object type.

# ! [Using Composite in Python]
def Composite_Exercise():
    print()
    print("Composite Exercise")

    try:
        filepath = "root"
        rootEntry = Composite_FileAccess.GetEntry(filepath)
        print("  Showing object '{}'".format(filepath))
        Composite_Exercise_ShowEntry(rootEntry)

        filepath = "root/subdir1/FileD.txt"
        rootEntry = Composite_FileAccess.GetEntry(filepath)
        print("  Showing object '{}'".format(filepath))
        Composite_Exercise_ShowEntry(rootEntry)
    except FileNotFoundError as ex:
        print("Error! {} ".format(ex))

    print("  Done.")
# ! [Using Composite in Python]
