/// @file
/// @brief
/// Declaration of the MapOfInt structure and supporting functions for
/// managing a map of integers keyed by a string.

#pragma once
#ifndef __MAPOFINTS_H__
#define __MAPOFINTS_H__

#include "uintarray.h"

/// <summary>
/// Represents an association between a string and an integer.
/// </summary>
typedef struct
{
    const char* key; ///< Key associated with this integer.  Borrowed pointer.
    int value;       ///< The integer value.
} MapOfIntEntry;

/// <summary>
/// Represents a list of MapOfIntEntry objects that maps a string to an integer
/// value.  Call MapOfInt_Initialize() to initialize the MapOfInt structure
/// and call MapOfInt_Clear() to release the memory of the structure.
/// </summary>
typedef struct
{
    MapOfIntEntry* entries;
    size_t entries_count;
} MapOfInt;

/// <summary>
/// Initialize the given MapOfInt structure so it is ready for use.
/// 
/// Alternatively, declare the MapOfInt instance like this:
/// <example>
/// <code>
/// MapOfInt map = { 0 };
/// </code>
/// </example>
/// </summary>
/// <param name="map">The MapOfInt object to initialize.</param>
void MapOfInt_Initialize(MapOfInt* map);

/// <summary>
/// Clear the given MapOfInt object, releasing all memory associated with
/// it.  Leaves the object in an initialize state to be reused, if desired.
/// </summary>
/// <param name="map">The MapOfInt object to clear.</param>
void MapOfInt_Clear(MapOfInt* map);

/// <summary>
/// Add a key/value association to the given MapOfInt object.  The
/// MapOfInt object takes ownership of the key and value arguments and will
/// free them when MapOfInt_Clear() is called in the object.
/// </summary>
/// <param name="map">The MapOfInt object to add to.</param>
/// <param name="key">The key value to be added.  This must be allocated, directly
/// or indirectly, with malloc() as it will be freed when the MapOfInt object
/// is cleared.</param>
/// <param name="value">The integer being mapped to the key.</param>
/// <returns>Returns true if the key/value was successfully added; otherwise,
/// returns false, indicating an out of memory condition (or NULL argument).
/// </returns>
bool MapOfInt_Add(MapOfInt* map, const char* key, int value);

/// <summary>
/// Find the specified key in the given MapOfInt object, returning an index
/// into the object.
/// </summary>
/// <param name="map">The MapOfInt object to search.</param>
/// <param name="key">The key to search for.</param>
/// <returns>Returns the index of the found item if successful; otherwise,
/// returns -1, indicating the key was not found.</returns>
int MapOfInt_Find(MapOfInt* map, const char* key);


#endif // __MAPOFINTS_H__

