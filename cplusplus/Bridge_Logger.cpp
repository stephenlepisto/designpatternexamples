#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <cstdarg>

#include "Bridge_Logger.h"
#include "Bridge_ConsoleLogger.h"
#include "Bridge_FileLogger.h"
#include "Bridge_NullLogger.h"


namespace DesignPatternExamples
{

/// <summary>
/// Constructor that takes a LoggerTypes value to create a logger.
/// </summary>
/// <param name="loggerType">A value from the LoggerTypes enum specifying the
/// type of logger object to create.</param>
Logger::Logger(LoggerTypes loggerType)
    : _logger(nullptr)
{

    switch (loggerType)
    {
    case LoggerTypes::ToNull:
        _logger = NullLogger::CreateLogger();
        break;

    case LoggerTypes::ToConsole:
        _logger = ConsoleLogger::CreateLogger();
        break;

    case LoggerTypes::ToFile:
        throw std::exception("A filename must be specified for the Logger.ToFile logger type.  Please use Logger::Logger(const std::string&) constructor instead.");

    default:
        {
            std::ostringstream msg;
            msg << "The logger type '" << loggerType << "' is not recognized.  Cannot construct a Logger.";
            throw std::exception(msg.str().c_str());
        }
    }
}


/// <summary>
/// Constructor that creates a file logger.
/// </summary>
/// <param name="filename">Path to a file to create for the file logger.</param>
Logger::Logger(const std::string& filename)
{
    _logger = FileLogger::CreateLogger(filename);
}


/// <summary>
/// Log trace messages to the configured output.
/// </summary>
/// <param name="message">The message to log.</param>
void Logger::LogTrace(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogTrace(message);
    }
}

/// <summary>
/// Log informational messages to the configured output.
/// </summary>
/// <param name="message">The message to log.</param>
void Logger::LogInfo(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogInfo(message);
    }
}

/// <summary>
/// Log error messages to the configured output.
/// </summary>
/// <param name="message">The message to log.</param>
void Logger::LogError(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogError(message);
    }
}

} // end namespace
