/// @file
/// @brief
/// Declaration of the ItemPair structure, along with the iterator functions,
/// Iterator_GetItems(), Iterator_GetKeys(), Iterator_GetValues(),
/// Iterator_NextItem(), Iterator_NextKey(), and Iterator_NextValue(),
/// as used in the @ref iterator_pattern.

#pragma once
#ifndef __ITERATOR_ITERATORS_H__
#define __ITERATOR_ITERATORS_H__

#include <stdbool.h>
#include <stddef.h>

/// <summary>
/// Represents a key/value pair where the key and value are strings.
/// </summary>
typedef struct
{
    const char* key;     ///< The key part of the item.
    const char* value;   ///< The value part of the item.
} ItemPair;

/// <summary>
/// Represents an iterator that retrieves whole items.
/// </summary>
typedef struct
{
    /// <summary>
    /// The key/value pair pointed to by this iterator. `item.key` and `item.value`
    /// are NULL if Iterator_NextItem() has not yet been called or the end of
    /// the data has been reached.
    /// </summary>
    ItemPair item;

    /// <summary>
    /// The (opaque) iterator value tracking progress through the data.
    /// </summary>
    size_t iterator;
} ItemIterator;

/// <summary>
/// Represents an iterator that retrieves the key of each item.
/// </summary>
typedef struct
{
    /// <summary>
    /// The key pointed to by this iterator.  `key` is NULL if
    /// Iterator_NextKey() has not yet been called or the end of the data
    /// has been reached.
    /// </summary>
    const char* key;

    /// <summary>
    /// The (opaque) iterator value tracking progress through the data.
    /// </summary>
    size_t iterator;
} KeyIterator;


/// <summary>
/// Represents an iterator that retrieves the value of each item.
/// </summary>
typedef struct
{
    /// <summary>
    /// The value pointed to by this iterator.  `value` is NULL if
    /// Iterator_NextValue() has not yet been called or the end of the data
    /// has been reached.
    /// </summary>
    const char* value;

    /// <summary>
    /// The (opaque) iterator value tracking progress through the data.
    /// </summary>
    size_t iterator;
} ValueIterator;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/// <summary>
/// Retrieve an iterator over the whole items in the internal data structure.
/// </summary>
/// <param name="iterator">Pointer to an ItemIterator object to populate with
/// the iterator.  Call Iterator_NextItem() to start using the iterator.</param>
void Iterator_GetItems(ItemIterator* iterator);

/// <summary>
/// Retrieve an iterator over the keys in the internal data structure.
/// </summary>
/// <param name="iterator">Pointer to an KeyIterator object to populate with
/// the iterator.  Call Iterator_NextKey() to start using the iterator.</param>
void Iterator_GetKeys(KeyIterator* iterator);

/// <summary>
/// Retrieve an iterator over the values in the internal data structure.
/// </summary>
/// <param name="iterator">Pointer to an ValueIterator object to populate with
/// the iterator.  Call Iterator_NextValue() to start using the iterator.</param>
void Iterator_GetValues(ValueIterator* iterator);

/// <summary>
/// Retrieve the next whole item (ItemPair) from the iterator.
/// </summary>
/// <param name="iterator">The KeyIterator used to get the next item.</param>
/// <returns>Returns true if an item was retrieved; otherwise, returns false,
/// there are no more items.</returns>
bool Iterator_NextItem(ItemIterator* iterator);

/// <summary>
/// Retrieve the next key (const char*) from the iterator.
/// </summary>
/// <param name="iterator">The ItemIterator used to get the next key.</param>
/// <returns>Returns true if a key was retrieved; otherwise, returns false,
/// there are no more keys.</returns>
bool Iterator_NextKey(KeyIterator* iterator);

/// <summary>
/// Retrieve the next value (const char*) from the iterator.
/// </summary>
/// <param name="iterator">The ValueIterator used to get the next value.</param>
/// <returns>Returns true if a value was retrieved; otherwise, returns false,
/// there are no more values.</returns>
bool Iterator_NextValue(ValueIterator* iterator);

#endif // __ITERATOR_ITERATORS_H__
