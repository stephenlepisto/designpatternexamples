/// @file
/// @brief
/// Implementation of the State_Exercise() function as used in the 
/// @ref state_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/dynamicstring.h"
#include "helpers/split.h"

#include "State_RemoveComments.h"

#include "State_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to display text from the State exercise.  Text is
/// displayed with line numbers.
/// </summary>
/// <param name="textToDisplay">Text to display.</param>
static void _State_DisplayText(const char* textToDisplay)
{
    SplitList lines = { 0 };
    char* text = _strdup(textToDisplay);
    if (text != NULL)
    {
        split(text, "\n", &lines);
        int lineNumber = 1;
        for (size_t index = 0; index < lines.strings_count; index++)
        {
            printf("    %2d) %s\n", lineNumber, lines.strings[index]);
            lineNumber++;
        }
        free(text);
    }
    else
    {
        printf("  Error!  Out of memory duplicating text to display with lines!\n");
    }
}


//=============================================================================
//=============================================================================

const char* textToFilter =
"/*####################  Block Comment  #################################*/\n"
"//####################  Line Comment  ####################################\n"
"// A comment.  /* A nested comment */\n"
"\n"
"void State_Exercise() // An exercise in state machines\n"
"{\n"
"    char character = '\\\"';\n"
"    printf(\"\\n\");\n"
"    printf(\"\\\"State\\\" /*Exercise*/\\n\");\n"
"\n"
"    bool success = State_RemoveComments(textToFilter, &filteredText);\n"
"\n"
"    printf(\"\\t\\tDone. //(No, really)//\\n\");\n"
"}";


/// <summary>
/// Example of using the @ref state_pattern.
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
// ! [Using State in C]
void State_Exercise()
{
    printf("\nState_Exercise\n");

    printf("  Text to filter:\n");
    _State_DisplayText(textToFilter);

    printf("  Filtering text...\n");
    DynamicString filteredText = { 0 };
    bool success = State_RemoveComments(textToFilter, &filteredText);
    if (success)
    {
        printf("  Filtered text:\n");
        _State_DisplayText(filteredText.string);
    }

    DynamicString_Clear(&filteredText);

    printf("  Done.\n");
}
// ! [Using State in C]
