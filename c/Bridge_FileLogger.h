/// @file
/// @brief
/// Declaration of the CreateFileLogger() and DestroyFileLogger() factory functions
/// used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_FILELOGGER_H__
#define __BRIDGE_FILELOGGER_H__

#include "Bridge_ILogger.h"

/// <summary>
/// Create an instance of an ILogger that outputs to a file.
/// </summary>
/// <param name="filename">Name of the file to log to.  The file will be
/// overwritten.</param>
/// <returns>Returns an ILogger instance to use for logging to a file;
/// returns NULL if something went wrong in creating the logger.</returns>
ILogger* CreateFileLogger(const char* filename);

/// <summary>
/// Destroy the given instance of an ILogger for outputting to a file.
/// </summary>
/// <param name="logger">The ILogger instance to destroy.</param>
void DestroyFileLogger(ILogger* logger);

#endif // __BRIDGE_FILELOGGER_H__

