// Helper functions for the various logger implementations used in the Bridge
// pattern example.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    /// <summary>
    /// Helper functions for all loggers.
    /// </summary>
    internal static class LoggerHelpers
    {
        /// <summary>
        /// Return a regular time stamp of the current time.
        /// </summary>
        /// <returns>A string containing the current date and time.</returns>
        private static string _GetTimeStamp()
        {
            return DateTime.Now.ToString();
        }

        /// <summary>
        /// Format a line for logging, including time stamp.
        /// </summary>
        /// <param name="logLevel">Level of logging (TRACE, INFO, ERROR)</param>
        /// <param name="msg">Message to log</param>
        /// <returns>The formatted string to log.</returns>
        public static string FormatLogLine(string logLevel, string msg)
        {
            string timestamp = _GetTimeStamp();
            string output = String.Format("{0} [{1}] {2}", timestamp, logLevel, msg);
            return output;
        }
    }
}
