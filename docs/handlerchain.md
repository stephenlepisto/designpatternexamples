# HandlerChain Pattern {#handlerchain_pattern}

@image html handlerchain_diagram.png "Diagram of the Handler Chain pattern"

The Handler Chain or Chain of Responsibility is a very old pattern.
A "chain" of handlers are built up.  An object is passed to the head of the
chain for handling.  That first handler decides whether it can handle the
object or not.  if so, it handles it and returns.  Otherwise, the handler
passes the object to the next handler in the chain.  This continues until
no more handlers remain or a handler processes the object.  The advantage
of a chain like this is handlers can be inserted into or removed from the
chain at runtime.

Windows uses this approach for handling messages passed to windows, where
each window handler either handles the message and/or passes the message
on to the next window handler in the chain until the default handler is
eventually called.  By inserting a handler into the chain, it is possible
to intercept the message and thus making it possible to add new
functionality to an existing window.

A variation on this is where an additional parameter determines whether a
handler that handled the object should pass the object to the next handler
instead of returning.

Another variation is a list of handlers to be called at some point.  For
example, the `atexit()` function in the C library takes a functon that is
added to a list that is then called in reverse order.  Technically, the
handlers aren't actually chained together except through the containing
list but the effect is the same; handlers in a dynamic list are called
until done.

The key to a Handler Chain is the chain of handlers is dynamic and the
handlers are invoked in order until all handlers have been invoked.  A
common variation is to allow a handler to stop the processing so no
additional handlers are called.

Handlers are set up through any number of ways, depending on what the
handlers do.  For example, with Windows message handlers, the chain is
updated when a new window is created or destroyed.

The Handler Chain, wherein an object is passed to a number of handlers
until processed, is also a form of the Observer pattern, where an object
is passed to a number of handlers.  Unlike the Observer pattern, though,
a handler in a Handler Chain can abort the sequence of calls to additional
handlers.

In an "ideal" object-oriented implementation, a Handler Chain is composed
of handler objects that are linked to the previous handler object and next
handler object in the chain.  The head of the chain has an empty previous
link while the last handler object in the chain has an empty next link.
Each handler object has a `Process()` method that either processes the incoming
arguments or calls the `Process()` method on the next handler object in the
chain, if any.

In addition, each handler object knows how to insert itself and remove
itself from the chain.  This implies each handler object has an `Add()` and
`Remove()` method, where `Add()` adds to the end of the chain (or insert based
on some qualifier) and `Remove()` removes from the chain.  The `Add()` method
requires the head of the chain.  The `Remove()` method doesn't need the head
of the chain as the links to the previous and next handlers are available in
the handler itself.

The advantage of this approach is the program only needs to deal with the
head handler object in the chain, either calling `Process()` on the head object
or calling `Add()` (or `Remove()` on the handler object) with a handler object.

A simpler approach is to designate a different class to handle the chain.
An instance of this class has the necessary `Process()`, `Add()`, and `Remove()`
methods on it but internally the handler objects are stored in a traditional
(and thoroughly-tested) container.  The handler of the chain can also take steps
to protect the list from multi-threaded incursions.  The handler is just a
single object that is passed around and it always exists even if there are no
handlers.

# How to Use

Links to the Handler Chain classes description:
- @ref DesignPatternExamples_cpp::HandlerChain "HandlerChain class" that controls the handlers (C++)
- @ref DesignPatternExamples_csharp.HandlerChain "HandlerChain class" that controls the handlers (C#)
- @ref DesignPatternExamples_cpp::MessageWindow "MessageWindow class" that participates in the handler chain (C++)
- @ref DesignPatternExamples_csharp::MessageWindow "MessageWindow class" that participates in the handler chain (C#)
- @ref DesignPatternExamples_cpp::IMessageHandler "IMessageHandler interface" (C++)
- @ref DesignPatternExamples_csharp::IMessageHandler "IMessageHandler interface" (C#)

The example presented here is a collection of "windows" represented by the
MessageWindow class.  Each window has a common message handler as
implemented through the IMessageHandler interface.  The windows are stored
in the HandlerChain collection and can interact with that collection.

ButtonDown messages are pushed in by the user of the HandlerChain class,
selecting and deselecting windows (based on a position associated with the
ButtonDown message).

A ButtonUp message is pushed in by the user of the HandlerChain class.  In a
window that is selected, the message causes an action to be taken, although
in this example, only one action is supported and that is the Close action.
However, the Close action is taken only if the message position is in the
"Close" region in the upper right corner of the window.

A "Close" action causes the window to send a Close message to the
collection.  This Close message is processed only by the currently selected
window and causes the window to remove itself from the collection so it no
longer receives messages.

__C++__

@snippet cplusplus/HandlerChain_Exercise.cpp Using HandlerChain in C++

__C#__

@snippet csharp/program.cs Using HandlerChain in C#

__Python__

@snippet python/DesignPatternExamples_python/handlerchain/handlerchain_exercise.py Using HandlerChain in Python

### See Also
- @ref mainpage "Main page"
