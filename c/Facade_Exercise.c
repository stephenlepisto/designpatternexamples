
/// @file
/// @brief
/// Implementation of the Facade_Exercise() function as used in the 
/// @ref facade_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Facade_Interface.h"

#include "Facade_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to present a formatted list of idcodes for a particular
/// device chain.  The output is on a single line.
/// </summary>
/// <param name="chainIndex">Index of the device chain being displayed.</param>
/// <param name="idcodes">Array of 32-bit idcodes to be printed in hex.</param>
static void _Facade_ShowIdCodes(int chainIndex, UIntArray* idcodes)
{
    if (idcodes != NULL)
    {
        printf("    On chain %d, idcodes = [ ", chainIndex);
        for (size_t index = 0; index < idcodes->length; index++)
        {
            printf("0x%04x ", idcodes->data[index]);
        }
        printf("]\n");
    }
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref facade_pattern.
/// 
/// The Facade pattern is used when a simplified version of an
/// interface on a complicated sub-system is needed in situations
/// where the whole complicated sub-system does not need to be
/// exposed.
/// 
/// In this example, the complicated subsystem is a representation of
/// a device network complete with scan chains, device idcodes, and device
/// devices that can be selected and deselected.  The Facade exposed
/// by this complex network exposes only the scan chain, getting
/// device idcodes based on an index into those scan chains, resetting
/// the scan chains and selecting a device to appear in the scan
/// chain.
/// </summary>
// ! [Using Facade in C]
void Facade_Exercise()
{
    printf("\nFacade_Exercise\n");

    IDeviceNetworkHighLevel* deviceChainFacade = Facade_GetHighLevelDeviceService();
    if (deviceChainFacade != NULL)
    {
        int numChains = deviceChainFacade->NumChains();
        printf("  Showing idcodes of devices after a device reset (expect one device on each chain)...\n");

        for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
        {
            deviceChainFacade->DisableDevicesInDeviceChain(chainIndex);
            UIntArray idcodes;
            UIntArray_Initialize(&idcodes);
            deviceChainFacade->GetIdcodes(chainIndex, &idcodes);
            _Facade_ShowIdCodes(chainIndex, &idcodes);
            UIntArray_Clear(&idcodes);
        }

        printf("  Showing idcodes of devices after selecting all devices...\n");
        for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
        {
            deviceChainFacade->EnableDevicesInDeviceChain(chainIndex, 0xffffffff);
            UIntArray idcodes;
            UIntArray_Initialize(&idcodes);
            deviceChainFacade->GetIdcodes(chainIndex, &idcodes);
            _Facade_ShowIdCodes(chainIndex, &idcodes);
            UIntArray_Clear(&idcodes);
        }
    }

    printf("  Done.\n");
}
// ! [Using Facade in C]
