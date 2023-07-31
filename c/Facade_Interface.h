/// @file
/// @brief
/// Declaration of the IDeviceNetworkHighLevel interface representing the
/// high-level system used in the @ref facade_pattern.

#pragma once
#ifndef __FACADE_INTERFACE_H__
#define __FACADE_INTERFACE_H__

#include "helpers/uintarray.h"

/// <summary>
/// Represents a high level view of a complex network of device chains.
/// A device chain can be thought of as a list of devices that can be made
/// visible or hidden in the list but maintain the same relationship to
/// each other regardless of visibility.
///
/// The methods on this high level interface may seem the same as on the
/// IDeviceNetworkLowLevel interface.  However, most of the methods on this
/// high level interface hide the need for taking a lock on a chain before
/// accessing the chain.
///
/// This high level interface is a simplification and thus a facade for the
/// low level interface and the system underneath.
///
/// Part of the @ref facade_pattern example.
/// </summary>
typedef struct
{
    /// <summary>
    /// The number of device chains available from the sub-system.
    /// </summary>
    int (*NumChains)(void);

    /// <summary>
    /// Returns a list of all idcodes from all selected devices in the
    /// given device chain.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
    /// <param name="idcodes">A UIntArray that is filled in with the idcodes of the
    /// selected devices.  This UIntArray object needs to be initialized before
    /// use with UIntArray_Initialize() and freed after use with
    /// UIntArray_Clear().</param>
    void (*GetIdcodes)(int chainIndex, UIntArray* idcodes);

    /// <summary>
    /// Make visible certain devices in the given device chain.  The selectMask value
    /// has a bit set for each device to make visible.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
    /// <param name="selectMask">A bit mask where each bit corresponds to a device,
    /// up to the number of devices in the given device chain.  Bit 0 is ignored
    /// as the first device is always visible.</param>
    void (*EnableDevicesInDeviceChain)(int chainIndex, uint32_t selectMask);

    /// <summary>
    /// Resets the given device chain so that all devices except the first
    /// are no longer visible.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
    void (*DisableDevicesInDeviceChain)(int chainIndex);
} IDeviceNetworkHighLevel;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/// <summary>
/// Retrieve a set of function pointers to the high-level device service used
/// in the @ref facade_pattern example.
/// </summary>
/// <returns>Returns an IDeviceNetworkHighLevel interface representing a
/// simplified access to the full device network.</returns>
IDeviceNetworkHighLevel* Facade_GetHighLevelDeviceService(void);

#endif // __FACADE_INTERFACE_H__
