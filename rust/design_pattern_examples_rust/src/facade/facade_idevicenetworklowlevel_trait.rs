//! Contains the IDeviceNetworkLowLevel trait that represents the complicated
//! facade sub-system.

/// Represents a network of device chains and the low level access to that
/// network.  In general, the caller should take a lock on a device chain
/// before accessing it then release the lock when done.
/// Part of the "Facade" pattern example.
///
/// This interface makes it easier to contrast with the IDeviceNetworkHighLevel
/// interface.
pub trait IDeviceNetworkLowLevel {
    /// Retrieve the number of device chains available in the network.
    ///
    /// # Returns
    /// Returns the number of device chains available.
    fn get_num_chains(&self) -> usize;

    /// Lock the specified device chain for exclusive access.
    ///
    /// # Parameters
    /// - chain_index
    ///
    ///   Index of the device chain (0..n-1).
    /// 
    /// # Returns
    /// Returns true if the device chain was successfully locked.
    fn lock_device_chain(&mut self, chain_index: usize) -> bool;

    /// Unlock the specified device chain to release exclusive access.
    ///
    /// # Parameters
    /// - chain_index
    ///
    ///   Index of the device chain (0..n-1).
    ///
    /// # Returns
    /// Returns true if the device chain was successfully unlocked.
    fn unlock_device_chain(&mut self, chain_index: usize) -> bool;

    /// Reset the visibility of all devices on the specified device chain.
    ///
    /// # Parameters
    /// - chain_index
    ///
    ///   Index of the device chain (0..n-1).
    fn reset_device_chain(&mut self, chain_index: usize);

    /// Make visible the specified devices on the specified device chain.
    ///
    /// # Parameters
    /// - chain_index
    ///
    ///   Index of the device chain (0..n-1).
    /// - devices_select_mask
    ///
    ///   Bit mask where each bit set indicates the corresponding TAP should be
    ///   made visible.  Bit 0 corresponds to the first TAP, bit 1 to the second
    ///   TAP, etc.  CLTAP (TAP controller) devices are always visible.
    fn enable_devices_in_device_chain(&mut self, chain_index: usize, devices_select_mask: u32);

    /// Make invisible the specified devices on the specified device chain.
    ///
    /// # Parameters
    /// - chain_index
    ///
    /// Index of the device chain (0..n-1).
    /// - devices_select_mask
    ///
    ///   Bit mask where each bit set indicates the corresponding TAP should be
    ///   made invisible.  Bit 0 corresponds to the first TAP, bit 1 to the
    ///   second TAP, etc.  CLTAP (TAP controller) devices are always visible.
    fn disable_devices_in_device_chain(&mut self, chain_index: usize, devices_select_mask: u32);

    /// Retrieve a list of idcodes of all visible devices in the given device chain.
    ///
    /// # Parameters
    /// - chain_index
    ///
    ///   Index of the device chain (0..n-1).
    ///
    /// # Returns
    /// Returns an array of idcodes for each visible TAP, with the first
    /// TAP being at index 0.
    fn get_idcodes(&self, chain_index: usize) -> Vec<u32>;

}
