#pragma once
#ifndef __BRIDGE_LOGGERHELPERS_H__
#define __BRIDGE_LOGGERHELPERS_H__

#include <string>

namespace DesignPatternExamples
{

    /// <summary>
    /// Helper functions for all loggers.
    /// </summary>
    namespace LoggerHelpers
    {

        /// <summary>
        /// Format a line for logging, including time stamp.
        /// </summary>
        /// <param name="logLevel">Level of logging (TRACE, INFO, ERROR)</param>
        /// <param name="msg">Message to log</param>
        /// <returns>The formatted string to log.</returns>
        std::string FormatLogLine(const std::string& logLevel, const std::string& msg);

    } // end namespace

} // end namespace

#endif // __BRIDGE_LOGGERHELPERS_H__

