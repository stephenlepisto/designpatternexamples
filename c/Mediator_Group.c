/// @file
/// @brief
/// Implementation the Group support functions
/// as used in the @ref mediator_pattern.

#include <stdlib.h>
#include <memory.h>

#include "Mediator_Group.h"

///////////////////////////////////////////////////////////////////////////////
// Group_Create()
///////////////////////////////////////////////////////////////////////////////
Group* Group_Create(const char* groupName)
{
    Group* group = NULL;

    if (groupName != NULL)
    {
        group = calloc(1, sizeof(Group));
        if (group != NULL)
        {
            group->Name = groupName;
            StringList_Initialize(&group->Users);
        }
    }

    return group;
}

///////////////////////////////////////////////////////////////////////////////
// Group_Destroy()
///////////////////////////////////////////////////////////////////////////////
void Group_Destroy(Group* group)
{
    if (group != NULL)
    {
        StringList_Clear(&group->Users);
        free(group);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Group_AddUser()
///////////////////////////////////////////////////////////////////////////////
bool Group_AddUser(Group* group, const char* userName)
{
    bool added = false;
    if (group != NULL && userName != NULL)
    {
        added = StringList_AddString(&group->Users, userName);
    }

    return added;
}

///////////////////////////////////////////////////////////////////////////////
// Group_FindUser()
///////////////////////////////////////////////////////////////////////////////
int Group_FindUser(Group* group, const char* userName)
{
    int foundIndex = -1;

    if (group != NULL && userName != NULL)
    {
        foundIndex = StringList_Find(&group->Users, userName);
    }

    return foundIndex;
}

///////////////////////////////////////////////////////////////////////////////
// Group_RemoveUser()
///////////////////////////////////////////////////////////////////////////////
void Group_RemoveUser(Group* group, int removeIndex)
{
    if (group != NULL)
    {
        StringList_Remove(&group->Users, removeIndex);
    }
}


///////////////////////////////////////////////////////////////////////////////
// Group_GetAllUsers()
///////////////////////////////////////////////////////////////////////////////
bool Group_GetAllUsers(Group* group, StringList* users)
{
    bool usersGathered = true;

    if (group != NULL && users != NULL)
    {
        for (size_t index = 0; index < group->Users.strings_count; index++)
        {
            if (!StringList_AddString(users, group->Users.strings[index]))
            {
                usersGathered = false;
                break;
            }
        }
    }

    return usersGathered;
}
