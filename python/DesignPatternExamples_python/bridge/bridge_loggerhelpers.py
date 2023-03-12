## @file
#  @brief
#  Implementation of the @ref DesignPatternExamples_python.bridge.bridge_loggerhelpers.LoggerHelpers.FormatLogLine "FormatLogLine"
#  function used in the @ref bridge_pattern "Bridge pattern".

from datetime import datetime

## Helper functions for all loggers.
class LoggerHelpers:
    ##  Return a regular time stamp of the current time in local time.
    #
    #  @returns
    #     A string containing the current date and time expressed in local time.
    def _GetTimeStamp() -> str:
        current_timestamp = datetime.now()
        return current_timestamp.strftime("%m/%d/%Y %I:%M:%S %p")


    ##  Format a line for logging, including time stamp.
    #
    #  @param logLevel
    #         Level of logging as a string (TRACE, INFO, ERROR)
    #  @param msg
    #         Message to log
    #  @returns
    #    The formatted string to log.
    def FormatLogLine(logLevel : str, msg : str) -> str:
        timestamp = LoggerHelpers._GetTimeStamp()
        return "{} [{}] {}".format(timestamp, logLevel, msg)
