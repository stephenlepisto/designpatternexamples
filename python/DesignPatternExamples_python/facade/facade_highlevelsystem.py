## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.facade.facade_highlevelsystem.DeviceNetworkHighLevel "DeviceNetworkHighLevel"
#  class, along with the
#  @ref DesignPatternExamples_python.facade.facade_highlevelsystem.CreateHighLevelInstance "CreateHighLevelInstance"()
#  class factory representing the high-level system used in the @ref facade_pattern "Facade pattern".

from .facade_interface import IDeviceNetworkHighLevel
from .facadesubsystem_interface import IDeviceNetworkLowLevel
from .facade_complicatedsubsystem import CreateLowLevelInstance

## This class wraps the
#  @ref DesignPatternExamples_python.facade.facadesubsystem_interface.IDeviceNetworkLowLevel "IDeviceNetworkLowLevel"
#  interface and implements the high level
#  @ref DesignPatternExamples_python.facade.facade_interface.IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
#  interface, which is a simpler interface.  All calls on the high level
#  interface are forwarded to the appropriate low level interface.
#  Part of the @ref facade_pattern example.
class DeviceNetworkHighLevel(IDeviceNetworkHighLevel):

    ## Constructor.
    #
    #  @param system
    #         The IDeviceNetworkLowLevel object to be wrapped by this class.
    def __init__(self, system : IDeviceNetworkLowLevel) -> None:
        if not system:
            raise ValueError("The system being wrapped cannot be None.")
        self._lowLevelSystem = system  # type: IDeviceNetworkLowLevel

    ## @var _lowLevelSystem
    #       The low level system being wrapped by this class.


    #====================================================================
    # IDeviceNetworkHighLevel methods
    #====================================================================

    #  @copydoc IDeviceNetworkHighLevel.GetNumChains()
    def GetNumChains(self) -> int:
        return self._lowLevelSystem.GetNumChains()


    #  @copydoc IDeviceNetworkHighLevel.GetIdcodes()
    def GetIdcodes(self, chainIndex : int) -> list:
        idcodes = []

        if self._lowLevelSystem.LockDeviceChain(chainIndex):
            idcodes = self._lowLevelSystem.GetIdcodes(chainIndex)
            self._lowLevelSystem.UnlockDeviceChain(chainIndex)

        return idcodes


    #  @copydoc IDeviceNetworkHighLevel::EnableDevicesInDeviceChain()
    def EnableDevicesInDeviceChain(self, chainIndex: int, selectMask : int) -> None:
        if self._lowLevelSystem.LockDeviceChain(chainIndex):
            self._lowLevelSystem.EnableDevicesInDeviceChain(chainIndex, selectMask)
            self._lowLevelSystem.UnlockDeviceChain(chainIndex)


    #  @copydoc IDeviceNetworkHighLevel::DisableDevicesInDeviceChain()
    def DisableDevicesInDeviceChain(self, chainIndex : int) -> None:
        if self._lowLevelSystem.LockDeviceChain(chainIndex):
            self._lowLevelSystem.ResetDeviceChain(chainIndex)
            self._lowLevelSystem.UnlockDeviceChain(chainIndex)



#########################################################################
#########################################################################

_instance = None # type: DeviceNetworkHighLevel

##  Class factory for a singleton instance of the
#  @ref DesignPatternExamples_python.facade.facade_interface.IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
#  interface.
#  Part of the @ref facade_pattern example.
#
#  @returns
#     Returns a singleton instance of the class.
def CreateHighLevelInstance() -> IDeviceNetworkHighLevel:
    global _instance
    if not _instance:
        lowlevelSystem = CreateLowLevelInstance()
        _instance = DeviceNetworkHighLevel(lowlevelSystem)
    return _instance
