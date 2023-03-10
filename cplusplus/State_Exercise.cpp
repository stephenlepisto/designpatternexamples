
/// @file
/// @brief
/// Implementation of the State_Exercise() function as used in the 
/// @ref state_pattern "State pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "helpers/split.h"
#include "helpers/stringlist.h"

#include "State_Exercise.h"
#include "State_Class.h"


namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// Helper method to display text from the State exercise.  Text is
    /// displayed with line numbers.
    /// </summary>
    /// <param name="textToDisplay">Text to display.</param>
    void _State_DisplayText(const std::string& textToDisplay)
    {
        StringList lines = Helpers::split(textToDisplay, "\n");
        int lineNumber = 1;
        for (std::string line : lines)
        {
            std::cout << std::format("    {0:2}) {1}", lineNumber, line) << std::endl;
            ++lineNumber;
        }
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref state_pattern "State" design pattern.
    /// 
    /// The State pattern alters the behavior of the class hierarchy based
    /// on some state.  This is the basis of a Finite State Machine.
    /// 
    /// In this exercise, the State class is a filter that parses text to
    /// remove C++-style line and block comments.  It needs to be smart
    /// enough to ignore comment characters inside quotes.
    /// 
    /// The filtering process starts with creating the context that drives
    /// the state machine.  Internal classes are provided for each state.
    /// </summary>
    // ! [Using State in C++]
    void State_Exercise()
    {
        std::cout << std::endl;
        std::cout << "State Exercise" << std::endl;

        StateContext_Class filterContext;
        std::string textToFilter =
            "//########################################################################\n"
            "//########################################################################\n"
            "// A comment.  /* A nested comment */\n"
            "\n"
            "void State_Exercise() // An exercise in state machines\n"
            "{\n"
            "    char character = '\\\"';\n"
            "    std::cout << std::endl;\n"
            "    std::cout << \"\\\"State\\\" /*Exercise*/\" << std::endl;\n"
            "\n"
            "    StateContext_Class filterContext;\n"
            "\n"
            "    std::cout << \"\\t\\tDone. //(No, really)//\" << std::endl;\n"
            "}";

        std::cout << "  Text to filter:" << std::endl;
        _State_DisplayText(textToFilter);

        std::cout << "  Filtering text..." << std::endl;
        std::string filteredText = filterContext.RemoveComments(textToFilter);

        std::cout << "  Filtered text:" << std::endl;
        _State_DisplayText(filteredText);

        std::cout << "  Done." << std::endl;
    }
    // ! [Using State in C++]

} // end namespace
