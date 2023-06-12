//! Contains the implementation of the complicated facade sub-system.

use super::facade_idevicenetworklowlevel_trait::IDeviceNetworkLowLevel;

//-----------------------------------------------------------------------------

/// Identifies the type of devices that can appear in a device chain.
/// Part of the "Facade" pattern example.
enum DeviceTypes {
    /// device controller.  This is always visible.
    DEVICECONTROLLER,
    /// Core device
    CORE,
    /// GTE device
    GTE,
    /// PCH device
    PCH,
    /// PMC device
    PMC,
}

//=============================================================================

/// Represents a single device in a device chain.
/// Part of the "Facade" pattern example.
struct DeviceNode {
    /// Whether the device is visible in the device chain.
    visible: bool,

    /// Name of this device.
    _name : String,

    /// The idcode for this device.
    idcode: u32,

    /// A value from the DeviceTypes enumeration identifying the type of the
    /// device.
    device_type : DeviceTypes,
}

impl DeviceNode {
    /// Constructor.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name to use.
    /// - idcode
    ///
    ///   idcode for the device.
    /// - tap_type
    ///
    ///   Value from the DeviceTypes enumeration.
    /// - initially_visible
    ///
    ///   true if initially visible; otherwise false.
    ///
    /// # Returns
    /// Returns a new DeviceNode instance.
    fn new(name: &str, idcode: u32, tap_type: DeviceTypes, initially_visible: bool) -> DeviceNode {
        DeviceNode {
            _name: name.to_string(),
            idcode: idcode,
            device_type: tap_type,
            visible: initially_visible,
        }
    }
}

//=============================================================================

/// Represents a device chain, which is a collection of DeviceNode objects.
/// Part of the "Facade" pattern example.
struct DeviceChain {
    /// The list of DeviceNodes on this device chain.
    _nodes: Vec<DeviceNode>,

    /// The Name of this device chain.
    _name: String,

    /// Whether this device chain is locked for access.
    locked: bool,
}

impl DeviceChain {
    /// Constructor.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of this device chain
    ///
    /// # Returns
    /// Returns a new DeviceChain instance.
    pub fn new(name: &str) -> DeviceChain {
        DeviceChain {
            _name: name.to_string(),
            locked: false,
            _nodes: vec![]
        }
    }

    /// Helper method to add a DeviceNode to the device chain.  DeviceNode
    /// objects that are of DEVICECONTROLLER are always inserted as the first
    /// device in the device chain, with the assumption there is only one
    /// DEVICECONTROLLER in a given device chain (this is not actually
    /// enforced, though).
    ///
    /// # Parameters
    /// - node
    ///
    ///   A DeviceNode object to add to the device chain.
    pub fn add_node(&mut self, node: DeviceNode) {
        match node.device_type {
            DeviceTypes::DEVICECONTROLLER => self._nodes.insert(0, node),
            _ => self._nodes.push(node)
        }
    }

    /// Resets the device chain so that all devices that are not CLdevices are
    /// no longer visible in the device chain.
    pub fn reset_visibility(&mut self) {
        for node in self._nodes.iter_mut() {
            if let DeviceTypes::DEVICECONTROLLER = node.device_type {
                // Device Controller's visibility is never touched
            } else {
                node.visible = false;
            }
        }
    }

    /// Make visible one or more devices in the device chain.
    ///
    /// # Parameters
    /// - node_select_mask
    ///
    ///   A bit mask specifying which device or devices to make visible, where
    ///   bit 0 is the first device, bit 1 is the second, etc.  Bit 0 is
    ///   ignored as the first device is always visible.
    pub fn select_nodes(&mut self, node_select_mask: u32) {
        self._show_hide_nodes(node_select_mask, true);

    }

    /// Make invisible one or more devices in the device chain.
    ///
    ///
    /// # Parameters
    /// - node_select_mask
    ///
    /// A bit mask specifying which device or devices to hide, where bit 0 is
    /// the first device, bit 1 is the second, etc.  Bit 0 is ignored as the
    ///  first device is always visible.
    pub fn deselect_nodes(&mut self, node_select_mask: u32) {
        self._show_hide_nodes(node_select_mask, false);
    }
   
    /// Retrieve a list of idcodes for all devices that are visible in
    /// the device chain.
    ///
    /// # Returns
    /// Returns an array of unsigned 32-bit integers corresponding to the
    /// idcodes of each visible device.  The first idcode corresponds to the
    /// first visible device.
    pub fn get_id_codes_for_visible_nodes(&self) -> Vec<u32> {
        let mut idcodes : Vec<u32> = vec![];

        for node in self._nodes.iter() {
            if node.visible {
                idcodes.push(node.idcode);
            }
        }
        idcodes
    }


