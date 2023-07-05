/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Interpreter_Class "Interpreter_Class"
/// class used in the @ref interpreter_pattern.

#pragma once
#ifndef __INTERPRETER_CLASS_H__
#define __INTERPRETER_CLASS_H__

#include <string>
#include <vector>

namespace DesignPatternExamples_cpp
{
    /// <summary>
    /// Alias to make it easier to work with a vector of vectors of int.
    /// </summary>
    using IntList = std::vector<int>;


    /// <summary>
    /// Representation of a simple interpreter.
    /// 
    /// This interpreter takes an array of integer tokens and converts each
    /// token into a word or punctuation mark.  The interpreter then arranges
    /// the words into a space-separated list in a single string.  In other
    /// words, the tokens are converted into a sentence, with the first word
    /// capitalized and no space between the last two "words" under the
    /// assumption the last word is actually a punctuation mark.
    /// 
    /// Interpreter Rules:
    /// 1. Each token must be in the range of 0 through 39 (maximum number of
    ///    words known by the interpreter) or must be 100 ('.') or 101 ('?').
    /// 2. The word corresponding to the first token is always capitalized.
    /// 3. A single space appears between each word.
    /// 4. No space appears between the last two tokens.
    /// </summary>
    class Interpreter_Class
    {
    public:
        const int PERIOD = 100;
        const int QUESTION = 101;

    private:
        /// <summary>
        /// The 40 most common words in English (in order but that doesn't really
        /// matter here).  A token is nothing more than an index into this list.
        /// </summary>
        static const char* _commonwords[];


        /// <summary>
        /// Helper method to convert the token into its corresponding word or
        /// punctuation mark.
        /// </summary>
        /// <param name="token">The token to interpret.</param>
        /// <returns>A std::string containing the corresponding word or punctuation.  If
        /// the token is not recognized, the std::string returns "<UNKNOWN TOKEN #>", where
        /// # is the token value.</returns>
        std::string _InterpretToken(int token);

    public:

        /// <summary>
        /// Given an array of integer tokens, convert the tokens into a single
        /// std::string of space-delimited words, following simple rules of
        /// formatting.
        /// </summary>
        /// <param name="tokens">The list of integers to interpret.</param>
        /// <returns>A std::string containing a sentence built from the tokens.</returns>
        std::string Interpret(IntList tokens);
    };

} // end namespace

#endif // __INTERPRETER_CLASS_H__

