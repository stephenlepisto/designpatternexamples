//! Implementation of the Items container, and the KeyIterator, ValueIterator,
//! and ItemIterator structs that each implement the IIterator trait.

//-----------------------------------------------------------------------------

use super::iterator_iiterator_trait::IIterator;

//-----------------------------------------------------------------------------

/// Represents a container that offers up three kinds of iterators for the
/// hard-coded contents, one that iterates over the "keys", one that iterates
/// over the "values", and one that iterates over "key"/"value" pairs.
/// 
/// This container is not a dictionary despite the use of "keys" and
/// "values"; it's just a simple example of a container that can be iterated
/// over without using any iterators provided by Rust.
pub struct Items {
    /// A collection of "keys" that can be iterated over.
    keys: Vec<String>,
    /// A collectio of "values" that can be iterated over.
    values: Vec<String>,
}

//-----------------------------------------------------------------------------

/// Represents a key/value pair where the key and value are strings.
pub struct ItemPair {
    /// The key part of the item.
    pub key: String,
    /// The value part of the item.
    pub value: String,
}

//-----------------------------------------------------------------------------

/// Represents an iterator over the data that returns an ItemPair object
/// containing both key and value for each entry.  This struct is always
/// represented publicly by the IIterator\<ItemPair\> trait.
pub struct ItemIterator<'a> {
    items: &'a Items,
    iterator: usize,
}

/// Represents an iterator over the "key" part of the data, where the
/// data returned from the iterator is a string type.  This struct is always
/// represented publicly by the IIterator\<String\> trait.
pub struct KeyIterator<'a> {
    items: &'a Items,
    iterator: usize,
}

/// Represents an iterator over the "value" part of the data, where the
/// data returned from the iterator is a string type.  This struct is always
/// represented publicly by the IIterator\<String\> trait.
pub struct ValueIterator<'a> {
    items: &'a Items,
    iterator: usize,
}

impl<'a> Items {
    /// Constructor
    ///
    /// Fills this container with a hard-coded list of "keys" and "values".
    pub fn new() -> Items {
        Items {
            keys: vec!(String::from("One"), String::from("Two"), String::from("Three")),
            values: vec!(String::from("Value 1"), String::from("Value 2"), String::from("Value 3")),
        }
    }


    /// Retrieve an iterator over the data that returns an ItemPair object
    /// containing both key and value for each entry.
    ///
    /// #Returns
    /// Returns an IIterator<ItemPair> trait representing the iterator.
    pub fn get_items(&'a self) -> impl IIterator<ItemPair> + 'a {
        ItemIterator { items: self, iterator: 0 }
    }

    /// Retrieve an iterator over the "key" part of the data, where the
    /// data returned from the iterator is a string type.
    ///
    /// #Returns
    /// Returns an IIterator<String> trait representing the iterator.
    pub fn get_keys(&'a self) -> impl IIterator<String> + 'a {
        KeyIterator { items: self, iterator: 0 }
    }

    /// Retrieve an iterator over the "value" part of the data, where the
    /// data returned from the iterator is a string type.
    ///
    /// #Returns
    /// Returns an IIterator<String> trait representing the iterator.
    pub fn get_values(&'a self) -> impl IIterator<String> + 'a {
        ValueIterator { items: self, iterator: 0 }
    }
}


impl<'a> IIterator<ItemPair> for ItemIterator<'a> {
    fn next(&mut self) -> Option<ItemPair> {
        if self.iterator < self.items.keys.len() {
            let index = self.iterator;
            self.iterator += 1;
            Some(ItemPair {
                key: self.items.keys[index].to_string(),
                value: self.items.values[index].to_string()
            })
        } else {
            None
        }
    }
}

impl<'a> IIterator<String> for KeyIterator<'a> {
    fn next(&mut self) -> Option<String> {
        if self.iterator < self.items.keys.len() {
            let index = self.iterator;
            self.iterator += 1;
            Some(self.items.keys[index].to_string())
        } else {
            None
        }
    }
}


impl<'a> IIterator<String> for ValueIterator<'a> {
    fn next(&mut self) -> Option<String> {
        if self.iterator < self.items.values.len() {
            let index = self.iterator;
            self.iterator += 1;
            Some(self.items.values[index].to_string())
        } else {
            None
        }
    }
}
