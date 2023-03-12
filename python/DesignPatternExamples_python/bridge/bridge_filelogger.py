##  @file
#  @brief
#  The @ref DesignPatternExamples_python.bridge.bridge_filelogger.FileLogger "FileLogger"
#  class as used in the @ref bridge_pattern "Bridge pattern".

from .bridge_loggerinterface import ILogger
from .bridge_loggerhelpers import LoggerHelpers

##  Represents a logger that writes its output to a file.
class FileLogger(ILogger):
    
    ## Constructor
    #
    # @param filename
    #        Name of the file to which to write log output.
    def __init__(self, filename : str) -> None:
        self._filename = filename
        self._file = open(filename, mode="w")

    ## @var _filename
    #       Name of the file to which to write log output
    #  @var _file
    #       File object to which to write log output

    ##  Write a formatted line to the log.
    #
    #  @param logLevel
    #         The level of the log detail as a string.
    #  @param msg
    #         The message to log.
    def _WriteLine(self, logLevel : str, msg : str) -> None:
        if self._file:
            formattedLine = LoggerHelpers.FormatLogLine(logLevel, msg)
            self._file.write("{}\n".format(formattedLine))

    #-------------------------------------------------------------------------
    # ILogger interface implementation
    #-------------------------------------------------------------------------

    ## Close the logger and release resources
    #
    #  Call only if the Logger was not created in a `with` statement.
    def Close(self) -> None:
        if self._file:
            self._file.close()
            self._file = None

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

    ##  Create an instance of a file logger, which writes to a file.
    #
    #  @returns
    #     An instance of an ILogger object.
    @staticmethod
    def CreateLogger(filename : str) -> ILogger:
        return FileLogger(filename)

