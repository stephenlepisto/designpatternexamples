/// @file
/// @brief
/// Implementation of the real service, accessed through the GetRealService()
/// function,
/// as used in the @ref proxy_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helpers/formatstring.h"

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
        char *buffer = formatstring(prompt, someArgument->string);
        if (buffer != NULL)
        {
            success = DynamicString_Set(someArgument, buffer);
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
