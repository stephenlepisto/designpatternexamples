/// @file
/// @brief
/// Declaration of the real service, accessed through the GetRealService() function,
/// as used in the @ref proxy_pattern.

#pragma once
#ifndef __PROXY_REALSERVICE_H__
#define __PROXY_REALSERVICE_H__

#include "Proxy_IWorkByProxy.h"

/// <summary>
/// Return a pointer to the real service expressed as an IWorkByProxy service.
/// </summary>
/// <returns>Returns an IWorkByProxy object representing the real service.</returns>
IWorkByProxy* GetRealService(void);


#endif // __PROXY_REALSERVICE_H__
