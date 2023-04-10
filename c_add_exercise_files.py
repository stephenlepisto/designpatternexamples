# Used to generate skeleton of .h/.c files for each exercise function.

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

void {0}();

#endif // __{3}_EXERCISE_H__
"""

c_template = """
/// @file
/// @brief
/// Implementation of the {0}() function as used in the 
/// @ref {1}_pattern "{2} pattern".

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "{3}"

//=============================================================================
//=============================================================================


//=============================================================================
//=============================================================================

void {0}()
{{
    printf("\\n{0}\\n");

    printf("  Done.\\n");
}}

"""

def process_exercise(exercise, output_path):
   
    function_name = exercise.function_name
    name_lowercase = exercise.name.lower()
    name = exercise.name
    name_uppercase = exercise.name.upper()
    
    header_filename = "{0}.h".format(function_name)
    c_filename = "{0}.c".format(function_name)
    headerfile_contents = header_template.format(function_name, name_lowercase, name, name_uppercase)
    cppfile_contents = c_template.format(function_name, name_lowercase, name, header_filename)
    
    header_path = os.path.join(output_path, header_filename)
    cpp_path = os.path.join(output_path, c_filename)
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
    output_path = "c"
    process_exercises(output_path)
    print("Done")

if __name__ == "__main__":
    sys.exit(main())
    