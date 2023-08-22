/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.FileLogger "FileLogger" class as used
/// in the @ref bridge_pattern "Bridge pattern".

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a logger to a file.
    /// </summary>
    internal class FileLogger : ILogger, IDisposable
    {
        StreamWriter _outputFile;
        bool _disposed;

        /// <summary>
        /// Constructor.  If successful, the file is opened for writing.  Raises
        /// an exception if the output file cannot be created.
        /// </summary>
        /// <param name="filename">Name of file to log to.</param>
        /// <exception cref="UnauthorizedAccessException">
        /// "The caller does not have the required permission.",
        /// "path specified a file that is read-only.", or
        /// "path specified a file that is hidden."</exception>
        /// <exception cref="ArgumentException">path is a zero-length string,
        /// contains only white space, or contains one or more invalid characters.</exception>
        /// <exception cref="ArgumentNullException">path is null.</exception>
        /// <exception cref="PathTooLongException">The specified path, file name,
        /// or both exceed the system-defined maximum length.</exception>
        /// <exception cref="DirectoryNotFoundException">The specified path is
        /// invalid (for example, it is on an unmapped drive).</exception>
        /// <exception cref="NotSupportedException">path is in an invalid format.</exception>
        public FileLogger(string filename)
        {
            _outputFile = File.CreateText(filename);
        }

        
        /// <summary>
        /// Write a formatted line to the log.
        /// </summary>
        /// <param name="logLevel">The level of the log detail.</param>
        /// <param name="msg">The message to log.</param>
        private void _WriteLine(string logLevel, string msg)
        {
            string output = LoggerHelpers.FormatLogLine(logLevel, msg);
            _outputFile.WriteLine(output);
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
        /// Close the log file gracefully.
        /// </summary>
        void IDisposable.Dispose()
        {
            if (!_disposed)
            {
                _outputFile.Close();
                _disposed = true;
            }
        }

        #endregion


        /// <summary>
        /// Create an instance of a file logger.
        /// </summary>
        /// <param name="filename">The filename to log to.</param>
        /// <returns>An instance of an ILogger object.</returns>
        public static ILogger CreateFileLogger(string filename)
        {
            return new FileLogger(filename);
        }
    }
}
