//! Contains the ObserverNumberProducer struct that maintains a number, along
//! with a list of observers to changes in that number, as represented by the
//! IObserverNumberChanged trait.

//-----------------------------------------------------------------------------

use std::rc::Rc;
use std::cell::RefCell;

use super::observer_inumberchanged_trait::IObserverNumberChanged;

//-----------------------------------------------------------------------------

/// Represents the Observer Subject in this example, in this case, a struct
/// that contains a single number that is updated with a call to the update()
/// method.  Whenever update() is called, the number is incremented and all
/// observers are notified.  The observers are passed ("pushed") the changed
/// number through the IObserverNumberChanged trait.
pub struct ObserverNumberProducer {
    /// The number being maintained.
    number: u32,
    /// The list of observers subscribed to this class instance.
    observers: Vec<Rc<RefCell<dyn IObserverNumberChanged>>>,
}


impl ObserverNumberProducer {
    /// Default constructor
    pub fn new() -> ObserverNumberProducer {
       ObserverNumberProducer {
           number: 0,
           observers : vec![],
       }
    }

    /// Call this method to subscribe an observer to this struct for
    /// notifications about changing numbers.  Does nothing if the given
    /// observer is already subscribed.
    ///
    /// # Parameters
    /// - observer
    ///
    ///   The observer as represented by the IObserverNumberChanged trait.
    pub fn add_observer(&mut self, observer: &Rc<RefCell<dyn IObserverNumberChanged>>) {
        let found_index = self.find_index_of_observer(observer);
        if let None = found_index {
            self.observers.push(observer.clone());
        }
    }

    /// Call this method to unsubscribe an observer from this struct so
    /// notifications are no longer received.  Does nothing if the given
    /// observer was not subscribed.
    ///
    /// # Parameters
    /// - observer
    ///
    ///   The observer as represented by the IObserverNumberChanged trait.
    pub fn remove_observer(&mut self, observer: &Rc<RefCell<dyn IObserverNumberChanged>>) {
        let found_index = self.find_index_of_observer(observer);
        if let Some(index) = found_index {
            self.observers.remove(index);
        }
    }

    /// Update the number then notify all observers.
    pub fn update(&mut self) {
        self.number += 1;
        self.notify_observers();
    }

    /// Helper method to retrieve the index to the specified observer if the
    /// observer is in the list.
    ///
    /// # Parameters
    /// - observer
    ///
    ///   The observer as represented by the IObserverNumberChanged trait.
    ///
    /// # Returns
    /// Returns Some(index) if the observer was found; otherwise, returns None.
    fn find_index_of_observer(&self, observer: &Rc<RefCell<dyn IObserverNumberChanged>>) -> Option<usize> {
        self.observers.iter().position(|x| x.as_ptr() == observer.as_ptr())
    }

    /// Helper method to notify all observers that the number has changed.
    fn notify_observers(&self) {
        if !self.observers.is_empty() {
            // Copy the list so observers can change the original observers
            // during the notification (this isn't strictly needed in this
            // example but it is good practice for any notification system
            // that handles multiple observers where multiple threads might
            // be in play or observers can unsubscribe at any time, even in
            // the event notification).
            let local_observers: Vec<Rc<RefCell<dyn IObserverNumberChanged>>> = self.observers.clone();

            for observer in local_observers.iter() {
                observer.borrow_mut().notify(self.number);
            }
        }
    }
}

