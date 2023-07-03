//! Contains the SortOptions enum and the ISortEntries trait that represents
//! different sorting strategies.

//-----------------------------------------------------------------------------

use super::strategy_entryinformation::EntryInformation;

//-----------------------------------------------------------------------------

/// Identifies the different sorting strategies available.
pub enum SortOptions {
    /// Sort alphabetically by name in ascending order.
    ByName,

    /// Sort numerically by age in ascending order.
    ByAge,

    /// Sort numerically by height in ascending order.
    ByHeight,
}


/// Represents a sorting strategy.
pub trait ISortEntries {

    /// Sort the specified list of entries in place.
    ///
    /// # Parameters
    /// - entries
    ///
    ///   The list of entries to sort.
    fn sort(&self, entries: &mut Vec<EntryInformation>);

    /// Retrieve a string representation of the sorting strategy.
    ///
    /// # Returns
    /// Returns a string containing the name of the sorting strategy this
    /// trait represents.
    fn as_string(&self) -> String;
}
