/// @file
/// @brief
/// IMplementation of the UserList support functions
/// as used in the @ref mediator_pattern.

#include <memory.h>
#include <string.h>

#include "Mediator_UserList.h"

///////////////////////////////////////////////////////////////////////////////
// UserList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void UserList_Initialize(UserList* userList)
{
    if (userList != NULL)
    {
        userList->users = NULL;
        userList->users_count = 0;
        userList->allocated_count = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
// UserList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void UserList_Clear(UserList* userList)
{
    if (userList != NULL)
    {
        for (size_t index = 0; index < userList->users_count; index++)
        {
            User_Destroy(userList->users[index]);
        }
        free(userList->users);
        UserList_Initialize(userList);
    }
}

///////////////////////////////////////////////////////////////////////////////
// UserList_Initialize()
///////////////////////////////////////////////////////////////////////////////
bool UserList_AddUser(UserList* userList, User* user)
{
    bool added = false;

    if (userList != NULL && user != NULL)
    {
        User** new_list = NULL;
        if (userList->users == NULL)
        {
            new_list = calloc(1, sizeof(User*));
            userList->allocated_count = 1;
        }
        else if (userList->users_count < userList->allocated_count)
        {
            new_list = userList->users;
        }
        else
        {
            size_t new_count = userList->allocated_count + 1;
            new_list = realloc(userList->users, new_count * sizeof(User*));
            userList->allocated_count = new_count;
        }
        if (new_list != NULL)
        {
            userList->users = new_list;
            userList->users[userList->users_count] = user;
            userList->users_count++;
            added = true;
        }
    }
    return added;
}

///////////////////////////////////////////////////////////////////////////////
// UserList_Initialize()
///////////////////////////////////////////////////////////////////////////////
int UserList_FindUser(UserList* userList, const char* userName)
{
    int foundIndex = -1;

    if (userList != NULL && userName != NULL)
    {
        for (size_t index = 0; index < userList->users_count; index++)
        {
            if (strcmp(userName, userList->users[index]->Name) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}

///////////////////////////////////////////////////////////////////////////////
// UserList_Initialize()
///////////////////////////////////////////////////////////////////////////////
void UserList_RemoveUser(UserList* userList, int removeIndex)
{
    if (userList != NULL && userList->users != NULL)
    {
        if (removeIndex >= 0 && (size_t)removeIndex < userList->users_count)
        {
            User_Destroy(userList->users[removeIndex]);
            for (size_t userIndex = removeIndex; userIndex < userList->allocated_count - 1; userIndex++)
            {
                userList->users[userIndex] = userList->users[userIndex + 1];
            }
            userList->users_count--;
        }
    }
}
