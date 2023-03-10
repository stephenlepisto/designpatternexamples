# Facade Pattern {#facade_pattern}

@image html facade_diagram.png "Diagram of the Facade pattern"

The Facade design pattern is basically a simplified interface to a
complicated sub-system.  Using facades is one more step in creating loose
coupling between sub-systems while at the same time simplifying the
functionality exposed from a sub-system.

Facades are sometimes known as facets.

A facade is used in situations where the full power of a sub-system isn't
needed but the sub-system needs to be kept intact.  In effect, a facade
provides a "beginner's" interface to a complicated chunk of code whereas
the API of the complicated chunk of code is for "advanced" users.

A simplification of a complex system could mean providing a high level
function that uses a number of lower level functions in the complex
system.  Or the facade could provide only a few of the entry points into
the complex system so the interface is kept simple.

Another way of thinking about Facades is on a large system that exposes
many different interfaces, depending on what entity needs to access the
system.  Each entity sees only the interface exposed to it by the large
system.  A specific example of this is Visual Studio.

Visual Studio enables plugins through the Component Object Model (COM)
architecture of Windows.  A COM interface can be obtained from an
implementation class (COM Class or coclass).  A coclass can implement
multiple different COM interfaces.  From any interface, any other interface
on that coclass can be requested.  A Visual Studio plugin is a coclass that
implements multiple interfaces exposed to Visual Studio.  Those interfaces
on the plugin are facades to the plugin.  Visual Studio itself is exposed
to the plugin through different COM interfaces, which become the facades on
the Visual Studio system.

In other words, COM is a formalized mechanism to expose facades
(interfaces) on a particular system to other entities that themselves could
expose facades in return.

One thing to keep in mind is the Facade does not add any functionality,
it only simplifies what is available.  This means the Facade interface
generally does not retain any state of its own, leaving that to the
complicated sub-system.  The Facade might retain one or more tokens or
handles from the sub-system to facility access to the sub-system.

# How to Use

Links to the Facade interface description:
- (high level) @ref DesignPatternExamples_cpp::IDeviceNetworkHighLevel "Facade interface" (C++)
- (high level) @ref DesignPatternExamples_csharp.IDeviceNetworkHighLevel "Facade interface" (C#)
- (low level) @ref DesignPatternExamples_cpp::IDeviceNetworkLowLevel "Advanced user interface" (C++)
- (low level) @ref DesignPatternExamples_csharp.IDeviceNetworkLowLevel "Advanced user interface" (C#)

The example provided is a complicated sub-system with many different low-
level functions.  This functionality is exposed through a low level
interface.  A facade is provided through a second interface that exposes
a simplified set of functions for most common operations.

__C++__

@snippet cplusplus/Facade_Exercise.cpp Using Facade in C++

__C#__

@snippet csharp/program.cs Using Facade in C#


### See Also
- @ref mainpage "Main page"
