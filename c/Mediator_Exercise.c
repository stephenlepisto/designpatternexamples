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
/// Helper function to convert a @ref MediatorErrorCode to a string.
/// </summary>
/// <param name="errorCode">A value from the @ref MediatorErrorCode enumeration
/// indicating some kind of error condition from the mediator.</param>
/// <returns>Returns a pointer to a string representing the error code.</returns>
const char* _GetMediatorErrorMessage(MediatorErrorCode errorCode)
{
    const char* msg = "";

    switch (errorCode)
    {
        case MediatorErrorCode_Group_Does_Not_Exist:
            msg = "Group does not exist";
            break;

        case MediatorErrorCode_User_Does_Not_Exist:
            msg = "User does not exist";
            break;

        case MediatorErrorCode_Null_Argument:
            msg = "Null argument";
            break;

        case MediatorErrorCode_No_Memory:
            msg = "Out of memory";
            break;

        default:
            msg = "Unknown error";
            break;
    }

    return msg;
}

/// <summary>
/// Helper function for reporting an error if an error has occurred.  Always
/// call this after any mediator call; if there is no error, nothing is
/// reported.
/// 
/// This function makes it easier to capture the context in which an error
/// occurred.
/// </summary>
/// <param name="prompt">What was happening when the error occurred.</param>
/// <param name="errorCode">A value from the @ref MediatorErrorCode enumeration
/// indicating what went wrong, if anything.</param>
void _ReportAnyMediatorError(const char* prompt, MediatorErrorCode errorCode)
{
    if (errorCode != MediatorErrorCode_No_Error)
    {
        const char* msg = _GetMediatorErrorMessage(errorCode);
        if (prompt == NULL)
        {
            prompt = "Unknown operation";
        }
        printf("  Error!  %s: %s!\n", prompt, msg);
    }
}


/// <summary>
/// Helper function to add a number of users to the Users list.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool Mediator_SetupUsers()
{
    MediatorErrorCode errorCode;
    // Operation 12: Add a user
    errorCode = Mediator_AddUser("Stephen");
    _ReportAnyMediatorError("Adding user \"Stephen\"", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Gladys");
        _ReportAnyMediatorError("Adding user \"Gladys\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Marvin");
        _ReportAnyMediatorError("Adding user \"Marvin\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUser("Arthur");
        _ReportAnyMediatorError("Adding user \"Arthur\"", errorCode);
    }

    return errorCode == MediatorErrorCode_No_Error;
}

/// <summary>
/// Helper function to add a number of groups to the Groups list and
/// then add users to the groups.  Note that everything here is done
/// with names.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool Mediator_SetupGroups()
{
    MediatorErrorCode errorCode;
    // Operation 10: Add a group
    errorCode = Mediator_AddGroup("admins");
    _ReportAnyMediatorError("Adding group \"admin\"", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddGroup("Users");
        _ReportAnyMediatorError("Adding group \"Users\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddGroup("Power Users");
        _ReportAnyMediatorError("Adding group \"Power Users\"", errorCode);
    }

    // Operation 7: Add user to a group
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Marvin", "admins");
        _ReportAnyMediatorError("Adding \"Marvin\" to \"admin\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Arthur", "admins");
        _ReportAnyMediatorError("Adding \"Arthur\" to \"admin\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Stephen", "Users");
        _ReportAnyMediatorError("Adding \"Stephen\" to \"Users\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Gladys", "Users");
        _ReportAnyMediatorError("Adding \"Gladys\" to \"Users\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Arthur", "Power Users");
        _ReportAnyMediatorError("Adding \"Arthur\" to \"Power Users\"", errorCode);
    }
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_AddUserToGroup("Marvin", "Power Users");
        _ReportAnyMediatorError("Adding \"Marvin\" to \"Power Users\"", errorCode);
    }

    return errorCode == MediatorErrorCode_No_Error;
}

/// <summary>
/// Helper function example of how to show all groups.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_ShowAllGroups()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    MediatorErrorCode errorCode;
    //-----------------------------------------------------------------
    // Operation 1: Determine all groups
    errorCode = Mediator_GetAllGroups(&groupNames);
    _ReportAnyMediatorError("Getting all groups", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        _ListToString(&groupNames, &output);
        printf("  Operation 1: Show all groups\n");
        printf("    All groups: %s\n", output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&groupNames);
        canContinue = true;
    }
    
    return canContinue;
}

