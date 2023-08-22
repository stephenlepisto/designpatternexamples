/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.IteratorContainer_Class "IteratorContainer_Class"
/// class and the @ref DesignPatternExamples_csharp.IIterator "IIterator"
/// template interface used in the @ref iterator_pattern "Iterator pattern".

using System.Collections.Generic;

namespace DesignPatternExamples_csharp
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
        TItemType? Next();
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
        public TItemType? Next()
        {
            TItemType? item = default(TItemType);

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
