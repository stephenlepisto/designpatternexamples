/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Interpreter_Exercise "Interpreter_Exercise"
/// class used in the @ref interpreter_pattern.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref interpreter_pattern in C#.
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
    internal class Interpreter_Exercise
    {

        /// <summary>
        /// Helper method to convert a list of ints to a string representation.
        /// </summary>
        /// <param name="tokens">Array of ints to work with.</param>
        /// <returns>A string representation of the integer list.</returns>
        string _TokensToString(int[] tokens)
        {
            StringBuilder output = new StringBuilder();

            output.Append("[");
            for (int index = 0; index < tokens.Length; ++index)
            {
                output.AppendFormat("{0,3}", tokens[index]);
                if (index + 1 < tokens.Length)
                {
                    output.Append(", ");
                }
            }
            output.Append("]");
            return output.ToString();
        }


        /// <summary>
        /// A list of pre-defined token lists.  Each token list represents
        /// a single sentence constructed from the 40 most common words in
        /// the English language.  I don't use all 40 words, though; that
        /// would be silly.
        /// </summary>
        static int[][] _sentenceTokenLists = new int[][] {
            new int[] { 39, 18, 17, 27, 2, 7, 101 }, // "What do you say to that?"
            new int[] { 32, 17, 1, 0, 34, 2, 1, 37, 101 }, // "Will you be the one to be there?"
            new int[] { 36, 17, 8, 5, 32, 2, 18, 7, 101 }, // "Would you have a will to do that?"
            new int[] { 11, 12, 17, 9, 36, 12, 1, 6, 20, 100 }, // "For not you I would not be in this."
            new int[] { 26, 27, 7, 21, 36, 17, 27, 10, 101 }, // "We say that but would you say it?"
            new int[] { 23, 28, 32, 26, 32, 18, 10, 100 } // "By her will we will do it."
        };

        /// <summary>
        /// Executes the example for the @ref interpreter_pattern in C#.
        /// </summary>
        // ! [Using Interpreter in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Interpreter Exercise");

            Interpreter_Class interpreter = new Interpreter_Class();

            for (int sentenceIndex = 0; sentenceIndex < _sentenceTokenLists.Length; ++sentenceIndex)
            {
                int[] tokenList = _sentenceTokenLists[sentenceIndex];

                string tokensAsString = _TokensToString(tokenList);

                string sentence = interpreter.Interpret(tokenList);

                // 50 is a magic number corresponding to the longest token list
                // expressed as a string.  Derived empirically.  It makes the
                // output easier to, er, interpret.
                Console.WriteLine("  {0,-50} ==> \"{1}\"", tokensAsString, sentence);
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Interpreter in C#]
    }
}
