/// @file
/// @brief
/// Implementation of the supporting functions for the MapOfStrings structure
/// for managing a map of strings keyed by another string.

#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "mapofstrings.h"

///////////////////////////////////////////////////////////////////////////////
// MapOfStrings_Initialize()
///////////////////////////////////////////////////////////////////////////////
void MapOfStrings_Initialize(MapOfStrings* map)
{
    if (map != NULL)
    {
        map->entries = NULL;
        map->entries_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// MapOfStrings_Clear()
///////////////////////////////////////////////////////////////////////////////
void MapOfStrings_Clear(MapOfStrings* map)
{
    if (map != NULL)
    {
        for (size_t index = 0; index < map->entries_count; index++)
        {
            ConstStringList_Clear(map->entries[index].value);
        }
        free(map->entries);
        MapOfStrings_Initialize(map);
    }
}

///////////////////////////////////////////////////////////////////////////////
// MapOfStrings_AddStringList()
///////////////////////////////////////////////////////////////////////////////
bool MapOfStrings_AddStringList(MapOfStrings* map, const char* key, ConstStringList* value)
{
    bool success = false;

    if (map != NULL && key != NULL && value != NULL)
    {
        MapOfStringsEntry* new_list;
        if (map->entries == NULL)
        {
            new_list = calloc(1, sizeof(MapOfStringsEntry));
        }
        else
        {
            size_t new_count = map->entries_count + 1;
            size_t new_size = new_count * sizeof(MapOfStringsEntry);
            new_list = realloc(map->entries, new_size);
        }
        if (new_list != NULL)
        {
            map->entries = new_list;
            map->entries[map->entries_count].key = key;
            map->entries[map->entries_count].value = value;
            map->entries_count++;
            success = true;
        }
    }
    
    return success;
}

///////////////////////////////////////////////////////////////////////////////
// MapOfStrings_AddArray()
///////////////////////////////////////////////////////////////////////////////
bool MapOfStrings_AddArray(MapOfStrings* map, const char* key, const char** value)
{
    bool success = false;

    if (map != NULL && key != NULL && value != NULL)
    {
        size_t numStrings = 0;
        for (size_t index = 0; value[index] != NULL; index++)
        {
            numStrings++;
        }
        ConstStringList* stringList = calloc(1, sizeof(ConstStringList));
        if (stringList != NULL)
        {
            success = ConstStringList_AddStrings(stringList, value, numStrings);
            if (success)
            {
                success = MapOfStrings_AddStringList(map, key, stringList);
            }
        }
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
// MapOfStrings_Find()
///////////////////////////////////////////////////////////////////////////////
int MapOfStrings_Find(MapOfStrings* map, const char* key)
{
    int foundIndex = -1;

    if (map != NULL && key != NULL)
    {
        for (size_t index = 0; index < map->entries_count; index++)
        {
            if (strcmp(map->entries[index].key, key) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}
