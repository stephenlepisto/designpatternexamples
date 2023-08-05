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
- Doxygen v1.9.6
- GraphViz v7.1
- Visual Studio 2022 (I used Community edition)
- Python 3.10
- rust v1.69 in release 2021
- Git Bash for Windows v2.40

### Linux
(I used Ubuntu 22.04 mounted through Windows Subsystem for Linux (WSL) v2)
- C/C++ build tools
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install build-essential
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- CMake v3.27
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo snap install cmake --classic
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Doxygen v1.9
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install doxygen gsfonts
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Graphviz v7.1
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  cd ~
  mkdir tools
  cd tools
  wget https://gitlab.com/api/v4/projects/4207231/packages/generic/graphviz-releases/7.1.0/graphviz-7.1.0.tar.gz
  tar xzf graphviz-7.1.0.tar.gz
  cd graphviz-7.1.0
  ./configure
  make
  make install
  sudo ln /usr/local/bin/dot /usr/bin/dot
  sudo ln /usr/lib/x86_64-linux-gnu/graphviz/libgvplugin_gd.so.6.0.0 /usr/local/lib/graphviz/libgvplugin_gd.so.6
  sudo dot -c
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Python 3.10
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  sudo apt install python310-full
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- rust v1.71.1 in release 2021
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
  curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  _Select option 1 (default) then follow the prompts._


## Building the Code
1. Open a Git Bash prompt or Linux terminal and create a directory where to
   download the code.  For example:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cd ~
    mkdir work
    cd work
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2. Use git to get the code from GitHub.com:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    git https://github.com/stephenlepisto/designpatternexamples.git
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3. Go into the created directory:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cd designpatternexamples
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
4. Create the build directory for cmake and go into it:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    mkdir build
    cd build
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
5. Use cmake to build everything:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
    cmake ..
    cmake --build . --config release
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# View the Code Documentation
After building everything, the following command lines displays Doxygen or Rust
source documentation when run from a Windows Command Prompt (navigate to the
build directory first, for example `cd %HOMEPATH%\designpatternexamples\build`).

| Documentation | Command Line  |
| ------------- | ------------- |
| Doxygen       | html\index.html |
| Rust          | rust\doc\design_pattern_examples_rust\index.html |

# Running the Examples
After building everything, the following command lines runs all examples
(navigate to the build directory first).

| Language | Windows Command line                              | Linux Command Line                      |
| -------- | ------------------------------------------------- | --------------------------------------- |
|          | `cd "%HOMEPATH%\desingpatternexamples\build"`     | `cd ~/work/designpatternexamples/build` |
| C        | `c\release\DesignPatternExamples_c.exe`           | `c/DesignPatternExamples_c`             |
| C++      | `cplusplus\release\DesignPatternExamples_cpp.exe` | `cplusplus/DesignPatternExamples_cpp`   |
| C#       | `csharp\release\DesignPatternExamples_csharp.exe` | N/A                                     |
| Python   | `py -m python.DesignPatternExamples_python`       | `python3 -m python.DesignPatternExamples_python` |
| Rust     | `rust\release\design_pattern_examples_rust.exe`   | `LD_LIBRARY_PATH=$(pwd)/Adapter_BackEnd/ rust/Release/design_pattern_examples_rust` |

To get help for each set of examples, use --help switch after the command line.

To run an individual design pattern example, add the name (or names) of the
example after the command line (all the names are shown with --help).

# Known Issues (all on Ubuntu Linux v22.04)
- C
  - The full path to the libAdapter_BackEnd.so is hardcoded into the
    DesignPatternExamples_c executable.  It can be run after being built but
    it cannot be installed.
- C++
  - The full path to the libAdapter_BackEnd.so is hardcoded into the
    DesignPatternExamples_cpp executable.  It can be run after being built but
    it cannot be installed.
- Python
  - Flyweight can be skipped only with the Enter key.
  - Doxygen might produce two warnings:
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    memento/memento.py:110: warning: unable to resolve reference to 'DesignPatternExamples_python.memento.memento.Memento_TextObject' for \ref command
    mediator/mediator_user_classes.py:37: warning: unable to resolve reference to 'DesignPatternExamples_python.mediator.mediator_user_classes.User' for \ref command
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    This may be due to doxygen being v1.9.1 on Ubuntu.
- Rust
  - Requires setting the LD_LIBRARY_PATH to the Adapter_BackEnd build directory
    in order to run the rust executable.
  - Flyweight can be skipped only with the Enter key.
