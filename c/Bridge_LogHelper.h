/// @file
/// @brief
/// Declaration of the LogHelper_FormatLogLine() function,
/// used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_LOGHELPER_H__
#define __BRIDGE_LOGHELPER_H__

#include <stdbool.h>
#include <stdlib.h>

/// <summary>
/// Format a line for logging, including time stamp.
/// </summary>
/// <param name="loglevel">Level of logging (TRACE, INFO, ERROR)</param>
/// <param name="message">Message to log</param>
/// <param name="output">Buffer to fill with the formatted log line.</param>
/// <param name="maxOutputSize">Maximum size of @p output buffer in characters.</param>
/// <returns>Returns true if the log was formatted into the buffer; otherwise,
/// returns false.</returns>
bool LogHelper_FormatLogLine(const char* loglevel, const char* message, char* output, size_t maxOutputSize);

#endif // __BRIDGE_LOGHELPER_H__
