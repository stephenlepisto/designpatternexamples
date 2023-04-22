/// @file
/// @brief
/// The front end of the Groups sub-system.  Contains the implementation of
/// the Group support functions as used in the @ref mediator_pattern.

#include <stdlib.h>

#include "Mediator_GroupList.h"
#include "Mediator_Groups.h"


/// <summary>
/// The list of all groups.
/// </summary>
static GroupList _groups = { 0 };

//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// Groups_Clear()
///////////////////////////////////////////////////////////////////////////////
void Groups_Clear()
{
    GroupList_Clear(&_groups);
}

///////////////////////////////////////////////////////////////////////////////
// Groups_AddGroup()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_AddGroup(const char* groupName)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (groupName != NULL)
    {
        int foundIndex = GroupList_FindGroup(&_groups, groupName);
        if (foundIndex == -1)
        {
            errorCode = GroupErrorCode_No_Memory;
            Group* newGroup = Group_Create(groupName);
            if (newGroup != NULL)
            {
                if (GroupList_AddGroup(&_groups, newGroup))
                {
                    errorCode = GroupErrorCode_No_Error;
                }
                else
                {
                    Group_Destroy(newGroup);
                    newGroup = NULL;
                }
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Groups_RemoveGroup()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_RemoveGroup(const char* groupName)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (groupName != NULL)
    {
        errorCode = GroupErrorCode_Group_Does_Not_Exist;
        int groupIndex = GroupList_FindGroup(&_groups, groupName);
        if (groupIndex != -1)
        {
            GroupList_RemoveGroup(&_groups, groupIndex);
            errorCode = GroupErrorCode_No_Error;
        }
    }

    return errorCode;
}


///////////////////////////////////////////////////////////////////////////////
// Groups_FindGroup()
///////////////////////////////////////////////////////////////////////////////
Group* Groups_FindGroup(const char* groupName)
{
    Group* foundGroup = NULL;

    if (groupName != NULL)
    {
        int foundIndex = GroupList_FindGroup(&_groups, groupName);
        if (foundIndex != -1)
        {
            foundGroup = _groups.groups[foundIndex];
        }
    }

    return foundGroup;
}


///////////////////////////////////////////////////////////////////////////////
// Groups_UserInGroup()
///////////////////////////////////////////////////////////////////////////////
bool Groups_UserInGroup(const char* userName, const char* groupName)
{
    bool userFound = false;

    if (userName != NULL && groupName != NULL)
    {
        int groupIndex = GroupList_FindGroup(&_groups, groupName);
        if (groupIndex != -1)
        {
            int userIndex = Group_FindUser(_groups.groups[groupIndex], userName);
            userFound = userIndex != -1;
        }
    }

    return userFound;
}

///////////////////////////////////////////////////////////////////////////////
// Groups_AddUser()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_AddUserGroup(const char* userName, const char* groupName)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (userName != NULL && groupName != NULL)
    {
        errorCode = GroupErrorCode_Group_Does_Not_Exist;
        int groupIndex = GroupList_FindGroup(&_groups, groupName);
        if (groupIndex != -1)
        {
            errorCode = GroupErrorCode_No_Memory;
            Group* group = _groups.groups[groupIndex];
            if (Group_AddUser(group, userName))
            {
                errorCode = GroupErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Groups_RemoveUser()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_RemoveUserFromGroup(const char* userName, const char* groupName)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (userName != NULL && groupName != NULL)
    {
        errorCode = GroupErrorCode_Group_Does_Not_Exist;
        int groupIndex = GroupList_FindGroup(&_groups, groupName);
        if (groupIndex != -1)
        {
            Group* group = _groups.groups[groupIndex];
            int userIndex = Group_FindUser(group, userName);
            if (userIndex != -1)
            {
                Group_RemoveUser(group, userIndex);
                errorCode = GroupErrorCode_No_Error;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Groups_RemoveUserFromAllGroups()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_RemoveUserFromAllGroups(const char* userName)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (userName != NULL)
    {
        errorCode = GroupErrorCode_No_Error;
        for (size_t index = 0; index < _groups.groups_count; index++)
        {
            Group* group = _groups.groups[index];
            int userIndex = Group_FindUser(group, userName);
            if (userIndex != -1)
            {
                Group_RemoveUser(group, userIndex);
            }
        }
    }

    return errorCode;
}


///////////////////////////////////////////////////////////////////////////////
// Groups_GetAllGroups()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_GetAllGroups(StringList* groups)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (groups != NULL)
    {
        errorCode = GroupErrorCode_No_Error;
        for (size_t index = 0; index < _groups.groups_count; index++)
        {
            Group* group = _groups.groups[index];
            if (!StringList_AddString(groups, group->Name))
            {
                errorCode = GroupErrorCode_No_Memory;
                    break;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// Groups_GetAllUsersInGroup()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_GetAllUsersInGroup(const char* groupName, StringList* users)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (groupName != NULL && users != NULL)
    {
        errorCode = GroupErrorCode_Group_Does_Not_Exist;
        int groupIndex = GroupList_FindGroup(&_groups, groupName);
        if (groupIndex != -1)
        {
            errorCode = GroupErrorCode_No_Error;
            Group* group = _groups.groups[groupIndex];
            if (!Group_GetAllUsers(group, users))
            {
                errorCode = GroupErrorCode_No_Memory;
            }
        }
    }

    return errorCode;
}


///////////////////////////////////////////////////////////////////////////////
// Groups_GetGroupsWithUser()
///////////////////////////////////////////////////////////////////////////////
GroupErrorCode Groups_GetGroupsWithUser(const char* userName, StringList* groups)
{
    GroupErrorCode errorCode = GroupErrorCode_Null_Argument;

    if (userName != NULL && groups != NULL)
    {
        errorCode = GroupErrorCode_No_Error;
        for (size_t index = 0; index < _groups.groups_count; index++)
        {
            Group* group = _groups.groups[index];
            int userIndex = Group_FindUser(group, userName);
            if (userIndex != -1)
            {
                if (!StringList_AddString(groups, group->Name))
                {
                    errorCode = GroupErrorCode_No_Memory;
                    break;
                }
            }
        }
    }

    return errorCode;
}
