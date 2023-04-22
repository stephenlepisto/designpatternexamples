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
void Mediator_SetupUsers()
{
    // Operation 12: Add a user
    Mediator_AddUser("Stephen");
    Mediator_AddUser("Gladys");
    Mediator_AddUser("Marvin");
    Mediator_AddUser("Arthur");
}

/// <summary>
/// Helper function to add a number of groups to the Groups list and
/// then add users to the groups.  Note that everything here is done
/// with names.
/// </summary>
void Mediator_SetupGroups()
{
    // Operation 10: Add a group
    Mediator_AddGroup("admins");
    Mediator_AddGroup("Users");
    Mediator_AddGroup("Power Users");

    // Operation 7: Add user to a group
    Mediator_AddUserToGroup("Marvin", "admins");
    Mediator_AddUserToGroup("Arthur", "admins");
    Mediator_AddUserToGroup("Stephen", "Users");
    Mediator_AddUserToGroup("Gladys", "Users");
    Mediator_AddUserToGroup("Arthur", "Power Users");
    Mediator_AddUserToGroup("Marvin", "Power Users");
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

    Mediator_SetupUsers();
    Mediator_SetupGroups();

    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    StringList userNames = { 0 };
    //-----------------------------------------------------------------
    // Operation 1: Determine all groups
    Mediator_GetAllGroups(&groupNames);
    _ListToString(&groupNames, &output);
    printf("  Operation 1: Show all groups\n");
    printf("    All groups: %s\n", output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);

    //-----------------------------------------------------------------
    // Operation 2: Determine all users
    Mediator_GetAllUsers(&userNames);
    _ListToString(&userNames, &output);
    printf("  Operation 2: Show all users\n");
    printf("    All users : %s\n", output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&userNames);

    //-----------------------------------------------------------------
    // Operation 3: Does a user belong to a group
    printf("  Operation 3: Determine if a user is a member of a specific group.\n");
    const char* userName = "Arthur";
    const char* groupName = "admins";
    printf("    Is user '%s' in the '%s' group?", userName, groupName);
    printf("  %s\n", Mediator_IsUserInGroup(userName, groupName) ? "Yes" : "No");

    //-----------------------------------------------------------------
    // Operation 4: Show all users in a group
    printf("  Operation 4: Show all users in a specific group.\n");
    groupName = "Users";
    Mediator_GetUsersInGroup(groupName, &userNames);
    _ListToString(&userNames, &output);
    printf("    All users in '%s' group: %s\n", groupName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&userNames);

    //-----------------------------------------------------------------
    // Operation 5: Show all groups with a user
    printf("  Operation 5: Show all groups containing a specific user.\n");
    userName = "Marvin";
    Mediator_GetGroupsWithUser(userName, &groupNames);
    _ListToString(&groupNames, &output);
    printf("    All groups with user '%s': %s\n", userName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);

    //-----------------------------------------------------------------
    // Operation 6: Show Remove a user from a group
    printf("  Operation 6: Remove a user from a group.\n");
    userName = "Marvin";
    groupName = "Power Users";
    Mediator_RemoveUserFromGroup(userName, groupName);
    printf("    Removed user '%s' from group '%s'\n", userName, groupName);
    Mediator_GetGroupsWithUser(userName, &groupNames);
    _ListToString(&groupNames, &output);
    printf("      All groups with user '%s': %s\n", userName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);

    //-----------------------------------------------------------------
    // Operation 7: Add a user to a group
    printf("  Operation 7: Add a user to a group.\n");
    groupName = "Users";
    printf("    Adding user '%s' to group '%s'.\n", userName, groupName);
    Mediator_AddUserToGroup(userName, groupName);
    Mediator_GetGroupsWithUser(userName, &groupNames);
    _ListToString(&groupNames, &output);
    printf("      All groups with user '%s': %s\n", userName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);

    //-----------------------------------------------------------------
    // Operation 8: Remove a user from all groups
    printf("  Operation 8: Remove a user from all groups.\n");
    userName = "Arthur";
    Mediator_GetGroupsWithUser(userName, &groupNames);
    _ListToString(&groupNames, &output);
    printf("    Removing user '%s' from all groups.\n", userName);
    printf("      Start: all groups with user '%s': %s\n", userName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);
    printf("      Removing...\n");
    Mediator_RemoveUserFromAllGroups(userName);
    Mediator_GetGroupsWithUser(userName, &groupNames);
    _ListToString(&groupNames, &output);
    printf("      End: all groups with user '%s': %s\n", userName, output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&groupNames);

    //-----------------------------------------------------------------
    // Operation 9: Remove a user (which also removes user from all groups)
    printf("  Operation 9: Remove a user (also removes the user from all groups).\n");
    userName = "Marvin";
    printf("    Removing user '%s'.\n", userName);
    Mediator_RemoveUser(userName);
    Mediator_GetAllUsers(&userNames);
    _ListToString(&userNames, &output);
    printf("      All users : %s\n", output.string);
    DynamicString_Clear(&output);
    StringList_Clear(&userNames);

    Mediator_GetAllGroups(&groupNames);
    for (size_t index = 0; index < groupNames.strings_count; index++)
    {
        const char* name = groupNames.strings[index];
        Mediator_GetUsersInGroup(name, &userNames);
        _ListToString(&userNames, &output);
        printf("      Users in group '%s': %s\n", name, output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&userNames);
    }
    //-----------------------------------------------------------------

    // Clean-up
    Mediator_ClearAll();

    printf("  Done.\n");
}
// ! [Using Mediator in C]
