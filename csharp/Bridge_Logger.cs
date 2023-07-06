/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Logger "Logger" class as used in the
/// @ref bridge_pattern "Bridge pattern".

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents the logger object to be used in the program.
    /// </summary>
    /// <remarks>This class wraps different implementations of loggers to show
    /// the @ref bridge_pattern.</remarks>
    internal class Logger : IDisposable
    {
        /// <summary>
        /// A value passed to Logger.Logger() constructor to specify the type of
        /// logger to create.
        /// </summary>
        public enum LoggerTypes
        {
            /// <summary>
            /// Log to nowhere, that is, throw out all logging.  No additional parameters.
            /// </summary>
            ToNull,

            /// <summary>
            /// Log to a file.  One additional parameter: the name of the file to log to.
            /// </summary>
            ToFile,

            /// <summary>
            /// Log to the console.  No additional parameters.
            /// </summary>
            ToConsole
        }

        /// <summary>
        /// Constructor that takes a LoggerTypes value and optional arguments to
        /// create a new Logger class.
        /// </summary>
        /// <param name="loggerType">A value from the LoggerTypes enum specifying the
        /// type of logger object to create.</param>
        /// <param name="arguments">Zero or more additional arguments that some logger types require.
        /// For example, a file logger requires a filename.</param>
        public Logger(LoggerTypes loggerType, params string[] arguments)
        {
            _logger = null;
            switch (loggerType)
            {
                case LoggerTypes.ToNull:
                    _logger = NullLogger.CreateNullLogger();
                    break;

                case LoggerTypes.ToConsole:
                    _logger = ConsoleLogger.CreateConsoleLogger();
                    break;

                case LoggerTypes.ToFile:
                    {
                        if (arguments != null && arguments.Length >= 1)
                        {
                            _logger = FileLogger.CreateFileLogger(arguments[0]);
                        }
                        else
                        {
                            string msg = String.Format("A filename must be specified for the {0} logger type.", loggerType);
                            throw new ArgumentException(msg, "arguments");
                        }
                    }
                    break;

                default:
                    {
                        string msg = String.Format("The logger type '{0}' is not recognized.  Cannot construct a Logger.", loggerType);
                        throw new ArgumentException(msg, "loggerType");
                    }
            }
        }


        /// <summary>
        /// Log trace messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        public void LogTrace(string message)
        {
            if (_logger != null)
            {
                _logger.LogTrace(message);
            }
        }

        /// <summary>
        /// Log informational messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        public void LogInfo(string message)
        {
            if (_logger != null)
            {
                _logger.LogInfo(message);
            }
        }

        /// <summary>
        /// Log error messages to the configured output.
        /// </summary>
        /// <param name="message">The message to log.</param>
        public void LogError(string message)
        {
            if (_logger != null)
            {
                _logger.LogError(message);
            }
        }

        #region IDisposable Members

        /// <summary>
        /// Dispose of this logger object in a friendly way.
        /// </summary>
        void IDisposable.Dispose()
        {
            if (_logger != null)
            {
                if (_logger is IDisposable)
                {
                    ((IDisposable)_logger).Dispose();
                }
            }
        }

        #endregion

        /// <summary>
        /// The logger implementation represented by the ILogger interface.
        /// </summary>
        private ILogger _logger;
    }

}
