/// @file
/// @brief
/// Implementation of the real service, accessed through the GetRealService()
/// function,
/// as used in the @ref proxy_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Proxy_RealService.h"

//-----------------------------------------------------------------------------

/// <summary>
/// The real function that does all the work in the real service.
/// </summary>
static bool _Real_DoWork(DynamicString* someArgument)
{
    bool success = false;

    if (someArgument != NULL)
    {
        const char* prompt = "Real class received '%s'";
        size_t bufferSize = strlen(prompt) + someArgument->length;
        char* buffer = malloc(bufferSize + 1);
        if (buffer != NULL)
        {
            int num_chars = sprintf_s(buffer, bufferSize + 1, prompt, someArgument->string);
            if (num_chars != -1)
            {
                success = DynamicString_Set(someArgument, buffer);
            }
            else
            {
                printf("  Error!  sprintf_s() failed to create real string!\n");
            }
            free(buffer);
        }
    }
    return success;
}

/// <summary>
/// The real service that does all the work.
///
/// This would normally be a very expensive to create because it might be
/// running on the server end of a remoting channel.
/// </summary>
static IWorkByProxy _real_service = {
    _Real_DoWork
};

//-----------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
// GetRealService()
///////////////////////////////////////////////////////////////////////////////
IWorkByProxy* GetRealService(void)
{
    return &_real_service;
}
