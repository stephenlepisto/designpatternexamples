/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::LoggerHelpers "LoggerHelpers"
/// namespace functions used in the @ref bridge_pattern "Bridge pattern".

#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif

#include <format> // Requires C++20

// Posix way of asking for bounds-checked versions of library functions.
#define __STDC_WANT_LIB_EXT1__ 1
#include <chrono>

#include "helpers/DateTime.h"
#include "Bridge_LoggerHelpers.h"
using Helpers::DateTime;

namespace // Anonymous
{

    /// <summary>
    /// Return a regular time stamp of the current time in local time.
    /// </summary>
    /// <returns>A string containing the current date and time expressed in
    /// local time.</returns>
    std::string _GetTimeStamp()
    {
        return DateTime::Now().ToString();
    }

} // end anonymous



namespace DesignPatternExamples_cpp
{

    namespace LoggerHelpers
    {
        /// <summary>
        /// Format a line for logging, including time stamp.
        /// </summary>
        /// <param name="logLevel">Level of logging (TRACE, INFO, ERROR)</param>
        /// <param name="msg">Message to log</param>
        /// <returns>The formatted string to log.</returns>
        std::string FormatLogLine(const std::string& logLevel, const std::string& msg)
        {
            std::string timestamp = _GetTimeStamp();
            return std::format("{} [{}] {}", timestamp, logLevel, msg);
        }

    } // end namespace

} // end namespace
