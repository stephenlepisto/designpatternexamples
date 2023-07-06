# Design Pattern Examples {#mainpage}

Created by Stephen P. Lepisto

## Overview

A treatise on the patterns defined in the book, *Design Patterns: Elements of
Object-Oriented Software*, by Gamma, Helm, Johnson, and Vlissides.

These patterns appeared over and over in the many years that object-oriented
programming grew and matured.  In 1995, Erich Gamma, Richard Helm, Ralph
Johnson, and John Vlissides formalized 23 patterns into a book, the first of
its kind.

To be sure, these patterns exited before the Design Patterns book was written,
which is why the Gang of Four wrote the book.  It was an attempt to formalize
the most well-known patterns, to provide terminology, methodology, and a place
to start discussions on the discipline of creating software, while focusing on
the latest movement of object-oriented programming.  However, most of the
design patterns in the book are not limited to object-oriented design or even
programming languages that prominently feature object-oriented features.

This documentation is built from my efforts to implement most of the design
patterns in four different programming languages: C, C++, C#, and Python.  I
also converted the patterns to Rust, but since Doxygen does not know how to
parse Rust (as of July 6, 2023), I have captured the Rust source code in its
own documentation site.


### The Design Pattern Examples Implemented Here
- @ref adapter_pattern
- @ref bridge_pattern
- @ref command_pattern
- @ref composite_pattern
- @ref decorator_pattern
- @ref facade_pattern
- @ref flyweight_pattern
- @ref handlerchain_pattern
- @ref interpreter_pattern
- @ref iterator_pattern
- @ref mediator_pattern
- @ref memento_pattern
- @ref nullobject_pattern
- @ref observer_pattern
- @ref proxy_pattern
- @ref state_pattern
- @ref strategy_pattern
- @ref visitor_pattern
 
### The Design Patterns with Indirect Examples
These design patterns do not have dedicated examples but instead point to one
or more of the above examples that use the following patterns.

- @ref factory_pattern
- @ref private_pattern
- @ref singleton_pattern

### The Design Patterns with No Examples
I did not create examples of the following design patterns as they are intended
for highly complex, object-oriented designs.  I tend to keep away from such
complex designs as they represent, in my opinion, the worst excesses of
object-oriented programming that lead to the problems of being very hard to
learn, very hard to debug, and therefore, very hard to maintain.

- @ref abstract_pattern
- @ref builder_pattern
- @ref prototype_pattern
- @ref template_pattern
 