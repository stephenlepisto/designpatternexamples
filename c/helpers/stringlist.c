/// @file
/// @brief
/// Implementation of the supporting functions for the StringList structure
/// that works with a list of allocated strings.

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "stringlist.h"

///////////////////////////////////////////////////////////////////////////////
// StringList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void StringList_Initialize(StringList* stringList)
{
    if (stringList != NULL)
    {
        stringList->strings = NULL;
        stringList->strings_count = 0;
        stringList->allocated_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// StringList_Clear()
///////////////////////////////////////////////////////////////////////////////
void StringList_Clear(StringList* stringList)
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
            StringList_Initialize(stringList);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// StringList_AddString()
///////////////////////////////////////////////////////////////////////////////
bool StringList_AddString(StringList* stringList, const char* string)
{
    bool stringAdded = false;

    if (stringList != NULL && string != NULL)
    {
        const char** new_list = NULL;
        if (stringList->strings == NULL)
        {
            new_list = malloc(sizeof(const char*));
            stringList->allocated_count = 1;
        }
        else if (stringList->strings_count < stringList->allocated_count)
        {
            new_list = stringList->strings;
        }
        else
        {
            size_t newCount = stringList->allocated_count + 1;
            new_list = realloc(stringList->strings, newCount * sizeof(const char*));
            stringList->allocated_count = newCount;
        }

        if (new_list != NULL)
        {
            stringList->strings = new_list;
            char* newString = _strdup(string);
            if (newString != NULL)
            {
                stringList->strings[stringList->strings_count] = newString;
                stringList->strings_count++;
                stringAdded = true;
            }
        }
    }
    return stringAdded;
}

///////////////////////////////////////////////////////////////////////////////
// StringList_AddStrings()
///////////////////////////////////////////////////////////////////////////////
bool StringList_AddStrings(StringList* stringList, const char** strings, size_t numStrings)
{
    bool stringsAdded = false;

    if (stringList != NULL && strings != NULL)
    {
        const char** new_list = NULL;
        if (stringList->strings == NULL)
        {
            new_list = calloc(numStrings, sizeof(const char*));
            stringList->allocated_count = numStrings;
        }
        else if ((stringList->strings_count + numStrings) < stringList->allocated_count)
        {
            new_list = stringList->strings;
        }
        else
        {
            size_t newCount = stringList->allocated_count + numStrings;
            new_list = realloc(stringList->strings, newCount * sizeof(const char*));
            stringList->allocated_count = newCount;
        }
        if (new_list != NULL)
        {
            stringsAdded = true;
            stringList->strings = new_list;
            size_t offset = stringList->strings_count;
            for (size_t index = 0; index < numStrings; index++)
            {
                char* newString = _strdup(strings[index]);
                if (newString == NULL)
                {
                    stringsAdded = false;
                    break;
                }
                stringList->strings[offset + index] = newString;
                stringList->strings_count++;
            }
        }
    }

    return stringsAdded;
}

///////////////////////////////////////////////////////////////////////////////
// StringList_Remove()
///////////////////////////////////////////////////////////////////////////////
void StringList_Remove(StringList* stringList, int removeIndex)
{
    if (stringList != NULL && stringList->strings != NULL)
    {
        if (removeIndex >= 0 && removeIndex < stringList->strings_count)
        {
            const char* stringToRemove = stringList->strings[removeIndex];
            for (size_t stringIndex = removeIndex; stringIndex < stringList->allocated_count - 1; stringIndex++)
            {
                stringList->strings[stringIndex] = stringList->strings[stringIndex + 1];
            }
            stringList->strings_count--;
            free((char*)stringToRemove);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// StringList_Find()
///////////////////////////////////////////////////////////////////////////////
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
