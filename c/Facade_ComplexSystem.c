/// @file
/// @brief
/// Implementation of the IDeviceNetworkLowLevel interface and the complex
/// system it represents for the @ref facade_pattern.

#include "Facade_Interface.h"
#include "Facade_ComplexSystem.h"

/// <summary>
/// Represents a single device.
/// Part of the @ref facade_pattern example.
/// </summary>
typedef struct
{
    /// <summary>
    /// Name of this device.
    /// </summary>
    const char* Name;

    /// <summary>
    /// The idcode for this device.
    /// </summary>
    uint32_t Idcode;

    /// <summary>
    /// A value from the DeviceTypes enumeration identifying the type of the
    /// device.
    /// </summary>
    DeviceTypes DeviceType;

    /// <summary>
    /// Whether the device is visible in the device chain.
    /// </summary>
    bool Visible;
} DeviceNode;


//#############################################################################
//#############################################################################

/// <summary>
/// Represents a single device chain, a collection of DeviceNode objects.
/// </summary>
typedef struct
{
    const char* Name;
    bool        IsLocked;
    DeviceNode* nodes;
    size_t      numNodes;
} DeviceChain;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//#############################################################################
//#############################################################################


/// <summary>
/// Device Chain 0, with 3 devices.  The first device is always the device
/// controller, which is always visible.
/// </summary>
static DeviceNode deviceChain0[] =
{
    { "DDD_DEVCTRL0", 0x10101010, DEVICECONTROLLER, true  },
    { "DDD_CORE0"   , 0x20202020, CORE            , false },
    { "DDD_GTE0"    , 0x30303030, GTE             , false },
};

/// <summary>
/// Device Chain 1, with 3 devices.  The first device is always the device
/// controller, which is always visible.
/// </summary>
static DeviceNode deviceChain1[] =
{
    { "DDD_DEVCTRL1", 0x10101011, DEVICECONTROLLER, true  },
    { "DDD_PCH0"    , 0x40404040, PCH             , false },
    { "DDD_PMC0"    , 0x50505050, PMC             , false },
};

/// <summary>
/// Device chains.  There are two device chains, which are accessed separately.
/// Each chain has its own lock for access, which is initially unlocked.
/// </summary>
static DeviceChain deviceChains[] = {
    { "CHAIN0", false, deviceChain0, sizeof(deviceChain0) / sizeof(deviceChain0[0]) },
    { "CHAIN1", false, deviceChain1, sizeof(deviceChain1) / sizeof(deviceChain0[1]) }
};

/// <summary>
/// Number of device chains that have been pre-defined.
/// </summary>
static int deviceChainCount = (int)(sizeof(deviceChains) / sizeof(deviceChains[0]));


//#############################################################################
//#############################################################################

/// <summary>
/// Helper function to show or hide devices on the device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain to manipulate.</param>
/// <param name="nodeSelectMask">A bit mask where the position of each bit
/// corresponds to a device in the device chain, with bit 0 being the first device,
/// bit 1 being the second device, and so on.</param>
/// <param name="makeVisible">true if the device is to be made visible on the
/// device chain; otherwise false, the device cannot be seen on the device chain.</param>
static void DeviceChain_ShowHideNodes(int chainIndex, uint32_t nodeSelectMask, bool makeVisible)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        // bit 0 is always the DEVICECONTROLLER and is always selected so skip
        // it in the mask
        uint32_t bitMask = 0x2;
        size_t numNodes = deviceChains[chainIndex].numNodes;
        DeviceNode* nodes = deviceChains[chainIndex].nodes;

        // Start at the device after the DEVICECONTROLLER
        for (size_t index = 1; index < numNodes; ++index)
        {
            if ((bitMask & nodeSelectMask) != 0)
            {
                nodes[index].Visible = makeVisible;
            }
            bitMask <<= 1;
            if (bitMask == 0)
            {
                // We don't allow more than 32 devices
                break;
            }
        }
    }
}

/// <summary>
/// Resets the specified device chain so that all devices that are not
/// device controllers are no longer visible in the device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain to manipulate.</param>
static void DeviceChain_ResetVisibility(int chainIndex)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        size_t numNodes = deviceChains[chainIndex].numNodes;
        DeviceNode* nodes = deviceChains[chainIndex].nodes;
        for (size_t index = 0; index < numNodes; index++)
        {
            if (nodes[index].DeviceType != DEVICECONTROLLER)
            {
                nodes[index].Visible = false;
            }
        }
    }
}

/// <summary>
/// Make visible one or more devices in the device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain to manipulate.</param>
/// <param name="nodeSelectMask">a bit mask specifying which device or devices
/// to make visible, where bit 0 is the first device, bit 1 is the second, etc.
/// Bit 0 is ignored as the first device is always visible.</param>
static void DeviceChain_SelectNodes(int chainIndex, uint32_t nodeSelectMask)
{
    DeviceChain_ShowHideNodes(chainIndex, nodeSelectMask, true);
}

/// <summary>
/// Make invisible one or more devices in the device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain to manipulate.</param>
/// <param name="nodeSelectMask">a bit mask specifying which device or devices
/// to hide, where bit 0 is the first device, bit 1 is the second, etc.
/// Bit 0 is ignored as the first device is always visible.</param>
static void DeviceChain_DeselectNodes(int chainIndex, uint32_t nodeSelectMask)
{
    DeviceChain_ShowHideNodes(chainIndex, nodeSelectMask, false);
}


