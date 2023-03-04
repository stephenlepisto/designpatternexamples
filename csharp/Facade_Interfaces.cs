/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.IDeviceNetworkLowLevel "IDeviceNetworkLowLevel"
/// and @ref DesignPatternExamples_csharp.IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
/// interfaces, used in the @ref facade_pattern "Facade pattern".

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a network of device chains and the low level access to that
    /// network.  In general, the caller should take a lock on a device chain
    /// before accessing it then release the lock when done.
    /// Part of the @ref facade_pattern "Facade pattern" example.
    /// </summary>
    /// <remarks>
    /// This interface makes it easier to contrast with the
    /// @ref DesignPatternExamples_csharp.IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
    /// interface.
    /// </remarks>
    public interface IDeviceNetworkLowLevel
    {
        /// <summary>
        /// Retrieve the number of device chains available in the network.
        /// </summary>
        /// <returns>Returns the number of device chains available.</returns>
        int GetNumChains();

        /// <summary>
        /// Lock the specified device chain for exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully locked.</returns>
        bool LockDeviceChain(int chainIndex);

        /// <summary>
        /// Unlock the specified device chain to release exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully unlocked.</returns>
        bool UnlockDeviceChain(int chainIndex);

        /// <summary>
        /// Reset the visibility of all devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        void ResetDeviceChain(int chainIndex);

        /// <summary>
        /// Make visible the specified devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made visible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        void EnableDevicesInDeviceChain(int chainIndex, uint devicesSelectMask);

        /// <summary>
        /// Make invisible the specified devices on the specified device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <param name="devicesSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made invisible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        void DisableDevicesInDeviceChain(int chainIndex, uint devicesSelectMask);

        /// <summary>
        /// Retrieve a list of idcodes of all visible devices in the given device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain (0..n-1).</param>
        /// <returns>Returns an array of idcodes for each visible TAP, with the first
        /// TAP being at index 0.</returns>
        uint[] GetIdcodes(int chainIndex);
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a high level view of a complex network of device chains.
    /// A device chain can be thought of as a list of devices that can be made
    /// visible or hidden in the list but maintain the same relationship to
    /// each other regardless of visibility.
    /// 
    /// The methods on this high level interface may seem the same as on the
    /// @ref DesignPatternExamples_csharp.IDeviceNetworkLowLevel "IDeviceNetworkLowLevel"
    /// interface.  However, most of the methods on this high level interface
    /// hide the need for taking a lock on a chain before accessing the chain.
    /// 
    /// This high level interface is a
    /// simplification and thus a facade for the low level interface and the
    /// system underneath.
    /// Part of the @ref facade_pattern "Facade pattern" example.
    /// </summary>
    public interface IDeviceNetworkHighLevel
    {
        /// <summary>
        /// The number of device chains available from the sub-system.
        /// </summary>
        int NumChains { get; }

        /// <summary>
        /// Returns a list of all idcodes from all selected devices in the
        /// given device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <returns>An array holding the idcodes of all visible devices in the given
        /// chain.</returns>
        uint[] GetIdcodes(int chainIndex);

        /// <summary>
        /// Make visible certain devices in the given device chain.  The selectMask value
        /// has a bit set for each TAP device to make visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <param name="selectMask">A bit mask where each bit corresponds to a TAP,
        /// up to the number of devices in the given device chain.  Bit 0 is ignored as the first
        /// TAP is always visible.</param>
        void EnableDevicesInDeviceChain(int chainIndex, uint selectMask);

        /// <summary>
        /// Resets the given device chain so that all devices except the TAP
        /// controller is no longer visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        void DisableDevicesInDeviceChain(int chainIndex);
    }
}
