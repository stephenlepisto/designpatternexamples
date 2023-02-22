#include <iostream>
#include <fstream>

#include "Bridge_FileLogger.h"
#include "Bridge_LoggerHelpers.h"

namespace // Anonymous
{
    /// <summary>
    /// Represents a logger that throws away anything sent its way.
    /// </summary>
    class FileLoggerImpl : public DesignPatternExamples_cpp::ILogger
    {
    private:
        std::ofstream _outputFile;

    private:

        /// <summary>
        /// Write a formatted line to the log.
        /// </summary>
        /// <param name="logLevel">The level of the log detail.</param>
        /// <param name="msg">The message to log.</param>
        void _WriteLine(const std::string& logLevel, const std::string& msg)
        {
            if (_outputFile.is_open())
            {
                std::string output = DesignPatternExamples_cpp::LoggerHelpers::FormatLogLine(logLevel, msg);
                _outputFile << output << std::endl;
            }

        }

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        FileLoggerImpl(const std::string& filename)
        {
            if (!filename.empty())
            {
                _outputFile.open(filename.c_str(), std::ofstream::out);
                if (!_outputFile.is_open())
                {

                }
            }
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
    /// Create an instance of a console logger, which writes to a file.
    /// </summary>
    /// <returns>An instance of an ILogger object.</returns>
    std::unique_ptr<ILogger> FileLogger::CreateLogger(const std::string& filename)
    {
        return std::make_unique<FileLoggerImpl>(filename);
    }

} // end namespace
