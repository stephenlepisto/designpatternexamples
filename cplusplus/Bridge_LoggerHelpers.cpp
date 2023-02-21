// Posix way of asking for bounds-checked versions of library functions.
#define __STDC_WANT_LIB_EXT1__ 1
#include <chrono>
#include <sstream>
#include <iomanip>

#include "helpers/makelocaltime.h"
#include "Bridge_LoggerHelpers.h"

namespace // Anonymous
{

    /// <summary>
    /// Return a regular time stamp of the current time in local time.
    /// </summary>
    /// <returns>A string containing the current date and time expressed in
    /// local time.</returns>
    std::string _GetTimeStamp()
    {
        auto now_time = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now_time);
        struct tm local_time { 0 };
        char str[128] { '\0' };
        auto returnval = Helpers::makelocaltime(&now_time_t, &local_time);
        if (returnval != nullptr)
        {
            strftime(str, sizeof str, "%m/%d/%Y %r", &local_time);
        }
        return str;
    }

} // end anonymous



namespace DesignPatternExamples
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
            std::ostringstream output;
            output << timestamp << " [" << logLevel << "] " << msg;
            return output.str();
        }

    } // end namespace

} // end namespace
