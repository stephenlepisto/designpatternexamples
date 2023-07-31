
/// @file
/// @brief
/// Implementation of the Bridge_Exercise() function as used in the
/// @ref bridge_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/formatstring.h"

#include "Bridge_ILogger.h"

#include "Bridge_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to show an example of writing to a logger.
///
/// This is called for all types of loggers, showing how the ILogger interface
/// hides the details of the underlying implementation.
/// </summary>
/// <param name="logger">An ILogger instance to log to.</param>
/// <param name="loggerType">The type of the underlying implementation.
/// </param>
static void _Bridge_Exercise_Demonstrate_Logging(ILogger* logger, const char* loggerType)
{
    if (logger != NULL && loggerType != NULL)
    {
        char *buffer = formatstring("Starting log to %s example", loggerType);
        if (buffer != NULL)
        {
            logger->LogTrace(buffer, logger->data);
            logger->LogInfo("An example of an informational line", logger->data);
            logger->LogError("An example of an error log entry", logger->data);
            free(buffer);
            buffer = NULL;
        }
        buffer = formatstring("Done with log to %s example", loggerType);
        if (buffer != NULL)
        {
            logger->LogTrace(buffer, logger->data);
            free(buffer);
            buffer = NULL;
        }
    }
}


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref bridge_pattern.
///
/// The Bridge pattern is used to allow a program to offer multiple
/// ways to perform logging without changing how the logging is
/// used throughout the program.
///
/// In this exercise, note how the calls into the logger are the
/// same regardless of the logger used.
/// </summary>
// ! [Using Bridge in C]
void Bridge_Exercise(void)
{
    printf("\nBridge_Exercise\n");

    {
        ILogger* fileLogger = CreateLogger(LoggerType_ToFile, "Bridge.log");
        if (fileLogger != NULL)
        {
            printf("  Example of writing to a log file...\n");
            _Bridge_Exercise_Demonstrate_Logging(fileLogger, "file");
            DestroyLogger(fileLogger);
        }
        else
        {
            printf("  Error! Failed to create a file logger\n");
        }
    }

    {
        ILogger* consoleLogger = CreateLogger(LoggerType_ToConsole, NULL);
        if (consoleLogger != NULL)
        {
            printf("  Example of writing to the console...\n");
            _Bridge_Exercise_Demonstrate_Logging(consoleLogger, "console");
            DestroyLogger(consoleLogger);
        }
        else
        {
            printf("  Error! Failed to create a console logger\n");
        }
    }

    {
        ILogger* nullLogger = CreateLogger(LoggerType_ToNull, NULL);
        if (nullLogger != NULL)
        {
            printf("  Example of writing to a Null object (no output)...\n");
            _Bridge_Exercise_Demonstrate_Logging(nullLogger, "null");
            DestroyLogger(nullLogger);
        }
        else
        {
            printf("  Error! Failed to create a console logger\n");
        }
    }

    printf("  Done.\n");
}
// ! [Using Bridge in C]
