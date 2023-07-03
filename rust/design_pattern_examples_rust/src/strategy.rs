//! The Strategy design pattern example module
//! 
//! The Strategy pattern provides a way to easily assign different algorithms
//! to an object instance that can be changed at the time the object is
//! created.
//! 
//! In this exercise, the StrategyShowEntries instance sorts and displays a
//! list of EntryInformation elements.  Three different sorting strategies are
//! provided (Name, Age, Height) and an option to reverse the normal order of
//! the sort.
//!
//! Accessed through the strategy_exercise() function.

//-----------------------------------------------------------------------------

pub mod strategy_isortentries_trait;
pub mod strategy_entryinformation;
pub mod strategy_sortentries;
pub mod strategy_showentries;

//-----------------------------------------------------------------------------

use strategy_showentries::StrategyShowEntries;
use strategy_isortentries_trait::SortOptions;
use strategy_entryinformation::EntryInformation;

//-----------------------------------------------------------------------------

/// Helper function to create a list of entries that can be sorted in various
/// ways.
///
/// # Returns
/// Returns a list of EntryInformation objects that can be sorted.
fn create_entries() -> Vec<EntryInformation> {
    let mut entries = vec![];
    // Name, age, height (in inches)
    entries.push(EntryInformation::new("Ronnie", 19, 84));
    entries.push(EntryInformation::new("Elaine", 29, 71));
    entries.push(EntryInformation::new("Jack", 20, 81));
    entries.push(EntryInformation::new("Myra", 35, 78));
    entries.push(EntryInformation::new("Fred", 18, 88));
    
    entries
}

/// Example of using the "Strategy" design pattern.
/// 
/// The Strategy pattern provides a way to easily assign different algorithms
/// to an object instance that can be changed at the time the object is
/// created.
/// 
/// In this exercise, the StrategyShowEntries instance sorts and displays a
/// list of EntryInformation elements.  Three different sorting strategies are
/// provided (Name, Age, Height) and an option to reverse the normal order of
/// the sort.
// ! [Using Strategy in Rust]
pub fn strategy_exercise() -> Result<(), String> {
    println!("");
    println!("Strategy Exercise");

    let entries = create_entries();

    let display_name_ascending = StrategyShowEntries::new(SortOptions::ByName, false);
    display_name_ascending.show_entries(&entries);

    let display_age_ascending = StrategyShowEntries::new(SortOptions::ByAge, false);
    display_age_ascending.show_entries(&entries);

    let display_name_ascending = StrategyShowEntries::new(SortOptions::ByHeight, true);
    display_name_ascending.show_entries(&entries);

    println!("  Done.");

    Ok(())
}
// ! [Using Strategy in Rust]
