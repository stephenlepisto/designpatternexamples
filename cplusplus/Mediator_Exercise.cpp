
/// @file
/// @brief
/// Implementation of the Mediator_Exercise() function as used in the 
/// @ref mediator_pattern "Mediator pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <sstream>

#include "Mediator_Exercise.h"
#include "Mediator_Class.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// Helper method to convert a list of strings to a comma-delimited
    /// list in a single string.
    /// </summary>
    /// <param name="items">The list of strings to convert.</param>
    /// <returns>A string containing a comma-delimited format of strings.</returns>
    std::string _ListToString(const std::vector<std::string>& items)
    {
        std::ostringstream output;
        for (size_t index = 0; index < items.size(); ++index)
        {
            if (index != 0)
            {
                output << ", ";
            }
            output << items[index];
        }
        return output.str();
    }

    /// <summary>
    /// Helper method to add a number of users to the Users list.
    /// </summary>
    /// <param name="mediator">The mediator object that owns the list of users.</param>
    void Mediator_SetupUsers(UserGroupMediator& mediator)
    {
        // Operation 12: Add a user
        mediator.AddUser("Stephen");
        mediator.AddUser("Gladys");
        mediator.AddUser("Marvin");
        mediator.AddUser("Arthur");
    }

    /// <summary>
    /// Helper method to add a number of groups to the Groups list and
    /// then add users to the groups.  Note that everything here is done
    /// with names.
    /// </summary>
    /// <param name="mediator">The mediator object that owns the list of groups.</param>
    void Mediator_SetupGroups(UserGroupMediator& mediator)
    {
        // Operation 10: Add a group
        mediator.AddGroup("admins");
        mediator.AddGroup("Users");
        mediator.AddGroup("Power Users");

        // Operation 7: Add user to a group
        mediator.AddUserToGroup("Marvin", "admins");
        mediator.AddUserToGroup("Arthur", "admins");
        mediator.AddUserToGroup("Stephen", "Users");
        mediator.AddUserToGroup("Gladys", "Users");
        mediator.AddUserToGroup("Arthur", "Power Users");
        mediator.AddUserToGroup("Marvin", "Power Users");
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref mediator_pattern "Mediator" design pattern.
    /// 
    /// A mediator is instantiated then populated with users and groups.
    /// Users are added to some of the groups.
    /// 
    /// A series of operations are then performed through the mediator.
    /// The output shows the results of each operation.  Note that all
    /// operations are done using user and group names, with no knowledge
    /// of the actual lists of users and groups.  The mediator hides all
    /// the details.
    /// </summary>
    // ! [Using Mediator in C++]
    void Mediator_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Mediator Exercise" << std::endl;

        UserGroupMediator mediator;

        Mediator_SetupUsers(mediator);
        Mediator_SetupGroups(mediator);

        //-----------------------------------------------------------------
        // Operation 1: Determine all groups
        std::cout << "  Operation 1: Show all groups" << std::endl;
        std::cout
            << std::format("    All groups: {0}", _ListToString(mediator.GetAllGroups()))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 2: Determine all users
        std::cout << "  Operation 2: Show all users" << std::endl;
        std::cout
            << std::format("    All users : {0}", _ListToString(mediator.GetAllUsers()))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 3: Does a user belong to a group
        std::cout << "  Operation 3: Determine if a user is a member of a specific group." << std::endl;
        std::string userName = "Arthur";
        std::string groupName = "admins";
        std::cout << std::format("    Is user '{0}' in the '{1}' group?", userName, groupName);
        std::cout
            << std::format("  {0}", mediator.IsUserInGroup(userName, groupName) ? "Yes" : "No")
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 4: Show all users in a group
        std::cout << "  Operation 4: Show all users in a specific group." << std::endl;
        groupName = "Users";
        StringList userNames = mediator.GetUsersInGroup(groupName);
        std::cout
            << std::format("    All users in '{0}' group: {1}", groupName, _ListToString(userNames))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 5: Show all groups with a user
        std::cout << "  Operation 5: Show all groups containing a specific user." << std::endl;
        userName = "Marvin";
        StringList groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << std::format("    All groups with user '{0}': {1}", userName, _ListToString(groupNames))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 6: Show Remove a user from a group
        std::cout << "  Operation 6: Remove a user from a group." << std::endl;
        userName = "Marvin";
        groupName = "Power Users";
        mediator.RemoveUserFromGroup(userName, groupName);
        std::cout << std::format("    Removed user '{0}' from group '{1}'", userName, groupName) << std::endl;
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << std::format("      All groups with user '{0}': {1}", userName, _ListToString(groupNames))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 7: Add a user to a group
        std::cout << "  Operation 7: Add a user to a group." << std::endl;
        groupName = "Users";
        std::cout << std::format("    Adding user '{0}' to group '{1}'.", userName, groupName) << std::endl;
        mediator.AddUserToGroup(userName, groupName);
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << std::format("      All groups with user '{0}': {1}", userName, _ListToString(groupNames))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 8: Remove a user from all groups
        std::cout << "  Operation 8: Remove a user from all groups." << std::endl;
        userName = "Arthur";
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout << std::format("    Removing user '{0}' from all groups.", userName) << std::endl;
        std::cout
            << std::format("      Start: all groups with user '{0}': {1}", userName, _ListToString(groupNames))
            << std::endl;
        std::cout << "      Removing..." << std::endl;
        mediator.RemoveUserFromAllGroups(userName);
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << std::format("      End: all groups with user '{0}': {1}", userName, _ListToString(groupNames))
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 9: Remove a user (which also removes user from all groups)
        std::cout << "  Operation 9: Remove a user (also removes the user from all groups)." << std::endl;
        userName = "Marvin";
        std::cout << std::format("    Removing user '{0}'.", userName) << std::endl;
        mediator.RemoveUser(userName);
        std::cout
            << std::format("      All users : {0}", _ListToString(mediator.GetAllUsers()))
            << std::endl;
        groupNames = mediator.GetAllGroups();
        for (std::string name : groupNames)
        {
            userNames = mediator.GetUsersInGroup(name);
            std::cout
                << std::format("      Users in group '{0}': {1}", name, _ListToString(userNames))
                << std::endl;
        }
        //-----------------------------------------------------------------

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Mediator in C++]

} // end namespace
