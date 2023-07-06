# Abstract Factory Pattern{#abstract_pattern}

A class factory represented by an interface that exposes multiple related
class factories.  Each factory creates concrete classes but exposes those
classes only through interfaces.  The most common example of an abstract
factory is an implementation of a graphical user interface or GUI, where
each component of the GUI is represented by an abstract interface and is
constructed by its own class factory.  The whole GUI system could then be
instantiated across multiple operating systems just by providing different
concrete classes.  The GUI system as a whole behaves the same despite the
underlying differences in the underlying operating system (and therefore
the concrete classes implementing the interfaces).

## How to Use

I did not write any examples of a Abstract Factory design pattern.

### See Also
- @ref mainpage "Main page"
