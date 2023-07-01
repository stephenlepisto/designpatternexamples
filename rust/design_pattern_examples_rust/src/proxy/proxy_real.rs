//! Contains the RealEntity struct that represents a (possibly remote) entity
//! for which a proxy is needed.  In this example, the RealEntity is located in
//! its own module.

//-----------------------------------------------------------------------------

use super::proxy_iworkbyproxy_trait::IWorkByProxy;

//-----------------------------------------------------------------------------

/// The real struct object that does all the work.
/// 
/// This would normally be a very expensive struct to instantiate and/or be
/// running on the server end of a remoting channel.  For demonstration
/// purposes, imagine this struct takes many seconds to instantiate.
pub struct RealEntity { }

impl RealEntity {
    /// Constructor
    ///
    /// # Returns
    /// Returns an instance of the RealEntity struct as represented by the
    /// IWorkByProxy trait.
    pub fn new() -> Box<dyn IWorkByProxy> {
        println!("  --> Creating instance of real entity...");
        Box::new(RealEntity {})
    }
}

impl IWorkByProxy for RealEntity {
    fn do_work(&mut self, some_argument: &str) -> String {
        format!("Real class received '{0}'", some_argument)
    }
}