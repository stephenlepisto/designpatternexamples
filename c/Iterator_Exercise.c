
/// @file
/// @brief
/// Implementation of the Iterator_Exercise() function as used in the
/// @ref iterator_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Iterator_Iterators.h"
#include "Iterator_Exercise.h"

//=============================================================================
//=============================================================================


//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref iterator_pattern.
///
/// A custom container is instantiated (it already contains hard-coded data
/// to iterate over).  The custom container can then deliver three
/// iterators, each providing a different aspect of the hard-coded data.
///
/// The output shows the output from each iterator.
/// </summary>
// ! [Using Iterator in C]
void Iterator_Exercise(void)
{
    printf("\nIterator Exercise\n");

    // For this example, the class already has built into it the data
    // to be iterated over.

    printf("  Iterating over keys only:\n");
    KeyIterator keyIterator;
    Iterator_GetKeys(&keyIterator);
    while (Iterator_NextKey(&keyIterator))
    {
        printf("    %s\n", keyIterator.key);
    }

    printf("  Iterating over values only:\n");
    ValueIterator valueIterator;
    Iterator_GetValues(&valueIterator);
    while (Iterator_NextValue(&valueIterator))
    {
        printf("    %s\n", valueIterator.value);
    }

    printf("  Iterating over all items:\n");
    ItemIterator itemIterator;
    Iterator_GetItems(&itemIterator);
    while (Iterator_NextItem(&itemIterator))
    {
        printf("    %s = %s\n", itemIterator.item.key, itemIterator.item.value);
    }

    printf("  Done.\n");
}
// ! [Using Iterator in C]
