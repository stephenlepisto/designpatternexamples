//! Contains the BigResourceManager struct that manages the large resource(s)
//! containing big images used by the Flyweight class.

//-----------------------------------------------------------------------------

use super::flyweight_bigresource::BigResource;

//-----------------------------------------------------------------------------


/// Represents a list of instances of the BigResource struct.  Use the
/// add_resource() method to add a BigResource instance to the list (and
/// also take ownership of the BigResource instance).  Call get_resource()
/// with the ID of the resource to get the BigResource instance.
pub struct BigResourceManager {
    resources: Vec<BigResource>,
}

impl BigResourceManager {
    pub fn new() -> BigResourceManager {
        BigResourceManager { resources: vec![] }
    }

    /// Add a BigResource object to the list of big resources.  The list takes
    /// ownership of the BigResource object.
    /// 
    /// # Parameters
    /// - resource
    ///
    ///   The BigResource to store in the manager.
    ///
    /// # Returns
    /// Returns the "id" of the resource so it can be used to access the
    /// resource later on.  Technically, the ID is actually the index where the
    /// BigResource instance appears in the internal list.
    pub fn add_resource(&mut self, resource: BigResource) -> usize {
        let resource_index = self.resources.len();
        self.resources.push(resource);
        resource_index
    }


    /// Retrieve the requested big resource.
    ///
    /// # Parameters
    /// - resource_id
    ///
    ///   The ID of the resource to retrieve.
    ///
    /// # Returns
    /// Returns Some(&BigResource) if the resource exists; otherwise, returns
    /// None.
    pub fn get_resource(&self, resource_id: usize) -> Option<&BigResource> {
        if resource_id < self.resources.len() {
            Some(&self.resources[resource_id])
        } else {
            None
        }
    }
}
