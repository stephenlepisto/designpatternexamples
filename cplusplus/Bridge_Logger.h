/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Logger "Logger"
/// class used in the @ref bridge_pattern "Bridge pattern".

#pragma once
#ifndef __BRIDGE_LOGGER_H__
#define __BRIDGE_LOGGER_H__

#include <memory>
#include <string>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples_cpp
{

    class Logger
    {
    private:
        // The logger implementation represented by the ILogger interface.
        std::unique_ptr<ILogger> _logger;

    public:
        /// <summary>
        /// A value passed to LoggerClassFactory.CreateLogger() to specify the type of
        /// logger to create.
        /// </summary>
        enum LoggerTypes
        {
            /// <summary>
            /// Log to nowhere, that is, throw out all logging.  No additional parameters.
            /// </summary>
            ToNull,

            /// <summary>
            /// Log to a file.  One additional parameter: the name of the file to log to.
            /// </summary>
            ToFile,

            /// <summary>
            /// Log to the console.  No additional parameters.
            /// </summary>
            ToConsole
        };

    public:
        /// <summary>
        /// Constructor that takes a LoggerTypes value to create a new Logger class.
        /// </summary>
        /// <param name="loggerType">A value from the LoggerTypes enum specifying the
        /// type of logger object to create.</param>
        /// <exception name="exception>Logger.ToFile type was specified but no filename was given.  Use Logger(const std::string&) instead.</exception>
        Logger(LoggerTypes loggerType);

        /// <summary>
        /// Constructor that creates a file logger.
        /// </summary>
        /// <param name="filename">Path to a file to create for the file logger.</param>
        Logger(const std::string& filename);

        /// Log trace messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void LogTrace(std::string message);

        /// <summary>
        /// Log informational messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void LogInfo(std::string message);

        /// <summary>
        /// Log error messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void LogError(std::string message);

    };

} // end namespace

#endif // __BRIDGE_LOGGER_H__

