/// @file
/// @brief
/// Implementation of the @ref StringList structure and supporting functions to
/// work with a list of strings: StringList_Create(), StringList_Destroy(), and
/// StringList_AddString().

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "stringlist.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void StringList_Initialize(StringList* stringList)
{
    if (stringList != NULL)
    {
        stringList->strings = NULL;
        stringList->strings_count = 0;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void StringList_Destroy(StringList* stringList)
{
    if (stringList != NULL)
    {
        if (stringList->strings != NULL && stringList->strings_count != 0)
        {
            for (size_t index = 0; index < stringList->strings_count; index++)
            {
                free((void *)stringList->strings[index]);
            }
            free(stringList->strings);
            stringList->strings = NULL;
            stringList->strings_count = 0;
        }
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool StringList_AddString(StringList* stringList, const char* string)
{
    bool stringAdded = false;
    const char** new_list = NULL;

    if (stringList != NULL && string != NULL)
    {
        if (stringList->strings == NULL)
        {
            new_list = malloc(sizeof(const char*));
        }
        else
        {
            size_t newSize = (stringList->strings_count + 1) * sizeof(const char*);
            new_list = (const char**)realloc(stringList->strings, newSize);
        }

        if (new_list != NULL)
        {
            stringList->strings = new_list;
            stringList->strings[stringList->strings_count] = _strdup(string);
            stringList->strings_count++;
            stringAdded = true;
        }
    }
    return stringAdded;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int StringList_Find(StringList* stringList, const char* string)
{
    int foundIndex = -1;

    if (stringList != NULL && string != NULL)
    {
        for (size_t index = 0; index < stringList->strings_count; index++)
        {
            if (strcmp(string, stringList->strings[index]) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}
