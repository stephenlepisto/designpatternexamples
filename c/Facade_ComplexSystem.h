/// @file
/// @brief
/// Declaration of the IDeviceNetworkLowLevel interface representing the complex
/// system for the @ref facade_pattern.

#pragma once
#ifndef __FACADE_COMPLEXSYSTEM_H__
#define __FACADE_COMPLEXSYSTEM_H__

#include <stdbool.h>

#include "helpers/uintarray.h"

/// <summary>
/// Identifies the type of devices that can appear in a device chain.
/// Part of the @ref facade_pattern example.
/// </summary>
typedef enum
{
    /// <summary>
    /// device controller.  This is always visible.
    /// </summary>
    DEVICECONTROLLER,
    /// <summary>
    /// Core device
    /// </summary>
    CORE,
    /// <summary>
    /// GTE device
    /// </summary>
    GTE,
    /// <summary>
    /// PCH device
    /// </summary>
    PCH,
    /// <summary>
    /// PMC device
    /// </summary>
    PMC,
} DeviceTypes;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


/// <summary>
/// Represents a network of device chains and the low level access to that
/// network.  In general, the caller should take a lock on a device chain
/// before accessing it then release the lock when done.
/// Part of the @ref facade_pattern example.
/// </summary>
/// <remarks>
/// This interface makes it easier to contrast with the IDeviceNetworkHighLevel
/// interface.
/// </remarks>
typedef struct
{
    /// <summary>
    /// Retrieve the number of device chains available in the network.
    /// </summary>
    /// <returns>Returns the number of device chains available.</returns>
    int (*GetNumChains)();

    /// <summary>
    /// Lock the specified device chain for exclusive access.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    /// <returns>Returns true if the device chain was successfully locked.</returns>
    bool (*LockDeviceChain)(int chainIndex);

    /// <summary>
    /// Unlock the specified device chain to release exclusive access.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    /// <returns>Returns true if the device chain was successfully unlocked.</returns>
    bool (*UnlockDeviceChain)(int chainIndex);

    /// <summary>
    /// Reset the visibility of all devices on the specified device chain.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    void (*ResetDeviceChain)(int chainIndex);

    /// <summary>
    /// Make visible the specified devices on the specified device chain.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
    /// corresponding device should be made visible.  Bit 0 corresponds to the
    /// first device, bit 1 to the second device, etc.  Bit 0 is ignored as the
    /// first device is always visible.</param>
    void (*EnableDevicesInDeviceChain)(int chainIndex, uint32_t devicesSelectMask);

    /// <summary>
    /// Make invisible the specified devices on the specified device chain.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
    /// corresponding device should be made invisible.  Bit 0 corresponds to the
    /// first device, bit 1 to the second device, etc.  Bit 0 is ignored as the
    /// first device is always visible.</param>
    void (*DisableDevicesInDeviceChain)(int chainIndex, uint32_t devicesSelectMask);

    /// <summary>
    /// Retrieve a list of idcodes of all visible devices in the given device chain.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
    /// <param name="idcodes">Returns an array of idcodes for each visible TAP,
    /// with the first TAP being at index 0.  This UIntArray object needs to be
    /// initialized before use with UIntArray_Initialize() and freed
    /// after use with UIntArray_Clear().</param>
    void (*GetIdcodes)(int chainIndex, UIntArray* idcodes);

} IDeviceNetworkLowLevel;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/// <summary>
/// Retrieve a set of function pointers to the low-level device service used
/// in the @ref facade_pattern example.
/// </summary>
/// <returns>Returns an IDeviceNetworkLowLevel interface representing the full
/// device network.</returns>
IDeviceNetworkLowLevel* Facade_GetLowLevelDeviceService();

#endif // __FACADE_COMPLEXSYSTEM_H__