/// <summary>
/// Helper function example of how to show all users.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_ShowAllUsers()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList userNames = { 0 };
    MediatorErrorCode errorCode;
    //-----------------------------------------------------------------
    // Operation 2: Determine all users
    errorCode = Mediator_GetAllUsers(&userNames);
    _ReportAnyMediatorError("Getting all users", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        _ListToString(&userNames, &output);
        printf("  Operation 2: Show all users\n");
        printf("    All users : %s\n", output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&userNames);
        canContinue = true;
    }

    return canContinue;
}

/// <summary>
/// Helper function example of how to see if a user is in a group.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_SeeIfUserInGroup()
{
    bool canContinue = true;
    const char* userName = "Arthur";
    const char* groupName = "admins";
    // Operation 3: Does a user belong to a group
    printf("  Operation 3: Determine if a user is a member of a specific group.\n");
    printf("    Is user '%s' in the '%s' group?", userName, groupName);
    printf("  %s\n", Mediator_IsUserInGroup(userName, groupName) ? "Yes" : "No");

    return canContinue;
}

/// <summary>
/// Helper function example of how to show all users in a group.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_ShowUsersInGroup()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList userNames = { 0 };
    const char* groupName = "Users";
    MediatorErrorCode errorCode;
    // Operation 4: Show all users in a group
    printf("  Operation 4: Show all users in a specific group.\n");
    errorCode = Mediator_GetUsersInGroup(groupName, &userNames);
    _ReportAnyMediatorError("Getting all users in a group", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        _ListToString(&userNames, &output);
        printf("    All users in '%s' group: %s\n", groupName, output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&userNames);
        canContinue = true;
    }

    return canContinue;
}

/// <summary>
/// Helper function example of how to show all groups containing a user.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_ShowAllGroupsContainingUser()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    const char* userName = "Marvin";
    MediatorErrorCode errorCode;
    // Operation 5: Show all groups with a user
    printf("  Operation 5: Show all groups containing a specific user.\n");
    errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
    _ReportAnyMediatorError("Getting all groups containing a user", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        _ListToString(&groupNames, &output);
        printf("    All groups with user '%s': %s\n", userName, output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&groupNames);
        canContinue = true;
    }

    return canContinue;
}


/// <summary>
/// Helper function example of how to remove a user from a group.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_RemoveUserFromGroup()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    const char* userName = "Marvin";
    const char* groupName = "Power Users";
    MediatorErrorCode errorCode;
    // Operation 6: Show Remove a user from a group
    printf("  Operation 6: Remove a user from a group.\n");
    errorCode = Mediator_RemoveUserFromGroup(userName, groupName);
    _ReportAnyMediatorError("Removing user from a group", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        printf("    Removed user '%s' from group '%s'\n", userName, groupName);
        errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
        _ReportAnyMediatorError("Getting groups with a user", errorCode);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&groupNames, &output);
            printf("      All groups with user '%s': %s\n", userName, output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&groupNames);
            canContinue = true;
        }
    }

    return canContinue;
}

/// <summary>
/// Helper function example of how to add a user to a group.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_AddUserToGroup()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    const char* userName = "Marvin";
    const char* groupName = "Users";
    MediatorErrorCode errorCode;
    // Operation 7: Add a user to a group
    printf("  Operation 7: Add a user to a group.\n");
    printf("    Adding user '%s' to group '%s'.\n", userName, groupName);
    errorCode = Mediator_AddUserToGroup(userName, groupName);
    _ReportAnyMediatorError("Adding user to a group", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
        _ReportAnyMediatorError("Getting groups with a user", errorCode);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&groupNames, &output);
            printf("      All groups with user '%s': %s\n", userName, output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&groupNames);
            canContinue = true;
        }
    }

    return canContinue;
}

