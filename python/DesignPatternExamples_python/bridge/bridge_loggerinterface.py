##  @file
#  @brief
#  The @ref DesignPatternExamples_python.bridge.bridge_loggerinterface.ILogger "ILogger"
#  interface as used in the @ref bridge_pattern.

from abc import ABC, abstractmethod


##  Represents an implementation of a logger object as called from the
#   @ref DesignPatternExamples_python.bridge.bridge_logger.Logger "Logger" class.
class ILogger(ABC):

    ## Close the logger and release resources
    #
    #  Call only if the Logger was not created in a `with` statement.
    @abstractmethod
    def Close(self) -> None:
        pass

    ##  Log trace messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    @abstractmethod
    def LogTrace(self, msg : str) -> None:
        pass

    ##  Log informational messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    @abstractmethod
    def LogInfo(self, msg : str) -> None:
        pass

    ##  Log error messages to the configured output.
    #
    #  @param msg
    #         The message to log.
    @abstractmethod
    def LogError(self, msg : str) -> None:
        pass
