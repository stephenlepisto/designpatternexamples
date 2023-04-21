/// @file
/// @brief
/// Declaration of the Interpreter_Interpret() function
/// used in the @ref interpreter_pattern.

#pragma once
#ifndef __INTERPRETER_INTERPRETER_H__
#define __INTERPRETER_INTERPRETER_H__

#include "helpers/dynamicstring.h"

/// <summary>
/// Enum to define constants for tokens.
/// </summary>
enum
{
    PERIOD = 100, ///< Period
    QUESTION = 101, ///< Question mark
    EOL = -1   ///< Marker for end of a token list.
};

/// <summary>
/// This function is a simple interpreter.
/// 
/// The interpreter takes an array of integer tokens and converts each
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
/// <param name="tokenList">List of integer tokens to be interpreted.  The list
/// is assumed to be terminated by -1 (EOL).</param>
/// <param name="output">A DynamicString object returning the sentence created
/// through interpreting the tokens.  Call DynamicString_Clear() when done with
/// the string.</param>
void Interpreter_Interpret(const int* tokenList, DynamicString* output);

#endif // __INTERPRETER_INTERPRETER_H__

