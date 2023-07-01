//! Contains the IWorkByProxy trait that is implemented on both the proxy
//! object and the real object.


/// Represents what can be done on the proxy object.
/// This same trait is implemented on the real object as well to ensure both
/// have the same methods.  The program accesses the proxy object only through
/// this trait.
pub trait IWorkByProxy {
    /// Does some work on the given argument and returns a new string.
    fn do_work(&mut self, some_argument: &str) -> String;
}