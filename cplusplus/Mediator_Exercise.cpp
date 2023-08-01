
/// @file
/// @brief
/// Implementation of the Mediator_Exercise() function as used in the 
/// @ref mediator_pattern.

#include <iostream>
#include <sstream>

#include "helpers/formatstring.h"

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
            << Helpers::formatstring("    All groups: %s", _ListToString(mediator.GetAllGroups()).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 2: Determine all users
        std::cout << "  Operation 2: Show all users" << std::endl;
        std::cout
            << Helpers::formatstring("    All users : {0}", _ListToString(mediator.GetAllUsers()).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 3: Does a user belong to a group
        std::cout << "  Operation 3: Determine if a user is a member of a specific group." << std::endl;
        std::string userName = "Arthur";
        std::string groupName = "admins";
        std::cout << Helpers::formatstring("    Is user '%s' in the '%s' group?",
            userName.c_str(), groupName.c_str());
        std::cout
            << Helpers::formatstring("  %s", mediator.IsUserInGroup(userName, groupName) ? "Yes" : "No")
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 4: Show all users in a group
        std::cout << "  Operation 4: Show all users in a specific group." << std::endl;
        groupName = "Users";
        StringList userNames = mediator.GetUsersInGroup(groupName);
        std::cout
            << Helpers::formatstring("    All users in '%s' group: %s",
                groupName.c_str(), _ListToString(userNames).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 5: Show all groups with a user
        std::cout << "  Operation 5: Show all groups containing a specific user." << std::endl;
        userName = "Marvin";
        StringList groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << Helpers::formatstring("    All groups with user '%s': %s",
                userName.c_str(), _ListToString(groupNames).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 6: Show Remove a user from a group
        std::cout << "  Operation 6: Remove a user from a group." << std::endl;
        userName = "Marvin";
        groupName = "Power Users";
        mediator.RemoveUserFromGroup(userName, groupName);
        std::cout << Helpers::formatstring("    Removed user '%s' from group '%s'",
            userName.c_str(), groupName.c_str()) << std::endl;
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << Helpers::formatstring("      All groups with user '%s': %s", userName.c_str(),
                _ListToString(groupNames).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 7: Add a user to a group
        std::cout << "  Operation 7: Add a user to a group." << std::endl;
        groupName = "Users";
        std::cout << Helpers::formatstring("    Adding user '%s' to group '%s'.",
                       userName.c_str(), groupName.c_str())
                  << std::endl;
        mediator.AddUserToGroup(userName, groupName);
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << Helpers::formatstring("      All groups with user '%s': %s",
                userName.c_str(), _ListToString(groupNames).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 8: Remove a user from all groups
        std::cout << "  Operation 8: Remove a user from all groups." << std::endl;
        userName = "Arthur";
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout << Helpers::formatstring("    Removing user '%s' from all groups.",
                      userName.c_str())
                  << std::endl;
        std::cout
            << Helpers::formatstring("      Start: all groups with user '%s': %s",
                userName.c_str(), _ListToString(groupNames).c_str())
            << std::endl;
        std::cout << "      Removing..." << std::endl;
        mediator.RemoveUserFromAllGroups(userName);
        groupNames = mediator.GetGroupsWithUser(userName);
        std::cout
            << Helpers::formatstring("      End: all groups with user '%s': %s",
                userName.c_str(), _ListToString(groupNames).c_str())
            << std::endl;

        //-----------------------------------------------------------------
        // Operation 9: Remove a user (which also removes user from all groups)
        std::cout << "  Operation 9: Remove a user (also removes the user from all groups)." << std::endl;
        userName = "Marvin";
        std::cout << Helpers::formatstring("    Removing user '%s'.", userName.c_str()) << std::endl;
        mediator.RemoveUser(userName);
        std::cout
            << Helpers::formatstring("      All users : %s", _ListToString(mediator.GetAllUsers()).c_str())
            << std::endl;
        groupNames = mediator.GetAllGroups();
        for (std::string name : groupNames)
        {
            userNames = mediator.GetUsersInGroup(name);
            std::cout
                << Helpers::formatstring("      Users in group '%s': %s", name.c_str(), _ListToString(userNames).c_str())
                << std::endl;
        }
        //-----------------------------------------------------------------

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Mediator in C++]

} // end namespace
