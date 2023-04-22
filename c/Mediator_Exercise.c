/// @file
/// @brief
/// Implementation of the Mediator_Exercise() function as used in the 
/// @ref mediator_pattern.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/stringlist.h"
#include "helpers/dynamicstring.h"

#include "Mediator_Functions.h"
#include "Mediator_Exercise.h"

//=============================================================================
//=============================================================================

/// <summary>
/// Helper function to convert a list of strings to a comma-delimited
/// list in a single string.
/// </summary>
/// <param name="items">The list of strings to convert.</param>
/// <param name="output">A DynamicString object to be filled with the string
/// representation of the list.</param>
void _ListToString(StringList* items, DynamicString* output)
{
    if (items != NULL && output != NULL)
    {
        for (size_t index = 0; index < items->strings_count; ++index)
        {
            if (index != 0)
            {
                DynamicString_Append(output, ", ");
            }
            DynamicString_Append(output, items->strings[index]);
        }
    }
}

/// <summary>
/// Helper function to add a number of users to the Users list.
/// </summary>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
MediatorErrorCode Mediator_SetupUsers()
{
    MediatorErrorCode errorCode;
    // Operation 12: Add a user
    errorCode = Mediator_AddUser("Stephen");
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Gladys");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Marvin");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Arthur");
    }

    return errorCode;
}