/// <summary>
/// Helper function example of how to remove a user from all groups.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_RemoveUserFromAllGroups()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    const char* userName = "Arthur";
    MediatorErrorCode errorCode;
    // Operation 8: Remove a user from all groups
    printf("  Operation 8: Remove a user from all groups.\n");
    errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
    _ReportAnyMediatorError("Getting groups with a user before removing user", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        _ListToString(&groupNames, &output);
        printf("    Removing user '%s' from all groups.\n", userName);
        printf("      Start: all groups with user '%s': %s\n", userName, output.string);
        DynamicString_Clear(&output);
        StringList_Clear(&groupNames);
        printf("      Removing...\n");
        errorCode = Mediator_RemoveUserFromAllGroups(userName);
        _ReportAnyMediatorError("Removing user from all groups", errorCode);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            errorCode = Mediator_GetGroupsWithUser(userName, &groupNames);
            _ReportAnyMediatorError("Getting groups with a user after removing user", errorCode);
            if (errorCode == MediatorErrorCode_No_Error)
            {
                _ListToString(&groupNames, &output);
                printf("      End: all groups with user '%s': %s\n", userName, output.string);
                DynamicString_Clear(&output);
                StringList_Clear(&groupNames);
                canContinue = true;
            }
        }
    }

    return canContinue;
}

/// <summary>
/// Helper function example of how to remove a user.
/// </summary>
/// <returns>Returns true if okay to continue running example; otherwise,
/// returns false, an error occurred.  The error has already been
/// reported.</returns>
bool _Mediator_Example_RemoveUser()
{
    bool canContinue = false;
    DynamicString output = { 0 };
    StringList groupNames = { 0 };
    StringList userNames = { 0 };
    const char* userName = "Marvin";
    MediatorErrorCode errorCode;
    // Operation 9: Remove a user (which also removes user from all groups)
    printf("  Operation 9: Remove a user (also removes the user from all groups).\n");
    printf("    Removing user '%s'.\n", userName);
    errorCode = Mediator_RemoveUser(userName);
    _ReportAnyMediatorError("Removing a user", errorCode);
    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetAllUsers(&userNames);
        _ReportAnyMediatorError("Getting all users after removing a user", errorCode);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            _ListToString(&userNames, &output);
            printf("      All users : %s\n", output.string);
            DynamicString_Clear(&output);
            StringList_Clear(&userNames);
        }
    }

    if (errorCode == MediatorErrorCode_No_Error)
    {
        errorCode = Mediator_GetAllGroups(&groupNames);
        _ReportAnyMediatorError("Getting all groups after removing a user", errorCode);
        if (errorCode == MediatorErrorCode_No_Error)
        {
            canContinue = true;
            for (size_t index = 0; index < groupNames.strings_count; index++)
            {
                const char* name = groupNames.strings[index];
                errorCode = Mediator_GetUsersInGroup(name, &userNames);
                _ReportAnyMediatorError("Getting users in a group after removing a user", errorCode);
                if (errorCode == MediatorErrorCode_No_Error)
                {
                    _ListToString(&userNames, &output);
                    printf("      Users in group '%s': %s\n", name, output.string);
                    DynamicString_Clear(&output);
                    StringList_Clear(&userNames);
                }
                else
                {
                    canContinue = false;
                    break;
                }
            }
        }
    }

    return canContinue;
}

//=============================================================================
//=============================================================================

/// <summary>
/// Example of using the @ref mediator_pattern.
/// 
/// A mediator is instantiated then populated with users and groups.
/// Users are added to some of the groups.
/// 
/// A series of operations are then performed through the Mediator.
/// The output shows the results of each operation.  Note that all
/// operations are done using user and group names, with no knowledge
/// of the actual lists of users and groups.  The mediator hides all
/// the details.
/// 
/// The odd design of this example is to more effectively accommodate error
/// handling from the mediator.  This is what you get if you don't have
/// exceptions, like in C++.
/// </summary>
// ! [Using Mediator in C]
void Mediator_Exercise()
{
    printf("\nMediator Exercise\n");

    bool canContinue = Mediator_SetupUsers();
    if (canContinue)
    {
        canContinue = Mediator_SetupGroups();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_ShowAllGroups();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_ShowAllUsers();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_SeeIfUserInGroup();
    }
    
    if (canContinue)
    {
        canContinue = _Mediator_Example_ShowUsersInGroup();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_ShowAllGroupsContainingUser();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_RemoveUserFromGroup();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_AddUserToGroup();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_RemoveUserFromAllGroups();
    }

    if (canContinue)
    {
        canContinue = _Mediator_Example_RemoveUser();
    }
    //-----------------------------------------------------------------

    // Clean-up
    Mediator_ClearAll();

    printf("  Done.\n");
}
// ! [Using Mediator in C]
