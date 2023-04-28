/// @file
/// @brief
/// Implementation of the MapOfInt structure's supporting functions for
/// managing a map of strings keyed by another string: MapOfInt_Initialize(),
/// MapOfInt_Clear(), MapOfInt_Add(), and MapOfInt_Find().

#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "mapofint.h"

///////////////////////////////////////////////////////////////////////////////
// MapOfInt_Initialize()
///////////////////////////////////////////////////////////////////////////////
void MapOfInt_Initialize(MapOfInt* map)
{
    if (map != NULL)
    {
        map->entries = NULL;
        map->entries_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// MapOfInt_Clear()
///////////////////////////////////////////////////////////////////////////////
void MapOfInt_Clear(MapOfInt* map)
{
    if (map != NULL)
    {
        free(map->entries);
        MapOfInt_Initialize(map);
    }
}

///////////////////////////////////////////////////////////////////////////////
// MapOfInt_Add()
///////////////////////////////////////////////////////////////////////////////
bool MapOfInt_Add(MapOfInt* map, const char* key, int value)
{
    bool success = false;

    if (map != NULL && key != NULL)
    {
        MapOfIntEntry* new_list;
        if (map->entries == NULL)
        {
            new_list = calloc(1, sizeof(MapOfIntEntry));
        }
        else
        {
            size_t new_count = map->entries_count + 1;
            size_t new_size = new_count * sizeof(MapOfIntEntry);
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
// MapOfInt_Find()
///////////////////////////////////////////////////////////////////////////////
int MapOfInt_Find(MapOfInt* map, const char* key)
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
