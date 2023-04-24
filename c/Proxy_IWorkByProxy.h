/// @file
/// @brief
/// Declaration of the IWorkByProxy structure, which represents both the real
/// service and the proxy service,
/// as used in the @ref proxy_pattern.

#pragma once
#ifndef __PROXY_IWORKBYPROXY_H__
#define __PROXY_IWORKBYPROXY_H__

#include "helpers/dynamicstring.h"

/// <summary>
/// Represents what can be done on the proxy object.
/// This same interface is implemented on the real object as well to
/// ensure both have the same methods.  The program accesses the
/// proxy object only through this interface.
/// </summary>
typedef struct
{
    /// <summary>
    /// Does some work on the given argument and updates the given argument.
    /// </summary>
    /// <param name="someArgument">A DynamicString object to be worked on.</param>
    bool (*DoWork)(DynamicString* someArgument);
} IWorkByProxy;


#endif // __PROXY_IWORKBYPROXY_H__

