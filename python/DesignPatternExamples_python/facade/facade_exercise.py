## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.facade.facade_exercise.Facade_Exercise "Facade_Exercise"()
# function as used in the @ref facade_pattern.

from io import StringIO

from .facade_interface import IDeviceNetworkHighLevel
from .facade_highlevelsystem import CreateHighLevelInstance


## Helper method to present a formatted list of idcodes for a particular
#  device chain.  The output is on a single line.
#
#  @param chainIndex
#         Index of the device chain being displayed.
#  @param idcodes
#         Array of 32-bit idcodes to be printed in hex.
def _Facade_ShowIdCodes(chainIndex : int, idcodes : list) -> None:
    output = StringIO()
    output.write("    On chain {0}, idcodes = [ ".format(chainIndex))
    for idcode in idcodes:
        output.write("0x{0:X} ".format(idcode))
    output.write("]")
    print(output.getvalue())



##  Example of using the @ref facade_pattern.
#  
#  The Facade pattern is used when a simplified version of an
#  interface on a complicated sub-system is needed in situations
#  where the whole complicated sub-system does not need to be
#  exposed.
#  
#  In this example, the complicated subsystem is a representation of
#  a device network complete with scan chains, device idcodes, and device
#  devices that can be selected and deselected.  The Facade exposed
#  by this complex network exposes only the scan chain, getting
#  device idcodes based on an index into those scan chains, resetting
#  the scan chains and selecting a device to appear in the scan
#  chain.

# ! [Using Facade in Python]
def Facade_Exercise():
    print()
    print("Facade Exercise")

    deviceChainFacade = CreateHighLevelInstance()
    numChains = deviceChainFacade.GetNumChains()
    print("  Showing idcodes of devices after a device reset (expect one device on each chain)...")
    for chainIndex in range(0, numChains):
        deviceChainFacade.DisableDevicesInDeviceChain(chainIndex)
        idcodes = deviceChainFacade.GetIdcodes(chainIndex)
        _Facade_ShowIdCodes(chainIndex, idcodes)

    print("  Showing idcodes of devices after selecting all devices...")
    for chainIndex in range(0, numChains):
        deviceChainFacade.EnableDevicesInDeviceChain(chainIndex, 0xffffffff)
        idcodes = deviceChainFacade.GetIdcodes(chainIndex)
        _Facade_ShowIdCodes(chainIndex, idcodes)
    
    print("  Done.")
# ! [Using Facade in Python]
