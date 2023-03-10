# Iterator Pattern {#iterator_pattern}

@image html iterator_diagram.png "Diagram of the Iterator pattern"

The Iterator pattern is used in situations where a collection of items
needs to be iterated over.  That is, where each item needs to be accessed
in some sequence, one at a time.

The C++ Standard Template Library (STL) provides many examples of such
iterators on the various STL container classes.  And in general, a C++-
based program should use those containers whenever possible because they
are well-tested and can have any number of pre-defined algorithms applied,
including the ability to easily iterate over the contents of the
containers.

Other programming languages such as C# have varying degrees of built-in
support for iterators over containers.  For example, in C#, all containers
can provide an iterator over the contents of the container.  Again, in
general you should use the built-in containers provided by the language
whenever possible to take advantage of well-tested code, including the
iterators.

A non-object-oriented kind of iterator uses an opaque token to represent
the index into the data.  A function retrieves this token pointing to the
first item.  A second function increments the index in the token to point
to the next item.  These functions can be implemented on the container
itself as methods or they can be functions that accept the container and
know how to get the number of items from the container and how to get the
items themselves from the container.

An iterator doesn't actually have to have a container to draw from or at
least not a container visible to the caller.  The iterator could be three
functions: One to start the iteration, the second to retrieve the next item
in the iteration, and the third function to release or close the iteration.
The functions know what they are iterating over and the starting function
takes parameters to adjust what is actually iterated over.  A good example
of this kind of iterator is the Win32 find file functions, FindFirstFile(),
FindNextFile(), FindClose().

The simplest kind of iterator is typically implemented on the container
itself as a pair of methods: One method returns the number of items to
iterate over and a second method returns the item at the specified index.
The caller then increments (or decrements) the index passed into the second
function.  This is a form of random-access iterator where the items can be
accessed in any order.

# How to Use

Links to the Iterator class and interface descriptions:
- @ref DesignPatternExamples_cpp::IteratorContainer_Class "IteratorContainer_Class" (C++)
- @ref DesignPatternExamples_csharp.IteratorContainer_Class "IteratorContainer_Class" (C#)
- @ref DesignPatternExamples_cpp::Iterator "IIterator" interface (C++)
- @ref DesignPatternExamples_csharp.Iterator "IIterator" interface (C#)
- @ref DesignPatternExamples_cpp::Iterator "Iterator" class (C++)
- @ref DesignPatternExamples_csharp.Iterator "Iterator" class (C#)

Having said all that, here is an example of how an object-oriented iterator
can be implemented.  In this case, the example uses the interface, `IIterator`,
to represent an iterator to the caller.  A custom container class,
`IteratorContainer_Class`, provides an instance of this interface to allow the
caller to iterate forward over the container.  This custom container can
expose multiple iterators, each independent of the others.  The use of
multiple iterators on the same container is normally used only when the
container is a read-only type; that is, the contents will not be changing.
Once the contents are changed (added or removed), all iterators are considered
invalid.

__C++__

@snippet cplusplus/Iterator_Exercise.cpp Using Iterator in C++

__C#__

@snippet csharp/program.cs Using Iterator in C#


### See Also
- @ref mainpage "Main page"
