/// @file
/// @brief
/// The front end of the Mediator system that mediates between the Users and
/// the Groups sub-systems.  Contains the declarations of the Mediator
/// functions as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_FUNCTIONS_H__
#define __MEDIATOR_FUNCTIONS_H__

#include "helpers/stringlist.h"

/// <summary>
/// Represents error codes that can be returned from the Mediator functions
/// used in the @ref mediator_pattern.
/// </summary>
typedef enum
{
    MediatorErrorCode_No_Error = 0,             ///< No error occurred
    MediatorErrorCode_Null_Argument = 1,        ///< One of the arguments was null or empty.
    MediatorErrorCode_User_Does_Not_Exist = 2,  ///< The specified user does not exist.
    MediatorErrorCode_Group_Does_Not_Exist = 3, ///< The specified group does not exist.
    MediatorErrorCode_No_Memory = 4,            ///< Indicates an out of memory condition.
} MediatorErrorCode;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/// <summary>
/// Clear all memory associated with groups and users.
/// </summary>
void Mediator_ClearAll(void);


/// <summary>
/// Add a user to the list of known users.  If the name is already in
/// the list of users, the request to add is ignored.
/// </summary>
/// <param name="userName">Name of the user to add.  Do nothing if null or empty.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` parameter is null.
/// @retval MediatorErrorCode_No_Memory indicates an out of memory condition.
MediatorErrorCode Mediator_AddUser(const char* userName);

/// <summary>
/// Removes the specified user from the list of known users, if the
/// user exists.  Also removes the user from all groups.
/// </summary>
/// <param name="userName">Name of user to remove.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` parameter is null.
/// @retval MediatorErrorCode_User_Does_Not_Exist indicates the user does not exist.
MediatorErrorCode Mediator_RemoveUser(const char* userName);

/// <summary>
/// Add a group to the list of known groups.  If the group is already
/// in the list, the request to add is ignored.
/// </summary>
/// <param name="groupName">Name of the group to add.  Do nothing if null or empty.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `group` parameter is null.
/// @retval MediatorErrorCode_No_Memory indicates an out of memory condition.
MediatorErrorCode Mediator_AddGroup(const char* groupName);

/// <summary>
/// Remove the specified group from the list of known groups if the
/// group exists.
/// </summary>
/// <param name="groupName">Name of group to remove.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `group` parameter is null.
/// @retval MediatorErrorCode_Group_Does_Not_Exist indicates the group does not exist.
MediatorErrorCode Mediator_RemoveGroup(const char* groupName);

/// <summary>
/// Add the specified user to the specified group.  If the user is already
/// in the group, do nothing.  The user must exist.
/// </summary>
/// <param name="userName">Name of user to add.  Must be an existing user.</param>
/// <param name="groupName">Name of group to add user to.  Must be an existing group.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` or `group` parameter is null.
/// @retval MediatorErrorCode_User_Does_Not_Exist indicates the user does not exist.
/// @retval MediatorErrorCode_Group_Does_Not_Exist indicates the group does not exist.
/// @retval MediatorErrorCode_No_Memory indicates an out of memory condition.
MediatorErrorCode Mediator_AddUserToGroup(const char* userName, const char* groupName);

/// <summary>
/// Remove the specified user from the specified group.
/// </summary>
/// <param name="userName">Name of user to remove.  Must be an existing user.</param>
/// <param name="groupName">Name of group to remove user from.  Must be an existing group.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` or `group` parameter is null.
/// @retval MediatorErrorCode_User_Does_Not_Exist indicates the user does not exist.
/// @retval MediatorErrorCode_Group_Does_Not_Exist indicates the group does not exist.
MediatorErrorCode Mediator_RemoveUserFromGroup(const char* userName, const char* groupName);

/// <summary>
/// Remove the specified user from all existing groups.  The user still exists.
/// </summary>
/// <param name="userName">Name of user to remove.  Must be an existing user.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` parameter is null.
/// @retval MediatorErrorCode_User_Does_Not_Exist indicates the user does not exist.
MediatorErrorCode Mediator_RemoveUserFromAllGroups(const char* userName);

/// <summary>
/// Retrieve a list of all known groups.
/// </summary>
/// <param name="groups">A StringList object to be filled with the names of all
/// known groups.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_No_Memory indicates an out of memory condition.
MediatorErrorCode Mediator_GetAllGroups(StringList* groups);

/// <summary>
/// Retrieve a list of all known users.
/// </summary>
/// <param name="users">A StringList object to be filled with the names of all
/// known users.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_No_Memory indicates an out of memory condition.
MediatorErrorCode Mediator_GetAllUsers(StringList* users);

/// <summary>
/// Determine if the specified user is in the specified group.
/// </summary>
/// <param name="userName">Name of user to find.  Should be an existing user.</param>
/// <param name="groupName">Name of group to look in.  Should be an existing group.</param>
/// <returns>Returns true if the user is in the group; otherwise, returns false.</returns>
bool Mediator_IsUserInGroup(const char* userName, const char* groupName);

/// <summary>
/// Retrieve a list of users in the specified group.
/// </summary>
/// <param name="groupName">Name of the group to examine.  Must be an existing group.</param>
/// <param name="users">A StringList object to be filled in with the names of
/// users in the group.  Object is empty if the group does not contain any users.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `group` or `users` parameter is null.
/// @retval MediatorErrorCode_Group_Does_Not_Exist indicates the group does not exist.
MediatorErrorCode Mediator_GetUsersInGroup(const char* groupName, StringList* users);

/// <summary>
/// Retrieve a list of all groups that contain the specified user.
/// </summary>
/// <param name="userName">Name of the user to look for.  Must be an existing user.</param>
/// <param name="groups">A StringList object to be filled with the names of the
/// groups containing the user.  Object is empty if the name is not in any group.</param>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
/// @retval MediatorErrorCode_No_Error indicates success.
/// @retval MediatorErrorCode_Null_Argument indicates the `user` or `groups` parameter is null.
/// @retval MediatorErrorCode_User_Does_Not_Exist indicates the user does not exist.
MediatorErrorCode Mediator_GetGroupsWithUser(const char* userName, StringList* groups);


#endif // __MEDIATOR_FUNCTIONS_H__
