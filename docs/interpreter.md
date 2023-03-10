# Interpreter Pattern {#interpreter_pattern}

@image html interpreter_diagram.png "Diagram of the Interpreter Chain pattern"

The interpreter pattern is used for situations where one thing needs to be
interpreted in order to do or produce something else.  What is being interpreted
could be, for example, the keywords of a programming language to produce
compiled code, the words in a sentence to determine meaning, or a series of
numbers to control a robot's motion.

Python is an example of an interpreted scripting language.  The commands and
expressions typed in are interpreted and converted to tokens (numbers).  These
tokens are then interpreted to perform a specific set of actions.  String all
those tokens together and a functional program is the result.

In the same way, C# goes through a similar path of interpretation to produce
abstract symbols (tokens) that are converted into an intermediate language that
is then interpreted by the .Net (or Mono) runtime.

Programming languages such as C or C++ are interpreted to produce abstract
symbols (tokens) that are converted directly into machine language (a discrete
series of bytes or numbers) -- which the CPU essentially interprets to produce
some kind of action.

Ar a much higher level of abstraction, a domain-specific language could be used
to make it simple to create business logic for an application.  This domain-
specific language typically consists of simple commands and parameters that,
when executed in sequence, accomplish some task specific to the application.
The process of executing the domain-specific language requires an interpreter.

In short, what is interpreted is a set of tokens that represent actions.
The tokens can be arranged in an abstract syntax tree to provide more
complex relationships between the tokens.  Where these tokens come from is
outside the interpreter's control.

What form the tokens take and what form the actions take after the tokens are
interpreted is up to the application and the interpreter.

Note: Another example of an interpreter (which includes a parser) is shown
in the @ref nullobject_pattern example.

# How to Use

Links to the Interpreter class description:
- @ref DesignPatternExamples_cpp::Interpreter_Class "Interpreter_Class" class (C++)
- @ref DesignPatternExamples_csharp.Interpreter_Class "Interpreter_Class" class (C#)

The example provided here takes an array of integers and converts each into
a text word or punctuation mark separated by a space from the previous
token, forming a complete sentence.  In essence, interpreting the list of
tokens reverses the effects of a parser.

__C++__

@snippet cplusplus/Interpreter_Exercise.cpp Using Interpreter in C++

__C#__

@snippet csharp/program.cs Using Interpreter in C#

__Python__

@snippet python/DesignPatternExamples_python/interpreter/interpreter_exercise.py Using Interpreter in Python

### See Also
- @ref mainpage "Main page"
