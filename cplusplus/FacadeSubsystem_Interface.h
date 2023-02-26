#pragma once
#ifndef __FACADESUBSYSTEM_INTERFACE_H__
#define __FACADESUBSYSTEM_INTERFACE_H__

#include <vector>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Identifies the type of devices that can appear in a device chain.
    /// </summary>
    enum DeviceTypes
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
    };


    /// <summary>
    /// Represents a network of device chains and the low level access to that
    /// network.  In general, the caller should take a lock on a device chain
    /// before accessing it then release the lock when done.
    /// </summary>
    /// <remarks>
    /// This interface makes it easier to contrast with the IDeviceNetworkLowLevel
    /// interface.
    /// </remarks>
    struct IDeviceNetworkLowLevel
    {
        virtual ~IDeviceNetworkLowLevel() {}

        /// <summary>
        /// Retrieve the number of device chains available in the network.
        /// </summary>
        /// <returns>Returns the number of device chains available.</returns>
        virtual  int GetNumChains() = 0;

        /// <summary>
        /// Lock the specified device chain for exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully locked.</returns>
        virtual bool LockDeviceChain(int chainIndex) = 0;

        /// <summary>
        /// Unlock the specified device chain to release exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully unlocked.</returns>
        virtual bool UnlockDeviceChain(int chainIndex) = 0;

        /// <summary>
        /// Reset the visibility of all devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        virtual void ResetDeviceChain(int chainIndex) = 0;

        /// <summary>
        /// Make visible the specified devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made visible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        virtual void EnableDevicesInDeviceChain(int chainIndex, uint32_t devicesSelectMask) = 0;

        /// <summary>
        /// Make invisible the specified devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made invisible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        virtual void DisableDevicesInDeviceChain(int chainIndex, uint32_t devicesSelectMask) = 0;

        /// <summary>
        /// Retrieve a list of idcodes of all visible devices in the given device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns an array of idcodes for each visible TAP, with the first
        /// TAP being at index 0.</returns>
        virtual std::vector<uint32_t> GetIdcodes(int chainIndex) = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Class factory for a singleton instance of the sub-system class.
    /// </summary>
    /// <returns>Returns a singleton instance of the class.</returns>
    IDeviceNetworkLowLevel* CreateLowLevelInstance();

} // end namespace

#endif // __FACADESUBSYSTEM_INTERFACE_H__

