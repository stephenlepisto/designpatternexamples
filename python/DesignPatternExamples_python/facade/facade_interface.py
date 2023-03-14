## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.facade.facade_interface.IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
#  interface representing the high-level system used in the @ref facade_pattern.

from abc import ABC, abstractmethod


## Represents a high level view of a complex network of device chains.
#  A device chain can be thought of as a list of devices that can be made
#  visible or hidden in the list but maintain the same relationship to
#  each other regardless of visibility.
#  
#  The methods on this high level interface may seem the same as on the
#  IDeviceNetworkLowLevel interface.  However, most of the methods on this
#  high level interface hide the need for taking a lock on a chain before
#  accessing the chain.
#  
#  This high level interface is a simplification and thus a facade for the
#  low level interface and the system underneath.
#  
#  Part of the @ref facade_pattern "Facade pattern" example.
class IDeviceNetworkHighLevel(ABC):
    ## The number of device chains available from the sub-system.
    @abstractmethod
    def NumChains(self) -> int:
        pass

    ## Returns a list of all idcodes from all selected devices in the
    #  given device chain.
    #
    #  @param chainIndex
    #         Index of the device chain to access (0..NumChains-1).
    #  @returns
    #     An array holding the idcodes of all visible devices in the given
    #  chain.
    @abstractmethod
    def GetIdcodes(self, chainIndex: int) -> list:
        pass

    ## Make visible certain devices in the given device chain.  The selectMask value
    #  has a bit set for each TAP device to make visible.
    #
    #  @param chainIndex
    #         Index of the device chain to access (0..NumChains-1).
    #  @param selectMask
    #         A bit mask where each bit corresponds to a TAP, up to the number
    #         of devices in the given device chain.  Bit 0 is ignored as the
    #         first TAP is always visible.
    @abstractmethod
    def EnableDevicesInDeviceChain(self, chainIndex : int, selectMask: int) -> None:
        pass

    ## Resets the given device chain so that all devices except the TAP
    #  controller is no longer visible.
    #
    #  @param chainIndex
    #         Index of the device chain to access (0..NumChains-1).
    @abstractmethod
    def DisableDevicesInDeviceChain(self, chainIndex : int) -> None:
        pass

