## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.interpreter.interpreter_class.Interpreter_Class "Interpreter_Class"
#  class as used in the @ref interpreter_pattern.

from io import StringIO


##  Representation of a simple interpreter.
#  
#   This interpreter takes an array of integer tokens and converts each
#   token into a word or punctuation mark.  The interpreter then arranges
#   the words into a space-separated list in a single string.  In other
#   words, the tokens are converted into a sentence, with the first word
#   capitalized and no space between the last two "words" under the
#   assumption the last word is actually a punctuation mark.
#  
#   Interpreter Rules:
#   1. Each token must be in the range of 0 through 39 (maximum number of
#      words known by the interpreter) or must be 100 ('.') or 101 ('?').
#   2. The word corresponding to the first token is always capitalized.
#   3. A single space appears between each word.
#   4. No space appears between the last two tokens.
class Interpreter_Class:
    ## Token for an end of sentence period
    PERIOD = 100
    ## Token for an end of sentence question mark
    QUESTION = 101

    ## The 40 most common words in English (in order but that doesn't really
    #  matter here).  A token is nothing more than an index into this list.
    _commonwords = [
        "the",
        "be",
        "to",
        "of",
        "and",
        "a",
        "in",
        "that",
        "have",
        "I",
        "it",
        "for",
        "not",
        "on",
        "with",
        "he",
        "as",
        "you",
        "do",
        "at",
        "this",
        "but",
        "his",
        "by",
        "from",
        "they",
        "we",
        "say",
        "her",
        "she",
        "or",
        "an",
        "will",
        "my",
        "one",
        "all",
        "would",
        "there",
        "their",
        "what",
    ]


    ## Helper method to convert the token into its corresponding word or
    #  punctuation mark.
    #
    #  @param token
    #         The token to interpret.</param>
    #  @returns
    #     A string containing the corresponding word or punctuation.  If the
    #     token is not recognized, the string returns "<UNKNOWN TOKEN #>",
    #     where # is the token value.
    def _InterpretToken(self, token : int) -> str:
        tokenAsString = ""

        # Rule 1: token is between 0 and the number of common words.
        if token >= 0 and token < len(Interpreter_Class._commonwords):
            tokenAsString = Interpreter_Class._commonwords[token]
        else:
            # Rule 1: token can also be a PERIOD
            if token == Interpreter_Class.PERIOD:
                tokenAsString = "."
            # Rule 1: or the token can also be a QUESTION
            elif token == Interpreter_Class.QUESTION:
                tokenAsString = "?"
            else:
                # Rule 1: Invalid tokens returned in a std::string.
                tokenAsString = "<UNKNOWN TOKEN {0}>".format(token)

        return tokenAsString;


    ## Given an array of integer tokens, convert the tokens into a single
    #  string of space-delimited words, following simple rules of formatting.
    #
    #  @param tokens
    #         The list of integers to interpret.
    #  @returns
    #     A containing a sentence built from the tokens.
    def Interpret(self, tokens : list[int]) -> str:
        output = StringIO()

        numTokens = len(tokens)

        for tokenIndex in range(0, numTokens):
            # Rule 1: Interpret token
            tokenAsString = self._InterpretToken(tokens[tokenIndex])
            if tokenIndex == 0:
                # Rule 2: First word in sentence gets capitalized according to local rules.
                tokenAsString = tokenAsString.title()
            output.write(tokenAsString)

            # Rule 4: No space between last two tokens (if the following expression is false)
            if tokenIndex + 2 < numTokens:
                # Rule 3: Separate all words by a single space.
                output.write(" ")

        return output.getvalue()
