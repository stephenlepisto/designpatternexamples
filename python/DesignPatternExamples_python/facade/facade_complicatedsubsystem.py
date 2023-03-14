## @file
#  @brief
#  Implementation of the @ref DesignPatternExamples_python.facade.facade_complicatedsubsystem.Facade_ComplicatedSubSystem "Facade_ComplicatedSubSystem"
#  class, along with the
#  @ref DesignPatternExamples_python.facade.facade_complicatedsubsystem.CreateLowLevelInstance "CreateLowLevelInstance"()
#  class factory representing the complicated sub-system used in the
#  @ref facade_pattern.

from .facadesubsystem_interface import DeviceTypes, IDeviceNetworkLowLevel

#  <summary>
#  Represents a single device.
#  Part of the @ref facade_pattern "Facade pattern" example.
#  </summary>
class DeviceNode:

    #  <summary>
    #  Constructor.
    #  </summary>
    #  @param name">Name to use.
    #  @param idcode">idcode for the device.
    #  @param tapType">Value from the DeviceTypes enumeration.
    #  @param initiallyVisible">true if initially visible otherwise false.
    def __init__(self, name: str, idcode: int, tapType: DeviceTypes, initiallyVisible: bool) -> None:
        self.Visible = initiallyVisible
        self.Name = name
        self.Idcode = idcode
        self.DeviceType = tapType

    ## @var Visible
    #       Whether the device is visible in the device chain.
    # @var Name
    #      Name of this device.
    # @var Idcode
    #      The idcode for this device.
    # @var DeviceType
    #      A value from the DeviceTypes enumeration identifying the type of the
    #  device.


#########################################################################
#########################################################################


##  Represents a device chain, which is a collection of DeviceNode objects.
#  Part of the @ref facade_pattern "Facade pattern" example.
class DeviceChain:

    ## Helper method to show or hide devices on the device chain.
    #
    #  @param nodeSelectMask
    #         A bit mask where the position of each bit corresponds to a device
    #         in the device chain, with bit 0 being the first device, bit 1
    #         being the second device, and so on.
    #  @param makeVisible
    #         true if the device is to be made visible on the device chain
    #         otherwise false, the device cannot be seen on the device chain.
    def _ShowHideNodes(self, nodeSelectMask: int, makeVisible : bool) -> None:
        bitMask = 0x2 # bit 0 is always the DEVICECONTROLLER and is always selected
        numNodes = len(self._nodes)

        # Start at the device after the DEVICECONTROLLER
        for index in range(1, numNodes):
            if (bitMask & nodeSelectMask) != 0:
                self._nodes[index].Visible = makeVisible
            bitMask <<= 1
            if bitMask == 0:
                # We don't allow more than 32 devices
                break


    ## Constructor.
    #
    #  @param name
    #         Name of this device chain.
    def __init__(self, name : str) -> None:
        self._nodes = []
        self.Name = name
        self.IsLocked = False

    ## @var _nodes
    #       The list of TAPNodes on this device chain.
    
    ## @var Name
    #       The Name of this device chain.

    ## @var IsLocked
    #       Whether this device chain is locked for access.


    ## Helper method to add a DeviceNode to the device chain.  DeviceNode
    #  objects that are of DeviceTypes::DEVICECONTROLLER are always
    #  inserted as the first device in the device chain, with the
    #  assumption there is only one DEVICECONTROLLER in a given device
    #  chain (this is not actually enforced, though).
    #
    #  @param node
    #         A DeviceNode object to add to the device chain.
    def AddNode(self, node : DeviceNode) -> None:
        if self._nodes and node.DeviceType == DeviceTypes.DEVICECONTROLLER:
            # DEVICECONTROLLER always goes at the start of the list.
            self._nodes.insert(0, node)
        else:
            self._nodes.append(node)



    ## Resets the device chain so that all devices that are not CLdevices are no
    #  longer visible in the device chain.    
    def ResetVisibility(self) -> None:
        for node in self._nodes:
            if node.DeviceType != DeviceTypes.DEVICECONTROLLER:
                node.Visible = False


    ## Make visible one or more devices in the device chain.
    #
    #  @param nodeSelectMask
    #         a bit mask specifying which device or devices to make visible,
    #         where bit 0 is the first device, bit 1 is the second, etc.
    #         Bit 0 is ignored as the first device is always visible.
    def SelectNodes(self, nodeSelectMask : int) -> None:
        self._ShowHideNodes(nodeSelectMask, True)


    ## Make invisible one or more devices in the device chain.
    #
    #  @param nodeSelectMask
    #         a bit mask specifying which device or devices to hide, where
    #         bit 0 is the first device, bit 1 is the second, etc. Bit 0 is
    #         ignored as the first device is always visible.
    def DeselectNodes(self, nodeSelectMask : int) -> None:
        self._ShowHideNodes(nodeSelectMask, False)


    ## Retrieve a list of idcodes for all devices that are visible in
    #  the device chain.
    #
    #  @returns
    #     Returns an array of ints corresponding to the idcodes of each
    #     visible device.  The first idcode corresponds to the first visible
    #     device.
    def GetIdCodesForVisibleNodes(self) -> list:
        idcodes = []

        for node in self._nodes:
            if node.Visible:
                idcodes.append(node.Idcode)

        return idcodes


#########################################################################
#########################################################################


