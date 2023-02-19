// The Logger class acts as the Bridge between the program and the logger
// implementations.  The logger implementations implement the ILogger interface
// so the Logger class doesn't know about the actual implementation of the
// logger.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents an implementation of a logger object as call from the Logger class.
    /// </summary>
    internal interface ILogger
    {
        /// <summary>
        /// Log trace messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        void LogTrace(string msg);

        /// <summary>
        /// Log informational messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        void LogInfo(string msg);

        /// <summary>
        /// Log error messages to the configured output.
        /// </summary>
        /// <param name="msg">The message to log.</param>
        void LogError(string msg);
    }
}
