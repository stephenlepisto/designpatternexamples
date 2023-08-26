# Design Pattern Examples
by Stephen P. Lepisto

### Copyright (c) 2023 Stephen P. Lepisto
### Licensed under the MIT License.  See LICENSE.md for details.


# Overview
This repository contains implementations of 18 of the classic object-oriented
Design Patterns as described in the book _Design Patterns: Elements of Reusable
Object-Oriented Software_ by Gamma, Helm, Johnson, and Vlissides.  There are
implementations in C, C++, C#, Python, and Rust.  These are not implementations
of the examples in the book but are my own creations to demonstrate my
experience with these patterns.

The C, C++, C#, and Python examples are documented with Doxygen and the results
are online at https://stephenlepisto.com/developer/designpatternexamples/.

Doxygen does not support Doxygen so the Rust example uses Rust's own
documentation support, with the results also available at
https://stephenlepisto.com/developer/designpatternexamples/.  Refer to the
Doxygen-based documentation for the overall discussion of each pattern (I didn't
want to duplicate the discussions with the Rust's less capable documentation
functionality).

# How to Build

## Minimum Requirements
These are the versions of the various applications the DesignPatternExamples
were written and tested on.  Later versions of these applications should
continue to work.

### Windows
- CMake v3.26
- Doxygen v1.9.6
- GraphViz v7.1
- Visual Studio 2022 (I used Community edition)
  - Work Loads
    - Python Development
    - .Net Desktop Development
    - Desktop Development with C++
- Python 3.11
- Rust v1.69 in release 2021
- Git Bash for Windows v2.40

### Linux
_(I used Ubuntu 22.04 mounted through Windows Subsystem for Linux (WSL) v2)_
- C/C++ build tools
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install build-essential
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- CMake v3.27
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo snap install cmake --classic
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Doxygen v1.9
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install doxygen gsfonts
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Graphviz v7.1
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  cd ~
  mkdir tools
  cd tools
  wget https://gitlab.com/api/v4/projects/4207231/packages/generic/graphviz-releases/7.1.0/graphviz-7.1.0.tar.gz
  tar xzf graphviz-7.1.0.tar.gz
  cd graphviz-7.1.0
  ./configure
  make
  make install
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  If doxygen generates errors about not supporting the PNG format (`Format: "png" not recognized.`),
  the following should fix that (later versions of graphviz might fix this "bug").
  Note: This has been tested only Ubuntu.  The "bug" is libgvplugin_gd.so.6 is not
  in /usr/local/lib/graphviz, which is where `dot -c` looks for plugins, so the
  following adds a symbolic link to the actual file:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo ln /usr/local/bin/dot /usr/bin/dot
  sudo ln /usr/lib/x86_64-linux-gnu/graphviz/libgvplugin_gd.so.6.0.0 /usr/local/lib/graphviz/libgvplugin_gd.so.6
  sudo dot -c
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Python 3.10
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install python310-full
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Rust v1.71.1 in release 2021
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  _Select option 1 (default) then follow the prompts._
- .Net SDK 7.0 (for C#)
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install dotnet-sdk-7.0
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


## Building the Code
1. Open a Git Bash prompt or Linux terminal and create a directory where to
   download the code.  For example:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cd ~
    mkdir work
    cd work
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2. Use git to get the code from GitHub.com:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    git https://github.com/stephenlepisto/designpatternexamples.git
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. Go into the created directory:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cd designpatternexamples
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
4. Create the build directory for cmake and go into it:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    mkdir build
    cd build
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
5. Use cmake to build everything:

    __Windows__
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cmake ..
    cmake --build . --config release
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    __Linux__
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cmake .. -D CMAKE_BUILD_TYPE=Release
    cmake --build .
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


# View the Code Documentation
After building everything, the following command lines displays Doxygen or Rust
source documentation when run from a Windows Command Prompt (navigate to the
build directory first, for example `cd %HOMEPATH%\designpatternexamples\build`).

Note: The documentation is not directly viewable on Linux unless a GUI and
browser are loaded and even then, the following command line invocations will
not work (load the browser and navigate to those files.  If you want to play
with a text-based browser such as lynx, be aware the diagrams will not be
visible).

| Documentation | Command Line/Location  |
| ------------- | ---------------------- |
| Doxygen       | html\index.html        |
| Rust          | rust\doc\design_pattern_examples_rust\index.html |

# Running the Examples
After building everything, the following command lines runs each example
(navigate to the build directory first).

| Language      | Windows Command line                              | Linux Command Line                      |
| ------------- | ------------------------------------------------- | --------------------------------------- |
| _go to build_ | `cd "%HOMEPATH%\designpatternexamples\build"`     | `cd ~/work/designpatternexamples/build` |
| C             | `c\release\DesignPatternExamples_c.exe`           | `c/DesignPatternExamples_c`             |
| C++           | `cplusplus\release\DesignPatternExamples_cpp.exe` | `cplusplus/DesignPatternExamples_cpp`   |
| C#            | `csharp\release\DesignPatternExamples_csharp.exe` | `csharp/DesignPatternExamples_csharp`   |
| Python        | `py -m python.DesignPatternExamples_python`       | `python3 -m python.DesignPatternExamples_python` |
| Rust          | `rust\release\design_pattern_examples_rust.exe`   | `rust/release/design_pattern_examples_rust` |

To get help for each set of examples, use `--help` switch after the command line.
For example: `c\release\DesignPatternExamples_c.exe --help`

To run a single design pattern example in a language, add the name (or names) of
the example after the command line (view all the names of examples with the
`--help` option.  For example: `c\release\DesignPatternExamples_c.exe Flyweight`).

# Known Issues (all on Ubuntu Linux v22.04)
- Python
  - Flyweight can be skipped only with the Enter key.
  - Doxygen might produce two warnings:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    memento/memento.py:110: warning: unable to resolve reference to 'DesignPatternExamples_python.memento.memento.Memento_TextObject' for \ref command
    mediator/mediator_user_classes.py:37: warning: unable to resolve reference to 'DesignPatternExamples_python.mediator.mediator_user_classes.User' for \ref command
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    This may be due to doxygen being v1.9.1 on Ubuntu.  Doxygen v1.9.6 on
    Windows does not produce this warning (the fix might have occurred in v1.9.2).
- Rust
  - Flyweight can be skipped only with the Enter key.
