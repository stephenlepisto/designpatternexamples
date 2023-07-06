# Private Class Data Pattern {#private_pattern}

The Private Class Data pattern is used to prevent manipulation of its data
properties after construction.  This is used in languages that do not have
the ability to mark class attributes as "final" or "const".  The intention
is to minimize exposure of the class's properties as seen in header files
that exposes the class declaration.

In other words, don't expose the inner design and workings of the class.

This design pattern also provides a way to (possibly) simplify serializing
the data of a class from one form to another.  All the data representing
the state of the class instance is one location and this might make it
easier convert the data into some form that allows the data to be saved to
disk or sent over some kind of network connection or even a data pipe
between processes.  How effective this is depends on the amount of data in
the class; lots of data makes a private data class somewhat more efficient.

There are actually two different ways this can be done:

1. An inner "data" class that contains the data used by the class's
   implementation.  The header file would expose only an opaque pointer
   to an instance of this "data" class.
2. Expose the class only through an interface, where only the methods
   the outside world can use are exposed in a header file.

The inner "data" class is often colloquially known as the "pimpl" pattern
since the opaque pointer is typically stored in the class as a pointer
to an implementation, commonly abbreviated as "pimpl" (pointer to
implementation).  The "data" class can either contain only the data
utilized by the class or it can be the actual implementation, with the
methods on the outer class forwarding to the "data" class.  In general,
the Private Class Data pattern expects the "data" class to hold only data,
bypassing any overhead of nested calls.

The interface approach is generally cleaner and forces the design to create
a contract through the interface and then adhere to that contract, making
for a more stable architecture.  However, this approach requires the
presence of some sort of class factory function through which an instance
of the class implementing the interface is made available.  This also
generally requires a second class factory function that disposes of the
class instance.

Strict adherence to the Private Class Data pattern doesn't really work in
C#, where there are no pointers to be seen and class declarations are not
stored in header files.  In fact, in C#, the class declaration is the same
as the class implementation.  So even if the private data was held in
another class that is private to this file, it is still visible to anyone
viewing the main class declaration (unless the private data was defined in
a partial class in another file but that just complicates things even more
with no benefit).  C# works around this problem by using interfaces to hide
the whole class, exposing only the declaration of the interface to outside
users (the interface goes in its own assembly, for example, so the class
definition and implementation are hidden from casual view).

The idea of hiding data in a private class is old-fashioned and there are
better ways of handling the hiding the implementation details of a class,
even in C++, and that is through interfaces.

## How to Use

See the @ref bridge_pattern for an example of using an interface to hide the
implementation details.

__C++__

- The `_logger` field of the DesignPatternExamples_cpp::Logger class
- The `_realClassInstance` field of the Proxy_Class_Private::Proxy_Class class

__C#__

- The `_logger` field of the DesignPatternExamples_csharp.Logger class
- The `_realClassInstance` field of the DesignPatternExamples_csharp.Proxy_Classes_Container.Proxy_Class class

__Python__

- The `_logger` field of the DesignPatternExamples_python.bridge.bridge_logger.Logger class
- The `_realClassInstance` field of the DesignPatternExamples_python.proxy.proxy_class.Proxy_Class class


### See Also
- @ref mainpage "Main page"
