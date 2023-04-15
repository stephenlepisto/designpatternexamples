/// @file
/// @brief
/// Implementation of the split() function, for splitting
/// a string on delimiters, along with the SplitList_Clear() function for
/// releasing the resources in a SplitList object.  Also has implementation for
/// SplitList_Initialize(), and SplitList_AddString() functions.

#include <stdlib.h>
#include <string.h>

#include "split.h"

/// <summary>
/// Initialize the given SplitList object.
/// </summary>
/// <param name="list">A SplitList object to initialize.</param>
void SplitList_Initialize(SplitList* list)
{
    if (list != NULL)
    {
        list->strings = NULL;
        list->strings_count = 0;
    }
}

/// <summary>
/// Clear the given SplitList object so it can be reused again.  Releases
/// the list of sub-strings (but does not delete the sub-strings themselves,
/// which are assumed to be pointers into an existing string).
/// </summary>
/// <param name="list">A SplitList object to clear.</param>
void SplitList_Clear(SplitList* list)
{
    if (list != NULL)
    {
        free(list->strings);
        list->strings = NULL;
        list->strings_count = 0;
    }
}

/// <summary>
/// Add a string to the given SplitList object.  The string is not duplicated
/// but instead is just copied into the list.
/// </summary>
/// <param name="list">The SplitList object to update.</param>
/// <param name="s">The string to add to the SplitList object.</param>
void SplitList_AddString(SplitList* list, const char* s)
{
    if (list != NULL && s != NULL)
    {
        const char** new_list = NULL;
        if (list->strings == NULL)
        {
            new_list = calloc(1, sizeof(char*));
        }
        else
        {
            size_t newSize = (list->strings_count + 1) * sizeof(const char*);
            new_list = realloc(list->strings, newSize);
        }
        if (new_list != NULL)
        {
            list->strings = new_list;
            list->strings[list->strings_count] = s;
            list->strings_count++;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// split()
///////////////////////////////////////////////////////////////////////////////
void split(char* s, const char* splitChars, SplitList* components)
{
    if (s != NULL && components != NULL)
    {
        SplitList_Clear(components);
        if (splitChars == NULL || *splitChars == '\0')
        {
            splitChars = " ";
        }
        char* work = s;
        for (;;)
        {
            size_t foundIndex = strcspn(work, splitChars);
            if (foundIndex < strlen(work))
            {
                work[foundIndex] = '\0';
                SplitList_AddString(components, work);
                work += foundIndex + 1;
            }
            else
            {
                SplitList_AddString(components, work);
                break;
            }
        }
    }
}
