/// @file
/// @brief
/// Implementation of the console logger, along with the CreateConsoleLogger() and
/// DestroyConsoleLogger() factory functions
/// used in the @ref bridge_pattern.

#include <stdlib.h>
#include <stdio.h>

#include "Bridge_LogHelper.h"
#include "Bridge_ConsoleLogger.h"

/// <summary>
/// Send a formatted line to the console.
/// </summary>
/// <param name="loglevel">The level of the log detail.</param>
/// <param name="message">The message to log.</param>
static void _WriteLine(const char* loglevel, const char* message)
{
    char buffer[512] = { 0 };

    if (LogHelper_FormatLogLine(loglevel, message, buffer, sizeof(buffer)))
    {
        printf("%s", buffer);
    }
}

/// <summary>
/// Write a trace message to the console.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Console_LogTrace(const char* message, void* data)
{
    (void)data; // Unused

    // We don't use the data field, so just add a local reference to avoid
    // a compiler warning.

    _WriteLine("TRACE", message);
}


/// <summary>
/// Write an informational message to the console.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Console_LogInfo(const char* message, void* data)
{
    (void)data; // Unused

    // We don't use the data field, so just add a local reference to avoid
    // a compiler warning.

    _WriteLine("INFO ", message);
}


/// <summary>
/// Write an error message to the console.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Console_LogError(const char* message, void* data)
{
    (void)data; // Unused

    // We don't use the data field, so just add a local reference to avoid
    // a compiler warning.

    _WriteLine("ERROR", message);
}


///////////////////////////////////////////////////////////////////////////////
// CreateConsoleLogger()
///////////////////////////////////////////////////////////////////////////////
ILogger* CreateConsoleLogger(void)
{
    ILogger* logger = calloc(1, sizeof(ILogger));
    if (logger != NULL)
    {
        logger->LogTrace = _Console_LogTrace;
        logger->LogInfo = _Console_LogInfo;
        logger->LogError = _Console_LogError;
        logger->data = NULL;
    }

    return logger;
}

///////////////////////////////////////////////////////////////////////////////
// DestroyConsoleLogger()
///////////////////////////////////////////////////////////////////////////////
void DestroyConsoleLogger(ILogger* logger)
{
    free(logger);
}
