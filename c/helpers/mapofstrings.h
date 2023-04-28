/// @file
/// @brief
/// Declaration of the MapOfStrings structure and supporting functions for
/// managing a map of strings keyed by another string: MapOfStrings_Initialize(),
/// MapOfStrings_Clear(), MapOfStrings_Add(), and MapOfStrings_Find().

#pragma once
#ifndef __MAPOFSTRINGS_H__
#define __MAPOFSTRINGS_H__

#include <stdlib.h>
#include "conststringlist.h"

/// <summary>
/// Represents an entry in the MapOfStrings structure, associating a string
/// "key" with a StringList "value".
/// </summary>
typedef struct
{
    const char* key;   ///< A string that is associated with the `value` field.
    ConstStringList* value; ///< The "value" that is a ConstStringList object.
} MapOfStringsEntry;


/// <summary>
/// Represents a list of structures that map strings to ConstStringList objects.
/// 
/// In other programming languages, functionally this is a map or dictionary
/// that associates a key with a value.
/// </summary>
typedef struct
{
    MapOfStringsEntry* entries; ///< List of MapOfStringsEntry for each mapping.
    size_t entries_count;       ///< Number of items in the `entries` list.
} MapOfStrings;

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize the given MapOfStrings structure so it is ready for use.
/// 
/// Alternatively, declare the MapOfStrings instance like this:
/// <example>
/// <code>
/// MapOfStrings map = { 0 };
/// </code>
/// </example>
/// </summary>
/// <param name="map">The MapOfStrings object to initialize.</param>
void MapOfStrings_Initialize(MapOfStrings* map);

/// <summary>
/// Clear the given MapOfStrings object, releasing all memory associated with
/// it.  Leaves the object in an initialize state to be reused, if desired.
/// </summary>
/// <param name="map">The MapOfStrings object to clear.</param>
void MapOfStrings_Clear(MapOfStrings* map);

/// <summary>
/// Add a key/value association to the given MapOfStrings object.  The
/// MapOfStrings object takes ownership of the key and value arguments and will
/// free them when MapOfStrings_Clear() is called in the object.
/// </summary>
/// <param name="map">The MapOfStrings object to add to.</param>
/// <param name="key">The key value to be added.  This must be allocated, directly
/// or indirectly, with malloc() as it will be freed when the MapOfStrings object
/// is cleared.</param>
/// <param name="value">The ConstStringList object to add as the value.  This must
/// be allocated with malloc() as it will be freed when the MapOfStrings object
/// is cleared.</param>
/// <returns>Returns true if the key/value was successfully added; otherwise,
/// returns false, indicating an out of memory condition (or NULL argument).
/// </returns>
bool MapOfStrings_AddStringList(MapOfStrings* map, const char* key, ConstStringList* value);

/// <summary>
/// Add a key/value association to the given MapOfStrings object, where the
/// value is provided as a NULL-terminated array of string pointer.  This array
/// is copied into a StringList object for storage in the map.
/// </summary>
/// <param name="map">The MapOfStrings object to add to.</param>
/// <param name="key">The key value to be added.  This must be allocated, directly
/// or indirectly, with malloc() as it will be freed when the MapOfStrings object
/// is cleared.</param>
/// <param name="value">An array of string pointers terminated by a NULL pointer.</param>
/// <returns>Returns true if the key/value was successfully added; otherwise,
/// returns false, indicating an out of memory condition (or NULL argument).
/// </returns>
bool MapOfStrings_AddArray(MapOfStrings* map, const char* key, const char** value);

/// <summary>
/// Find the specified key in the given MapOfStrings object, returning an index
/// into the object.
/// </summary>
/// <param name="map">The MapOfStrings object to search.</param>
/// <param name="key">The key to search for.</param>
/// <returns>Returns the index of the found item if successful; otherwise,
/// returns -1, indicating the key was not found.</returns>
int MapOfStrings_Find(MapOfStrings* map, const char* key);

#endif // __MAPOFSTRINGS_H__

