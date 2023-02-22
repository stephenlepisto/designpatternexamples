// The Bridge design pattern is used to separate the implementation from the
// abstract interface presented to the caller.  This is also colloquially
// known as the "pimpl" pattern, since the abstract interface forwards all
// method calls to an underlying implementation via a "pointer to the
// implementation" or "pimpl".
//
// The Bridge pattern separates the abstraction from the implementation so
// that both abstraction and, more importantly, implementation can vary
// without affecting the other side of the bridge.  The Bridge pattern is not
// limited to a single class with one or more implementations.  The abstract
// side can have a hierarchy of classes inheriting from a base abstraction.
// The implementation side can also have a parallel hierarchy of inherited
// classes.
//
// The key idea is the caller is presented with an abstract class that knows
// how to create a specific implementation based on input from the caller.
// The definition of the implementation is completely hidden from the caller,
// who sees only the abstract class.
//
// That abstract class must be a class since it must contain some kind of
// reference to the underlying implementation.
//
// In this example, the Logger class is what the program uses for all logging.
// The program logs information at various levels of granularity to some
// output.  The program doesn't care where the logged output ends up.
//
// The Logger abstract class can make use of three different implementations
// of loggers: File, Console, Null.  Each of these loggers implements the
// ILogger interface so the Logger object doesn't have to care about the
// implementation details.  And the user of the Logger class has no idea of
// how the Logger class does what it does, only that it provides the same
// methods regardless of the actual implementation.
//
// In this way, the Logger class is the bridge between the program and the
// logger implementations.
//
// Note: The Bridge_NullLogger is an example of the Null Object pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents the logger object to be used in the program.
    /// </summary>
    /// <remarks>This class wraps different implementations of loggers to show
    /// the Bridge pattern.</remarks>
    internal class Logger : IDisposable
    {
        ILogger _logger;

        /// <summary>
        /// Constructor that takes an ILogger object to delegate to.
        /// </summary>
        /// <param name="logger">An ILogger object.</param>
        public Logger(ILogger logger)
        {
            _logger = logger;
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
    }


    /// <summary>
    /// Represents the class factory for the Logger class.
    /// </summary>
    internal static class LoggerClassFactory
    {
        /// <summary>
        /// A value passed to LoggerClassFactory.CreateLogger() to specify the type of
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
        /// Create an instance of the Logger object with the specified logger type.
        /// </summary>
        /// <param name="loggerType">A value from the LoggerTypes enum specifying the
        /// type of logger object to create.</param>
        /// <param name="argument">An additional argument that some logger types require.
        /// For example, a file logger requires a filename.</param>
        /// <returns></returns>
        internal static Logger CreateLogger(LoggerTypes loggerType, string argument)
        {
            ILogger logger = null;

            switch(loggerType)
            {
                case LoggerTypes.ToNull:
                    logger = NullLogger.CreateNullLogger();
                    break;

                case LoggerTypes.ToConsole:
                    logger = ConsoleLogger.CreateConsoleLogger();
                    break;

                case LoggerTypes.ToFile:
                    logger = FileLogger.CreateFileLogger(argument);
                    break;

                default:
                    break;
            }

            return new Logger(logger);
        }

        /// <summary>
        /// Create an instance of the Logger object with the specified logger type.
        /// </summary>
        /// <param name="loggerType">A value from the LoggerTypes enum specifying the
        /// type of logger object to create.</param>
        /// <returns></returns>
        internal static Logger CreateLogger(LoggerTypes loggerType)
        {
            return CreateLogger(loggerType, null);
        }
    }
}
