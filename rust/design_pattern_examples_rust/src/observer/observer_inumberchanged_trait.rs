//! Contains the IObserverNumberChanged trait, which is implemented on a struct
//! and then passed to the ObserverNumberProducer struct when notifications are
//! wanted about changes to the number in the ObserverNumberProducer struct.

//-----------------------------------------------------------------------------

/// Represents an observer to the ObserverNumberProducer struct.  An observer
/// implements this trait and then subscribes to the ObserverNumberProducer
/// struct with the trait.  The observer will be called whenever a change in
/// the number is made.
/// 
/// This trait is specific to the ObserverNumberProducer struct example, which
/// is a typical requirement for a subject that supports observers.
pub trait IObserverNumberChanged {
    /// This is called whenever the number in the ObserverNumberProducer object
    /// is changed.
    ///
    /// # Parameters
    /// - The updated number the observer is being told about.
    fn notify(&mut self, updated_number: u32);
}
