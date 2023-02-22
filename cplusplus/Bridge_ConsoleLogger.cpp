#include <iostream>
#include "Bridge_LoggerHelpers.h"
#include "Bridge_ConsoleLogger.h"

namespace // Anonymous
{
    /// <summary>
    /// Represents a logger that throws away anything sent its way.
    /// </summary>
    class ConsoleLoggerImpl : public DesignPatternExamples_cpp::ILogger
    {
    private:

        /// <summary>
        /// Send a formatted line to the console.
        /// </summary>
        /// <param name="logLevel">The level of the log detail.</param>
        /// <param name="msg">The message to log.</param>
        void _WriteLine(const std::string& logLevel, const std::string& msg)
        {
            std::string output = DesignPatternExamples_cpp::LoggerHelpers::FormatLogLine(logLevel, msg);
            std::cout << output << std::endl;
        }

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        ConsoleLoggerImpl()
        {
        }

        // ILogger Members

        void LogTrace(const std::string& msg)
        {
            _WriteLine("TRACE", msg);
        }

        void LogInfo(const std::string& msg)
        {
            _WriteLine("INFO ", msg);
        }

        void LogError(const std::string& msg)
        {
            _WriteLine("ERROR", msg);
        }
    };

} // end anonymous namespace


namespace DesignPatternExamples_cpp
{
    /// <summary>
    /// Create an instance of a console logger, which writes to the standard
    /// output.
    /// </summary>
    /// <returns>An instance of an ILogger object.</returns>
    std::unique_ptr<ILogger> ConsoleLogger::CreateLogger()
    {
        return std::make_unique<ConsoleLoggerImpl>();
    }

} // end namespace
