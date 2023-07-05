/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::ConsoleLogger "ConsoleLogger"
/// class used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_CONSOLELOGGER_H__
#define __BRIDGE_CONSOLELOGGER_H__

#include <memory>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a logger that writes logging to the standard output.
    /// </summary>
    class ConsoleLogger
    {
    public:
        /// <summary>
        /// Create an instance of a console logger, which writes to the standard
        /// output.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        static std::unique_ptr<ILogger> CreateLogger();
    };

} // end namespace

#endif // __BRIDGE_CONSOLELOGGER_H__

