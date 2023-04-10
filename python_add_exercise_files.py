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

# {0} = function name
# {1} = pattern name, lowercase
# {2} = pattern name
init_file_template = """
## @file
#  @brief
#  Python implementation of the @ref {1}_pattern "{2}" pattern example.

from .{1}_exercise import {0}
"""

# {0} = function name
# {1} = pattern name, lowercase
# {2} = pattern name
python_exercise_template = """
## @file
#  @brief
#  Implementation of the {0}() function as used in the 
#  @ref {1}_pattern "{2} pattern".

def {0}():
    print()
    print("{0}")

    print("  Done.")
"""

def process_exercise(exercise, output_path):
   
    function_name = exercise.function_name
    name_lowercase = exercise.name.lower()
    name = exercise.name
    name_uppercase = exercise.name.upper()
    
    package_name = name_lowercase
    init_filename = "__init__.py"
    python_filename = "{0}.py".format(function_name.lower())
    initfile_contents = init_file_template.format(function_name, name_lowercase, name)
    pythonfile_contents = python_exercise_template.format(function_name, name_lowercase, name)

    package_path = os.path.join(output_path, package_name)
    os.makedirs(package_path, exist_ok=True)
    init_path = os.path.join(package_path, init_filename)
    python_path = os.path.join(package_path, python_filename)
    if not os.path.exists(init_path):
        with open(init_path, "wb") as f:
            f.write(initfile_contents.encode("utf-8"))
    else:
        print("{0} already exists.".format(init_path))
        
    if not os.path.exists(python_path):
        with open(python_path, "wb") as f:
            f.write(pythonfile_contents.encode("utf-8"))
    else:
        print("{0} already exists.".format(python_path))

def process_exercises(output_path):
    for exercise in exercises:
        process_exercise(exercise, output_path)
        
def main():
    output_path = os.path.join("python", "DesignPatternExamples_python")
    process_exercises(output_path)
    print("Done")

if __name__ == "__main__":
    sys.exit(main())
    