//! The Iterator design pattern example module
//!
//! A custom container is instantiated (it already contains hard-coded data
//! to iterate over).  The custom container can then deliver three
//! iterators, each providing a different aspect of the hard-coded data.
//!
//! Accessed through the iterator_exercise() function.

//-----------------------------------------------------------------------------

pub mod iterator_iiterator_trait;
pub mod iterator_iterators;

//-----------------------------------------------------------------------------

use iterator_iiterator_trait::IIterator;
use iterator_iterators::Items;

//-----------------------------------------------------------------------------

/// Example of using the "Iterator" design pattern.
/// 
/// A custom container is instantiated (it already contains hard-coded data
/// to iterate over).  The custom container can then deliver three
/// iterators, each providing a different aspect of the hard-coded data.
/// 
/// The output shows the output from each iterator.
// ! [Using Iterator in Rust]
pub fn iterator_exercise() -> Result<(), String> {
    println!("");
    println!("Iterator Exercise");

    // For this example, the class already has built into it the data
    // to be iterated over.

    // Instantiate the container to be iterated over.
    let items = Items::new();
 
    println!("  Iterating over keys only:");
    let mut key_iterator = items.get_keys();
    loop {
        match key_iterator.next() {
            Some(key) => println!("    {key}"),
            None => break,
        }
    }

    println!("  Iterating over values only:");
    let mut value_iterator = items.get_values();
    loop {
        match value_iterator.next() {
            Some(value) => println!("    {value}"),
            None => break,
        }
    }

    println!("  Iterating over all items:");
    let mut item_iterator = items.get_items();
    loop {
        match item_iterator.next() {
            Some(item) => println!("    {} = {}", item.key, item.value),
            None => break,
        }
    }

    println!("  Done.");

    Ok(())
}
// ! [Using Iterator in Rust]