    /// Helper method to show or hide devices on the device chain.
    ///
    /// # Parameters
    /// - node_select_mask
    ///
    ///   A bit mask where the position of each bit corresponds to a device in
    ///   the device chain, with bit 0 being the first device, bit 1 being the
    ///   second device, and so on.
    /// - make_visible
    ///
    ///   true if the device is to be made visible on the device chain;
    ///   otherwise false, the device cannot be seen on the device chain.
    fn _show_hide_nodes(&mut self, node_select_mask: u32, make_visible: bool) {
        let mut bit_mask: u32 = 0x2; // bit 0 is always the DEVICECONTROLLER and is always selected
        let num_nodes = self._nodes.len();

        // Start at the device after the DEVICECONTROLLER
        for index in 1..num_nodes {
            if (bit_mask & node_select_mask) != 0 {
                self._nodes[index].visible = make_visible;
            }
            bit_mask <<= 1;
            if bit_mask == 0 {
                // We don't allow more than 32 devices
                break;
            }
        }
    }
}

//-----------------------------------------------------------------------------

/// Represents some kind of system that contains multiple device chains.
/// Part of the "Facade" pattern example.
///
/// The following operations are available:
///  - get_num_chains()
///  - lock_devices()
///  - unlock_devices()
///  - reset_devices()
///  - select_devices()
///  - deselect_devices()
///  - get_idcodes()
pub struct FacadeComplicatedSubSystem {
    device_chains: Vec<DeviceChain>,
}

impl FacadeComplicatedSubSystem {
    /// Constructor.
    pub fn new() -> Box<dyn IDeviceNetworkLowLevel> {
        let mut device_chain0 = DeviceChain::new("CHAIN0");
        let mut device_chain1 = DeviceChain::new("CHAIN1");

        device_chain0.add_node(DeviceNode::new("DDD_DEVCTRL0", 0x10101010, DeviceTypes::DEVICECONTROLLER, true));
        device_chain0.add_node(DeviceNode::new("DDD_CORE0", 0x20202020, DeviceTypes::CORE, false));
        device_chain0.add_node(DeviceNode::new("DDD_GTE0", 0x30303030, DeviceTypes::GTE, false));

        device_chain1.add_node(DeviceNode::new("DDD_DEVCTRL1", 0x10101011, DeviceTypes::DEVICECONTROLLER, true));
        device_chain1.add_node(DeviceNode::new("DDD_PCH0", 0x40404040, DeviceTypes::PCH, false));
        device_chain1.add_node(DeviceNode::new("DDD_PMC0", 0x50505050, DeviceTypes::PMC, false));

        Box::new(FacadeComplicatedSubSystem {
            device_chains: vec![device_chain0, device_chain1],
        })
    }
}

impl IDeviceNetworkLowLevel for FacadeComplicatedSubSystem {
    fn get_num_chains(&self) -> usize {
        self.device_chains.len()
    }

    fn lock_device_chain(&mut self, chain_index: usize) -> bool {
        let mut locked = false;
        if chain_index < self.device_chains.len() {
            if !self.device_chains[chain_index].locked {
                self.device_chains[chain_index].locked = true;
                locked = true;
            }
        }
        locked
    }

    fn unlock_device_chain(&mut self, chain_index: usize) -> bool {
        let mut unlocked = false;
        if chain_index < self.device_chains.len() {
            if self.device_chains[chain_index].locked {
                self.device_chains[chain_index].locked = false;
                unlocked = true;
            }
        }
        unlocked
    }

    fn reset_device_chain(&mut self, chain_index: usize) {
        if chain_index < self.device_chains.len() {
            self.device_chains[chain_index].reset_visibility();
        }
    }

    fn enable_devices_in_device_chain(&mut self, chain_index: usize, devices_select_mask: u32) {
        if chain_index < self.device_chains.len() {
            self.device_chains[chain_index].select_nodes(devices_select_mask);
        }
    }

    fn disable_devices_in_device_chain(&mut self, chain_index: usize, devices_select_mask: u32) {
        if chain_index < self.device_chains.len() {
            self.device_chains[chain_index].deselect_nodes(devices_select_mask);
        }
    }

    fn get_idcodes(&self, chain_index: usize) -> Vec<u32> {
        let mut idcodes: Vec<u32> = vec![];

        if chain_index < self.device_chains.len() {
            idcodes = self.device_chains[chain_index].get_id_codes_for_visible_nodes();
        }

        idcodes
    }
}