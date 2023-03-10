
/// @file
/// @brief
/// Implementation of the Interpreter_Exercise() function as used in the 
/// @ref interpreter_pattern "Interpreter pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <sstream>

#include "Interpreter_Exercise.h"
#include "Interpreter_Class.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// Helper method to convert a list of ints to a string representation.
    /// </summary>
    /// <param name="tokens">Array of ints to work with.</param>
    /// <returns>A string representation of the integer list.</returns>
    std::string _TokensToString(const IntList& tokens)
    {
        std::ostringstream output;

        output << "[";
        for (size_t index = 0; index < tokens.size(); ++index)
        {
            output << std::format("{0:3}", tokens[index]);
            if (index + 1 < tokens.size())
            {
                output << ", ";
            }
        }
        output << "]";
        return output.str();
    }


    /// <summary>
    /// A list of pre-defined token lists.  Each token list represents
    /// a single sentence constructed from the 40 most common words in
    /// the English language.  I don't use all 40 words, though; that
    /// would be silly.
    /// </summary>
    const std::vector<IntList> _sentenceTokenLists{
        { 39, 18, 17, 27, 2, 7, 101 }, // "What do you say to that?"
        { 32, 17, 1, 0, 34, 2, 1, 37, 101 }, // "Will you be the one to be there?"
        { 36, 17, 8, 5, 32, 2, 18, 7, 101 }, // "Would you have a will to do that?"
        { 11, 12, 17, 9, 36, 12, 1, 6, 20, 100 }, // "For not you I would not be in this."
        { 26, 27, 7, 21, 36, 17, 27, 10, 101 }, // "We say that but would you say it?"
        { 23, 28, 32, 26, 32, 18, 10, 100 } // "By her will we will do it."
    };

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref interpreter_pattern "Interpreter" design pattern.
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
    //! [Using Interpreter in C++]
    void Interpreter_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Interpreter Exercise" << std::endl;

        Interpreter_Class interpreter;

        for (size_t sentenceIndex = 0; sentenceIndex < _sentenceTokenLists.size(); ++sentenceIndex)
        {
            const IntList& tokenList = _sentenceTokenLists[sentenceIndex];

            std::string tokensAsString = _TokensToString(tokenList);

            std::string sentence = interpreter.Interpret(tokenList);

            // 50 is a magic number corresponding to the longest token list
            // expressed as a string.  Derived empirically.  It makes the
            // output easier to, er, interpret.
            std::cout
                << std::format("  {0:<50} ==> \"{1}\"", tokensAsString, sentence)
                << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    //! [Using Interpreter in C++]

} // end namespace
