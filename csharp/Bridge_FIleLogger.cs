// The Bridge design pattern.  See Bridge_Logger.cs for the details.
//
// This is a specific implementation of a logger that logs to a file.
// The logger is represented by the ILogger interface.

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
        /// Constructor.  If successful, the file is opened for writing.
        /// </summary>
        /// <param name="filename">Name of file to log to.</param>
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
            if (_outputFile != null)
            {
                string output = LoggerHelpers.FormatLogLine(logLevel, msg);
                _outputFile.WriteLine(output);
            }

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
                if (_outputFile != null)
                {
                    _outputFile.Close();
                    _outputFile = null;
                }
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
