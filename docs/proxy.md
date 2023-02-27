# Proxy Pattern {#proxy_pattern}

@image html proxy_diagram.png "Diagram of the proxy pattern"

The Proxy design pattern creates a class as a stand-in for another class
that might be too large to instantiate all the time or might be implemented
somewhere else.  The proxy class knows how to instantiate and talk to the
"real" class and typically does so when the first call on the proxy class
is made.  This allows the proxy class to be instantiated locally but the
cost of creating the "real" class is deferred until the proxy class is
actually used (called on).  There is always a one-to-one relationship
between the proxy class and the "real" class.

The key to the proxy class is it has the same interface (methods) as the
"real" class.  All calls made to the proxy class are forwarded to the
"real" class.  As far as the local program is concerned, the proxy class
is the real class because the two classes look and act the same.

Proxies are most often seen at either end of a communications channel of
some kind.  For example, in C#, the remoting channel functionality that
allows one process to talk to another uses proxy classes on the client end
of the remoting channel to represent the real classes on the server end.
When a proxy class is instantiated, information about the remoting channel
is stashed in the proxy class.  When the first call is made on the proxy
class, the real class on the server side is instantiated and then the call
is forwarded to the real class.  The proxy class takes care of
communicating across the remoting channel to the real class, where the
actual work is done.  All of this instantiation is taken care of by C#
itself so the client application only sees what it thinks is the real
class.

A less well-known use case is when a proxy is used to represent a class that is
"expensive" to create and therefore should be deferred until it is actually
used.  The proxy class is created as usual but as long as it is not
actually called on, the "expensive" class is not created.  It means the
program doesn't have to make any special effort to figure out when to call
the "expensive" class.

The proxy class and the "real" class interfaces are the same to help with
maintenance.  When a new method is added to the "real" class interface, the
proxy class also needs to be updated with the new method.  If the two
classes are in the same process, using an actual interface makes this a lot
easier to maintain.

# How to Use

Links to the Facade interface description:
- @ref DesignPatternExamples_cpp::IWorkByProxy "IWorkByProxy interface" (C++)
- @ref Proxy_Class_Private::Proxy_Class "Proxy_Class class" (C++)
- @ref Proxy_Class_Private::Real_Class "Real_Class class" (C++)
- @ref DesignPatternExamples_csharp.IWorkByProxy "IWorkByProxy interface" (C#)
- @ref DesignPatternExamples_csharp.Proxy_Classes_Container.Proxy_Class "Proxy_Class class" (C#)
- @ref DesignPatternExamples_csharp.Proxy_Classes_Container.Real_Class "Real_Class class" (C#)

__C++__

@snippet cplusplus/program.cpp Using Proxy in C++

__C#__

@snippet csharp/program.cs Using Proxy in C#


### See Also
- @ref mainpage "Main page"
