/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::NullLogger "NullLogger"
/// class used in the @ref bridge_pattern.

#pragma once
#ifndef __BRIDGE_NULLLOGGER_H__
#define __BRIDGE_NULLLOGGER_H__

#include <memory>
#include "Bridge_LoggerInterface.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a logger that throws away anything sent its way.
    /// </summary>
    class NullLogger
    {
    public:
        /// <summary>
        /// Create an instance of a null logger, a logger that doesn't do anything.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        static std::unique_ptr<ILogger> CreateLogger();
    };

} // end namespace

#endif // __BRIDGE_NULLLOGGER_H__
