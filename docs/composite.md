# Composite Pattern {#composite_pattern}

@image html composite_diagram.png "Diagram of the composite pattern"

A composite design is used for a hierarchical list of items where some items
are containers for additional items.  The root of the list is always a container.
The hierarchical list is a composite of all the node types in the list.  The
program deals with all the nodes as though they were the same, as represented
by the base class.

A common example of this is a file/directory structure.  A directory contains
entries that can be a file or another directory.  The root of the structure
is a directory.

## How to Use

<table>
<caption>Links to the Composite classes</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::FileDirEntry "FileDirEntry" base class
  <td>@ref DesignPatternExamples_csharp.FileDirEntry "FileDirEntry" base class
  <td>@ref DesignPatternExamples_python.composite.composite_filedirentry.FileDirEntry "FileDirEntry" base class
  <td>FileDirEntry structure
<tr>
  <td>@ref DesignPatternExamples_cpp::FileEntry "FileEntry" derived class
  <td>@ref DesignPatternExamples_csharp.FileEntry "FileEntry" derived class
  <td>@ref DesignPatternExamples_python.composite.composite_filedirentry.FileEntry "FileEntry" derived class
  <td>FileEntry structure
<tr>
  <td>@ref DesignPatternExamples_cpp::DirEntry "DirEntry" derived class
  <td>@ref DesignPatternExamples_csharp.DirEntry "DirEntry" derived class
  <td>@ref DesignPatternExamples_python.composite.composite_filedirentry.DirEntry "DirEntry" derived class
  <td>DirEntry structure
</table>

This example uses a file/directory approach, although the files and directories
are hardcoded examples.  Each entry, be it a file or a directory, is represented
by the FileDirEntry base class.  Each entry has a name, a length, and a date
when it was last modified.  For directories, the length is the sum of all child
files and directories contained within.

The type of the entry is determined by the FileDirType property/getter.  If the
entry is a directory, then it might have child entries in the Children
property/getter.

Note: In a flat list, getting to any entry is straightforward: Just provide
the index to the entry.  For hierarchical lists, however, a "path" must be
provided to get to any entry.  This "path" describes all the entries that
must be passed through to get to the desired entry, starting with the root
entry.

For example, a container called "root" contains a child entry called
"itemcontainer1" that is also a container.  The "itemcontainer1" entry
contains an entry called "item2" that is not a container.  The "path" to
the "item2" entry must pass through "root" and "itemcontainer1".  This "path"
can be written in any number of ways, with a common approach separating the
names of each entry by '/' like this: "/root/itemcontainer1/item2".  This
should look familiar as it is very much like a file path in an operating
system with a hierarchical file structure.

__C++__

@snippet cplusplus/Composite_Exercise.cpp Using Composite in C++

__C#__

@snippet csharp/Composite_Exercise.cs Using Composite in C#

__Python__

@snippet python/DesignPatternExamples_python/composite/composite_exercise.py Using Composite in Python

__C__

@snippet c/Composite_Exercise.c Using Composite in C


### See Also
- @ref mainpage "Main page"
