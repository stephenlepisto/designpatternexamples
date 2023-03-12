/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::FileLogger "FileLogger"
/// class used in the @ref bridge_pattern "Bridge pattern".

#pragma once
#ifndef __BRIDGE_FILELOGGER_H__
#define __BRIDGE_FILELOGGER_H__

#include <memory>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a logger that writes logging to a file.
    /// </summary>
    class FileLogger
    {
    public:
        /// <summary>
        /// Create an instance of a file logger, which writes to a file.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        static std::unique_ptr<ILogger> CreateLogger(const std::string& filename);
    };

} // end namespace

#endif // __BRIDGE_FILELOGGER_H__

