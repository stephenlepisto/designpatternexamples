
/// @file
/// @brief
/// Implementation of the Composite_Exercise() function as used in the
/// @ref composite_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/datetime.h"
#include "helpers/dynamicstring.h"
#include "helpers/makelocaltime.h"

#include "Composite_FileDirEntry.h"
#include "Composite_FileAccess.h"
#include "Composite_Exercise.h"


//=============================================================================
//=============================================================================

/// <summary>
/// Format the specified entry for display.
///
/// This is a recursive call.
/// </summary>
/// <param name="entry">The FileDirEntry object to format</param>
/// <param name="depth">The current recursion depth.  This is used as
/// leading space.</param>
/// <param name="output">A DynamicString in which to collect the output.</param>
static void Composite_Exercise_FormatEntry(FileDirEntry* entry, int depth, DynamicString* output)
{
    size_t NAME_PADDING_SIZE = 20;
    char indentspaces[20] = { 0 };

    const char* entryName = FileDirEntry_GetName(entry);
    if (entryName != NULL)
    {
        char line[128] = { 0 };
        errno_t err = 0;
        for (int index = 0; index < depth * 2 && index < (int)(sizeof(indentspaces) - 1); index++)
        {
            indentspaces[index] = ' ';
        }

        err = strcpy_s(line, sizeof(line), indentspaces);
        if (!err)
        {
            err = strcat_s(line, sizeof(line), entryName);
            if (err)
            {
                printf("  Error!  strcat_s() failed in Composite_Exercise_FormatEntry()!\n");
            }
        }
        else
        {
            printf("  Error!  strcpy_s() failed in Composite_Exercise_FormatEntry()!\n");
        }

        if (!err)
        {
            size_t nameSize = strlen(entryName);
            size_t padding = NAME_PADDING_SIZE - nameSize - (depth * 2);
            if (FileDirEntry_GetFileDirType(entry) == FileDirType_Directory)
            {
                strcat_s(line, sizeof(line), "/");
                padding--;
            }

            char* paddingSpaces = calloc(1, padding + 1);
            if (paddingSpaces != NULL)
            {
                memset(paddingSpaces, ' ', padding);
                err = strcat_s(line, sizeof(line), paddingSpaces);
                free(paddingSpaces);
                if (err)
                {
                    printf("  Error!  strcat_s failed in Composite_Exercise_FormatEntry() to add padding to line!\n");
                }
            }
        }
        if (!err)
        {
            int entryLength = FileDirEntry_GetLength(entry);
            const char* timestampAsString = datetime_to_string(FileDirEntry_GetWhenModified(entry));
            size_t lineLength = strlen(line);
            size_t bufferLength = sizeof(line) - lineLength;
            int num_chars = sprintf_s(line + lineLength, bufferLength, "%4d  %s\n", entryLength, timestampAsString);
            if (num_chars != -1)
            {
                if (DynamicString_Append(output, line))
                {

                    FileDirEntry* child = FileDirEntry_GetChildren(entry);
                    if (child != NULL)
                    {
                        while (child != NULL)
                        {
                            Composite_Exercise_FormatEntry(child, depth + 1, output);
                            child = child->next;
                        }
                    }
                }
                else
                {
                    printf("  Error!  Out of memory appending line to the output in Composite_Exercise_FormatEntry()!\n");
                }
            }
            else
            {
                printf("  Error!  sprintf_s() failed in Composite_Exercise_FormatEntry() while building line for output.\n");
            }
        }
    }
}
//-----------------------------------------------------------------------------

/// <summary>
/// Recursively display the contents of the hierarchical list of FileDirEntry
/// objects starting with the given object.
/// </summary>
/// <param name="entry">The FileDirEntry object to display</param>
static void Composite_Exercise_ShowEntry(FileDirEntry* entry)
{
    DynamicString output = { 0 };

    Composite_Exercise_FormatEntry(entry, 2, &output);
    printf("%s\n", output.string);
    DynamicString_Clear(&output);

}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref composite_pattern.
///
/// The Composite pattern is used when a collection of objects is to
/// be formed in a hierarchical form where each object needs to be
/// treated like any other object but some objects can contain other
/// objects.
///
/// This example uses a file structure of file and directories to
/// represent each object type.
/// </summary>
// ! [Using Composite in C]
void Composite_Exercise(void)
{
    printf("\nComposite_Exercise\n");

    const char* filepath = "root";
    FileDirEntry* rootEntry = Composite_FileAccess_GetEntry(filepath);
    if (rootEntry != NULL)
    {
        printf("  Showing object '%s'\n", filepath);
        Composite_Exercise_ShowEntry(rootEntry);

        filepath = "root/subdir1/FileD.txt";
        rootEntry = Composite_FileAccess_GetEntry(filepath);
        if (rootEntry != NULL)
        {
            printf("  Showing object '%s'\n", filepath);
            Composite_Exercise_ShowEntry(rootEntry);
        }
        else
        {
            printf("  Error!  Unable to get a FileDirEntry for the path \"%s\"!", filepath);
        }
    }
    else
    {
        printf("  Error!  Unable to get a FileDirEntry for the path \"%s\"!", filepath);
    }
    printf("  Done.\n");
}
// ! [Using Composite in C]
