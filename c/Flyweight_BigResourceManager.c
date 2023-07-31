/// @file
/// @brief
/// Implementation of the BigResourceList structure and its supporting functions,
/// along with the Big Resource Manager functions, BigResourceManager_Clear(),
/// BigResourceManager_AddResource(), and BigResourceManager_GetResource(),
/// used in the @ref flyweight_pattern.

#include <stdlib.h>

#include "Flyweight_BigResourceManager.h"

/// <summary>
/// Represents an expandable list of pointers to BigResource objects.  Use
/// the BigResourceList_Clear() to free up the resources in the list.  Use the
/// BigResourceList_AddResource() to add a BigResource object to the list (and
/// also take ownership of the BigResource object).
/// </summary>
typedef struct
{
    BigResource** resources; ///< Dynamic list of pointers to BigResource objects.
    size_t resources_count;  ///< Number of BigResource objects in the list.
} BigResourceList;

//=============================================================================
//=============================================================================

/// <summary>
/// A list of BigResource objects.  Initialized by a call to the
/// BigResourceList_AddResource().  This is used by the
/// BigResourceManager_GetResource() to retrieve a BigResource object.
/// </summary>
static BigResourceList _resources = { 0 };

//=============================================================================
//=============================================================================

/// <summary>
/// Clear the given BigResourceList object by freeing up all allocated BigResource
/// objects and resetting the list to a "new" state so it can be reused.
///
/// This is called from the BigResourceManager_Clear() function.
/// </summary>
/// <param name="resourceList">A pointer to the BigResourceList to be cleared.</param>
static void BigResourceList_Clear(BigResourceList* resourceList)
{
    if (resourceList != NULL && resourceList->resources != NULL && resourceList->resources_count != 0)
    {
        for (size_t index = 0; index < resourceList->resources_count; index++)
        {
            BigResource_Clear(resourceList->resources[index]);
        }
        free(resourceList->resources);
        resourceList->resources = NULL;
        resourceList->resources_count = 0;
    }
}

/// <summary>
/// Add a BigResource object to the given BigResourceList object.  The list
/// takes ownership of the BigResource object and is responsible for releasing
/// all memory associated with it.
///
/// This is called from the BigResourceManager_AddResource() function.
/// </summary>
/// <param name="resourceList">The BigResourceList object to add to.</param>
/// <param name="resource">The BigResource object to add to the BigResourceList.</param>
/// <returns>Returns the index of the image added if successful; otherwise,
/// returns -1 to indicate an error (typically an out of memory problem).</returns>
static int BigResourceList_AddResource(BigResourceList* resourceList, BigResource* resource)
{
    int resourceIndex = -1;
    BigResource** new_list = NULL;

    if (resourceList != NULL && resource != NULL)
    {
        if (resourceList->resources == NULL)
        {
            new_list = malloc(sizeof(BigResource*));
        }
        else
        {
            size_t newSize = (resourceList->resources_count + 1) * sizeof(BigResource*);
            new_list = realloc(resourceList->resources, newSize);
        }

        if (new_list != NULL)
        {
            resourceIndex = (int)resourceList->resources_count;
            resourceList->resources = new_list;
            resourceList->resources[resourceIndex] = resource;
            resourceList->resources_count++;
        }
    }
    return resourceIndex;
}


//=============================================================================
//=============================================================================


///////////////////////////////////////////////////////////////////////////////
// BigResourceManager_Clear()
///////////////////////////////////////////////////////////////////////////////
void BigResourceManager_Clear(void)
{
    BigResourceList_Clear(&_resources);
}


///////////////////////////////////////////////////////////////////////////////
// BigResourceManager_AddResource()
///////////////////////////////////////////////////////////////////////////////
int BigResourceManager_AddResource(BigResource* rawResource)
{
    int handle = -1;
    if (rawResource != NULL)
    {
        handle = (int)BigResourceList_AddResource(&_resources, rawResource);
    }
    return handle;
}

///////////////////////////////////////////////////////////////////////////////
// BigResourceManager_GetResource()
///////////////////////////////////////////////////////////////////////////////
BigResource* BigResourceManager_GetResource(int bigResourceId)
{
    BigResource* resource = NULL;

    if (bigResourceId >= 0 && bigResourceId < _resources.resources_count)
    {
        resource = _resources.resources[bigResourceId];
    }

    return resource;
}
