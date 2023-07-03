//! Contains the StrategyShowEntries struct that can make use of different
//! sorting strategies to show an ordered list of entries.

//-----------------------------------------------------------------------------

use super::strategy_sortentries::SortStrategyFactory;
use super::strategy_entryinformation::EntryInformation;
use super::strategy_isortentries_trait::{SortOptions,ISortEntries};

//-----------------------------------------------------------------------------

/// Represents a way of displaying a list of EntryInformation objects in a
/// particular order.  The order of sorting is a strategy that can be
/// specified when the struct is instantiated.  The sorting strategy can be
/// modified with a flag indicating whether the sort is reversed from normal
/// (in this case, descending instead of ascending).
///
/// In this particular approach, a struct with a specific sorting strategy
/// is instantiated.  The instance can be applied to any number of lists to
/// achieve the specified sorting behavior.  Note that the sorting behavior
/// cannot be changed once the StrategyShowEntries struct is instantiated.
/// 
/// An alternative implementation would be to pass the choice of sorting
/// strategy to the show_entries() method and instantiate the sorting
/// struct there and the list is sorted and displayed using the specified
/// sorting strategy.  The advantage of this approach is that only one instance
/// of the StrategyShowEntries struct is needed.  The disadvantage is the need
/// for two additional parameters that must be passed in all the time along
/// with the entries to be sorted (there might be places in the program where
/// the sorting strategy is not known or is unavailable from the user).
pub struct StrategyShowEntries {
    /// Specify the sort direction (true = Ascending, false = Descending).
    reversed_sort: bool,
    /// The sorting strategy to use.
    sort_strategy: Box<dyn ISortEntries>,
}

impl StrategyShowEntries {
    /// Constructor.
    ///
    /// # Parameters
    /// - sort_option
    ///
    ///   A value from the SortOptions enumeration indicating the sorting
    ///   strategy to use.
    /// - reversed_sort
    ///
    ///   true if to sort in descending order; otherwise, sort in ascending
    ///   order.
    ///
    /// # Returns
    /// Returns a new instance of the StrategyShowEntries struct.
    pub fn new(sort_options: SortOptions, reversed_sort: bool) -> StrategyShowEntries {
        StrategyShowEntries {
            reversed_sort,
            sort_strategy : SortStrategyFactory::new(sort_options, reversed_sort),
        }
    }

    /// Display the specified entries in sorted order.  The sorting strategy
    /// and the order of the sort were established when the
    /// StrategyShowEntries struct was instantiated.
    ///
    /// # Parameters
    /// - entries
    ///
    ///   The list of entries to sort and display.  The original list is not
    ///   changed.
    pub fn show_entries(&self, entries: &Vec<EntryInformation>) {
        // Make a local copy of the entries so we don't disturb the original list.
        let mut local_entries = entries.to_vec();

        self.sort_strategy.sort(&mut local_entries);

        // This is a tabular display, making it easier to follow the sorted data.
        let sort_order = match self.reversed_sort {
            true => "Descending",
            false => "Ascending",
        };
        
        println!("    Sort strategy: {0} (order = {1})", self.sort_strategy.as_string(), sort_order);
        
        println!("      {0:6} {1:3} {2:3}", "Name", "Age", "Height");
        println!("      {0:6} {1:3} {2:3}", "------", "---", "------");
        for entry in local_entries {
            println!("      {0}", entry);
        }
    }
}
