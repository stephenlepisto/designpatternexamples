//! Contains the ObserverDecimal, ObserverHexadecimal, and ObserverBinary
//! structs representing the various observers that can be used in this
//! Observer design pattern example.

//-----------------------------------------------------------------------------

use std::{rc::Rc, cell::RefCell};

use super::observer_inumberchanged_trait::IObserverNumberChanged;

//-----------------------------------------------------------------------------


/// Represents an observer that prints out the current number from the
/// Subject in decimal.
pub struct ObserverDecimal { }

impl ObserverDecimal {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the ObserverDecimal class as represented by
    /// the IObserverNumberChanged trait.
    pub fn new() -> Rc<RefCell<dyn IObserverNumberChanged>> {
        Rc::new(RefCell::new(ObserverDecimal {}))
    }

    /// Helper method to display the number in decimal.
    ///
    /// # Parameters
    /// - number
    ///
    ///   The number to display.
    fn show(&self, number: u32) {
        println!("    Decimal    : {0}", number);
    }
}

impl IObserverNumberChanged for ObserverDecimal {
    fn notify(&mut self, updated_number: u32) {
        self.show(updated_number);
    }
}

//#############################################################################
//#############################################################################

/// Represents an observer that prints out the current number from the
/// Subject in hexadecimal.
pub struct ObserverHexadecimal { }

impl ObserverHexadecimal {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the ObserverHexadecimal class as represented
    /// by the IObserverNumberChanged trait.
    pub fn new() -> Rc<RefCell<dyn IObserverNumberChanged>> {
        Rc::new(RefCell::new(ObserverHexadecimal {}))
    }

    /// Helper method to display the number in hexadecimal.
    ///
    /// # Parameters
    /// - number
    ///
    ///   The number to display.
    fn show(&self, number: u32) {
        println!("    Hexadecimal: 0X{0:08X}", number);
    }
}

impl IObserverNumberChanged for ObserverHexadecimal {
    fn notify(&mut self, updated_number: u32) {
        self.show(updated_number);
    }
}

//#############################################################################
//#############################################################################

/// Represents an observer that prints out the current number from the
/// Subject in binary.
pub struct ObserverBinary { }

impl ObserverBinary {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the ObserverBinary class as represented by
    /// the IObserverNumberChanged trait.
    pub fn new() -> Rc<RefCell<dyn IObserverNumberChanged>> {
        Rc::new(RefCell::new(ObserverBinary {}))
    }

    /// Helper method to display the number in binary.
    ///
    /// # Parameters
    /// - number
    ///
    ///   The number to display.
    fn show(&self, number: u32) {
        println!("    Binary     : 0b{0:032b}", number);
    }
}

impl IObserverNumberChanged for ObserverBinary {
    fn notify(&mut self, updated_number: u32) {
        self.show(updated_number);
    }
}
