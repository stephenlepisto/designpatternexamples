// The Bridge design pattern.  See Bridge_Logger.cs for the details.
//
// This is a specific implementation of a logger that logs to nowhere (all
// logging output is thrown away).  The logger is represented by the ILogger
// interface.

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
