/// @file
/// @brief
/// Declaration of the ILogger interface, along with the CreateLogger() and
/// DestroyLogger() functions
/// used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_ILOGGER_H__
#define __BRIDGE_ILOGGER_H__

/// <summary>
/// A value passed to CreateLogger() to specify the type of logger to create.
/// </summary>
typedef enum
{
    /// <summary>
    /// Log to nowhere, that is, throw out all logging.  No additional parameters.
    /// </summary>
    LoggerType_ToNull,

    /// <summary>
    /// Log to a file.  One additional parameter: the name of the file to log to.
    /// </summary>
    LoggerType_ToFile,

    /// <summary>
    /// Log to the console.  No additional parameters.
    /// </summary>
    LoggerType_ToConsole
} LoggerTypes;


typedef struct
{
    /// Log trace messages to the configured output.
    /// </summary>
    /// <param name="message">The message to log.</param>
    void (*LogTrace)(const char* message, void* data);

    /// <summary>
    /// Log informational messages to the configured output.
    /// </summary>
    /// <param name="message">The message to log.</param>
    void (*LogInfo)(const char* message, void* data);

    /// <summary>
    /// Log error messages to the configured output.
    /// </summary>
    /// <param name="message">The message to log.</param>
    void (*LogError)(const char* message, void* data);

    /// <summary>
    /// The type of this logger, as identified by a value from the @ref LoggerTypes
    /// enumeration.
    /// </summary>
    LoggerTypes loggerType;

    /// <summary>
    /// Data associated with a specific instance of a logger.
    /// </summary>
    void* data;
} ILogger;


/// <summary>
/// Return an interface for the specified logger.
/// </summary>
/// <param name="loggerType">A value from the @ref LoggerTypes enumeration
/// specifying the type of logger to create.</param>
/// <param name="filename">For @ref LoggerType_ToFile, this is the path and name of
/// the log file to write to.  Ignored for other logger types.</param>
/// <returns>Returns an ILogger instance that is to be used to log messages.
/// Returns NULL if the logger type is not recognized.</returns>
ILogger* CreateLogger(LoggerTypes loggerType, const char* filename);

/// <summary>
/// Release any resources associated with the given logger.  The given ILogger
/// instance is no longer valid after this function returns.
/// </summary>
/// <param name="logger">An ILogger object representing a logger to be destroyed.
/// </param>
void DestroyLogger(ILogger* logger);

#endif // __BRIDGE_ILOGGER_H__

