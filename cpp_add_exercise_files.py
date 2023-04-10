# Used to generate skeleton of .h/.cpp files for each exercise function.

import os
import sys


class Exercise:
    def __init__(self, name, function_name):
        self.name = name
        self.function_name = function_name


exercises = [
                Exercise("Adapter", "Adapter_Exercise"),
                Exercise("Bridge", "Bridge_Exercise"),
                Exercise("Composite", "Composite_Exercise"),
                Exercise("Decorator", "Decorator_Exercise"),
                Exercise("Facade", "Facade_Exercise"),
                Exercise("Flyweight", "Flyweight_Exercise"),
                Exercise("Proxy", "Proxy_Exercise"),
                Exercise("Visitor", "Visitor_Exercise"),
                Exercise("Command", "Command_Exercise"),
                Exercise("HandlerChain", "HandlerChain_Exercise"),
                Exercise("Interpreter", "Interpreter_Exercise"),
                Exercise("Iterator", "Iterator_Exercise"),
                Exercise("Mediator", "Mediator_Exercise"),
                Exercise("Memento", "Memento_Exercise"),
                Exercise("NullObject", "NullObject_Exercise"),
                Exercise("Observer", "Observer_Exercise"),
                Exercise("State", "State_Exercise"),
                Exercise("Strategy", "Strategy_Exercise"),
]

header_template = """
/// @file
/// @brief
/// Declaration of the {0}() function as used in the 
/// @ref {1}_pattern "{2} pattern".

#pragma once
#ifndef __{3}_EXERCISE_H__
#define __{3}_EXERCISE_H__

namespace DesignPatternExamples_cpp
{{
    void {0}();

}} // end namespace

#endif // __{3}_EXERCISE_H__
"""

cpp_template = """
/// @file
/// @brief
/// Implementation of the {0}() function as used in the 
/// @ref {1}_pattern "{2} pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "{3}"

namespace // Anonymous
{{
    using namespace DesignPatternExamples_cpp;
    
}} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{{

}} // end namespace
"""

def process_exercise(exercise, output_path):
   
    function_name = exercise.function_name
    name_lowercase = exercise.name.lower()
    name = exercise.name
    name_uppercase = exercise.name.upper()
    
    header_filename = "{0}.h".format(function_name)
    cpp_filename = "{0}.cpp".format(function_name)
    headerfile_contents = header_template.format(function_name, name_lowercase, name, name_uppercase)
    cppfile_contents = cpp_template.format(function_name, name_lowercase, name, header_filename)
    
    header_path = os.path.join(output_path, header_filename)
    cpp_path = os.path.join(output_path, cpp_filename)
    if not os.path.exists(header_path):
        with open(header_path, "wb") as f:
            f.write(headerfile_contents.encode("utf-8"))
    else:
        print("{0} already exists.".format(header_path))
        
    if not os.path.exists(cpp_path):
        with open(cpp_path, "wb") as f:
            f.write(cppfile_contents.encode("utf-8"))
    else:
        print("{0} already exists.".format(cpp_path))

def process_exercises(output_path):
    for exercise in exercises:
        process_exercise(exercise, output_path)
        
def main():
    output_path = "cplusplus"
    process_exercises(output_path)
    print("Done")

if __name__ == "__main__":
    sys.exit(main())
    