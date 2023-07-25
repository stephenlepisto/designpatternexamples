# Design Pattern Examples
by Stephen P. Lepisto

# Overview
This repository contains implementations of 18 of the classic object-oriented
Design Patterns as described in the book _Design Patterns: Elements of Reusable
Object-Oriented Software_ by Gamma, Helm, Johnson, and Vlissides.  There are
implementations in C, C++, C#, Python, and Rust.  These are not implementations
of the examples in the book but are my own creations to demonstrate my
experience with these patterns.

The C, C++, C#, and Python examples are documented with Doxygen and the results
are online at https://stephenlepisto.com/developer/designpatternexamples/.

The Rust example doesn't work with Doxygen but instead uses Rust's own
documentation, with the results also
https://stephenlepisto.com/developer/designpatternexamples/.  Refer to the
Doxygen documentation for the overall discussion of each pattern (I didn't want
to duplicate the discussions with the Rust's less capable documentation
functionality).


# How to Build

## Minimum Requirements
These are the versions of the various applications the DesignPatternExamples
were written and tested on.  Later versions of these applications should
continue to work.

### Windows
- CMake v3.26
- Doxygen v1.9
- GraphViz v7.1
- Visual Studio 2022 (I used Community edition)
- Python 3.10
- rust v1.69 in release 2021
- Git Bash for Windows v2.40

## Building the Code
1. Open a Git Bash prompt create a directory where to download the code.  For
   example:

        md c:\work
        cd c:\work

2. Use git to get the code from GitHub.com:

        git https://github.com/stephenlepisto/designpatternexamples.git

3. Go into the created directory:

        cd designpatternexamples

4. Create the build directory for cmake and go into it:

        md build
        cd build

5. Use cmake to build everything:

        cmake ..\
        cmake --build . --config release

## Running the Examples
After building everything, the following command lines displays Doxygen or Rust
source documentation or runs all examples (from Command Prompt, navigate to the
build directory first).

| Documentation | Command Line  |
| ------------- | ------------- |
| Doxygen       | html\index.html |
| Rust          | rust\doc\design_pattern_examples_rust\index.html |

| Language | Command line |
| -------- | ------------ |
| C        | c\release\DesignPatternExamples_c.exe |
| C++      | cplusplus\release\DesignPatternExamples_cpp.exe |
| C#       | csharp\release\DesignPatternExamples_csharp.exe |
| Python   | py -m python.DesignPatternExamples_python |
| Rust     | rust\release\design_pattern_examples_rust.exe |


To get help for each set of examples, use --help switch after the command line.

To run an individual design pattern example, add the name (or names) of the
example after the command line (all the names are shown with --help).
