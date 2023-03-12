##  @file
#  @brief
#  The @ref DesignPatternExamples_python.bridge.bridge_nulllogger.NullLogger "NullLogger"
#  class as used in the @ref bridge_pattern.

from .bridge_loggerinterface import ILogger

## Represents a logger that throws away anything sent its way.
class NullLogger(ILogger):
    
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
        pass

    ##  Log informational messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    def LogInfo(self, msg : str) -> None:
        pass

    ##  Log error messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    def LogError(self, msg : str) -> None:
        pass


    #--------------------------------------------------------------------------
    # Class factory static method
    #--------------------------------------------------------------------------

    ##  Create an instance of a null logger, a logger that doesn't do anything.
    #
    #  @returns
    #     An instance of an ILogger object.
    @staticmethod
    def CreateLogger() -> ILogger:
        return NullLogger()

