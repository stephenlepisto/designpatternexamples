/// @file
/// @brief
/// Implementation of the @ref ConstStringList structure and supporting functions to
/// work with a list of strings: ConstStringList_Initialize(), ConstStringList_Clear(),
/// ConstStringList_AddString(), ConstStringList_Remove(), and ConstStringList_Find().

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "conststringlist.h"

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void ConstStringList_Initialize(ConstStringList* stringList)
{
    if (stringList != NULL)
    {
        stringList->strings = NULL;
        stringList->strings_count = 0;
        stringList->allocated_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_Clear()
///////////////////////////////////////////////////////////////////////////////
void ConstStringList_Clear(ConstStringList* stringList)
{
    if (stringList != NULL)
    {
        if (stringList->strings != NULL && stringList->strings_count != 0)
        {
            // The strings in the list are constant and are not supposed to be
            // deleted.  Just forget they existed.
            free(stringList->strings);
            ConstStringList_Initialize(stringList);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_AddString()
///////////////////////////////////////////////////////////////////////////////
bool ConstStringList_AddString(ConstStringList* stringList, const char* string)
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
            stringList->strings[stringList->strings_count] = string;
            stringList->strings_count++;
            stringAdded = true;
        }
    }
    return stringAdded;
}

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_AddStrings()
///////////////////////////////////////////////////////////////////////////////
bool ConstStringList_AddStrings(ConstStringList* stringList, const char** strings, size_t numStrings)
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
                stringList->strings[offset + index] = strings[index];
                stringList->strings_count++;
            }
        }
    }

    return stringsAdded;
}

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_Remove()
///////////////////////////////////////////////////////////////////////////////
void ConstStringList_Remove(ConstStringList* stringList, int removeIndex)
{
    if (stringList != NULL && stringList->strings != NULL)
    {
        if (removeIndex >= 0 && removeIndex < stringList->strings_count)
        {
            for (size_t stringIndex = removeIndex; stringIndex < stringList->allocated_count - 1; stringIndex++)
            {
                stringList->strings[stringIndex] = stringList->strings[stringIndex + 1];
            }
            stringList->strings_count--;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_Find()
///////////////////////////////////////////////////////////////////////////////
int ConstStringList_Find(ConstStringList* stringList, const char* string)
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

///////////////////////////////////////////////////////////////////////////////
// ConstStringList_Find()
///////////////////////////////////////////////////////////////////////////////
bool ConstStringList_AreListsEqual(ConstStringList* left, ConstStringList* right)
{
    bool matched = false;

    if (left != NULL && right != NULL)
    {
        if (left->strings_count == right->strings_count)
        {
            matched = true;
            for (size_t index = 0; index < left->strings_count; index++)
            {
                int found_index = ConstStringList_Find(right, left->strings[index]);
                if (found_index == -1)
                {
                    matched = false;
                    break;
                }
            }
        }
    }

    return matched;
}
