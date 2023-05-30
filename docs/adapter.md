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

<table>
<caption>Links to the DataReaderWriter class (or functions)</caption>
<tr>
  <th>C++
  <th>C#
  <th>Python
  <th>C
<tr>
  <td>@ref DesignPatternExamples_cpp::DataReaderWriter "DataReaderWriter" class
  <td>@ref DesignPatternExamples_csharp.DataReaderWriter "DataReaderWriter" class
  <td>@ref DesignPatternExamples_python.adapter.adapter_frontendclass.DataReaderWriter "DataReaderWriter" class
  <td>Adapter_OpenMemory()<br>
  Adapter_CloseMemory()<br>
  Adapter_GetMemorySize()<br>
  Adapter_ReadMemory()<br>
  Adapter_WriteMemory()<br>
  Adapter_BufferToString()<br>
  Adapter_GetLastErrorMessage()
</table>

In the Adapter pattern example, the DataReaderWriter class is the Adapter.  It
hides the details of getting data into and out of some external entity.  In
this example, some data is created, the DataReaderWriter class is used to write
the data out (to the external component), followed by using the DataReaderWriter
class to read the data back.

For all programming languages, the "external entity" is the
@ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.  This DLL is written in C and
exposes its interface as C-style functions.  The functions are used to access
one of several memory blocks, and the access is in discrete 32-bit values.
Error codes are returned from each function to indicate success or failure.

In addition, each language needs to adapt to the external DLL, thus demonstrating
that language's capabilities of connecting to an external dynamic library.
Naturally, the C and C++ examples can call directly into the DLL, while the
other languages need to go through a translation layer provided by those
languages (C# uses the Platform/Invoke or P/Invoke layer, Python uses the ctypes
package, and rust uses Foreign Function Interface or FFI).

__C++__

@snippet cplusplus/Adapter_Exercise.cpp Using Adapter in C++

__C#__

@snippet csharp/Adapter_Exercise.cs Using Adapter in C#

__Python__

@snippet python/DesignPatternExamples_python/adapter/adapter_exercise.py Using Adapter in Python

__C__

@snippet c/Adapter_Exercise.c Using Adapter in C

__Rust__

(_Apologies.  Doxygen does not understand Rust syntax and therefore cannot colorize the code._)

@snippet rust/design_pattern_examples_rust/src/adapter.rs Using Adapter in Rust


### See Also
- @ref mainpage "Main page"
