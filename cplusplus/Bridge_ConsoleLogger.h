#pragma once
#ifndef __BRIDGE_CONSOLELOGGER_H__
#define __BRIDGE_CONSOLELOGGER_H__

#include <memory>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples
{

    /// <summary>
    /// Represents a logger that writes logging to the standard output.
    /// </summary>
    namespace ConsoleLogger
    {
        /// <summary>
        /// Create an instance of a console logger, which writes to the standard
        /// output.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        std::unique_ptr<ILogger> CreateLogger();
    }
} // end namespace

#endif // __BRIDGE_CONSOLELOGGER_H__

