/// @file
/// @brief
/// Implementation of the User support functions
/// as used in the @ref mediator_pattern.

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "Mediator_User.h"

///////////////////////////////////////////////////////////////////////////////
// User_Create()
///////////////////////////////////////////////////////////////////////////////
User* User_Create(const char* userName)
{
    User* user = NULL;

    if (userName != NULL)
    {
        user = calloc(1, sizeof(User));
        if (user != NULL)
        {
            user->Name = (const char*)_strdup(userName);
            if (user->Name == NULL)
            {
                free(user);
                user = NULL;
            }
        }
    }

    return user;
}

///////////////////////////////////////////////////////////////////////////////
// User_Destroy()
///////////////////////////////////////////////////////////////////////////////
void User_Destroy(User* user)
{
    if (user != NULL)
    {
        free((char*)user->Name);
        user->Name = NULL;
        free(user);
    }
}
