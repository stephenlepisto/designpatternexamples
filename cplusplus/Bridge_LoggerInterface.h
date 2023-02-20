#pragma once
#ifndef __BRIDGE_LOGGERINTERFACE_H__
#define __BRIDGE_LOGGERINTERFACE_H__

#include <string>

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents an implementation of a logger object as call from the Logger class.
    /// </summary>
    struct ILogger
    {
        virtual ~ILogger() { }

        /// <summary>
        /// Log trace messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        virtual void LogTrace(const std::string& msg) = 0;

        /// <summary>
        /// Log informational messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        virtual void LogInfo(const std::string& msg) = 0;

        /// <summary>
        /// Log error messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        virtual void LogError(const std::string& msg) = 0;
    };

} // end namespace

#endif // __BRIDGE_LOGGERINTERFACE_H__

