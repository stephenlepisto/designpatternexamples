/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Interpreter_Class "Interpreter_Class"
/// class used in the @ref interpreter_pattern "Interpreter pattern".

using System;
using System.Globalization;
using System.Text;
using System.Threading;

namespace DesignPatternExamples_csharp
{

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
        const int PERIOD = 100;
        const int QUESTION = 101;

        /// <summary>
        /// The 40 most common words in English (in order but that doesn't really
        /// matter here).  A token is nothing more than an index into this list.
        /// </summary>
        static string[] _commonwords = new string[]
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
        /// Helper method to convert the token into its corresponding word or
        /// punctuation mark.
        /// </summary>
        /// <param name="token">The token to interpret.</param>
        /// <returns>A string containing the corresponding word or punctuation.  If
        /// the token is not recognized, the string returns "<UNKNOWN TOKEN #>", where
        /// # is the token value.</returns>
        string _InterpretToken(int token)
        {
            string tokenAsString = "";

            // Rule 1: token is between 0 and the number of common words.
            if (token >= 0 && token < _commonwords.Length)
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
                    // Rule 1: Invalid tokens returned in a string.
                    tokenAsString = String.Format("<UNKNOWN TOKEN {0}>", token);
                }
            }
            return tokenAsString;
        }


        /// <summary>
        /// Given an array of integer tokens, convert the tokens into a single
        /// string of space-delimited words, following simple rules of
        /// formatting.
        /// </summary>
        /// <param name="tokens">The list of integers to interpret.</param>
        /// <returns>A string containing a sentence built from the tokens.</returns>
        public string Interpret(int[] tokens)
        {
            StringBuilder output = new StringBuilder();

            CultureInfo cultureInfo = Thread.CurrentThread.CurrentCulture;
            TextInfo textInfo = cultureInfo.TextInfo;

            int numTokens = tokens.Length;

            for (int tokenIndex = 0; tokenIndex < numTokens; ++tokenIndex)
            {
                // Rule 1: Interpret token
                string tokenAsString = _InterpretToken(tokens[tokenIndex]);
                if (tokenIndex == 0)
                {
                    // Rule 2: First word in sentence gets capitalized according to local rules.
                    tokenAsString = textInfo.ToTitleCase(tokenAsString);
                }
                output.Append(tokenAsString);

                // Rule 4: No space between last two tokens (if the following expression is false)
                if (tokenIndex + 2 < numTokens)
                {
                    // Rule 3: Separate all words by a single space.
                    output.Append(" ");
                }
            }

            return output.ToString();
        }
    }
}
