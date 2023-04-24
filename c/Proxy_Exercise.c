/// @file
/// @brief
/// Implementation of the Proxy_Exercise() function as used in the 
/// @ref proxy_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/dynamicstring.h"

#include "Proxy_ProxyService.h"

#include "Proxy_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref proxy_pattern "Proxy" design pattern.
/// 
/// The Proxy pattern is used when a large or expensive object cannot be
/// represented directly in the program, typically because the object is
/// in another process or even another system altogether.
/// 
/// In this exercise, a Proxy class implements the same interface as the
/// Real class, making the Proxy class look like the Real class.  Calls
/// made on the Proxy class are passed to the Real class where the work
/// is actually done (in this case, a munged string with the text
/// "Real class received 'xxxx'".
/// 
/// The only difference in output here is one additional line for the
/// first call showing the real class being instantiated.  The subsequent
/// calls do not show this line.
/// </summary>
// ! [Using Proxy in C]
void Proxy_Exercise()
{
    printf("\nProxy Exercise\n");

    DynamicString output;
    DynamicString_Initialize(&output);

    printf("  Getting proxy object...\n");
    IWorkByProxy* proxyObject = GetProxyService();

    printf("  Calling Dowork() on proxy...\n");
    bool success = DynamicString_Set(&output, "Initial call");
    if (success)
    {
        success = proxyObject->DoWork(&output);
        if (success)
        {
            printf("  Output from proxy = \"%s\"\n", output.string);
        }
    }
    if (success)
    {
        printf("  Calling Dowork() on proxy...\n");
        success = DynamicString_Set(&output, "Second call");
        if (success)
        {
            success = proxyObject->DoWork(&output);
            if (success)
            {
                printf("  Output from proxy = \"%s\"\n", output.string);
            }
        }
    }
    if (success)
    {
        printf("  Calling Dowork() on proxy...\n");
        success = DynamicString_Set(&output, "Third call");
        if (success)
        {
            success = proxyObject->DoWork(&output);
            if (success)
            {
                printf("  Output from proxy = \"%s\"\n", output.string);
            }
        }
    }

    DynamicString_Clear(&output);

    printf("  Done.\n");
}
// ! [Using Proxy in C]
