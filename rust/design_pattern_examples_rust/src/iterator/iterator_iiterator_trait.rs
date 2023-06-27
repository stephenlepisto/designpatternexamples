//! Definition of the IIterator trait that is implemented by the various
//! iterators shown in the "Iterator" design pattern example.

pub trait IIterator<T> {
    /// Retrieve the next item Some\<T\> from the iterator.  Returns None if there
    /// are no more items to iterator over.
    fn next(&mut self) -> Option<T>;
}
