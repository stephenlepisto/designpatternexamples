// The Iterator pattern is used in situations where a collection of items
// needs to be iterated over.  That is, where each item needs to be accessed
// in some sequence, one at a time.
//
// The C++ Standard Template Library (STL) provides many examples of such
// iterators on the various STL container classes.  And in general, a C++-
// based program should use those containers whenever possible because they
// are well-tested and can have any number of pre-defined algorithms applied,
// including the ability to easily iterate over the contents of the
// containers.
//
// Other programming languages such as C# have varying degrees of built-in
// support for iterators over containers.  For example, in C#, all containers
// can provide an iterator over the contents of the container.  Again, in
// general you should use the built-in containers provided by the language
// whenever possible to take advantage of well-tested code, including the
// iterators.
//
// A non-object-oriented kind of iterator uses an opaque token to represent
// the index into the data.  A function retrieves this token pointing to the
// first item.  A second function increments the index in the token to point
// to the next item.  These functions can be implemented on the container
// itself as methods or they can be functions that accept the container and
// know how to get the number of items from the container and how to get the
// items themselves from the container.
//
// An iterator doesn't actually have to have a container to draw from or at
// least not a container visible to the caller.  The iterator could be three
// functions: One to start the iteration, the second to retrieve the next item
// in the iteration, and the third function to release or close the iteration.
// The functions know what they are iterating over and the starting function
// takes parameters to adjust what is actually iterated over.  A good example
// of this kind of iterator is the Win32 find file functions, FindFirstFile(),
// FindNextFile(), FindClose().
//
// The simplest kind of iterator is typically implemented on the container
// itself as a pair of methods: One method returns the number of items to
// iterate over and a second method returns the item at the specified index.
// The caller then increments (or decrements) the index passed into the second
// function.  This is a form of random-access iterator where the items can be
// accessed in any order.
//
// Having said all that, here is an example of how an object-oriented iterator
// can be implemented.  In this case, the example uses the interface IIterator
// to represent an iterator to the caller.  A custom container class provides
// an instance of this interface to allow the caller to iterate forward
// over the container.  In this example, the container can expose multiple
// iterators, each independent of the others.  The use of multiple iterators
// on the same container is normally used only when the container is a
// read-only type; that is, the contents will not be changing.  Once the
// contents are changed (added or removed), all iterators are considered
// invalid.

using System.Collections.Generic;

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents a key/value pair where the key and value are strings.
    /// </summary>
    public class ItemPair
    {
        public string Key;
        public string Value;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="key">The key to use.</param>
        /// <param name="value">The value to use.</param>
        public ItemPair(string key, string value)
        {
            Key = key;
            Value = value;
        }
    }


    /// <summary>
    /// Represents an iterator for some type.  This is a forward-only iterator
    /// in that it can only start at 0 and increment through the items until
    /// done.
    /// </summary>
    /// <typeparam name="TItemType">The type of each item provided by the iterator</typeparam>
    /// <example>
    /// var iterator = container.GetItems();
    /// for (var item in iterator.Next(); item != null; item = iterator.Next())
    /// {
    ///     // Use item here
    /// }
    /// </example>
    /// <remarks>
    /// A generic type is used in this example so I didn't have to come up
    /// with either two iterators (one for ItemPair and the other for string)
    /// or one iterator that returned an object that would have to be cast to
    /// the appropriate type before using.
    /// </remarks>
    public interface IIterator<TItemType>
    {
        /// <summary>
        /// Start iteration from beginning of container.
        /// </summary>
        void Reset();
    
        /// <summary>
        /// Retrieve the next item from the container.
        /// </summary>
        /// <returns>Returns a TItemType object or null, if there are no more
        /// items in the iteration.</returns>
        TItemType Next();
    }


    /// <summary>
    /// Represents an iterator for a container by implementing the IIterator
    /// interface.
    /// 
    /// This class retains a copy of the elements to be iterated over so it is
    /// immune to changes in the container from which this iterator was
    /// generated.
    /// </summary>
    /// <typeparam name="TItemType">The type of each item provided by the iterator</typeparam>
    /// <remarks>
    /// This iterator is immune to changes in the source container.  However,
    /// that makes this iterator expensive because the items being iterated
    /// over have to be duplicated in this class.
    /// 
    /// One alternative is for there to be only a single iterator and that
    /// iterator is implemented on the container class itself.  If there are
    /// more than one type of iterator (as in this example) then the source
    /// container would have to implement multiple iterators, one for each
    /// type of item returned from the iterator.
    /// 
    /// Another alternative is for this iterator class to have a way to access
    /// the source container's data so the data doesn't have to be copied.
    /// </remarks>
    class Iterator<TItemType> : IIterator<TItemType>
    {
        /// <summary>
        /// The array of items to iterate over.
        /// </summary>
        TItemType[] _items;

        /// <summary>
        /// The index into the _items array to the next item.
        /// </summary>
        int _index;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="items">The items to iterate over.</param>
        public Iterator(TItemType[] items)
        {
            _items = (TItemType[])items.Clone();
        }

        /// <summary>
        /// Returns the next item in the iteration or null, if there are no
        /// more items.
        /// </summary>
        /// <returns>The next item or null if no more items.</returns>
        public TItemType Next()
        {
            TItemType item = default(TItemType);

            if (_index < _items.Length)
            {
                item = _items[_index];
                ++_index;
            }
            return item;
        }

        /// <summary>
        /// Reset the iterator to the beginning.
        /// </summary>
        public void Reset()
        {
            _index = 0;
        }
    }


    /// <summary>
    /// Represents a container that offers up two kinds of iterators for the
    /// hardcoded contents.
    /// </summary>
    public class IteratorContainer_Class
    {
        // Hardcoded data to be iterated over.
        // The number of keys must match the number of values.
        // This container is not a dictionary despite the use of Keys and
        // Values as names but it was the simplest form of data I could come
        // up with that didn't use any of the C# containers.
        string[] _keys = new string[] { "One", "Two", "Three" };
        string[] _values = new string[] { "Value 1", "Value 2", "Value 3" };

        /// <summary>
        /// Retrieve an iterator over the data that returns an ItemPair object
        /// containing both key and value for each entry.
        /// </summary>
        /// <returns>An IIterator object for getting ItemPair objects.</returns>
        public IIterator<ItemPair> GetItems()
        {
            List<ItemPair> items = new List<ItemPair>();

            int numItems = _keys.Length;
            for (int index = 0; index < numItems; ++index)
            {
                items.Add(new ItemPair(_keys[index], _values[index]));
            }

            // Note: the ToArray() creates a copy of the list but as an
            // array.
            return new Iterator<ItemPair>(items.ToArray());
        }

        /// <summary>
        /// Retrieve an iterator over the "key" part of the data, where the
        /// data returned from the iterator is a string type.
        /// </summary>
        /// <returns>An IIterator object for getting strings.</returns>
        public IIterator<string> GetKeys()
        {
            return new Iterator<string>(_keys);
        }

        /// <summary>
        /// Retrieve an iterator over the "value" part of the data, where the
        /// data returned from the iterator is a string type.
        /// </summary>
        /// <returns>An IIterator object for getting strings.</returns>
        public IIterator<string> GetValues()
        {
            return new Iterator<string>(_values);
        }
    }
}
