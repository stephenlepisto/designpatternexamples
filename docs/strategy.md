# Strategy Pattern {#strategy_pattern}

@image html strategy_diagram.png "Diagram of the Strategy pattern"

The Strategy pattern is used when a choice of multiple different but
related algorithms can be made at run time.  The implementation of each
related algorithm exposes the same interface so as to hide the details of
implementation from the calling program and the algorithm.

In a more general form, a "Strategy" is nothing more than a class
implementation hidden behind an abstract interface.  This allows the
implementation to be changed without affecting the caller.  The Strategy
pattern takes this one step further to allow entire algorithms to be
hidden behind the interface and then swap in different instances of the
interface at run time to change the algorithm being used.

Typically a Strategy pattern implementation specifies the algorithm at the
time the program starts up or is configured.  It can also be configured at
the time a class representing the functionality is instantiated.  The
algorithm to use is generally selected by the user based on some input.
Once set, the algorithm selected does not change until reconfigured or the
user selects another algorithm.

The value of a Strategy pattern is the ability to create a basic
infrastructure for the program and then allow the user to alter the
behavior of that infrastructure using options.  Also, additional strategies
for each option can be added without changing the basic infrastructure or
affecting any other strategy.  The drawback is now the functionality of the
program is spread out across many different classes and it can be quite
difficult following the flow of execution, especially if a strategy can
itself have its own set of strategies.

The only tricky part of making use of the Strategy pattern is figuring out
what the interface should be for all possible algorithms for a given
situation.  The simplest approach to solving this is to determine what must
the algorithm provide to the caller to allow the caller to get work done
then defining an interface that provides that functionality.  Then create
the implementation of algorithms that satisfies the required functionality.

For example, a program such as `dir` or `ls` can list files and folders in a
variety of formats.  This program has one feature: display information
about files and folders.  This feature can be broken down into two
components:

1. Fetch information about files/folders
2. Show the fetched information about the files/folders

To fetch the information about files and folders, there are several
options:
  - with no arguments, look at all files and folders in the current folder
  - Specify matching files/folders (can include wildcards)
  - Specify with a wildcard the files/folders to look at
  - Recurse through all folders for all files/folders
  - Recurse through all folders for all matching files/folders

Each of these can be represented by a strategy for reading information
about files/folders.  That is, an interface can be defined that returns a
list of files/folders given a pattern.  Then specific implementations of
the interface can deal with matching files and recursing through folders.

The same approach can be taken with displaying the information:
  - Show all information about files/folders in sorted order
  - Show only the names of files/folders in sorted order
  - Show only the names of files in sorted order
  - Show only the names of folders in sorted order

Each of these display options could be a strategy.  Define an interface
that takes a list of information about files/folders and display all or
some of the information in the given order. 

The "in sorted order" suggests a third strategy is needed: How to sort the
list of files/folders.  For example, sort by name, length, type, or date, with
an option to reverse the order.

The `ls` program works (in general) like this (based on input parameters,
including default parameters):
  1. Select and use a strategy to read in information about files/folders.
  2. Select and use a strategy to sort the list of information about
     files/folders
  3. Select and use a strategy to display the sorted list of information
     about files/folders.

With this approach, the pseudo-code for an object-oriented implementation of
the `ls` program might look like this:
  1. Create instance of file fetch interface based on input parameters
  2. Create instance of sorting interface based on input parameters
  3. Create instance of display interface based on input parameters
  4. Get list of files using file fetch interface
  5. Sort list of files using sorting interface
  6. Show list of files using display interface
  7. Done.

All the really hard stuff happens inside the implementation of each
strategy.  And additional implementations of each strategy can be added
later on without affecting the above pseudo-code.

# How to Use

<table>
<caption>Links to the Strategy classes and interfaces</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::ISortEntries "ISortEntries" interface
  <td>@ref DesignPatternExamples_csharp.ISortEntries "ISortEntries" interface
  <td>@ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory" interface
  <td>&lt;Not Applicable&gt;
<tr>
  <td>@ref DesignPatternExamples_cpp::Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory" class
  <td>@ref DesignPatternExamples_csharp.ISortEntries "ISortEntries" interface
  <td>@ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ClassFactory "Strategy_SortEntries_ClassFactory" class
  <td>SortStrategy_Initialize()
<tr>
  <td>@ref DesignPatternExamples_cpp::Strategy_SortEntries_ByName "Strategy_SortEntries_ByName" class
  <td>@ref DesignPatternExamples_csharp.Strategy_SortEntries_ByName "Strategy_SortEntries_ByName" class
  <td>@ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ByName "Strategy_SortEntries_ByName" class
  <td>Sort_Entries()<br>
      _Compare_Name()
<tr>
  <td>@ref DesignPatternExamples_cpp::Strategy_SortEntries_ByAge "Strategy_SortEntries_ByAge" class
  <td>@ref DesignPatternExamples_csharp.Strategy_SortEntries_ByAge "Strategy_SortEntries_ByAge" class
  <td>@ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ByAge "Strategy_SortEntries_ByAge" class
  <td>Sort_Entries()<br>
      _Compare_Age()
<tr>
  <td>@ref DesignPatternExamples_cpp::Strategy_SortEntries_ByHeight "Strategy_SortEntries_ByHeight" class
  <td>@ref DesignPatternExamples_csharp.Strategy_SortEntries_ByHeight "Strategy_SortEntries_ByHeight" class
  <td>@ref DesignPatternExamples_python.strategy.strategy_sortentries_class.Strategy_SortEntries_ByHeight "Strategy_SortEntries_ByHeight" class
  <td>Sort_Entries()<br>
      _Compare_Height()
<tr>
  <td>@ref DesignPatternExamples_cpp::Strategy_ShowEntries_Class "Strategy_ShowEntries_Class"
  <td>@ref DesignPatternExamples_csharp.Strategy_ShowEntries_Class "Strategy_ShowEntries_Class" class
  <td>@ref DesignPatternExamples_python.strategy.strategy_showentries_class.Strategy_ShowEntries_Class "Strategy_ShowEntries_Class" class
  <td>Display_Entries()<br>
</table>

As interesting as the above file lister example would be, it would be just
a bit too long as an example (like a 1000 lines long).  So in a
considerably simpler example with only one strategy, a list of people with
Name, Age, and Height are sorted in some order based on a selected strategy.
The list of individuals is then shown in the sorted order.  The sort has a
modification where the order can be reversed from ascending to descending.

Note: It is strongly advised not to use the word "Strategy" when naming the
interfaces.  That name is too generic.  Name the interfaces based on what
the interfaces are used for and that includes the methods exposed through
the interface.  The only reason I'm using "Strategy" in this example is
to help group the public classes into the patterns being demonstrated.

__C++__

@snippet cplusplus/Strategy_Exercise.cpp Using Strategy in C++

__C#__

@snippet csharp/Strategy_Exercise.cs Using Strategy in C#

__Python__

@snippet python/DesignPatternExamples_python/strategy/strategy_exercise.py Using Strategy in Python

__C__

@snippet c/Strategy_Exercise.c Using Strategy in C

### See Also
- @ref mainpage "Main page"
