#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "Bridge_LoggerHelpers.h"

namespace // Anonymous
{

    /// <summary>
    /// Return a regular time stamp of the current time.
    /// </summary>
    /// <returns>A string containing the current date and time.</returns>
    std::string _GetTimeStamp()
    {
        auto now_time = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now_time);
        struct tm local_time { 0 };
#ifdef _MSC_VER
        errno_t err = localtime_s(&local_time, &now_time_t);
#elif defined(__STDC_LIB_EXT1__)
        localtime_s(&now_time_t, &local_time);
#else
        localtime_r(&now_time_t, &local_Time)
#endif
        char str[128]{ '\0'};
        if (err == 0)
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
