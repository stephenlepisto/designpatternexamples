//! The Facade design pattern example module
//!
//! The Facade pattern is used when a simplified version of an interface on a
//! complicated sub-system is needed in situations where the whole complicated
//! sub-system does not need to be exposed.
//! 
//! In this example, the complicated subsystem is a representation of a device
//! network complete with scan chains, device idcodes, and device devices that
//! can be selected and deselected.  The Facade exposed by this complex network
//! exposes only the scan chain, getting device idcodes based on an index into
//! those scan chains, resetting the scan chains and selecting a device to
//! appear in the scan chain.
//!
//! Accessed through the facade_exercise() function.

//-----------------------------------------------------------------------------

pub mod facade_idevicenetworkhighlevel_trait;
pub mod facade_idevicenetworklowlevel_trait;
pub mod facade_complicatedsubsystem;
pub mod facade_devicenetworkhighlevel;

//-----------------------------------------------------------------------------

use facade_devicenetworkhighlevel::DeviceNetworkHighLevel;

//-----------------------------------------------------------------------------

/// Helper function to present a formatted list of idcodes for a particular
/// device chain.  The output is on a single line.
///
/// # Parameters
/// - chain_index
///
///   Index of the device chain being displayed.
/// - idcodes
///
///   Array of 32-bit idcodes to be printed in hex.
fn _facade_show_id_codes(chain_index : usize, idcodes: &Vec<u32>)
{
    print!("    On chain {}, idcodes = [ ", chain_index);
    for idcode in idcodes {
        print!("0x{:X} ", idcode);
    }
    println!("]");
}


/// Example of using the "Facade" pattern.
/// 
/// The Facade pattern is used when a simplified version of an
/// interface on a complicated sub-system is needed in situations
/// where the whole complicated sub-system does not need to be
/// exposed.
/// 
/// In this example, the complicated subsystem is a representation of
/// a device network complete with scan chains, device idcodes, and device
/// devices that can be selected and deselected.  The Facade exposed
/// by this complex network exposes only the scan chain, getting
/// device idcodes based on an index into those scan chains, resetting
/// the scan chains and selecting a device to appear in the scan
/// chain.
// ! [Using Facade in Rust]
pub fn facade_exercise() -> Result<(), String> {
    println!("");
    println!("Facade Exercise");

    let mut device_chain_facade = DeviceNetworkHighLevel::new();
    let chain_count = device_chain_facade.num_chains();

    println!("  Showing idcodes of devices after a device reset (expect one device on each chain)...");
    for chain_index in 0..chain_count {
        device_chain_facade.disable_devices_in_device_chain(chain_index);
        let idcodes = device_chain_facade.get_idcodes(chain_index);
        _facade_show_id_codes(chain_index, &idcodes);
    }

    println!("  Showing idcodes of devices after selecting all devices...");
    for chain_index in 0..chain_count {
        device_chain_facade.enable_devices_in_device_chain(chain_index, 0xffffffff);
        let idcodes = device_chain_facade.get_idcodes(chain_index);
        _facade_show_id_codes(chain_index, &idcodes);
    }

    println!("  Done.");

    Ok(())
}
// ! [Using Facade in Rust]
