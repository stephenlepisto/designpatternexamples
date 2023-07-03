//! Contains the structs representing the various sorting strategies:
//! StrategySortByName, StrategySortByAge, and StrategySortByHeight, along with
//! a factory, SortStrategyFactory, that can instantiate a desired sorting
//! strategy.

//-----------------------------------------------------------------------------

use super::strategy_entryinformation::EntryInformation;
use super::strategy_isortentries_trait::{SortOptions,ISortEntries};

//-----------------------------------------------------------------------------

/// Strategy for sorting the names in ascending (or descending) order.
struct StrategySortByName {
    /// Controls order of sort: true for descending, false for ascending.
    reversed_sort: bool,
}

impl StrategySortByName {
    /// Constructor.
    ///
    /// # Parameters
    /// - reversed_sort
    ///
    ///   true if to sort in descending order; otherwise, sort in ascending
    ///   order.
    ///
    /// # Returns
    /// Returns a new instance of the StrategySortByName struct as
    /// represented by the ISortEntries trait.
    fn new(reversed_sort: bool) -> Box<dyn ISortEntries> {
        Box::new(StrategySortByName {
            reversed_sort
        })
    }
}

impl ISortEntries for StrategySortByName {
    fn sort(&self, entries: &mut Vec<EntryInformation>) {
        entries.sort_by(|left, right| {
                if self.reversed_sort {
                    right.name.cmp(&left.name)
                } else {
                    left.name.cmp(&right.name)
                }
            }
        )
    }

    fn as_string(&self) -> String {
        String::from("StrategySortByName")
    }
}

//#############################################################################
//#############################################################################

/// Strategy for sorting the age in ascending (or descending) order.
struct StrategySortByAge {
    /// Controls order of sort: true for descending, false for ascending.
    reversed_sort: bool,
}

impl StrategySortByAge {
    /// Constructor.
    ///
    /// # Parameters
    /// - reversed_sort
    ///
    ///   true if to sort in descending order; otherwise, sort in ascending
    ///   order.
    ///
    /// # Returns
    /// Returns a new instance of the StrategySortByAge struct as
    /// represented by the ISortEntries trait.
    fn new(reversed_sort: bool) -> Box<dyn ISortEntries> {
        Box::new(StrategySortByAge {
            reversed_sort
        })
    }
}

impl ISortEntries for StrategySortByAge {
    fn sort(&self, entries: &mut Vec<EntryInformation>) {
        entries.sort_by(|left, right| {
                if self.reversed_sort {
                    right.age.cmp(&left.age)
                } else {
                    left.age.cmp(&right.age)
                }
            }
        )
    }

    fn as_string(&self) -> String {
        String::from("StrategySortByAge")
    }
}

//#############################################################################
//#############################################################################

/// Strategy for sorting the height in ascending (or descending) order.
struct StrategySortByHeight {
    /// Controls order of sort: true for descending, false for ascending.
    reversed_sort: bool,
}

impl StrategySortByHeight {
    /// Constructor.
    ///
    /// # Parameters
    /// - reversed_sort
    ///
    ///   true if to sort in descending order; otherwise, sort in ascending
    ///   order.
    ///
    /// # Returns
    /// Returns a new instance of the StrategySortByHeight struct as
    /// represented by the ISortEntries trait.
    fn new(reversed_sort: bool) -> Box<dyn ISortEntries> {
        Box::new(StrategySortByHeight {
            reversed_sort
        })
    }
}

impl ISortEntries for StrategySortByHeight {
    fn sort(&self, entries: &mut Vec<EntryInformation>) {
        entries.sort_by(|left, right| {
                if self.reversed_sort {
                    right.height.cmp(&left.height)
                } else {
                    left.height.cmp(&right.height)
                }
            }
        )
    }

    fn as_string(&self) -> String {
        String::from("StrategySortByHeight")
    }
}

//#############################################################################
//#############################################################################

/// Holds the factory used for instantiating for the sorting strategies.
pub struct SortStrategyFactory { }

impl SortStrategyFactory {
    /// Constructor.
    ///
    /// Generate an instance of a sorting strategy based on the given sorting
    /// option and reversed sort flag.  A new instance of the sorting strategy
    /// is created each time this method is called.
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
    /// Returns a new instance of a sorting strategy as represented by the
    /// ISortEntries trait.
    pub fn new(sort_option: SortOptions, reversed_sort: bool) -> Box<dyn ISortEntries> {
        match sort_option {
            SortOptions::ByName => StrategySortByName::new(reversed_sort),
            SortOptions::ByAge => StrategySortByAge::new(reversed_sort),
            SortOptions::ByHeight => StrategySortByHeight::new(reversed_sort)
        }
    }
}
