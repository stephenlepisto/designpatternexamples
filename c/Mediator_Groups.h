/// @file
/// @brief
/// The front end of the Groups sub-system.  Contains the declarations of the
/// support functions for working with groups as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_GROUPS_H__
#define __MEDIATOR_GROUPS_H__

#include "helpers/stringlist.h"

#include "Mediator_Group.h"

/// <summary>
/// Represents error codes that can be returned from the Group functions
/// used in the @ref mediator_pattern.
/// </summary>
typedef enum
{
    GroupErrorCode_No_Error = 0, ///< Indicates success.
    GroupErrorCode_Null_Argument = 1, ///< Indicates an argument is NULL.
    GroupErrorCode_Group_Does_Not_Exist = 2, ///< Indicates the group does not exist.
    GroupErrorCode_No_Memory = 3, ///< Indicates an out of memory condition.
} GroupErrorCode;

//-----------------------------------------------------------------------------

/// <summary>
/// Release all memory associated with list of groups.
/// </summary>
void Groups_Clear();

/// <summary>
/// Add a group to the list of groups.
/// </summary>
/// <param name="groupName">Name of the group to add.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `groupName` parameter is NULL.
/// @retval GroupErrorCode_Group_Does_Not_Exist indicates the group does not exist.
/// @retval GroupErrorCode_No_Memory indicates an out of memory condition.
GroupErrorCode Groups_AddGroup(const char* groupName);

/// <summary>
/// Remove a group from the list of groups.
/// </summary>
/// <param name="groupName">Name of the group to remove.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `groupName` parameter is NULL.
/// @retval GroupErrorCode_Group_Does_Not_Exist indicates the group does not exist.
GroupErrorCode Groups_RemoveGroup(const char* groupName);

/// <summary>
/// Find a group from the list of groups given the group's name.
/// </summary>
/// <param name="groupName">Name of the group to search for.</param>
/// <returns>A pointer to a Group object if found; otherwise, returns NULL.
/// This is a borrowed pointer; do not deallocate it.</returns>
Group* Groups_FindGroup(const char* groupName);

/// <summary>
/// Determine if the specified user is in this group.  This is a case-
/// sensitive search.
/// </summary>
/// <param name="userName">Name of the user to look for.  Should not be NULL.</param>
/// <param name="groupName">Name of the group to look in.  Should not be NULL.</param>
/// <returns>Return true if the user is in this group; otherwise false.</returns>
bool Groups_UserInGroup(const char* userName, const char* groupName);

/// <summary>
/// Add the specified user to the specified group.  If the user is already in
/// the group, the operation is ignored.
/// </summary>
/// <param name="userName">Name of the user to add.  Cannot be null or empty.</param>
/// <param name="groupName">Name of the group to add to.  Cannot be null or empty.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `userName` or `groupName` parameter is NULL.
/// @retval GroupErrorCode_No_Memory indicates an out of memory condition.
GroupErrorCode Groups_AddUserGroup(const char* userName, const char* groupName);

/// <summary>
/// Remove the specified user from the specified group.  If the user is not in
/// the group, the operation is ignored.
/// </summary>
/// <param name="userName">Name of the user to remove.  Cannot be null or empty.</param>
/// <param name="groupName">Name of the group to remove from.  Cannot be null or empty.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `userName` or `groupName` parameter is NULL.
GroupErrorCode Groups_RemoveUserFromGroup(const char* userName, const char* groupName);

/// <summary>
/// Remove the specified user from all groups.
/// </summary>
/// <param name="userName">Name of the user to remove. Cannot be null.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `userName` parameter is NULL.
GroupErrorCode Groups_RemoveUserFromAllGroups(const char* userName);


/// <summary>
/// Retrieve a list of all group names.
/// </summary>
/// <param name="groups">A StringList object to be populated with the names of
/// all groups.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `groups` parameter is NULL.
GroupErrorCode Groups_GetAllGroups(StringList* groups);

/// <summary>
/// Retrieve a list of all users in the specified group.
/// </summary>
/// <param name="groupName">Name of the group to examine.</param>
/// <param name="users">A StringList object to be populated with the names of
/// all users in the group.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `groupName` or `groups` parameter is NULL.
GroupErrorCode Groups_GetAllUsersInGroup(const char* groupName, StringList* users);

/// <summary>
/// Retrieve a list of all groups that contains the given user.
/// </summary>
/// <param name="userName">Name of the user to search for.</param>
/// <param name="groups">A StringList object to be filled with the names of
/// groups containing the given user.</param>
/// <returns>A value from the @ref GroupErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval GroupErrorCode_No_Error indicates success.
/// @retval GroupErrorCode_Null_Argument indicates the `userName` or `groups` parameter is NULL.
/// @retval GroupErrorCode_No_Memory indicates an out of memory condition.
GroupErrorCode Groups_GetGroupsWithUser(const char* userName, StringList* groups);

#endif // __MEDIATOR_GROUPS_H__

