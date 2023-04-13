/// @file
/// @brief
/// Implementation of the CreateLogger() and DestroyLogger() functions
/// used in the @ref bridge_pattern.

#include <stdlib.h>

#include "Bridge_FileLogger.h"
#include "Bridge_ConsoleLogger.h"
#include "Bridge_NullLogger.h"

#include "Bridge_ILogger.h"



///////////////////////////////////////////////////////////////////////////////
// CreateLogger()
///////////////////////////////////////////////////////////////////////////////
ILogger* CreateLogger(LoggerTypes loggerType, const char* filename)
{
    ILogger* logger = NULL;

    switch (loggerType)
    {
        case LoggerType_ToConsole:
            logger = CreateConsoleLogger();
            break;

        case LoggerType_ToNull:
            logger = CreateNullLogger();
            break;

        case LoggerType_ToFile:
            logger = CreateFileLogger(filename);
            break;

        default:
            break;
    }

    if (logger != NULL)
    {
        logger->loggerType = loggerType;
    }

    return logger;
}

///////////////////////////////////////////////////////////////////////////////
// DestroyLogger()
///////////////////////////////////////////////////////////////////////////////
void DestroyLogger(ILogger* logger)
{
    if (logger != NULL)
    {
        switch (logger->loggerType)
        {
            case LoggerType_ToConsole:
                DestroyConsoleLogger(logger);
                break;

            case LoggerType_ToNull:
                DestroyNullLogger(logger);
                break;

            case LoggerType_ToFile:
                DestroyFileLogger(logger);
                break;

            default:
                break;
        }
    }
}
