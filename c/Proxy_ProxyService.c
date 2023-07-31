/// @file
/// @brief
/// Implementation of the proxy service, accessed through the GetProxyService()
/// function, as used in the @ref proxy_pattern.

#include <stdlib.h>
#include <stdio.h>
#include "Proxy_RealService.h"
#include "Proxy_ProxyService.h"

//-----------------------------------------------------------------------------

/// <summary>
/// The one and only instance of the real service associated with this proxy
/// service instance.
/// </summary>
static IWorkByProxy* _realService = NULL;


/// <summary>
/// Helper function to retrieve the one and only instance of the real service.
/// This hides the details of instantiating the real service.
/// </summary>
/// <returns>A single instance of the real service represented by
/// the IWorkByProxy interface.</returns>
static IWorkByProxy* Proxy_GetRealService(void)
{
    if (_realService == NULL)
    {
        printf("  --> Creating instance of real class...\n");
        _realService = GetRealService();
    }

    return _realService;
}

/// <summary>
/// Do some work on a dynamic string.
/// </summary>
/// <param name="someArgument">A DynamicString object to alter.</param>
/// <remarks>
/// The real service this proxy represents is not instantiated until
/// this function is called, even though the proxy service has been obtained.
/// When this function is called for the first time, /// the real service is
/// obtained, incurring a performance penalty only on the first call.
/// </remarks>
bool Proxy_DoWork(DynamicString* someArgument)
{
    bool success = false;

    printf("  --> proxy class DoWork() in\n");
    if (someArgument != NULL)
    {
        IWorkByProxy* service = Proxy_GetRealService();
        printf("  --> Forwarding DoWork() call to real class...\n");
        success = service->DoWork(someArgument);
    }

    return success;
}

/// <summary>
/// The proxy service.
/// </summary>
IWorkByProxy proxy_service = {
    Proxy_DoWork
};

//-----------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
// GetProxyService()
///////////////////////////////////////////////////////////////////////////////
IWorkByProxy* GetProxyService(void)
{
    printf("  --> Creating instance of proxy class...\n");
    return &proxy_service;
}
