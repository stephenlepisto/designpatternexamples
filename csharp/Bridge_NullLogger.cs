/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.NullLogger "NullLogger"
/// class as used in the @ref bridge_pattern "Bridge pattern".

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a logger that throws away anything sent its way.
    /// </summary>
    internal class NullLogger : ILogger, IDisposable
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        private NullLogger()
        {
        }


        #region ILogger Members

        void ILogger.LogTrace(string msg)
        {
        }

        void ILogger.LogInfo(string msg)
        {
        }

        void ILogger.LogError(string msg)
        {
        }

        #endregion

        #region IDisposable Members

        /// <summary>
        /// Nothing to do for a graceful shutdown.
        /// </summary>
        void IDisposable.Dispose()
        {
        }

        #endregion


        /// <summary>
        /// Create an instance of a null logger, a logger that doesn't do anything.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        public static ILogger CreateNullLogger()
        {
            return new NullLogger();
        }
    }
}
