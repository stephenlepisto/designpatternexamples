//! Contains the ProxyEntity struct that locally represents a (possibly remote)
//! real entity.  In this example, the real entity being proxied is located in
//! its own module.

//-----------------------------------------------------------------------------

use super::proxy_iworkbyproxy_trait::IWorkByProxy;
use super::proxy_real::RealEntity;

//-----------------------------------------------------------------------------

/// The proxy entity that implements the IWorkByProxy and forwards the calls
/// on that trait to a real entity, which is instantiated when the do_work()
/// method on the IWorkByProxy trait is first called.
pub struct ProxyEntity {
    /// The one and only instance of the real entity associated with this
    /// proxy entity.  Initialized with None so it can be filled in later with
    /// a pointer to the actual real entity instance.
    real_entity: Option<Box<dyn IWorkByProxy>>,
}

impl ProxyEntity {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the ProxyEntity struct as implemented by the
    /// IWorkByProxy trait.
    pub fn new() -> Box<dyn IWorkByProxy> {
        Box::new(ProxyEntity {
            real_entity: None,
        })
    }

    /// Helper method to retrieve the one and only instance of the
    /// real entity.  This hides the details of instantiating the real
    /// entity and enforces a "singleton" nature on the instance.
    ///
    /// # Returns
    /// Returns a reference to the real entity as implemented by the
    /// IWorkByProxy trait.
    pub fn get_real_entity(&mut self) -> &mut Box<dyn IWorkByProxy> {
        if let None = self.real_entity {
            self.real_entity = Some(RealEntity::new());
        }
        self.real_entity.as_mut().unwrap()
    }
}

impl IWorkByProxy for ProxyEntity {
    fn do_work(&mut self, some_argument: &str) -> String {
        println!("  --> proxy class DoWork() in");
        let real_entity = self.get_real_entity();
        println!("  --> Forwarding DoWork() call to real entity...");
        real_entity.do_work(some_argument)
    }
}
