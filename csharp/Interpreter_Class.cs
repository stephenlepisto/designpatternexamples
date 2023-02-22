// The interpreter pattern is used in situations where interpretation of a
// "sentence" of tokens is required.  It requires thinking of the business
// logic like a domain-specific language, where each element in the grammar
// represents an unambiguous operation.
//
// A "sentence" consists of one or more "words".  Each "word" represents
// some specific action or operation.  A grammar is a set of rules controlling
// how a "sentence" is constructed with "words".
//
// The process of converting one or more "sentences" into tokens or objects is
// called parsing.  The result of parsing is a list of these tokens.  For a
// complex grammar, a hierarchical tree of tokens may be created so as to
// maintain a particular relationship between tokens.  This tree is known as
// an abstract syntax tree or AST.
//
// To convert the tokens into actions, the tokens must be interpreted.  This
// is where the Interpreter pattern comes in.  The interpreter moves through
// an AST, performing actions based on the tokens.  Those actions are
// typically functions or methods on a class.  What those actions are depends
// on what is expected from the grammar.
//
// The most obvious form of this parse/interpret cycle is a programming
// language.  The grammar for a programming language describes how all the
// symbols and keywords relate to each other and to user-provided elements
// such as variables.  A parser converts the text of the program into an AST.
// This AST is then handed to a compiler that interprets the tokens and takes
// actions based on those tokens.  The actions are typically producing some
// kind of assembly language that will eventually be executed on a CPU.
//
// Some applications may be able to express their business logic as a set of
// text-based commands.  In other words, a scripting language that may be
// specific to the application (unless the application uses an already-
// existing scripting language).  The application knows how to parse that
// script into tokens that then need to be interpreted.
//
// In short, what is interpreted is a set of tokens that represent actions.
// The tokens can be arranged in an abstract syntax tree to provide more
// complex relationships between the tokens.  Where these tokens come from is
// outside the interpreter's control.
//
// The interpreter pattern primarily exists to apply the interpretation of an
// AST in object-oriented form, although it certainly doesn't have to be that
// way.  In fact, there are two methodologies to interpret an abstract syntax
// tree:
// 1. A function traverses the tokens in the AST, altering the state of the
//    program as part of interpreting each token.
// 2. The tokens in the AST are actually class objects or nodes.  The nodes
//    are arranged into a linked tree where each node can have zero, one, or
//    two children.  All nodes have a method called interpret().  The head
//    node is called with a context object and that node calls its children
//    in a recursive fashion until the entire tree is traversed, with each
//    node updating the context as it is called.
//
// As the complexity of the domain-specific language grows, the complexity
// of the interpreter grows exponentially.  Making an interpreter for a
// simple language with half a dozen "words" can be done from scratch but
// it is better to use tools specifically designed for creating parsers and
// interpreters from a general grammar.
//
// A common use case for interpreters is handling simple one line "sentences"
// or expressions that the user enters to alter the behavior of the program
// at certain strategic points.  For example, a regular expression parser
// converts a set of match tokens into an abstract syntax tree and then an
// interpreter processes that tree in the context of a string to search for
// a matching pattern.
//
// Another example is a simple mathematical expression interpreter, where the
// value of a variable is defined as an expression requiring interpretation.
// The expression might include other variables.
//
// Where there is an interpreter, there is (usually) a parser to create the
// elements that are interpreted.  The process of interpreting the elements
// causes changes to the program's state or the data contained within the
// program.
//
// Note: Another example of an interpreter (which includes a parser) is shown
// in the Null_Object design pattern example.
//
// The example provided here takes an array of integers and converts each into
// a text word or punctuation mark separated by a space from the previous
// token, forming a complete sentence.  In essence, interpreting the list of
// tokens reverses the effects of a parser.  This is an example of an external
// function controlling the interpretation.  Building an object-oriented form
// of this by hand got ridiculously complicated and very hard to follow.

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
