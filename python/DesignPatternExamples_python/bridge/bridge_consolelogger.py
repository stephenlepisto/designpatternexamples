##  @file
#  @brief
#  The @ref DesignPatternExamples_python.bridge.bridge_consolelogger.ConsoleLogger "ConsoleLogger"
#  class as used in the @ref bridge_pattern.

from .bridge_loggerinterface import ILogger
from .bridge_loggerhelpers import LoggerHelpers


## Represents a logger that writes logging to the standard output.
class ConsoleLogger(ILogger):

    ##  Write a formatted line to the log.
    #
    #  @param logLevel
    #         The level of the log detail as a string.
    #  @param msg
    #         The message to log.
    def _WriteLine(self, logLevel : str, msg : str) -> None:
        formattedLine = LoggerHelpers.FormatLogLine(logLevel, msg)
        print(formattedLine)

    #-------------------------------------------------------------------------
    # ILogger interface implementation
    #-------------------------------------------------------------------------

    ## Close the logger and release resources
    #
    #  Call only if the Logger was not created in a `with` statement.
    def Close(self) -> None:
        pass

    ##  Log trace messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    def LogTrace(self, msg : str) -> None:
        self._WriteLine("TRACE", msg)

    ##  Log informational messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    def LogInfo(self, msg : str) -> None:
        self._WriteLine("INFO", msg)

    ##  Log error messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    def LogError(self, msg : str) -> None:
        self._WriteLine("ERROR", msg)


    #--------------------------------------------------------------------------
    # Class factory static method
    #--------------------------------------------------------------------------

    ##  Create an instance of a console logger, which writes to the standard
    #   output.
    #
    #  @returns
    #     An instance of an ILogger object.
    @staticmethod
    def CreateLogger() -> ILogger:
        return ConsoleLogger()
