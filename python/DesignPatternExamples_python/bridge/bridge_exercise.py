## @file
# @brief
# Implementation of the Bridge_Exercise() function as used in the 
# @ref bridge_pattern "Bridge pattern".

from .bridge_logger import Logger

##  Helper function to show an example of writing to a logger.
#  
#  This is called for all types of loggers, showing how the Logger
#  class hides the details of the underlying implementation.
#
#  @param logger
#         A Logger instance to log to
#  @param loggerType
#         The type of the underlying implementation.
def _Bridge_Exercise_Demonstrate_Logging(logger : Logger, loggerType : str) -> None:
    logger.LogTrace("Starting log to {0} example".format(loggerType))
    logger.LogInfo("An example of an informational line")
    logger.LogError("An example of an error log entry")
    logger.LogTrace("Done with log to {0} example".format(loggerType))


## Example of using the @ref bridge_pattern "Bridge" design pattern.
# 
# The Bridge pattern is used to allow a program to offer multiple
# ways to perform logging without changing how the logging is
# used throughout the program.
#
# In this exercise, note how the calls into the logger are the
# same regardless of the logger used.

# ! [Using Bridge in Python]
def Bridge_Exercise():
    print()
    print("Bridge Exercise")

    with Logger(Logger.LoggerTypes.ToFile, "Bridge.log") as logger:
        print("  Example of writing to a log file...")
        _Bridge_Exercise_Demonstrate_Logging(logger, "file")

    with Logger(Logger.LoggerTypes.ToConsole) as logger:
        print("  Example of writing to the console...")
        _Bridge_Exercise_Demonstrate_Logging(logger, "console")

    with Logger(Logger.LoggerTypes.ToNull) as logger:
        print("  Example of writing to a Null object (no output)...")
        # Note: The resulting log lines will not be shown anywhere.
        _Bridge_Exercise_Demonstrate_Logging(logger, "null")

    print("  Done.")
# ! [Using Bridge in Python]