## Represents some kind of system that contains multiple device chains.
#  Part of the @ref facade_pattern "Facade pattern" example.
#
#  The following operations are available:
#   - GetNumChains()
#   - LockDevices()
#   - UnlockDevices()
#   - ResetDevices()
#   - SelectDevices()
#   - DeselectDevices()
#   - GetIdcodes()
class Facade_ComplicatedSubSystem(IDeviceNetworkLowLevel):

    ## Constructor.  Sets up the device chains.
    def __init__(self) -> None:
        self._deviceChains = [ DeviceChain("CHAIN0"), DeviceChain("CHAIN1") ]
        self._deviceChains[0].AddNode(DeviceNode("DDD_DEVCTRL0", 0x10101010, DeviceTypes.DEVICECONTROLLER, True))
        self._deviceChains[0].AddNode(DeviceNode("DDD_CORE0", 0x20202020, DeviceTypes.CORE, False))
        self._deviceChains[0].AddNode(DeviceNode("DDD_GTE0", 0x30303030, DeviceTypes.GTE, False))

        self._deviceChains[1].AddNode(DeviceNode("DDD_DEVCTRL1", 0x10101011, DeviceTypes.DEVICECONTROLLER, True))
        self._deviceChains[1].AddNode(DeviceNode("DDD_PCH0", 0x40404040, DeviceTypes.PCH, False))
        self._deviceChains[1].AddNode(DeviceNode("DDD_PMC0", 0x50505050, DeviceTypes.PMC, False))

    ## @var _deviceChains
    #        The list of device chains.  In this case, there are two.

    #====================================================================
    # IDeviceNetworkLowLevel methods
    #====================================================================

    ## Retrieve the number of device chains.
    #
    #  @returns
    #     Returns the number of device chains</returns>
    def GetNumChains(self) -> int:
        return len(self._deviceChains)


    ## Lock the specified device chain to indicate exclusive access is
    #  desired.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    #  @returns
    #     Returns True if the device chain was successfully locked otherwise,
    #     returns False (chain index out of range or the device chain is
    #     already locked)
    def LockDeviceChain(self, chainIndex : int) -> bool:
        locked = False

        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            if not self._deviceChains[chainIndex].IsLocked:
                self._deviceChains[chainIndex].IsLocked = True
                locked = True

        return locked


    ## Unlock the specified device chain to indicate exclusive access is no
    #  longer desired.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    #  @returns
    #     Returns True if the device chain was successfully unlocked otherwise,
    #     returns False (chain index out of range or the device chain is
    #     already unlocked)
    def UnlockDeviceChain(self, chainIndex : int) -> bool:
        unlocked = False

        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            if self._deviceChains[chainIndex].IsLocked:
                self._deviceChains[chainIndex].IsLocked = False
                unlocked = True

        return unlocked


    ## Reset the visibility of all devices on the given device chain so that
    #  all devices except the first are not visible.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    def ResetDeviceChain(self, chainIndex : int) -> None:
        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            self._deviceChains[chainIndex].ResetVisibility()


    ## Select one or more devices in the given device chain so those devices are
    #  visible.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    #  @param deviceselectMask
    #         A bit mask indicating which devices to make visible, with bit 0
    #         corresponding to the first device, bit 1 corresponding to the
    #         second device, etc.  Bit 0 is ignored as the first device is
    #         always visible.
    def EnableDevicesInDeviceChain(self, chainIndex : int, deviceselectMask : int) -> None:
        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            self._deviceChains[chainIndex].SelectNodes(deviceselectMask)


    ## Deselect one or more devices in the given device chain so those devices are
    #  no longer visible.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    #  @param deviceselectMask
    #         A bit mask indicating which devices to make invisible, with bit 0
    #         corresponding to the first device, bit 1 corresponding to the
    #         second device, etc.  Bit 0 is ignored as the first device is
    #         always visible.
    def DisableDevicesInDeviceChain(self, chainIndex : int, deviceselectMask : int) -> None:
        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            self._deviceChains[chainIndex].DeselectNodes(deviceselectMask)


    ## Retrieve a list of idcodes for each device in the given device chain
    #  that is visible.
    #
    #  @param chainIndex
    #         The index of the device chain to access (0..n-1).
    #  @returns
    #     An array of uints holding the idcodes for each device, with the
    #     first idcode corresponding to the first visible device.
    def GetIdcodes(self, chainIndex : int) -> list:
        idcodes = []

        if chainIndex >= 0 and chainIndex < len(self._deviceChains):
            idcodes = self._deviceChains[chainIndex].GetIdCodesForVisibleNodes()
        return idcodes


## A singleton instance of the sub-system.
#  Part of the @ref facade_pattern "Facade pattern" example. 
_instance = None # type: Facade_ComplicatedSubSystem

## Class factory for a singleton instance of the sub-system class as represented
#  by the
#  @ref DesignPatternExamples_python.facade.facadesubsystem_interface.IDeviceNetworkLowLevel "IDeviceNetworkLowLevel"
#  interface.  Part of the @ref facade_pattern example.
#
#  @returns
#     Returns a singleton instance of the class.
def  CreateLowLevelInstance() -> IDeviceNetworkLowLevel:
    global _instance
    if not _instance:
        _instance = Facade_ComplicatedSubSystem()
    return _instance
