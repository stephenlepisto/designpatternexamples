//! The Observer design pattern example module
//! 
//! The Observer pattern allows for one or more observers to react to changes
//! in a Subject entity.
//! 
//! In this exercise, a number producer (the Subject) updates an internal
//! value every time the update() method is called.  Three different
//! observers are attached to the number producer and print out the
//! current value in different formats whenever the number is changed.
//!
//! Accessed through the observer_exercise() function.

//-----------------------------------------------------------------------------

pub mod observer_inumberchanged_trait;
pub mod observer_numberproducer;
pub mod observer_observers;

//-----------------------------------------------------------------------------

use observer_numberproducer::ObserverNumberProducer;
use observer_observers::{ObserverDecimal, ObserverHexadecimal, ObserverBinary};

//-----------------------------------------------------------------------------

/// Example of using the "Observer" design pattern.
/// 
/// The Observer pattern allows for one or more observers to react to changes
/// in a Subject entity.
/// 
/// In this exercise, a number producer (the Subject) updates an internal
/// value every time the update() method is called.  Three different
/// observers are attached to the number producer and print out the
/// current value in different formats whenever the number is changed.
/// 
/// Note: Interfaces are used throughout this example.  For example, to
/// subscribe to the number producer, the IEventNotifications interface
/// must be obtained from the number producer.  The number producer is
/// represented to the observers with the INumberProducer interface and
/// the observers are represented to the number producer with the
/// IObserverNumberChanged interface.  This highlights a common way to
/// implement a "pull" style observer without having too much knowledge
/// about the Subject.
// ! [Using Observer in Rust]
pub fn observer_exercise() -> Result<(), String> {
    println!("");
    println!("Observer Exercise");

    let mut number_producer = ObserverNumberProducer::new();
    let observer_decimal = ObserverDecimal::new();
    let observer_hexadecimal = ObserverHexadecimal::new();
    let observer_binary = ObserverBinary::new();

    // Add all observers to the number producer.
    number_producer.add_observer(&observer_decimal);
    number_producer.add_observer(&observer_hexadecimal);
    number_producer.add_observer(&observer_binary);

    // Call the number producer's update() method a number of times.
    // The observers automatically print out the current value in
    // different bases.
    for index in 0..10 {
        println!("  update {0} on number producer.  Results from observers:", index);
        number_producer.update();
    }

    // When done, remove the observers from the number producer.
    // It's always good to clean up after ourselves.
    number_producer.remove_observer(&observer_binary);
    number_producer.remove_observer(&observer_hexadecimal);
    number_producer.remove_observer(&observer_decimal);

    println!("  Done.");

    Ok(())
}
// ! [Using Observer in Rust]