/// <summary>
/// Retrieve a list of idcodes for all devices that are visible in
/// the device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain to manipulate.</param>
/// <param name="idcodes">Returns an array of idcodes for each visible device,
/// with the first device being at index 0.  This UIntArray object needs to be
/// initialized before use with UIntArray_Initialize() and freed
/// after use with UIntArray_Clear().</param>
static void DeviceChain_GetIdCodesForVisibleNodes(int chainIndex, UIntArray* idcodes)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        if (idcodes != NULL)
        {
            size_t numNodes = deviceChains[chainIndex].numNodes;
            DeviceNode* nodes = deviceChains[chainIndex].nodes;
            for (size_t index = 0; index < numNodes; index++)
            {
                if (nodes[index].Visible)
                {
                    UIntArray_AddInt(idcodes, nodes[index].Idcode);
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//====================================================================
// IDeviceNetworkLowLevel methods
//====================================================================

/// <summary>
/// Retrieve the number of device chains.
/// </summary>
/// <returns>Returns the number of device chains</returns>
static int GetNumChains()
{
    return (int)deviceChainCount;
}

/// <summary>
/// Lock the specified device chain to indicate exclusive access is
/// desired.
/// </summary>
/// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
/// <returns>Returns true if the device chain was successfully locked; otherwise,
/// returns false (chain index out of range or the device chain is already locked)</returns>
static bool LockDeviceChain(int chainIndex)
{
    bool IsLocked = false;

    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        if (!deviceChains[chainIndex].IsLocked)
        {
            deviceChains[chainIndex].IsLocked = true;
            IsLocked = true;
        }
    }

    return IsLocked;
}

/// <summary>
/// Unlock the specified device chain to indicate exclusive access is no
/// longer desired.
/// </summary>
/// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
/// <returns>Returns true if the device chain was successfully unlocked; otherwise,
/// returns false (chain index out of range or the device chain is already unlocked)</returns>
static bool UnlockDeviceChain(int chainIndex)
{
    bool unlocked = false;

    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        if (deviceChains[chainIndex].IsLocked)
        {
            deviceChains[chainIndex].IsLocked = false;
            unlocked = true;
        }
    }

    return unlocked;
}

/// <summary>
/// Reset the visibility of all devices on the given device chain so that
/// all devices except the first are not visible.
/// </summary>
/// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
static void ResetDeviceChain(int chainIndex)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        DeviceChain_ResetVisibility(chainIndex);
    }
}

/// <summary>
/// Select one or more devices in the given device chain so those devices are
/// visible.
/// </summary>
/// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
/// <param name="deviceselectMask">A bit mask indicating which devices to make
/// visible, with bit 0 corresponding to the first device, bit 1 corresponding
/// to the second device, etc.  Bit 0 is ignored as the first device is always
/// visible.</param>
static void EnableDevicesInDeviceChain(int chainIndex, uint32_t deviceselectMask)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        DeviceChain_SelectNodes(chainIndex, deviceselectMask);
    }
}

/// <summary>
/// Deselect one or more devices in the given device chain so those devices are
/// no longer visible.
/// </summary>
/// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
/// <param name="deviceselectMask">A bit mask indicating which devices to make
/// invisible, with bit 0 corresponding to the first device, bit 1 corresponding
/// to the second device, etc.  Bit 0 is ignored as the first device is always
/// visible.</param>
static void DisableDevicesInDeviceChain(int chainIndex, uint32_t deviceselectMask)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        DeviceChain_DeselectNodes(chainIndex, deviceselectMask);
    }
}

/// <summary>
/// Retrieve a list of idcodes of all visible devices in the given device chain.
/// </summary>
/// <param name="chainIndex">Index of the device chain (0..n-1).</param>
/// <param name="idcodes">Returns an array of idcodes for each visible TAP,
/// with the first TAP being at index 0.  This UIntArray object needs to be
/// initialized before use with UIntArray_Initialize() and freed
/// after use with UIntArray_Clear().</param>
static void GetIdcodes(int chainIndex, UIntArray* idcodes)
{
    if (chainIndex >= 0 && chainIndex < deviceChainCount)
    {
        DeviceChain_GetIdCodesForVisibleNodes(chainIndex, idcodes);
    }
}


//#############################################################################
//#############################################################################

/// <summary>
/// Definition of the IDeviceNetworkLowLevel interface, using function pointers
/// to each function.
/// </summary>
/// <remarks>
/// The function pointers set here must be in the same order they are defined
/// in the IDeviceNetworkLowLevel structure representing the interface.
/// </remarks>
IDeviceNetworkLowLevel lowlevelService =
{
    GetNumChains,
    LockDeviceChain,
    UnlockDeviceChain,
    ResetDeviceChain,
    EnableDevicesInDeviceChain,
    DisableDevicesInDeviceChain,
    GetIdcodes
};

//-----------------------------------------------------------------------------

IDeviceNetworkLowLevel* Facade_GetLowLevelDeviceService()
{
    return &lowlevelService;
}
