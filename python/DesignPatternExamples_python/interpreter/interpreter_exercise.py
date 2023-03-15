## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.interpreter.interpreter_exercise.Interpreter_Exercise "Interpreter_Exercise"()
#  function as used in the @ref interpreter_pattern.

from io import StringIO

from .interpreter_class import Interpreter_Class

## A list of predefined token lists.  Each token list represents a single
#  sentence constructed from the 40 most common words in the English language.
#  I don't use all 40 words, though; that would be silly.
_sentenceTokenLists = [
    [ 39, 18, 17, 27, 2, 7, 101 ],            # "What do you say to that?"
    [ 32, 17, 1, 0, 34, 2, 1, 37, 101 ],      # "Will you be the one to be there?"
    [ 36, 17, 8, 5, 32, 2, 18, 7, 101 ],      # "Would you have a will to do that?"
    [ 11, 12, 17, 9, 36, 12, 1, 6, 20, 100 ], # "For not you I would not be in this."
    [ 26, 27, 7, 21, 36, 17, 27, 10, 101 ],   # "We say that but would you say it?"
    [ 23, 28, 32, 26, 32, 18, 10, 100 ]       # "By her will we will do it."
]

## Helper method to convert a list of tokens to a string representation.
#
#  @param tokens
#         Array of ints to work with.
#  @returns
#     A string representation of the token list.
def _TokensToString(tokens : list[int]) -> str:
    output = StringIO()

    output.write("[");
    for index in range(0, len(tokens)):
        output.write("{0:3}".format(tokens[index]))
        if index + 1 < len(tokens):
            output.write(", ")
    output.write("]")
    return output.getvalue()


## Example of using the @ref interpreter_pattern.
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

    interpreter = Interpreter_Class()

    for sentenceIndex in range(0, len(_sentenceTokenLists)):
        tokenList = _sentenceTokenLists[sentenceIndex]

        tokensAsString = _TokensToString(tokenList)

        sentence = interpreter.Interpret(tokenList)

        # 50 is a magic number corresponding to the longest token list
        # expressed as a string.  Derived empirically.  It makes the
        # output easier to, er, interpret.
        print("  {0:<50} ==> \"{1}\"".format(tokensAsString, sentence))

    print("  Done.")
# ! [Using Interpreter in Python]
