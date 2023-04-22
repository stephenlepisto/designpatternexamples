/// @file
/// @brief
/// The front end of the Users sub-system.  Contains the declarations of the
/// support functions for working with users as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_USERS_H__
#define __MEDIATOR_USERS_H__

#include "helpers/stringlist.h"

#include "Mediator_User.h"

/// <summary>
/// Represents error codes that can be returned from the User functions
/// used in the @ref mediator_pattern.
/// </summary>
typedef enum
{
    UserErrorCode_No_Error = 0, ///< Indicates success.
    UserErrorCode_Null_Argument = 1, ///< Indicates an argument is NULL.
    UserErrorCode_User_Does_Not_Exist = 2, ///< Indicates the user does not exist.
    UserErrorCode_No_Memory = 3, ///< Indicates an out of memory condition.
} UserErrorCode;

//-----------------------------------------------------------------------------

/// <summary>
/// Release all memory associated with the list of users.
/// </summary>
void Users_Clear();

/// <summary>
/// Add a user to the list of users.
/// </summary>
/// <param name="userName">Name of the user to add.</param>
/// <returns>A value from the @ref UserErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval UserErrorCode_No_Error indicates success.
/// @retval UserErrorCode_Null_Argument indicates the `user` parameter is NULL.
/// @retval UserErrorCode_User_Does_Not_Exist indicates the user does not exist.
/// @retval UserErrorCode_No_Memory indicates an out of memory condition.
UserErrorCode Users_AddUser(const char* userName);

/// <summary>
/// Remove a user from the list of users.
/// </summary>
/// <param name="userName">Name of the user to remove.</param>
/// <returns>A value from the @ref UserErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval UserErrorCode_No_Error indicates success.
/// @retval UserErrorCode_Null_Argument indicates the `user` parameter is NULL.
/// @retval UserErrorCode_User_Does_Not_Exist indicates the user does not exist.
UserErrorCode Users_RemoveUser(const char* userName);

/// <summary>
/// Find a user from the list of users given the user's name.
/// </summary>
/// <param name="userName">Name of the user to search for.</param>
/// <returns>A pointer to a User object if found; otherwise, returns NULL.
/// This is a borrowed pointer; do not deallocate it.</returns>
User* Users_FindUser(const char* userName);

/// <summary>
/// Retrieve a list of all users.
/// </summary>
/// <param name="userNames">A StringList object to be populated with all user
/// names.</param>
/// <returns>A value from the @ref UserErrorCode enumeration indicating success or
/// failure.</returns>
/// @retval UserErrorCode_No_Error indicates success.
/// @retval UserErrorCode_Null_Argument indicates the `userName` parameter is NULL.
/// @retval UserErrorCode_No_Memory indicates an out of memory condition.
UserErrorCode Users_GetAllUsers(StringList* userNames);

#endif // __MEDIATOR_USERS_H__
