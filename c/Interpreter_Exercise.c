
/// @file
/// @brief
/// Implementation of the Interpreter_Exercise() function as used in the
/// @ref interpreter_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Interpreter_Interpreter.h"
#include "Interpreter_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Represents the sentence: "What do you say to that?"
/// </summary>
static int sentenceTokens0[] = { 39, 18, 17, 27,  2,  7, QUESTION, EOL };

/// <summary>
/// Represents the sentence: "Will you be the one to be there?"
/// </summary>
static int sentenceTokens1[] = { 32, 17,  1,  0, 34,  2,   1,  37, QUESTION, EOL };

/// <summary>
/// Represents the sentence: "Would you have a will to do that?"
/// </summary>
static int sentenceTokens2[] = { 36, 17,  8,  5, 32,  2,  18,   7, QUESTION, EOL };

/// <summary>
/// Represents the sentence: "For not you I would not be in this."
/// </summary>
static int sentenceTokens3[] = { 11, 12, 17,  9, 36, 12,   1,   6,  20, PERIOD, EOL };

/// <summary>
/// Represents the sentence: "We say that but would you say it?"
/// </summary>
static int sentenceTokens4[] = { 26, 27,  7, 21, 36, 17,  27,  10, QUESTION, EOL };

/// <summary>
/// Represents the sentence: "By her will we will do it."
/// </summary>
static int sentenceTokens5[] = { 23, 28, 32, 26, 32, 18,  10, PERIOD, EOL };

/// <summary>
/// A list of pre-defined token lists.  Each token list represents
/// a single sentence constructed from the 40 most common words in
/// the English language.  I don't use all 40 words, though; that
/// would be silly.
/// </summary>
static int* _sentenceTokenLists[] = {
    sentenceTokens0,
    sentenceTokens1,
    sentenceTokens2,
    sentenceTokens3,
    sentenceTokens4,
    sentenceTokens5,
    NULL
};


/// <summary>
/// Helper function to convert a list of ints to a string representation.
/// </summary>
/// <param name="tokens">Array of ints to work with.  Assumed to be terminated
/// with a -1 (EOL).</param>
/// <returns>A string representation of the integer list.  This is a pointer to
/// a static buffer and is valid only until the next call to this function.</returns>
static const char* _TokensToString(int* tokens)
{
    static char buffer[256] = { 0 };

    errno_t err = 0;
    memset(buffer, 0, sizeof(buffer));

    buffer[0] = '[';
    for (size_t index = 0; tokens[index] != EOL; ++index)
    {
        char numBuffer[6] = { 0 };
        int num_chars = sprintf_s(numBuffer, sizeof(numBuffer), "%3d", tokens[index]);
        if (num_chars == -1)
        {
            printf("  Error!  sprintf_s() failed in _TokensToString()!\n");
            break;
        }
        err = strcat_s(buffer, sizeof(buffer), numBuffer);
        if (err)
        {
            printf("  Error!  strcat_s() failed to add number in _TokensToString()!\n");
            break;
        }
        if (tokens[index + 1] != EOL)
        {
            err = strcat_s(buffer, sizeof(buffer), ", ");
            if (err)
            {
                printf("  Error!  strcat_s() failed in _TokensToString()!\n");
                break;
            }
        }
    }
    err = strcat_s(buffer, sizeof(buffer), "]");
    if (err)
    {
        printf("  Error! strcat_s() failed at the end of _TokensToString()!\n");
    }

    return buffer;
}


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref interpreter_pattern.
///
/// The interpreter is instantiated then fed a series of arrays
/// containing integer tokens.  Each token represents a single word or
/// punctuation mark.  The interpreter converts that array of tokens
/// to an actual sentence by interpreting the meaning of the tokens.
///
/// This is a very simple interpreter that handles the first token in
/// a special way and supports punctuation.  It is an example of a
/// linear interpreter where tokens can appear in any order (it's up
/// to the creator of the token list to make sure the outcome makes
/// any sense).
///
/// The output shows the token list followed by the sentence produced
/// from the tokens.
/// </summary>
// ! [Using Interpreter in C]
void Interpreter_Exercise(void)
{
    printf("\nInterpreter Exercise\n");

    for (size_t sentenceIndex = 0; _sentenceTokenLists[sentenceIndex] != NULL; ++sentenceIndex)
    {
        int* tokenList = _sentenceTokenLists[sentenceIndex];

        const char* tokensAsString = _TokensToString(tokenList);

        DynamicString sentence = { 0 };
        bool success = Interpreter_Interpret(tokenList, &sentence);

        if (success)
        {
            // 50 is a magic number corresponding to the longest token list
            // expressed as a string.  Derived empirically.  It makes the
            // output easier to, er, interpret.
            printf("  %-50s ==> \"%s\"\n", tokensAsString, sentence.string);
        }
        DynamicString_Clear(&sentence);
        if (!success)
        {
            break;
        }
    }

    printf("  Done.\n");
    // ! [Using Interpreter in C]
}
