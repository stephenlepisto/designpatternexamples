/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
/// interface representing the high-level system used in the @ref facade_pattern "Facade pattern".

#pragma once
#ifndef __FACADE_INTERFACE_H__
#define __FACADE_INTERFACE_H__

#include <vector>

namespace DesignPatternExamples_cpp
{

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
    /// Part of the @ref facade_pattern "Facade pattern" example.
    /// </summary>
    struct IDeviceNetworkHighLevel
    {
        virtual ~IDeviceNetworkHighLevel() {}

        /// <summary>
        /// The number of device chains available from the sub-system.
        /// </summary>
        virtual int NumChains() = 0;

        /// <summary>
        /// Returns a list of all idcodes from all selected devices in the
        /// given device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <returns>An array holding the idcodes of all visible devices in the given
        /// chain.</returns>
        virtual std::vector<uint32_t> GetIdcodes(int chainIndex) = 0;

        /// <summary>
        /// Make visible certain devices in the given device chain.  The selectMask value
        /// has a bit set for each TAP device to make visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <param name="selectMask">A bit mask where each bit corresponds to a TAP,
        /// up to the number of devices in the given device chain.  Bit 0 is ignored as the first
        /// TAP is always visible.</param>
        virtual void EnableDevicesInDeviceChain(int chainIndex, uint32_t selectMask) = 0;

        /// <summary>
        /// Resets the given device chain so that all devices except the TAP
        /// controller is no longer visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        virtual  void DisableDevicesInDeviceChain(int chainIndex) = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Class factory for a singleton instance of the IDeviceNetworkHighLevel
    /// interface.
    /// Part of the @ref facade_pattern "Facade pattern" example.
    /// </summary>
    /// <returns>Returns a singleton instance of the class.</returns>
    IDeviceNetworkHighLevel* CreateHighLevelInstance();

} // end namespace

#endif // __FACADE_INTERFACE_H__

