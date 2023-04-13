/// @file
/// @brief
/// Implementation of the null logger, along with the CreateNullLogger() and
/// DestroyNullLogger() factory functions
/// used in the @ref bridge_pattern.

#include <stdlib.h>

#include "Bridge_NullLogger.h"


/// <summary>
/// Write a trace message to a null logger (basically, discard the log message).
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Null_LogTrace(const char* message, void* data)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
    message;
    data;
}


/// <summary>
/// Write an informational message to a null logger (basically, discard the log message).
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Null_LogInfo(const char* message, void* data)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
    message;
    data;
}


/// <summary>
/// Write an error message to a null logger (basically, discard the log message).
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">Unused.</param>
static void _Null_LogError(const char* message, void *data)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
    message;
    data;
}


///////////////////////////////////////////////////////////////////////////////
// CreateNullLogger()
///////////////////////////////////////////////////////////////////////////////
ILogger* CreateNullLogger()
{
    ILogger* logger = (ILogger*)malloc(sizeof(ILogger));
    if (logger != NULL)
    {
        logger->LogTrace = _Null_LogTrace;
        logger->LogInfo = _Null_LogInfo;
        logger->LogError = _Null_LogError;
        logger->data = NULL;
    }

    return logger;
}

///////////////////////////////////////////////////////////////////////////////
// DestroyNullLogger()
///////////////////////////////////////////////////////////////////////////////
void DestroyNullLogger(ILogger* logger)
{
    free(logger);
}
