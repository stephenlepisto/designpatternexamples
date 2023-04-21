/// @file
/// @brief
/// Implementation of the Interpreter_Interpret() function
/// used in the @ref interpreter_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "helpers/titlecase.h"

#include "Interpreter_Interpreter.h"

/// <summary>
/// The 40 most common words in English (in order but that doesn't really
/// matter here).  A token is nothing more than an index into this list.
/// </summary>
static const char* _commonwords[] =
{
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
};

/// <summary>
/// Helper function to convert the token into its corresponding word or
/// punctuation mark.
/// </summary>
/// <param name="token">The token to interpret.</param>
/// <returns>Returns a pointer to the corresponding word or punctuation.  If
/// the token is not recognized, the pointer returns "<UNKNOWN TOKEN #>",
/// where # is the token value.</returns>
static const char* _InterpretToken(int token)
{
    const char* tokenAsString = "";

    // Rule 1: token is between 0 and the number of common words.
    int numCommonWords = sizeof(_commonwords) / sizeof(_commonwords[0]);
    if (token >= 0 && token < numCommonWords)
    {
        tokenAsString = _commonwords[token];
    }
    else
    {
        // Rule 1: token can also be a PERIOD
        if (token == PERIOD)
        {
            tokenAsString = ".";
        }
        // Rule 1: or the token can also be a QUESTION
        else if (token == QUESTION)
        {
            tokenAsString = "?";
        }
        else
        {
            static char buffer[32] = { 0 };
            int num_chars = sprintf_s(buffer, sizeof(buffer), "<UNKNOWN TOKEN %d>", token);
            if (num_chars != -1)
            {
                // Rule 1: Invalid tokens returned as unknown.
                tokenAsString = buffer;
            }
        }
    }
    return tokenAsString;
}


///////////////////////////////////////////////////////////////////////////////
// Interpreter_Interpret()
///////////////////////////////////////////////////////////////////////////////
void Interpreter_Interpret(const int* tokenList, DynamicString* output)
{
    if (tokenList != NULL && output != NULL)
    {
        for (size_t tokenIndex = 0; tokenList[tokenIndex] != EOL; ++tokenIndex)
        {
            const char* tokenAsString = _InterpretToken(tokenList[tokenIndex]);
            char* titleString = NULL;
            if (tokenIndex == 0)
            {
                // Rule 2: First word in sentence gets capitalized according to local rules.
                titleString = titlecase(tokenAsString);  // Note: titleString must be freed
                if (titleString == NULL)
                {
                    printf("  Error!  titlecase() in Interpreter_Interpret() encountered an out of memory condition!\n");
                    break;
                }
                tokenAsString = titleString;
            }
            DynamicString_Append(output, tokenAsString);
            free(titleString); // Free this now that we are done with it

            // Rule 4: No space between last two tokens (if the following expression is false)
            if (tokenList[tokenIndex + 2] != EOL)
            {
                // Rule 3: Separate all words by a single space.
                DynamicString_Append(output, " ");
            }
        }
    }
}