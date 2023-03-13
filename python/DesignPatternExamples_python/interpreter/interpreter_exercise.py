## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.interpreter.interpreter_exercise.Interpreter_Exercise "Interpreter_Exercise"()
# function as used in the @ref interpreter_pattern.


##  Example of using the @ref interpreter_pattern.
#  
#  The interpreter is instantiated then fed a series of arrays 
#  containing integer tokens.  Each token represents a single word or
#  punctuation mark.  The interpreter converts that array of tokens
#  to an actual sentence by interpreting the meaning of the tokens.
#  
#  This is a very simple interpreter that handles the first token in
#  a special way and supports punctuation.  It is an example of a
#  linear interpreter where tokens can appear in any order (it's up
#  to the creator of the token list to make sure the outcome makes
#  any sense).
#  
#  The output shows the token list followed by the sentence produced
#  from the tokens.

# ! [Using Interpreter in Python]
def Interpreter_Exercise():
    print()
    print("Interpreter Exercise")

    print("  Done.")
# ! [Using Interpreter in Python]
