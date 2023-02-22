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
    
    /// <summary>
    /// Create an instance of a null logger, a logger that doesn't do anything.
    /// </summary>
    /// <returns>An instance of an ILogger object.</returns>
    std::unique_ptr<ILogger> NullLogger::CreateLogger()
    {
        return std::make_unique<NullLoggerImpl>();
    }
    
} // end namespace
