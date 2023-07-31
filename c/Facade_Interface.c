/// @file
/// @brief
/// Implementation of the IDeviceNetworkHighLevel interface and the simplified
/// implementation on top of the complex system for the @ref facade_pattern.

#include "Facade_ComplexSystem.h"

#include "Facade_Interface.h"

static IDeviceNetworkLowLevel* _lowlevelSystem = NULL;

/// <summary>
/// Make sure we have access to the low-level system.
/// </summary>
/// <returns>Returns true if the low-level system is available; otherwise,
/// return false, cannot use the low-level system.</returns>
static bool _InitializeLowLevelSystem(void)
{
    if (_lowlevelSystem == NULL)
    {
        _lowlevelSystem = Facade_GetLowLevelDeviceService();
    }

    return _lowlevelSystem != NULL;
}


//====================================================================
// IDeviceNetworkHighLevel methods
//====================================================================

/// @copydoc IDeviceNetworkHighLevel::NumChains()
static int NumChains(void)
{
    int numChains = 0;

    if (_InitializeLowLevelSystem())
    {
        numChains = _lowlevelSystem->GetNumChains();
    }

    return numChains;
}

/// @copydoc IDeviceNetworkHighLevel::GetIdcodes()
static void GetIdcodes(int chainIndex, UIntArray* idcodes)
{
    if (_InitializeLowLevelSystem())
    {
        if (_lowlevelSystem->LockDeviceChain(chainIndex))
        {
            _lowlevelSystem->GetIdcodes(chainIndex, idcodes);
            _lowlevelSystem->UnlockDeviceChain(chainIndex);
        }
    }
}

/// @copydoc IDeviceNetworkHighLevel::EnableDevicesInDeviceChain()
static void EnableDevicesInDeviceChain(int chainIndex, uint32_t selectMask)
{
    if (_InitializeLowLevelSystem())
    {
        if (_lowlevelSystem->LockDeviceChain(chainIndex))
        {
            _lowlevelSystem->EnableDevicesInDeviceChain(chainIndex, selectMask);
            _lowlevelSystem->UnlockDeviceChain(chainIndex);
        }
    }
}

/// @copydoc IDeviceNetworkHighLevel::DisableDevicesInDeviceChain()
static void DisableDevicesInDeviceChain(int chainIndex)
{
    if (_InitializeLowLevelSystem())
    {
        if (_lowlevelSystem->LockDeviceChain(chainIndex))
        {
            _lowlevelSystem->ResetDeviceChain(chainIndex);
            _lowlevelSystem->UnlockDeviceChain(chainIndex);
        }
    }
}


//#############################################################################
//#############################################################################

/// <summary>
/// Definition of the IDeviceNetworkHighLevel interface, using function pointers
/// to each function.
/// </summary>
/// <remarks>
/// The function pointers set here must be in the same order they are defined
/// in the IDeviceNetworkHighLevel structure representing the interface.
/// </remarks>
IDeviceNetworkHighLevel highlevelService =
{
    NumChains,
    GetIdcodes,
    EnableDevicesInDeviceChain,
    DisableDevicesInDeviceChain,
};

//-----------------------------------------------------------------------------

IDeviceNetworkHighLevel* Facade_GetHighLevelDeviceService(void)
{
    return &highlevelService;
}
