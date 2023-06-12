//! Contains the DeviceNetworkHighLevel struct that wraps the low-level
//! complicated facade sub-system and which is exposed by the IDeviceNetworkHighLevel
//! trait.

use super::facade_complicatedsubsystem::FacadeComplicatedSubSystem;
use super::facade_idevicenetworklowlevel_trait::IDeviceNetworkLowLevel;
use super::facade_idevicenetworkhighlevel_trait::IDeviceNetworkHighLevel;

/// This struct wraps the IDeviceNetworkLowLevel interface and implements
/// the high level IDeviceNetworkHighLevel interface, which is a simpler
/// interface.  All calls on the high level interface are forwarded to the
/// appropriate low level interface.
/// Part of the "Facade" pattern example.
pub struct DeviceNetworkHighLevel {
    low_level_system: Box<dyn IDeviceNetworkLowLevel>,
}

impl DeviceNetworkHighLevel {
    /// Constructor.
    pub fn new() -> Box<dyn IDeviceNetworkHighLevel> {
        Box::new(DeviceNetworkHighLevel {
            low_level_system : FacadeComplicatedSubSystem::new(),
        })
    }
}

impl IDeviceNetworkHighLevel for DeviceNetworkHighLevel {
    fn num_chains(&self) -> usize {
        self.low_level_system.get_num_chains()
    }

    fn get_idcodes(&mut self, chain_index: usize) -> Vec<u32> {
        let mut idcodes: Vec<u32> = vec![];
        if self.low_level_system.lock_device_chain(chain_index) {
            idcodes = self.low_level_system.get_idcodes(chain_index);
            self.low_level_system.unlock_device_chain(chain_index);
        }

        idcodes
    }

    fn enable_devices_in_device_chain(&mut self, chain_index: usize, select_mask: u32) {
        if self.low_level_system.lock_device_chain(chain_index) {
            self.low_level_system.enable_devices_in_device_chain(chain_index, select_mask);
            self.low_level_system.unlock_device_chain(chain_index);
        }
    }

    fn disable_devices_in_device_chain(&mut self, chain_index: usize) {
        if self.low_level_system.lock_device_chain(chain_index) {
            self.low_level_system.reset_device_chain(chain_index);
            self.low_level_system.unlock_device_chain(chain_index);
        }
    }
}
