/// @file
/// @brief
/// Declaration of the proxy service, accessed through the GetProxyService() function,
/// as used in the @ref proxy_pattern.

#pragma once
#ifndef __PROXY_PROXYSERVICE_H__
#define __PROXY_PROXYSERVICE_H__

#include "Proxy_IWorkByProxy.h"

/// <summary>
/// Obtain the proxy service.
/// 
/// Note that the real service will not be obtained until the first call into
/// the proxy service.
/// </summary>
/// <returns>Returns an IWorkByProxy object representing the proxy service.</returns>
IWorkByProxy* GetProxyService();

#endif // __PROXY_PROXYSERVICE_H__

