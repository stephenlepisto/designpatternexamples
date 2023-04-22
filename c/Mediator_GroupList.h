/// @file
/// @brief
/// Declaration of the GroupList structure and the associated support functions
/// as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_GROUPLIST_H__
#define __MEDIATOR_GROUPLIST_H__

#include <stdlib.h>

#include "Mediator_Group.h"

/// <summary>
/// Represents a list of groups.  Call GroupList_Initialize() to start and
/// GroupList_Clear() to release all resources and restore to empty state.
/// </summary>
typedef struct
{
    Group** groups;         ///< Array of pointers to Group objects.
    size_t groups_count;    ///< Number of pointers in the `groups` list.
    size_t allocated_count; ///< Size of the allocated `groups` list.
} GroupList;

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize the given GroupList object for initial use.
/// </summary>
/// <param name="groupList">The GroupList object to initialize.</param>
void GroupList_Initialize(GroupList* groupList);

/// <summary>
/// Clear the given GroupList object to release all associated resources.
/// 
/// After this function returns, the object is an empty list ready to be used
/// again.
/// </summary>
/// <param name="groupList">The GroupList object to clear.</param>
void GroupList_Clear(GroupList* groupList);

/// <summary>
/// Add the specified Group object to the specified GroupList object.  The
/// list takes ownership of the Group object and is responsible for releasing
/// the memory associated with the Group object.
/// </summary>
/// <param name="groupList">The GroupList object to which to add the group.</param>
/// <param name="group">The Group object to add to the list.</param>
bool GroupList_AddGroup(GroupList* groupList, Group* group);

/// <summary>
/// Search the given GroupList object for the specified group by name and
/// return the index of the group if found.
/// </summary>
/// <param name="groupList">The GroupList object to search.</param>
/// <param name="groupName">The name of the group to look for.  This is a case-
/// sensitive search.</param>
/// <returns>Returns the index of the group in the group list if found;
/// otherwise returns -1, indicating the group does not exist.</returns>
int GroupList_FindGroup(GroupList* groupList, const char* groupName);

/// <summary>
/// Remove the group at the specified index in the given GroupList object.
/// 
/// Since this changes the list of groups, all index values after the given
/// index are no longer valid.
/// </summary>
/// <param name="groupList">The GroupList object to remove from.</param>
/// <param name="removeIndex">Index of the group to remove.  Use GroupList_FindGroup()
/// to get this index.</param>
void GroupList_RemoveGroup(GroupList* groupList, int removeIndex);


#endif //__MEDIATOR_GROUPLIST_H__

