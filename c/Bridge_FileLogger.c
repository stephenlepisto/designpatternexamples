/// @file
/// @brief
/// Implementation of the file logger, along with the CreateFileLogger() and
/// DestroyFileLogger() factory functions
/// used in the @ref bridge_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "Bridge_LogHelper.h"
#include "Bridge_FileLogger.h"

/// <summary>
/// Send a formatted line to a log file.
/// </summary>
/// <param name="loglevel">The level of the log detail.</param>
/// <param name="message">The message to log.</param>
/// <param name="fp">Handle to file to write to.  If NULL, nothing is written.</param>
static void _WriteLine(const char* loglevel, const char* message, FILE* fp)
{
    char buffer[512] = { 0 };

    if (fp != NULL)
    {
        if (LogHelper_FormatLogLine(loglevel, message, buffer, sizeof(buffer)))
        {
            size_t numElementsToWrite = strlen(buffer);
            size_t numElementsWritten = fwrite(buffer, sizeof(char), numElementsToWrite, fp);
            if (numElementsWritten != numElementsToWrite)
            {
                errno_t errorcode = errno;
                char errmessage[64] = { 0 };
                errno_t err = strerror_s(errmessage, sizeof(errmessage), errorcode);
                if (err == 0)
                {
                    printf("  Error (%d) writing log file: %s\n", errorcode, errmessage);
                }
                else
                {
                    printf("  Error writing log file: Unable to get error string for code %d\n", errorcode);
                }
                printf("%s", buffer);
            }
        }
    }
}

/// <summary>
/// Write a trace message to a log file.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">The data associated with an instance of an ILogger.
/// In this case, the file handle to write to.</param>
static void _File_LogTrace(const char* message, void* data)
{
    FILE* fp = NULL;
    if (data != NULL)
    {
        fp = (FILE*)data;
    }
    _WriteLine("TRACE", message, fp);
}


/// <summary>
/// Write an informational message to a log file.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">The data associated with an instance of an ILogger.
/// In this case, the file handle to write to.</param>
static void _File_LogInfo(const char* message, void* data)
{
    FILE* fp = NULL;
    if (data != NULL)
    {
        fp = (FILE*)data;
    }
    _WriteLine("INFO ", message, fp);
}


/// <summary>
/// Write an error message to a log file.
/// </summary>
/// <param name="message">The message to log.</param>
/// <param name="data">The data associated with an instance of an ILogger.
/// In this case, the file handle to write to.</param>
static void _File_LogError(const char* message, void* data)
{
    FILE* fp = NULL;
    if (data != NULL)
    {
        fp = (FILE*)data;
    }
    _WriteLine("ERROR", message, fp);
}


///////////////////////////////////////////////////////////////////////////////
// CreateFileLogger()
///////////////////////////////////////////////////////////////////////////////
ILogger* CreateFileLogger(const char* filename)
{
    ILogger* logger = (ILogger*)malloc(sizeof(ILogger));
    if (logger != NULL && filename != NULL)
    {
        logger->LogTrace = _File_LogTrace;
        logger->LogInfo = _File_LogInfo;
        logger->LogError = _File_LogError;
        logger->data = NULL;
        FILE* fp = NULL;
        errno_t err = fopen_s(&fp, filename, "w");
        if (err == 0)
        {
            logger->data = fp;
        }
        else
        {
            free(logger);
            logger = NULL;
        }
    }

    return logger;
}

///////////////////////////////////////////////////////////////////////////////
// DestroyFileLogger()
///////////////////////////////////////////////////////////////////////////////
void DestroyFileLogger(ILogger* logger)
{
    if (logger != NULL)
    {
        if (logger->data != NULL)
        {
            FILE* fp = (FILE*)logger->data;
            fclose(fp);
        }
        free(logger);
    }
}
