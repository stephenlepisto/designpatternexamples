# Used to generate skeleton of python packages for each exercise function.

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

# {0} = function name, lowercase
# {1} = function name, '_' replaced by ' '
# {2} = pattern name, lowercase
rust_exercise_template = """
/// @file
/// @brief
/// Implementation of the {0}() function as used in the 
/// @ref {2}_pattern.

pub fn {0}() {{
    println!("");
    println!("{1}");

    println!("  Done.");
}}
"""

def process_exercise(exercise, output_path):
   
    function_name = exercise.function_name.replace('_', ' ')
    function_name_lowercase = exercise.function_name.lower()
    name_lowercase = exercise.name.lower()
    name = exercise.name
    
    package_name = name_lowercase
    rust_exercise_filename = "{0}.rs".format(package_name)
    rustfile_contents = rust_exercise_template.format(function_name_lowercase, function_name, name_lowercase)

    # Create the module directory for subsequent files (not added here)
    package_path = os.path.join(output_path, package_name)
    os.makedirs(package_path, exist_ok=True)

    # Create the entry module to the exercise (in the main source directory)
    rust_path = os.path.join(output_path, rust_exercise_filename)
        
    if not os.path.exists(rust_path):
        with open(rust_path, "wb") as f:
            f.write(rustfile_contents.encode("utf-8"))
    else:
        print("{0} already exists.".format(rust_path))

def process_exercises(output_path):
    for exercise in exercises:
        process_exercise(exercise, output_path)
        
def main():
    output_path = os.path.join("rust", "design_pattern_examples_rust", "src")
    process_exercises(output_path)
    print("Done")

if __name__ == "__main__":
    sys.exit(main())
    