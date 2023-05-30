/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Bridge_Exercise "Bridge_Exercise"
/// class used in the @ref bridge_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref bridge_pattern in C#.
    /// 
    /// The Bridge pattern is used to allow a program to offer multiple
    /// ways to perform logging without changing how the logging is
    /// used throughout the program.
    ///
    /// In this exercise, note how the calls into the logger are the
    /// same regardless of the logger used.
    /// </summary>
    internal class Bridge_Exercise
    {
        /// <summary>
        /// Helper function to show an example of writing to a logger.
        /// 
        /// This is called for all types of loggers, showing how the Logger
        /// class hides the details of the underlying implementation.
        /// </summary>
        /// <param name="logger">A Logger instance to log to</param>
        /// <param name="loggerType">The type of the underlying implementation.</param>
        void _Bridge_Exercise_Demonstrate_Logging(Logger logger, string loggerType)
        {
            logger.LogTrace(String.Format("Starting log to {0} example", loggerType));
            logger.LogInfo("An example of an informational line");
            logger.LogError("An example of an error log entry");
            logger.LogTrace(String.Format("Done with log to {0} example", loggerType));
        }

        /// <summary>
        /// Executes the example for the @ref bridge_pattern in C#.
        /// </summary>
        // ! [Using Bridge in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Bridge Exercise");
            using (Logger logger = new Logger(Logger.LoggerTypes.ToFile, "Bridge.log"))
            {
                Console.WriteLine("  Example of writing to a log file...");
                _Bridge_Exercise_Demonstrate_Logging(logger, "file");
            }

            using (Logger logger = new Logger(Logger.LoggerTypes.ToConsole))
            {
                Console.WriteLine("  Example of writing to the console...");
                _Bridge_Exercise_Demonstrate_Logging(logger, "console");
            }

            using (Logger logger = new Logger(Logger.LoggerTypes.ToNull))
            {
                Console.WriteLine("  Example of writing to a Null object (no output)...");
                // Note: The resulting log lines will not be shown anywhere.
                _Bridge_Exercise_Demonstrate_Logging(logger, "null");
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Bridge in C#]
    }
}
