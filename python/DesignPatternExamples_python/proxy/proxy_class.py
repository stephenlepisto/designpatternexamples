## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.proxy.proxy_class.Proxy_Class "Proxy_Class"
#  class and the
#  @ref DesignPatternExamples_python.proxy.proxy_class.Proxy_Classes_Container "Proxy_Classes_Container"
#  class factory as used in the @ref proxy_pattern.

from .proxy_interface import IWorkByProxy
from .proxy_class_real import Real_Classes_Container

## The proxy class that implements the
#  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
#  interface.
#
#  This is the stand-in for the real class that might be on a different server
#  or might be really expensive to create so it should be created only when
#  needed.  This proxy hides the details of creating the real class.
class Proxy_Class(IWorkByProxy):

    ## Constructor
    def __init__(self) -> None:
        self._realClassInstance = None # type: IWorkByProxy

    ## @var _realClassInstance
    #  The one and only instance of the real class associated with
    #  this proxy class instance.


    ## Helper method to retrieve the one and only instance of the
    #  real class.  This hides the details of instantiating the real
    #  class.
    #
    #  @returns
    #     A single instance of the real class represented by
    #  the
    #  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
    #  interface.
    def _GetRealClass(self) -> IWorkByProxy:
        if not self._realClassInstance:
            print("  --> Creating instance of real class...")
            self._realClassInstance = Real_Classes_Container.CreateReal()
        return self._realClassInstance


    #-------------------------------------------------
    # Implementation of the IWorkByProxy interface
    #-------------------------------------------------

    ## Do some work on a string.
    #
    #  The real class this proxy represents is not instantiated until
    #  this method is called even though the proxy class has been
    #  instantiated.  When this method is called for the first time,
    #  the real class is instantiated, incurring a performance penalty
    #  only on the first call.
    #
    #  @param someArgument
    #         A string to work on.
    #  @returns
    #     Returns a new string.
    def DoWork(self, someArgument : str) -> str:
        print("  --> proxy class DoWork() in")
        realClass = self._GetRealClass()
        print("  --> Forwarding DoWork() call to real class...")
        return realClass.DoWork(someArgument)


#========================================================================
#========================================================================


## A class factory for getting the proxy.
#  
#  For the purposes of this example, this class hides the details about
#  the proxy class and the real class, exposing only the
#  @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
#  interface of the proxy.  In a real program, the real class would be in
#  its own application/DLL/assembly and separate from the proxy class.
class Proxy_Classes_Container:
    
    ## Retrieve a new instance of the proxy class.
    #
    #  @returns
    #     An instance of a proxy class that implements the
    #     @ref DesignPatternExamples_python.proxy.proxy_interface.IWorkByProxy "IWorkByProxy"
    #     interface.
    def CreateProxy() -> IWorkByProxy:
        return Proxy_Class()


## Control what will be exported from this module if the user were to use
#  `from proxy_class import *`
#  (Which no one really should be doing as it's bad form.)
__all__ = ["Proxy_Classes_Container"]