/// <summary>
/// Helper function to add a number of groups to the Groups list and
/// then add users to the groups.  Note that everything here is done
/// with names.
/// </summary>
/// <returns>Returns a value from the @ref MediatorErrorCode enumeration
/// indicating success or failure.</returns>
MediatorErrorCode Mediator_SetupGroups()
{
    MediatorErrorCode errorCode;
    // Operation 10: Add a group
    errorCode = Mediator_AddGroup("admins");
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddGroup("Users");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddGroup("Power Users");
    }

    // Operation 7: Add user to a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Marvin", "admins");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Arthur", "admins");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Stephen", "Users");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Gladys", "Users");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Arthur", "Power Users");
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Marvin", "Power Users");
    }

    return errorCode;
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref mediator_pattern.
/// 
/// A mediator is instantiated then populated with users and groups.
/// Users are added to some of the groups.
/// 
/// A series of operations are then performed through the Mediator_
/// The output shows the results of each operation.  Note that all
/// operations are done using user and group names, with no knowledge
/// of the actual lists of users and groups.  The mediator hides all
/// the details.
/// </summary>
// ! [Using Mediator in C]
void Mediator_Exercise()
{
    printf("\nMediator Exercise\n");

    MediatorErrorCode errorCode;
    errorCode = Mediator_SetupUsers();
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = errorCode = Mediator_SetupGroups();
    }

    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    StringList userNames = { 0 };
    //-----------------------------------------------------------------
    // Operation 1: Determine all groups
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetAllGroups(&groupNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&groupNames, &output);
            printf("  Operation 1: Show all groups\n");
            printf("    All groups: %s\n", output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&groupNames);
        }
    }

    //-----------------------------------------------------------------
    // Operation 2: Determine all users
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetAllUsers(&userNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&userNames, &output);
            printf("  Operation 2: Show all users\n");
            printf("    All users : %s\n", output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&userNames);
        }
    }

    //-----------------------------------------------------------------
    const char* userName = NULL;
    const char* groupName = NULL;

    // Operation 3: Does a user belong to a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 3: Determine if a user is a member of a specific group.\n");
        userName = "Arthur";
        groupName = "admins";
        printf("    Is user '%s' in the '%s' group?", userName, groupName);
        printf("  %s\n", Mediator_IsUserInGroup(userName, groupName) ? "Yes" : "No");
    }

    //-----------------------------------------------------------------
    // Operation 4: Show all users in a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 4: Show all users in a specific group.\n");
        groupName = "Users";
        errorCode = Mediator_GetUsersInGroup(groupName, &userNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&userNames, &output);
            printf("    All users in '%s' group: %s\n", groupName, output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&userNames);
        }
    }

    //-----------------------------------------------------------------
    // Operation 5: Show all groups with a user
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 5: Show all groups containing a specific user.\n");
        userName = "Marvin";
        errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&groupNames, &output);
            printf("    All groups with user '%s': %s\n", userName, output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&groupNames);
        }
    }

    //-----------------------------------------------------------------
    // Operation 6: Show Remove a user from a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 6: Remove a user from a group.\n");
        userName = "Marvin";
        groupName = "Power Users";
        errorCode = Mediator_RemoveUserFromGroup(userName, groupName);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            printf("    Removed user '%s' from group '%s'\n", userName, groupName);
            errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
            if (errorCode == MediatorErrorCode_No_Error)
            {
                _ListToString(&groupNames, &output);
                printf("      All groups with user '%s': %s\n", userName, output.string);
                DynamicString_Clear(&output);
                StringList_Clear(&groupNames);
            }
        }
    }

    //-----------------------------------------------------------------
    // Operation 7: Add a user to a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 7: Add a user to a group.\n");
        groupName = "Users";
        printf("    Adding user '%s' to group '%s'.\n", userName, groupName);
        errorCode = Mediator_AddUserToGroup(userName, groupName);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
            if (errorCode == MediatorErrorCode_No_Error)
            {
                _ListToString(&groupNames, &output);
                printf("      All groups with user '%s': %s\n", userName, output.string);
                DynamicString_Clear(&output);
                StringList_Clear(&groupNames);
            }
        }
    }

    //-----------------------------------------------------------------
    // Operation 8: Remove a user from all groups
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 8: Remove a user from all groups.\n");
        userName = "Arthur";
        errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&groupNames, &output);
            printf("    Removing user '%s' from all groups.\n", userName);
            printf("      Start: all groups with user '%s': %s\n", userName, output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&groupNames);
            printf("      Removing...\n");
            errorCode = Mediator_RemoveUserFromAllGroups(userName);
            if (errorCode == MediatorErrorCode_No_Error)
            {
                errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
                if (errorCode == MediatorErrorCode_No_Error)
                {
                    _ListToString(&groupNames, &output);
                    printf("      End: all groups with user '%s': %s\n", userName, output.string);
                    DynamicString_Clear(&output);
                    StringList_Clear(&groupNames);
                }
            }
        }
    }

    //-----------------------------------------------------------------
    // Operation 9: Remove a user (which also removes user from all groups)
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("  Operation 9: Remove a user (also removes the user from all groups).\n");
        userName = "Marvin";
        printf("    Removing user '%s'.\n", userName);
        errorCode = Mediator_RemoveUser(userName);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            errorCode = Mediator_GetAllUsers(&userNames);
            if (errorCode == MediatorErrorCode_No_Error)
            {
                _ListToString(&userNames, &output);
                printf("      All users : %s\n", output.string);
                DynamicString_Clear(&output);
                StringList_Clear(&userNames);
            }
        }
    }

    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetAllGroups(&groupNames);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            for (size_t index = 0; index < groupNames.strings_count; index++)
            {
                const char* name = groupNames.strings[index];
                errorCode = Mediator_GetUsersInGroup(name, &userNames);
                if (errorCode == MediatorErrorCode_No_Error)
                {
                    _ListToString(&userNames, &output);
                    printf("      Users in group '%s': %s\n", name, output.string);
                    DynamicString_Clear(&output);
                    StringList_Clear(&userNames);
                }
                else
                {
                    break;
                }
            }
        }
    }
    //-----------------------------------------------------------------

    if (errorCode != MediatorErrorCode_No_Error)
    {
        if (errorCode == MediatorErrorCode_No_Memory)
        {
            printf("  Error!  Out of memory condition in a Mediator call!\n");
        }
        else if (errorCode == MediatorErrorCode_Group_Does_Not_Exist)
        {
            printf("  Error!  Unknown group specified in a Mediator call!\n");
        }
        else if (errorCode == MediatorErrorCode_User_Does_Not_Exist)
        {
            printf("  Error!  Unknown user specified in a Mediator call!\n");
        }
        else if (errorCode == MediatorErrorCode_Null_Argument)
        {
            printf("  Error!  Null argument passed in a Mediator call!");
        }
    }

    // Clean-up
    Mediator_ClearAll();

    printf("  Done.\n");
}
// ! [Using Mediator in C]
