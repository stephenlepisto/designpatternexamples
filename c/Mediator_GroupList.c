/// @file
/// @brief
/// Implementation of the GroupList structure's support functions
/// as used in the @ref mediator_pattern.

#include <string.h>

#include "Mediator_GroupList.h"

///////////////////////////////////////////////////////////////////////////////
// GroupList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void GroupList_Initialize(GroupList* groupList)
{
    if (groupList != NULL)
    {
        groupList->groups = NULL;
        groupList->groups_count = 0;
        groupList->allocated_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// GroupList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void GroupList_Clear(GroupList* groupList)
{
    if (groupList != NULL)
    {
        for (size_t index = 0; index < groupList->groups_count; index++)
        {
            Group_Destroy(groupList->groups[index]);
        }
        free(groupList->groups);
        GroupList_Initialize(groupList);
    }
}

///////////////////////////////////////////////////////////////////////////////
// GroupList_Initialize()
///////////////////////////////////////////////////////////////////////////////
bool GroupList_AddGroup(GroupList* groupList, Group* group)
{
    bool added = false;

    if (groupList != NULL && group != NULL)
    {
        Group** new_list = NULL;
        if (groupList->groups == NULL)
        {
            new_list = calloc(1, sizeof(Group*));
            groupList->allocated_count = 1;
        }
        else if (groupList->groups_count < groupList->allocated_count)
        {
            new_list = groupList->groups;
        }
        else
        {
            size_t new_count = groupList->allocated_count + 1;
            new_list = realloc(groupList->groups, new_count * sizeof(Group*));
            groupList->allocated_count = new_count;
        }
        if (new_list != NULL)
        {
            groupList->groups = new_list;
            groupList->groups[groupList->groups_count] = group;
            groupList->groups_count++;
            added = true;
        }
    }
    return added;
}

///////////////////////////////////////////////////////////////////////////////
// GroupList_Initialize()
///////////////////////////////////////////////////////////////////////////////
int GroupList_FindGroup(GroupList* groupList, const char* groupName)
{
    int foundIndex = -1;

    if (groupList != NULL && groupName != NULL)
    {
        for (size_t index = 0; index < groupList->groups_count; index++)
        {
            if (strcmp(groupName, groupList->groups[index]->Name) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}

///////////////////////////////////////////////////////////////////////////////
// GroupList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void GroupList_RemoveGroup(GroupList* groupList, int removeIndex)
{
    if (groupList != NULL && groupList->groups != NULL)
    {
        if (removeIndex >= 0 && (size_t)removeIndex < groupList->groups_count)
        {
            Group_Destroy(groupList->groups[removeIndex]);
            for (size_t groupIndex = removeIndex; groupIndex < groupList->allocated_count - 1; groupIndex++)
            {
                groupList->groups[groupIndex] = groupList->groups[groupIndex + 1];
            }
            groupList->groups_count--;
        }
    }
}
