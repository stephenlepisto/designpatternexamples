/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::IteratorContainer_Class "IteratorContainer_Class"
/// class, the @ref DesignPatternExamples_cpp::IIterator "IIterator" interface,
/// along with the implementations of the 
/// @ref DesignPatternExamples_cpp::Iterator "Iterator" and
/// @ref DesignPatternExamples_cpp::ItemPair "ItemPair" classes
/// as used in the @ref iterator_pattern "Iterator pattern".

#pragma once
#ifndef __ITERATOR_CLASS_H__
#define __ITERATOR_CLASS_H__

#include <algorithm>
#include <memory>

#include "helpers/stringlist.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a key/value pair where the key and value are strings.
    /// </summary>
    class ItemPair
    {
    public:
        std::string Key;
        std::string Value;

        /// <summary>
        /// Default Constructor
        /// </summary>
        ItemPair()
        {
        }


        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="key">The key to use.</param>
        /// <param name="value">The value to use.</param>
        ItemPair(std::string key, std::string value)
            : Key(key)
            , Value(value)
        {
        }
    };


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
    template <typename TItemType>
    struct IIterator
    {
        /// <summary>
        /// Virtual destructor so this struct can be used as an interface.
        /// </summary>
        virtual ~IIterator() {}

        /// <summary>
        /// Start iteration from beginning of container.
        /// </summary>
        virtual void Reset() = 0;

        /// <summary>
        /// Retrieve the next item from the container.
        /// </summary>
        /// <returns>Returns a TItemType object or null, if there are no more
        /// items in the iteration.</returns>
        virtual bool Next(TItemType& item) = 0;
    };


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
    template <typename TItemType>
    class Iterator : public IIterator<TItemType>
    {
    private:
        /// <summary>
        /// The array of items to iterate over.
        /// </summary>
        TItemType* _items;

        /// <summary>
        /// The number of items in the array of items.
        /// </summary>
        size_t _numItems;

        /// <summary>
        /// The index into the _items array to the next item.
        /// </summary>
        size_t _index;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="items">The items to iterate over.</param>
        /// <param name="numItems">Number of items in the array.</param>
        Iterator(TItemType* items, size_t numItems)
            : _items(nullptr)
            , _numItems(numItems)
            , _index(0)
        {
            _items = new TItemType[numItems];
            std::copy(items, items + numItems, _items);
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        ~Iterator()
        {
            delete[] _items;
        }

        /// <summary>
        /// Fetches the next item in the iteration, if any.
        /// </summary>
        /// <param name="item">Returns the next item.</param>
        /// <returns>True if an item was returned; otherwise, returns false,
        /// no more items to return</returns>
        bool Next(TItemType& item)
        {
            bool retrieved_item = true;
            if (_index < _numItems)
            {
                item = _items[_index];
                ++_index;
            }
            else
            {
                retrieved_item = false;
            }
            return retrieved_item;
        }

        /// <summary>
        /// Reset the iterator to the beginning.
        /// </summary>
        void Reset() override
        {
            _index = 0;
        }
    };


    /// <summary>
    /// Represents a container that offers up two kinds of iterators for the
    /// hardcoded contents, ItemPair and std::string.
    /// 
    /// This container is not a dictionary despite the use of keys and
    /// values but it was the simplest form of data I could come up with that
    /// didn't use any of the C++ containers.
    /// </summary>
    class IteratorContainer_Class
    {
    public:
        /// <summary>
        /// Retrieve an iterator over the data that returns an ItemPair object
        /// containing both key and value for each entry.
        /// </summary>
        /// <returns>An IIterator object for getting ItemPair objects.</returns>
        std::shared_ptr<IIterator<ItemPair>> GetItems();

        /// <summary>
        /// Retrieve an iterator over the "key" part of the data, where the
        /// data returned from the iterator is a string type.
        /// </summary>
        /// <returns>An IIterator object for getting strings.</returns>
        std::shared_ptr<IIterator<std::string>> GetKeys();

        /// <summary>
        /// Retrieve an iterator over the "value" part of the data, where the
        /// data returned from the iterator is a string type.
        /// </summary>
        /// <returns>An IIterator object for getting strings.</returns>
        std::shared_ptr<IIterator<std::string>> GetValues();
    };

} // end namespace

#endif // __ITERATOR_CLASS_H__
