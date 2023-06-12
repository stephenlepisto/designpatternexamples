//! Contains the IDeviceNetworkHighLevel trait that represents a simplified
//! view of a complicated facade sub-system.

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
pub trait IDeviceNetworkHighLevel {
    /// The number of device chains available from the sub-system.
    fn num_chains(&self) -> usize;

    /// Returns a list of all idcodes from all selected devices in the
    /// given device chain.
    fn get_idcodes(&mut self, chain_index: usize) -> Vec<u32>;

    /// Make visible certain devices in the given device chain.  The `selectMask`
    /// value has a bit set for each TAP device to make visible.
    fn enable_devices_in_device_chain(&mut self, chain_index: usize, select_mask: u32);

    /// Resets the given device chain so that all devices except the TAP
    /// controller is no longer visible.
    fn disable_devices_in_device_chain(&mut self, chain_index: usize);
}
