/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::NullLogger "NullLogger"
/// class factory used in the @ref bridge_pattern.

#include "Bridge_NullLogger.h"

namespace // Anonymous
{
    /// <summary>
    /// Represents a logger that throws away anything sent its way.
    /// </summary>
    class NullLoggerImpl : public DesignPatternExamples_cpp::ILogger
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        NullLoggerImpl()
        {
        }

        // ILogger Members

        void LogTrace(const std::string&)
        {
        }

        void LogInfo(const std::string&)
        {
        }

        void LogError(const std::string&)
        {
        }
    };

} // end anonymous namespace


namespace DesignPatternExamples_cpp
{
    
    std::unique_ptr<ILogger> NullLogger::CreateLogger()
    {
        return std::make_unique<NullLoggerImpl>();
    }
    
} // end namespace
