/// @file
/// @brief
/// Declaration of the CreateNullLogger() and DestroyNullLogger() factory functions
/// used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_NULLLOGGER_H__
#define __BRIDGE_NULLLOGGER_H__

#include "Bridge_ILogger.h"

/// <summary>
/// Create an instance of an ILogger that outputs to a console.
/// </summary>
/// <returns>Returns an ILogger instance to use for logging to a console;
/// returns NULL if something went wrong in creating the logger.</returns>
ILogger* CreateNullLogger(void);

/// <summary>
/// Destroy the given instance of an ILogger for outputting to a console.
/// </summary>
/// <param name="logger">The ILogger instance to destroy.</param>
void DestroyNullLogger(ILogger* logger);

#endif // __BRIDGE_NULLLOGGER_H__
