/// @file
/// @brief
/// Declaration of the Group structure and the associated support functions
/// as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_GROUP_H__
#define __MEDIATOR_GROUP_H__

#include "helpers/stringlist.h"


/// <summary>
/// Represents a single group.  A group has a name and zero or more users.
/// Users are tracked by name.
/// </summary>
typedef struct
{
    /// <summary>
    /// Name of this group.
    /// </summary>
    const char* Name;

    /// <summary>
    /// The list of users in this group.
    /// </summary>
    StringList Users;
} Group;

//-----------------------------------------------------------------------------

/// <summary>
/// Create a new Group object with the specified name.
/// </summary>
/// <param name="groupName">Name of the group.</param>
/// <returns>Returns a pointer to a new Group object if successful; otherwise,
/// returns NULL (out of memory condition).  Call Group_Destroy() to free the
/// memory of the object when done with it.</returns>
Group* Group_Create(const char* groupName);

/// <summary>
/// Release the memory of the specified Group object.  After this function
/// returns, the pointer to the Group object is no longer valid.
/// </summary>
/// <param name="group">The Group object to free.</param>
void Group_Destroy(Group* group);

/// <summary>
/// Add a user to the specified group.  Does nothing if the user is already in
/// the group.
/// </summary>
/// <param name="group">The Group object to add to.</param>
/// <param name="userName">Name of the user to add.</param>
/// <returns>Returns true if the user was added (or already present);
/// otherwise, returns false, indicating an out of memory error condition.</returns>
bool Group_AddUser(Group* group, const char* userName);

/// <summary>
/// Search the specified group for the specified user.
/// </summary>
/// <param name="group">The Group object to search.</param>
/// <param name="userName">The name of the user to find.</param>
/// <returns>Returns an index of the user in the group if found; otherwise,
/// returns -1, indicating the user is not in the group.</returns>
int Group_FindUser(Group* group, const char* userName);

/// <summary>
/// Remove a user from the specified group.  Does nothing if the user is not
/// in the group.
/// </summary>
/// <param name="group">The Group object to remove from.</param>
/// <param name="removeIndex">Index of the user to remove.  Call Group_FindUser()
/// to get the index.</param>
void Group_RemoveUser(Group* group, int removeIndex);

/// <summary>
/// Retrieve the names of all users in the group.
/// </summary>
/// <param name="group">The Group object to examine.</param>
/// <param name="users">A StringList object to fill in with the names of the
/// users in the list.</param>
/// <returns>Returns true if the users where gathered; otherwise, returns
/// false, indicating an out of memory error condition.</returns>
bool Group_GetAllUsers(Group* group, StringList* users);

#endif // __MEDIATOR_GROUP_H__

