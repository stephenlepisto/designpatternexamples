/// @file
/// @brief
/// Implementation of the Bridge_Exercise() function as used in the 
/// @ref bridge_pattern "Bridge pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Bridge_Exercise.h"
#include "Bridge_Logger.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// Helper function to show an example of writing to a logger.
    /// 
    /// This is called for all types of loggers, showing how the Logger
    /// class hides the details of the underlying implementation.
    /// </summary>
    /// <param name="logger">A Logger instance to log to</param>
    /// <param name="loggerType">The type of the underlying implementation.
    /// </param>
    void _Bridge_Exercise_Demonstrate_Logging(
        Logger& logger, std::string loggerType)
    {
        std::string output;
        output = std::format("Starting \"log to {}\" example", loggerType);
        logger.LogTrace(output);

        logger.LogInfo("An example of an informational line");
        logger.LogError("An example of an error log entry");

        output = std::format("Done with \"log to {}\" example", loggerType);
        logger.LogTrace(output);
    }

} // end anonymous namespace


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref bridge_pattern "Bridge" design pattern.
    /// 
    /// The Bridge pattern is used to allow a program to offer multiple
    /// ways to perform logging without changing how the logging is
    /// used throughout the program.
    ///
    /// In this exercise, note how the calls into the logger are the
    /// same regardless of the logger used.
    /// </summary>
    // ! [Using Bridge in C++]
    void Bridge_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Bridge Exercise" << std::endl;

        // Note: Use local contexts to automatically close the various loggers
        // when the loggers go out of scope.
        {
            Logger logger("Bridge.log"); // Logger::LoggerTypes::ToFile type
            std::cout << "  Example of writing to a log file..." << std::endl;
            _Bridge_Exercise_Demonstrate_Logging(logger, "file");
        }

        {
            Logger logger(Logger::LoggerTypes::ToConsole);
            std::cout << "  Example of writing to the console..." << std::endl;
            _Bridge_Exercise_Demonstrate_Logging(logger, "console");
        }

        {
            Logger logger(Logger::LoggerTypes::ToNull);
            std::cout << "  Example of writing to a Null object (no output)..."
                << std::endl;
            // Note: The resulting log lines will not be shown anywhere.
            _Bridge_Exercise_Demonstrate_Logging(logger, "null");
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Bridge in C++]

} // end namespace
