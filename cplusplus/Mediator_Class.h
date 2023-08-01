/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::UserGroupsContainer "UserGroupsContainer"
/// and the @ref DesignPatternExamples_cpp::UserGroupMediator "UserGroupMediator"
/// classes used in the @ref mediator_pattern.

#pragma once
#ifndef __MEDIATOR_CLASS_H__
#define __MEDIATOR_CLASS_H__

#include <exception>

#include "helpers/argumentinvalid_error.h"
#include "helpers/formatstring.h"

#include "Mediator_User_Classes.h"
#include "Mediator_Group_Classes.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// A simple container for the user and group lists.  This represents
    /// some entity external to the mediator that handles such things.
    /// 
    /// For this example, an instance of this class is contained in the
    /// mediator rather than deal with a singleton external entity.
    /// </summary>
    class UserGroupsContainer
    {
    public:
        UserList Users;
        GroupList Groups;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the mediator between caller, users, and groups.  All users
    /// and groups are identified by string name.  The names are case-sensitive.
    /// </summary>
    class UserGroupMediator
    {
    private:
        // Normally this would be held somewhere else but for this example,
        // the mediator will be the owner.
        UserGroupsContainer _userGroupsContainer;

    public:
        /// <summary>
        /// Add a user to the list of known users.  If the name is already in
        /// the list of users, the request to add is ignored.
        /// </summary>
        /// <param name="name">Name of the user to add.  Must not be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter cannot be null or empty.</exception>
        void AddUser(std::string name)
        {
            _userGroupsContainer.Users.AddUser(name);
        }


        /// <summary>
        /// Removes the specified user from the list of known users, if the
        /// user exists.  Also removes the user from all groups.
        /// </summary>
        /// <param name="name">Name of user to remove.</param>
        void RemoveUser(std::string name)
        {
            RemoveUserFromAllGroups(name);
            _userGroupsContainer.Users.RemoveUser(name);
        }


        /// <summary>
        /// Add a group to the list of known groups.  If the group is already
        /// in the list, the request to add is ignored.
        /// </summary>
        /// <exception cref="ArgumentNullException">The 'name' parameter cannot be null or empty.</exception>
        /// <param name="name">Name of the user to add.  Must not be null or empty.</param>
        void AddGroup(std::string name)
        {
            _userGroupsContainer.Groups.AddGroup(name);
        }


        /// <summary>
        /// Remove the specified group from the list of known groups if the
        /// group exists.
        /// </summary>
        /// <param name="name">Name of group to remove.</param>
        void RemoveGroup(std::string name)
        {
            _userGroupsContainer.Groups.RemoveGroup(name);
        }


        /// <summary>
        /// Add the specified user to the specified group.  If the user is already
        /// in the group, do nothing.  The user must exist.
        /// </summary>
        /// <param name="userName">Name of user to add.  Must be an existing user.</param>
        /// <param name="groupName">Name of group to add user to.  Must be an existing group.</param>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        void AddUserToGroup(std::string userName, std::string groupName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            if (_userGroupsContainer.Users.FindUser(userName) == nullptr)
            {
                std::string message = Helpers::formatstring("User '%s' does not exist.  Cannot add to group '%s'!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("userName", message.c_str());
            }

            Group* foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == nullptr)
            {
                std::string message = Helpers::formatstring("Cannot add user '%s' to group '%s' as that group does not exist!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("groupName", message.c_str());
            }

            foundGroup->AddUser(userName);
        }


        /// <summary>
        /// Remove the specified user from the specified group.
        /// </summary>
        /// <param name="userName">Name of user to remove.  Must be an existing user.</param>
        /// <param name="groupName">Name of group to remove user from.  Must be an existing group.</param>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        void RemoveUserFromGroup(std::string userName, std::string groupName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            if (_userGroupsContainer.Users.FindUser(userName) == nullptr)
            {
                std::string message = Helpers::formatstring("User '%s' does not exist.  Cannot remove from group '%s'!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("userName", message.c_str());
            }

            Group* foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == nullptr)
            {
                std::string message = Helpers::formatstring("Cannot remove user '%s' from group '%s' as that group does not exist!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("groupName", message.c_str());
            }

            foundGroup->RemoveUser(userName);
        }


        /// <summary>
        /// Remove the specified user from all existing groups.
        /// </summary>
        /// <param name="userName">Name of user to remove.  Must be an existing user.</param>
        /// <exception cref="ArgumentException">User does not exist.</exception>
        void RemoveUserFromAllGroups(std::string userName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            if (_userGroupsContainer.Users.FindUser(userName) == nullptr)
            {
                std::string message = Helpers::formatstring("User '%s' does not exist.  Cannot remove from all groups'!",
                    userName.c_str());
                throw Helpers::argumentinvalid_error("userName", message.c_str());
            }

            for(std::string groupName : _userGroupsContainer.Groups.GroupNames())
            {
                Group* group = _userGroupsContainer.Groups.FindGroup(groupName);
                if (group != nullptr)
                {
                    if (group->ContainsUser(userName))
                    {
                        group->RemoveUser(userName);
                    }
                }
            }
        }


        /// <summary>
        /// Determine if the specified user is in the specified group.
        /// </summary>
        /// <param name="userName">Name of user to find.  Must be an existing user.</param>
        /// <param name="groupName">Name of group to look in.  Must be an existing group.</param>
        /// <returns>Returns true if the user is in the group; otherwise, returns false.</returns>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        bool IsUserInGroup(std::string userName, std::string groupName)
        {
            bool userInGroup = false;

            if (_userGroupsContainer.Users.FindUser(userName) == nullptr)
            {
                std::string message = Helpers::formatstring("User '%s' does not exist.  Cannot determine if user is in group '%s'!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("userName", message.c_str());
            }

            Group* foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == nullptr)
            {
                std::string message = Helpers::formatstring("Cannot determine if user '%s' is in group '%s' as that group does not exist!",
                    userName.c_str(), groupName.c_str());
                throw Helpers::argumentinvalid_error("groupName", message.c_str());
            }

            userInGroup = foundGroup->ContainsUser(userName);

            return userInGroup;
        }


        /// <summary>
        /// Retrieve a list of all groups that contain the specified user.
        /// </summary>
        /// <param name="userName">Name of the user to look for.  Must be an existing user.</param>
        /// <returns>An array of group names containing the user.  Array is empty if the
        /// user is not found in any group.</returns>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        StringList GetGroupsWithUser(std::string userName)
        {
            if (_userGroupsContainer.Users.FindUser(userName) == nullptr)
            {
                std::string message = Helpers::formatstring("User '%s' does not exist.  Cannot get groups containing user!",
                    userName.c_str());
                throw Helpers::argumentinvalid_error("userName", message.c_str());
            }

            StringList groupNames;
            for(std::string groupName : _userGroupsContainer.Groups.GroupNames())
            {
                Group* group = _userGroupsContainer.Groups.FindGroup(groupName);
                if (group != nullptr)
                {
                    if (group->ContainsUser(userName))
                    {
                        groupNames.push_back(groupName);
                    }
                }
            }
            return groupNames;
        }


        /// <summary>
        /// Retrieve a list of users in the specified group.
        /// </summary>
        /// <param name="groupName">Name of the group to examine.  Must be an existing group.</param>
        /// <returns>Returns an array of user names.  The array can be empty if no users
        /// are in the group.</returns>
        /// <exception cref="ArgumentException">Group does not exist.</exception>
        StringList GetUsersInGroup(std::string groupName)
        {
            Group* foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == nullptr)
            {
                std::string message = Helpers::formatstring("Cannot determine get users in group '%s' as that group does not exist!",
                    groupName.c_str());
                throw Helpers::argumentinvalid_error("groupName", message.c_str());
            }
            return foundGroup->Users();
        }


        /// <summary>
        /// Retrieve a list of all known groups.
        /// </summary>
        /// <returns>An array of group names.</returns>
        StringList GetAllGroups()
        {
            return _userGroupsContainer.Groups.GroupNames();
        }


        /// <summary>
        /// Retrieve a list of all known users.
        /// </summary>
        /// <returns>An array of user names.</returns>
        StringList GetAllUsers()
        {
            return _userGroupsContainer.Users.UserNames();
        }
    };

} // end namespace

#endif // __MEDIATOR_CLASS_H__

