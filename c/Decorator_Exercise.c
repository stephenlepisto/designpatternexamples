/// @file
/// @brief
/// Implementation of the various decorator functions that are called from the
/// Decorator_Exercise() function as used in the @ref decorator_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/dynamicstring.h"
#include "helpers/formatstring.h"

#include "Decorator_Exercise.h"


//=============================================================================
//=============================================================================

/// <summary>
/// Helper function for applying decorations to the given string.
/// </summary>
/// <param name="s">A DynamicString object that contains the string to
/// be decorated.</param>
/// <param name="decoration">A string passed to sprintf() that wraps the `%%s`
/// (which represents the given string) in some kind of decoration.</param>
/// <returns>Returns the DynamicString object so the decorator functions can be
/// chained together.</returns>
DynamicString* _Decorate(DynamicString* s, const char* decoration)
{
    if (s != NULL && decoration != NULL)
    {
        char *line = formatstring(decoration, s->string);
        if (line != NULL)
        {
            DynamicString_Set(s, line);
            free(line);
        }
    }
    return s;
}


/// <summary>
/// Represents the RedForeground decorator, which alters the wrapped content
/// to render as red text.
/// </summary>
/// <param name="s">A DynamicString object that contains the string to be
/// decorated.</param>
/// <returns>Returns the DynamicString object so the decorator functions can be
/// chained together.</returns>
DynamicString* RedForegroundDecorator(DynamicString* s)
{
    return _Decorate(s, "\x1b[31m%s\x1b[39m");
}

/// <summary>
/// Represents the WhiteBackground decorator, which alters the wrapped content
/// to render the background color as white.
/// </summary>
/// <param name="s">A DynamicString object that contains the string to be
/// decorated.</param>
/// <returns>Returns the DynamicString object so the decorator functions can be
/// chained together.</returns>
DynamicString* WhiteBackgroundDecorator(DynamicString* s)
{
    return _Decorate(s, "\x1b[47m%s\x1b[49m");
}

/// <summary>
/// Represents the Underline decorator, which alters the wrapped content to
/// render it as underlined.
/// </summary>
/// <param name="s">A DynamicString object that contains the string to be
/// decorated.</param>
/// <returns>Returns the DynamicString object so the decorator functions can be
/// chained together.</returns>
DynamicString* UnderlineDecorator(DynamicString* s)
{
    return _Decorate(s, "\x1b[4m%s\x1b[24m");
}


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref decorator_pattern.
///
/// The Decorator pattern is used when some data element at run time needs
/// to have its behavior altered.  This is supported by providing wrapper
/// functions called decorators that take an instance of the data element and
/// return the data element.  Each wrapper function alters the data element and
/// returns it so it can be passed to the next wrapper function.
/// </summary>
// ! [Using Decorator in C]
void Decorator_Exercise(void)
{
    printf("\nDecorator_Exercise\n");

    const char* text = "This is raw text";

    DynamicString string;
    DynamicString_Initialize(&string);
    DynamicString_Set(&string, text);

    // Wrap the base element in three decorators.
    DynamicString* rendering = NULL;
    rendering = WhiteBackgroundDecorator(UnderlineDecorator(RedForegroundDecorator(&string)));

    printf("  Base Text element: \"%s\"\n", text);
    printf("  Decorated element: \"%s\"\n", rendering->string);
    DynamicString_Clear(&string);

    printf("  Done.\n");
}
// ! [Using Decorator in C]
