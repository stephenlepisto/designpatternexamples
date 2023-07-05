/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Logger "Logger"
/// class used in the @ref bridge_pattern.

#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <cstdarg>

#include "Bridge_Logger.h"
#include "Bridge_ConsoleLogger.h"
#include "Bridge_FileLogger.h"
#include "Bridge_NullLogger.h"


namespace DesignPatternExamples_cpp
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
        throw std::runtime_error("A filename must be specified for the Logger.ToFile logger type.  Please use Logger::Logger(const std::string&) constructor instead.");

    default:
        {
            std::ostringstream msg;
            msg << "The logger type '" << loggerType << "' is not recognized.  Cannot construct a Logger.";
            throw std::runtime_error(msg.str().c_str());
        }
    }
}


//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
Logger::Logger(const std::string& filename)
{
    _logger = FileLogger::CreateLogger(filename);
}


//////////////////////////////////////////////////////////////////////////////
// LogTrace
//////////////////////////////////////////////////////////////////////////////
void Logger::LogTrace(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogTrace(message);
    }
}

//////////////////////////////////////////////////////////////////////////////
// LogInfo
//////////////////////////////////////////////////////////////////////////////
void Logger::LogInfo(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogInfo(message);
    }
}

//////////////////////////////////////////////////////////////////////////////
// LogError
//////////////////////////////////////////////////////////////////////////////
void Logger::LogError(std::string message)
{
    if (_logger != nullptr)
    {
        _logger->LogError(message);
    }
}

} // end namespace
