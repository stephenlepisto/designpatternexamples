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
/// <param name="const char*">The message to log.</param>
/// <param name="void*">Unused.</param>
static void _Null_LogTrace(const char* /*message*/, void* /*data*/)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
}


/// <summary>
/// Write an informational message to a null logger (basically, discard the log message).
/// </summary>
/// <param name="const char*">The message to log.</param>
/// <param name="void*">Unused.</param>
static void _Null_LogInfo(const char* /*message*/, void* /*data*/)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
}


/// <summary>
/// Write an error message to a null logger (basically, discard the log message).
/// </summary>
/// <param name="const char*">The message to log.</param>
/// <param name="void*">Unused.</param>
static void _Null_LogError(const char* /*message*/, void* /*data*/)
{
    // We don't do anything here, just reference the parameters to avoid a
    // compiler warning.
}


///////////////////////////////////////////////////////////////////////////////
// CreateNullLogger()
///////////////////////////////////////////////////////////////////////////////
ILogger* CreateNullLogger(void)
{
    ILogger* logger = calloc(1, sizeof(ILogger));
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
