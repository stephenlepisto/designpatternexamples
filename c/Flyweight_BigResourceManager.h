/// @file
/// @brief
/// Declaration of the Big Resource Manager functions, BigResourceManager_Clear(),
/// BigResourceManager_AddResource(), and BigResourceManager_GetResource(),
/// used in the @ref flyweight_pattern.

#pragma once
#ifndef __FLYWEIGHT_BIGRESOURCEMANAGER_H__
#define __FLYWEIGHT_BIGRESOURCEMANAGER_H__

#include <stdbool.h>

#include "Flyweight_BigResource.h"
#include "Flyweight_Image.h"

/// <summary>
/// Release all resources owned by the Big Resource Manager.
/// </summary>
void BigResourceManager_Clear();

/// <summary>
/// Add a new big resource and return the ID of the resource.  If the resource
/// is successfully added, the Big Resource Manager owns the resource and will
/// free it on exit.
/// </summary>
/// <param name="rawResource">The BigResource object to add.</param>
/// <returns>Returns the handle to the new big resource added to the manager.
/// Returns -1 if something went wrong (typically an out of memory condition).</returns>
int BigResourceManager_AddResource(BigResource* rawResource);

/// <summary>
/// Retrieve the requested big resource.
/// </summary>
/// <param name="bigResourceId">Handle to the big resource to retrieve.</param>
/// <returns>Returns a pointer to the big resource if found; otherwise, returns
/// NULL.</returns>
BigResource* BigResourceManager_GetResource(int bigResourceId);


#endif // __FLYWEIGHT_BIGRESOURCEMANAGER_H__

