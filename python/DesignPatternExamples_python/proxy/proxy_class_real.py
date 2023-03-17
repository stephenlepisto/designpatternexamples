## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.proxy.proxy_class_real.Real_Class "Real_Class"
#  class and the
#  @ref DesignPatternExamples_python.proxy.proxy_class_real.Real_Classes_Container "Real_Classes_Container"
#  class factory as used in the @ref proxy_pattern.

from .proxy_interface import IWorkByProxy

## The real class object that does all the work.
#
#  Note how this class implements the
#  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
#  interface, so as to match what the proxy can do.
#  
#  This would normally be a very expensive class to instantiate and/or
#  be running on the server end of a remoting channel.  For
#  demonstration purposes, imagine this class takes many seconds to
#  instantiate.
class Real_Class(IWorkByProxy):

    def __init__(self) -> None:
        pass

    #-------------------------------------------------
    # Implementation of the IWorkByProxy interface
    #-------------------------------------------------

    ## Do some work on a string.
    #
    #  @param someArgument
    #         A string to work on.
    #  @returns
    #     Returns a new string.
    def DoWork(self, someArgument : str) -> str:
        return "Real class received '{0}'".format(someArgument)


#========================================================================
#========================================================================


## A class factory for getting the real class.
#  
#  For the purposes of this example, this class hides the details about
#  the real class and the real class, exposing only the
#  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
#  interface of the proxy.  In a real program, the real class would be in
#  its own application/DLL/assembly and separate from the proxy class.
class Real_Classes_Container:
    
    ## Retrieve a new instance of the real class.
    #
    #  @returns
    #     An instance of a real class that implements the
    #     @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
    #     interface.
    def CreateReal() -> IWorkByProxy:
        return Real_Class()

## Control what will be exported from this module if the user were to use
#  `from proxy_class_real import *`
#  (Which no one really should be doing as it's bad form.)
__all__ = ["Real_Classes_Container"]
