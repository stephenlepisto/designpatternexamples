##  @file
#  @brief
#  The @ref DesignPatternExamples_python.bridge.bridge_logger.Logger "Logger"
#  bridge class as used in the @ref bridge_pattern.

from enum import Enum
from .bridge_loggerinterface import ILogger
from .bridge_filelogger import FileLogger
from .bridge_consolelogger import ConsoleLogger
from .bridge_nulllogger import NullLogger

##  Represents the bridge logger object to be used in the program.
#
#  This class wraps different implementations of loggers to show
#  the @ref bridge_pattern.
class Logger(ILogger):

    ##  A value passed to LoggerClassFactory.CreateLogger() to specify the type of
    #  logger to create.
    class LoggerTypes(Enum):
        ##  Log to nowhere, that is, throw out all logging.  No additional parameters.
        ToNull = 0,

        ##  Log to a file.  One additional parameter: the name of the file to log to.
        ToFile = 1,

        ##  Log to the console.  No additional parameters.
        ToConsole = 2


    ## Constructor that takes a LoggerTypes value and optional arguments to
    #  create a new Logger class.
    #
    #  @param loggerType
    #         A value from the LoggerTypes enum specifying the type of logger
    #         object to create.
    #  @param arguments
    #         Zero or more additional arguments that some logger types require.
    #         For example, a file logger requires a filename.
    def __init__(self, loggerType : LoggerTypes, *arguments):
        self._logger = None
        match (loggerType):
            case Logger.LoggerTypes.ToNull:
                self._logger = NullLogger.CreateLogger()

            case Logger.LoggerTypes.ToConsole:
                self._logger = ConsoleLogger.CreateLogger()

            case Logger.LoggerTypes.ToFile:
                if arguments:
                    self._logger = FileLogger.CreateLogger(arguments[0])
                else:
                    msg = "A filename must be specified for the {0} logger type.".format(loggerType)
                    raise ValueError(msg)

            case _: # default
                msg = "The logger type '{0}' is not recognized.  Cannot construct a Logger.".format(loggerType)
                raise ValueError(msg)

    ## @var _logger
    #       Instance of the desired logger type

    ## Entry function used in the `with` statement to initialize an instance
    #  of the reader/writer.
    def __enter__(self):
        return self


    ## Exit function automatically called when used in the `with` statement.
    def __exit__(self, *args):
        if self._logger:
            self._logger.Close()
            self._logger = None

    #-------------------------------------------------------------------------
    # ILogger interface implementation
    #-------------------------------------------------------------------------

    ## Close the logger and release resources
    #
    #  Call only if the Logger was not created in a `with` statement.
    def Close(self):
        if self._logger:
            self._logger.Close()
            self._logger = None

    ##  Log trace messages to the configured output.
    #
    #  @param message
    #         The message to log.
    def LogTrace(self, message : str):
        if self._logger:
            self._logger.LogTrace(message)



    ##  Log informational messages to the configured output.
    #
    #  @param message
    #         The message to log.
    def LogInfo(self, message : str):
        if self._logger:
            self._logger.LogInfo(message)


    ##  Log error messages to the configured output.
    #
    #  @param message
    #         The message to log.
    def LogError(self, message : str):
        if self._logger:
            self._logger.LogError(message)


