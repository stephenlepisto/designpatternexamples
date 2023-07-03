//! Contains the EntryInformation struct that holds information about each
//! entry that can be sorted.

//-----------------------------------------------------------------------------

use std::fmt::Display;

//-----------------------------------------------------------------------------

/// Represents an individual with a Name, Age, and Height.
#[derive(Clone)]
pub struct EntryInformation {
    /// Name of this individual.
    pub name: String,
    /// Age of this individual, in years.
    pub age: i32,
    /// Height of this individual, in inches.
    pub height: i32,
}

impl EntryInformation {
    /// Constructor
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of an individual
    /// - age
    ///
    ///   Age of an individual (in years)
    /// - height
    ///
    ///   Height of an individual (in inches)
    ///
    /// # Returns
    /// Returns a new instance of the EntryInformation struct.
    pub fn new(name: &str, age: i32, height: i32) -> EntryInformation {
        EntryInformation {
            name: name.to_string(),
            age,
            height,
        }
    }
}

impl Display for EntryInformation {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_fmt(format_args!("{0:6} {1:3} {2:3}\"", self.name, self.age, self.height))
    }
}
