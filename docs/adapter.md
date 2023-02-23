# Adapter Pattern{#adapter_pattern}

@image html adapter_diagram.png "Diagram of the adapter pattern"

The Adapter pattern is a wrapper class around an external component.
The wrapper class adapts the external component to match how the rest of
the program behaves so the program doesn't know it is dealing with an
external component.  The wrapper class is responsible for initializing
and disposing of the external component, as well as adapting procedure
calls, arguments, and error handling.

A function can also act as an adapter, where the function adapts the
calling conventions of the external component to the conventions of the
program.  One common use of adapter functions is to hide differences in
external libraries that arise from different implementations, such as
the C library as it appears on different operating systems.

## How to Use

Links to the DataReaderWriter class description:
- @ref DesignPatternExamples_cpp::DataReaderWriter "DataReaderWriter class" (C++)
- @ref DesignPatternExamples_csharp.DataReaderWriter "DataReaderWriter class" (C#)

In the Adapter pattern example, the DataReaderWriter class is the adapter
class.  It hides the details of getting data into and out of some external
entity.  In this example, some data is created, the DataReaderWriter class is
used to write the data out (to the external component), followed by using the
DataReaderWriter class to read the data back.

__C++__

@snippet cplusplus/program.cpp Using Adapter in C++

__C#__

@snippet csharp/program.cs Using Adapter in C#


### See Also
- @ref mainpage "Main page"
