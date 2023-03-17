## @file
#  @brief
#  Declaration of the
#  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
#  interface as used in the @ref proxy_pattern.

from abc import ABC, abstractmethod


## Represents what can be done on the proxy object.
#  This same interface is implemented on the real object as well to
#  ensure both have the same methods.  The program accesses the
#  proxy object only through this interface.
class IWorkByProxy(ABC):

    ## Does some work on the given argument and returns a new string.
    #
    #  @param someArgument
    #         A string to be worked on.
    #  @returns
    #     A string containing the given argument string.
    @abstractmethod
    def DoWork(self, someArgument : str) -> str:
        pass

