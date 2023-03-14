## @file
#  @brief
#  Declaration of the
#  @ref DesignPatternExamples_python.facade.facadesubsystem_interface.IDeviceNetworkLowLevel "IDeviceNetworkLowLevel"
#  interface representing the high-level system used in the @ref facade_pattern.

from abc import ABC, abstractmethod
from enum import Enum

## Identifies the type of devices that can appear in a device chain.
#  Part of the @ref facade_pattern "Facade pattern" example.
class DeviceTypes(Enum):
    ## device controller.  This is always visible.
    DEVICECONTROLLER = 0,
    ## Core device
    CORE = 1,
    ## GTE device
    GTE = 2,
    ## PCH device
    PCH = 3,
    ## PMC device
    PMC = 4


#  <summary>
#  Represents a network of device chains and the low level access to that
#  network.  In general, the caller should take a lock on a device chain
#  before accessing it then release the lock when done.
#  Part of the @ref facade_pattern "Facade pattern" example.
#  </summary>
#  <remarks>
#  This interface makes it easier to contrast with the IDeviceNetworkHighLevel
#  interface.
#  </remarks>
class IDeviceNetworkLowLevel(ABC):
    ## Retrieve the number of device chains available in the network.
    #
    #  @returns Returns the number of device chains available.
    @abstractmethod
    def GetNumChains(self) -> int:
        pass

    ## Lock the specified device chain for exclusive access.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    #  @returns
    #    Returns true if the device chain was successfully locked.
    @abstractmethod
    def LockDeviceChain(self, chainIndex : int) -> bool:
        pass

    ## Unlock the specified device chain to release exclusive access.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    #  @returns
    #    Returns true if the device chain was successfully unlocked.
    @abstractmethod
    def UnlockDeviceChain(self, chainIndex : int) -> bool:
        pass

    ## Reset the visibility of all devices on the specified device chain.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    @abstractmethod
    def ResetDeviceChain(self, chainIndex : int) -> None:
        pass

    ## Make visible the specified devices on the specified device chain.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    #  @param devicesSelectMask
    #         Bit mask where each bit set indicates the corresponding TAP
    #         should be made visible.  Bit 0 corresponds to the first TAP,
    #         bit 1 to the second TAP, etc.  CLTAP devices are always visible.
    @abstractmethod
    def EnableDevicesInDeviceChain(self, chainIndex : int, devicesSelectMask : int) -> None:
        pass

    ## Make invisible the specified devices on the specified device chain.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    #  @param devicesSelectMask
    #         Bit mask where each bit set indicates the corresponding TAP
    #         should be made invisible.  Bit 0 corresponds to the first TAP,
    #         bit 1 to the second TAP, etc.  CLTAP devices are always visible.
    @abstractmethod
    def DisableDevicesInDeviceChain(self, chainIndex : int, devicesSelectMask : int) -> None:
        pass

    ## Retrieve a list of idcodes of all visible devices in the given device chain.
    #
    #  @param chainIndex
    #         Index of the device chain (0..n-1).
    #  @returns
    #    Returns an array of idcodes for each visible TAP, with the first
    #  TAP being at index 0.
    @abstractmethod
    def GetIdcodes(self, chainIndex : int) -> list:
        pass

