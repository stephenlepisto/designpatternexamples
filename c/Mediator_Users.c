/// @file
/// @brief
/// The front end of the Users sub-system.  Contains the implementation of the
/// support functions for working with users as used in the @ref mediator_pattern.

#include "Mediator_UserList.h"
#include "Mediator_Users.h"

/// <summary>
/// The list of users.
/// </summary>
static UserList _users = { 0 };

//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Users_Clear()
///////////////////////////////////////////////////////////////////////////////
void Users_Clear()
{
    UserList_Clear(&_users);
}

///////////////////////////////////////////////////////////////////////////////
// Users_AddUser()
///////////////////////////////////////////////////////////////////////////////
UserErrorCode Users_AddUser(const char* userName)
{
    UserErrorCode errorCode = UserErrorCode_Null_Argument;

    if (userName != NULL)
    {
        errorCode = UserErrorCode_No_Memory;
        User* newUser = User_Create(userName);
        if (newUser != NULL)
        {
            if (UserList_AddUser(&_users, newUser))
            {
                errorCode = UserErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Users_RemoveUser()
///////////////////////////////////////////////////////////////////////////////
UserErrorCode Users_RemoveUser(const char* userName)
{
    UserErrorCode errorCode = UserErrorCode_Null_Argument;

    if (userName != NULL)
    {
        errorCode = UserErrorCode_User_Does_Not_Exist;
        int foundIndex = UserList_FindUser(&_users, userName);
        if (foundIndex != -1)
        {
            UserList_RemoveUser(&_users, foundIndex);
            errorCode = UserErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Users_FindUser()
///////////////////////////////////////////////////////////////////////////////
User* Users_FindUser(const char* userName)
{
    User* user = NULL;

    if (userName != NULL)
    {
        int foundIndex = UserList_FindUser(&_users, userName);
        if (foundIndex != -1)
        {
            user = _users.users[foundIndex];
        }
    }

    return user;
}


///////////////////////////////////////////////////////////////////////////////
// Users_FindUser()
///////////////////////////////////////////////////////////////////////////////
UserErrorCode Users_GetAllUsers(StringList* userNames)
{
    UserErrorCode errorCode = UserErrorCode_Null_Argument;

    if (userNames != NULL)
    {
        for (size_t index = 0; index < _users.users_count; index++)
        {
            User* user = _users.users[index];
            if (!StringList_AddString(userNames, user->Name))
            {
                errorCode = UserErrorCode_No_Memory;
                break;
            }
        }
    }

    return errorCode;
}
