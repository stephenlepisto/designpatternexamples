/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.ConsoleLogger "ConsoleLogger" class
/// as used in the @ref bridge_pattern "Bridge pattern".

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a logger that writes to the console window.
    /// </summary>
    internal class ConsoleLogger : ILogger, IDisposable
    {
        private bool _disposed;

        /// <summary>
        /// Constructor.
        /// </summary>
        private ConsoleLogger()
        {
        }


        /// <summary>
        /// Send a formatted line to the console.
        /// </summary>
        /// <param name="logLevel">The level of the log detail.</param>
        /// <param name="msg">The message to log.</param>
        private void _WriteLine(string logLevel, string msg)
        {
            string output = LoggerHelpers.FormatLogLine(logLevel, msg);
            Console.WriteLine(output);
        }



        #region ILogger Members

        void ILogger.LogTrace(string msg)
        {
            _WriteLine("TRACE", msg);
        }

        void ILogger.LogInfo(string msg)
        {
            _WriteLine("INFO ", msg);
        }

        void ILogger.LogError(string msg)
        {
            _WriteLine("ERROR", msg);
        }

        #endregion

        #region IDisposable Members

        /// <summary>
        /// Shut down the logger gracefully (in this case, nothing really needs to be done).
        /// </summary>
        void IDisposable.Dispose()
        {
            if (!_disposed)
            {
                _disposed = true;
            }
        }

        #endregion


        /// <summary>
        /// Create an instance of a console logger, where logging goes to the console.
        /// </summary>
        /// <returns>An instance of an ILogger object.</returns>
        public static ILogger CreateConsoleLogger()
        {
            return new ConsoleLogger();
        }
    }
}
