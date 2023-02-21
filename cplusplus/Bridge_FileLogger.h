#pragma once
#ifndef __BRIDGE_FILELOGGER_H__
#define __BRIDGE_FILELOGGER_H__

#include <memory>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples
{

    /// <summary>
    /// Represents a logger that writes logging to a file.
    /// </summary>
    namespace FileLogger
    {
        /// <summary>
        /// Create an instance of a console logger, which writes to a file.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        std::unique_ptr<ILogger> CreateLogger(const std::string& filename);
    }
} // end namespace

#endif // __BRIDGE_FILELOGGER_H__
