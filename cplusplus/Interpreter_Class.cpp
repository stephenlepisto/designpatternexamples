/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Interpreter_Class "Interpreter_Class"
/// class used in the @ref interpreter_pattern.

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20
#include <sstream>

#include "helpers/_countof.h"
#include "helpers/titlecase.h"

#include "Interpreter_Class.h"

namespace DesignPatternExamples_cpp
{

    const char* Interpreter_Class::_commonwords[] =
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


    std::string Interpreter_Class::_InterpretToken(int token)
    {
        std::string tokenAsString = "";

        // Rule 1: token is between 0 and the number of common words.
        if (token >= 0 && token < _countof(_commonwords))
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
                // Rule 1: Invalid tokens returned in a std::string.
                tokenAsString = std::format("<UNKNOWN TOKEN {0}>", token);
            }
        }
        return tokenAsString;
    }


    std::string Interpreter_Class::Interpret(IntList tokens)
    {
        std::ostringstream output;

        size_t numTokens = tokens.size();

        for (size_t tokenIndex = 0; tokenIndex < numTokens; ++tokenIndex)
        {
            // Rule 1: Interpret token
            std::string tokenAsString = _InterpretToken(tokens[tokenIndex]);
            if (tokenIndex == 0)
            {
                // Rule 2: First word in sentence gets capitalized according to local rules.
                tokenAsString = Helpers::titlecase(tokenAsString);
            }
            output << tokenAsString;

            // Rule 4: No space between last two tokens (if the following expression is false)
            if (tokenIndex + 2 < numTokens)
            {
                // Rule 3: Separate all words by a single space.
                output << " ";
            }
        }

        return output.str();
    }

} // end namespace
