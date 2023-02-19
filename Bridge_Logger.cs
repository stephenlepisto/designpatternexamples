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
//
// An alternative implementation would use a class factory method to take
// the LoggerType and optional parameter as arguments and return an actual
// implementation represented by the ILogger class.  This eliminates the need
// for a bridge class altogether and completely hides any details of the
// implementation.
//
// Basically, the use of an interface and a class factory can hide any
// implementation and it works in any programming language that supports the
// idea of a base class or interface.

using System;

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents the logger object to be used in the program.
    /// </summary>
    /// <remarks>This class wraps different implementations of loggers to show
    /// the Bridge pattern.</remarks>
    internal class Logger : IDisposable
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

        private ILogger _logger;
    }

}
