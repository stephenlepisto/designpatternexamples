/// @file
/// @brief
/// Declaration of the User structure and the associated support functions
/// as used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_USER_H__
#define __MEDIATOR_USER_H__

/// <summary>
/// Represents a user with a name.
/// </summary>
typedef struct
{
    /// <summary>
    /// The name of the user.
    /// </summary>
    const char* Name;
}  User;

//-----------------------------------------------------------------------------

/// <summary>
/// Create a User object with the specified name.
/// </summary>
/// <param name="userName">Name of the user</param>
/// <returns>Returns a new User object initialized to the given name; returns
/// NULL if there was an out of memory condition.</returns>
User* User_Create(const char* userName);

/// <summary>
/// Destroy the given User object, releasing any associated memory resources.
/// After this function returns, the pointer to the User object is no longer
/// valid.
/// </summary>
/// <param name="user">The User object to destroy.</param>
void User_Destroy(User* user);


#endif // __MEDIATOR_USER_H__

