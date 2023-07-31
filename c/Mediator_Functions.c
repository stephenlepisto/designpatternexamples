/// @file
/// @brief
/// The front end of the Mediator system that mediates between the Users and
/// the Groups sub-systems.  Contains the implementation of the Mediator
/// functions as used in the @ref mediator_pattern.

#include <stdlib.h>

#include "Mediator_Users.h"
#include "Mediator_Groups.h"

#include "Mediator_Functions.h"


///////////////////////////////////////////////////////////////////////////////
// Mediator_ClearAll()
///////////////////////////////////////////////////////////////////////////////
void Mediator_ClearAll(void)
{
    Users_Clear();
    Groups_Clear();
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_AddUser()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_AddUser(const char* userName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL)
    {
        UserErrorCode userErrorCode = Users_AddUser(userName);
        if (userErrorCode == UserErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_RemoveUser()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_RemoveUser(const char* userName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL)
    {
        errorCode = Mediator_RemoveUserFromAllGroups(userName);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            UserErrorCode userErrorCode = Users_RemoveUser(userName);
            if (userErrorCode == UserErrorCode_User_Does_Not_Exist)
            {
                errorCode = MediatorErrorCode_User_Does_Not_Exist;
            }
            else
            {
                errorCode = MediatorErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_AddGroup()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_AddGroup(const char* groupName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (groupName != NULL)
    {
        GroupErrorCode groupErrorCode = Groups_AddGroup(groupName);
        if (groupErrorCode == GroupErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_RemoveGroup()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_RemoveGroup(const char* groupName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (groupName != NULL)
    {
        GroupErrorCode groupErrorCode = Groups_RemoveGroup(groupName);
        if (groupErrorCode == GroupErrorCode_Group_Does_Not_Exist)
        {
            errorCode = MediatorErrorCode_Group_Does_Not_Exist;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_AddUserToGroup()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_AddUserToGroup(const char* userName, const char* groupName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL && groupName != NULL)
    {
        errorCode = MediatorErrorCode_User_Does_Not_Exist;
        if (!Groups_UserInGroup(userName, groupName))
        {
            GroupErrorCode groupErrorCode = Groups_AddUserGroup(userName, groupName);
            if (groupErrorCode == GroupErrorCode_No_Memory)
            {
                errorCode = MediatorErrorCode_No_Memory;
            }
            else if (groupErrorCode == GroupErrorCode_Group_Does_Not_Exist)
            {
                errorCode = MediatorErrorCode_Group_Does_Not_Exist;
            }
            else
            {
                errorCode = MediatorErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_RemoveUserFromGroup()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_RemoveUserFromGroup(const char* userName, const char* groupName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL && groupName != NULL)
    {
        errorCode = MediatorErrorCode_User_Does_Not_Exist;
        if (Groups_UserInGroup(userName, groupName))
        {
            GroupErrorCode groupErrorCode = Groups_RemoveUserFromGroup(userName, groupName);
            if (groupErrorCode == GroupErrorCode_Group_Does_Not_Exist)
            {
                errorCode = MediatorErrorCode_Group_Does_Not_Exist;
            }
            else
            {
                errorCode = MediatorErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_RemoveUserFromAllGroups()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_RemoveUserFromAllGroups(const char* userName)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL)
    {
        errorCode = MediatorErrorCode_User_Does_Not_Exist;
        User* user = Users_FindUser(userName);
        if (user != NULL)
        {
            GroupErrorCode groupErrorCode = Groups_RemoveUserFromAllGroups(userName);
            if (groupErrorCode == GroupErrorCode_No_Error)
            {
                errorCode = MediatorErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_GetAllGroups()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_GetAllGroups(StringList* groupNames)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;
    if (groupNames != NULL)
    {
        GroupErrorCode groupErrorCode = Groups_GetAllGroups(groupNames);
        if (groupErrorCode == GroupErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_GetAllUsers()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_GetAllUsers(StringList* userNames)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;
    if (userNames != NULL)
    {
        UserErrorCode userErrorCode = Users_GetAllUsers(userNames);
        if (userErrorCode == UserErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_IsUserInGroup()
///////////////////////////////////////////////////////////////////////////////
bool Mediator_IsUserInGroup(const char* userName, const char* groupName)
{
    bool inGroup = false;

    if (userName != NULL && groupName != NULL)
    {
        inGroup = Groups_UserInGroup(userName, groupName);
    }

    return inGroup;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_GetUsersInGroup()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_GetUsersInGroup(const char* groupName, StringList* userNames)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (groupName != NULL && userNames != NULL)
    {
        GroupErrorCode groupErrorCode = Groups_GetAllUsersInGroup(groupName, userNames);
        if (groupErrorCode == GroupErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Mediator_GetGroupsWithUser()
///////////////////////////////////////////////////////////////////////////////
MediatorErrorCode Mediator_GetGroupsWithUser(const char* userName, StringList* groupNames)
{
    MediatorErrorCode errorCode = MediatorErrorCode_Null_Argument;

    if (userName != NULL && groupNames != NULL)
    {
        GroupErrorCode groupErrorCode = Groups_GetGroupsWithUser(userName, groupNames);
        if (groupErrorCode == GroupErrorCode_No_Memory)
        {
            errorCode = MediatorErrorCode_No_Memory;
        }
        else
        {
            errorCode = MediatorErrorCode_No_Error;
        }
    }

    return errorCode;
}
