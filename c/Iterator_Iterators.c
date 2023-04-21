/// @file
/// @brief
/// Implementation of the iterator functions,
/// Iterator_GetItems(), Iterator_GetKeys(), Iterator_GetValues(),
/// Iterator_NextItem(), Iterator_NextKey(), and Iterator_GetValue(),
/// as used in the @ref iterator_pattern.

#include "Iterator_Iterators.h"

#include <stdlib.h>


/// <summary>
/// A list of keys as example data. The number of keys must match the number
/// of values in the `values` list.
/// </summary>
static const char* _keys[] =   { "One"    , "Two"    , "Three"   };

/// <summary>
/// A list of values as example data.  The number of values must match the
/// number of keys in the `keys` list.
/// </summary>
static const char* _values[] = { "Value 1", "Value 2", "Value 3" };


//=============================================================================
//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
void Iterator_GetItems(ItemIterator* iterator)
{
    if (iterator != NULL)
    {
        iterator->item.key = NULL;
        iterator->item.value = NULL;
        iterator->iterator = 0; // The iterator field is the index into the data.
    }
}

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
void Iterator_GetKeys(KeyIterator* iterator)
{
    if (iterator != NULL)
    {
        iterator->key = NULL;
        iterator->iterator = 0; // The iterator field is the index into the data.
    }
}

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
void Iterator_GetValues(ValueIterator* iterator)
{
    if (iterator != NULL)
    {
        iterator->value = NULL;
        iterator->iterator = 0; // The iterator field is the index into the data.
    }
}

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
bool Iterator_NextItem(ItemIterator* iterator)
{
    bool retrievedItem = false;

    if (iterator != NULL)
    {
        size_t index = iterator->iterator;
        size_t numKeys = sizeof(_keys) / sizeof(_keys[0]);

        if (index < numKeys)
        {
            iterator->item.key = _keys[index];
            iterator->item.value = _values[index];
            index++;
            iterator->iterator = index;
            retrievedItem = true;
        }
        else
        {
            iterator->item.key = NULL;
            iterator->item.value = NULL;
        }
    }

    return retrievedItem;
}

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
bool Iterator_NextKey(KeyIterator* iterator)
{
    bool retrievedKey = false;

    if (iterator != NULL)
    {
        size_t index = iterator->iterator;
        size_t numKeys = sizeof(_keys) / sizeof(_keys[0]);

        if (index < numKeys)
        {
            iterator->key = _keys[index];
            index++;
            iterator->iterator = index;
            retrievedKey = true;
        }
        else
        {
            iterator->key = NULL;
        }
    }

    return retrievedKey;
}

///////////////////////////////////////////////////////////////////////////////
// Iterator_GetItems()
///////////////////////////////////////////////////////////////////////////////
bool Iterator_NextValue(ValueIterator* iterator)
{
    bool retrievedValue = false;

    if (iterator != NULL)
    {
        size_t index = iterator->iterator;
        size_t numValues = sizeof(_values) / sizeof(_values[0]);

        if (index < numValues)
        {
            iterator->value = _values[index];
            index++;
            iterator->iterator = index;
            retrievedValue = true;
        }
        else
        {
            iterator->value = NULL;
        }
    }

    return retrievedValue;
}

