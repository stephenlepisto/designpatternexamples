/// @file
/// @brief
/// Declaration of the UserList structure and the associated support functions
/// as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_USERLIST_H__
#define __MEDIATOR_USERLIST_H__

#include <stdlib.h>
#include <stdbool.h>

#include "Mediator_User.h"

/// <summary>
/// Represents a list of users.  Call UserList_Initialize() to start and
/// UserList_Clear() to release all resources and restore to empty state.
/// </summary>
typedef struct
{
    User** users;           ///< Array of pointers to User objects.
    size_t users_count;     ///< Number of pointers in the `users` list.
    size_t allocated_count; ///< Size of the allocated `users` list.
} UserList;

//-----------------------------------------------------------------------------

/// <summary>
/// Initialize the given UserList object for initial use.
/// </summary>
/// <param name="userList">The UserList object to initialize.</param>
void UserList_Initialize(UserList* userList);

/// <summary>
/// Clear the given UserList object to release all associated resources.
/// 
/// After this function returns, the object is an empty list ready to be used
/// again.
/// </summary>
/// <param name="userList">The UserList object to clear.</param>
void UserList_Clear(UserList* userList);

/// <summary>
/// Add the specified User object to the specified UserList object.  The
/// list takes ownership of the User object and is responsible for releasing
/// the memory associated with the User object.
/// </summary>
/// <param name="userList">The UserList object to which to add the user.</param>
/// <param name="user">The User object to add to the list.</param>
bool UserList_AddUser(UserList* userList, User* user);

/// <summary>
/// Search the given UserList object for the specified user by name and
/// return the index of the user if found.
/// </summary>
/// <param name="userList">The UserList object to search.</param>
/// <param name="userName">The name of the user to look for.  This is a case-
/// sensitive search.</param>
/// <returns>Returns the index of the user in the user list if found;
/// otherwise returns -1, indicating the user does not exist.</returns>
int UserList_FindUser(UserList* userList, const char* userName);

/// <summary>
/// Remove the user at the specified index in the given UserList object.
/// 
/// Since this changes the list of users, all index values after the given
/// index are no longer valid.
/// </summary>
/// <param name="userList">The UserList object to remove from.</param>
/// <param name="removeIndex">Index of the user to remove.  Use UserList_FindUser()
/// to get this index.</param>
void UserList_RemoveUser(UserList* userList, int removeIndex);

#endif // __MEDIATOR_USERLIST_H__
