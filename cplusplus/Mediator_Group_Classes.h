/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Group "Group" and the
/// @ref DesignPatternExamples_cpp::GroupList "GroupList" classes
/// used in the @ref mediator_pattern "Mediator pattern".

#pragma once
#ifndef __MEDIATOR_GROUP_CLASSES_H__
#define __MEDIATOR_GROUP_CLASSES_H__

#include <algorithm>
#include <string>
#include <vector>

#include "helpers/argumentnull_error.h"
#include "helpers/stricmp.h"
#include "helpers/stringlist.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a single group.  A group has a name and zero or more users.
    /// Users are tracked by name.
    /// </summary>
    class Group
    {
    private:
        /// <summary>
        /// Name of this group.
        /// </summary>
        std::string _groupName;

        /// <summary>
        /// The list of users in this group.
        /// </summary>
        StringList _users;

        /// <summary>
        /// Get an iterator pointing to the user with the specified name.
        /// Returns std::end(_users) if the user was not found with that name.
        /// </summary>
        StringList::iterator _SearchForUser(const std::string& name)
        {
            return std::find(std::begin(_users), std::end(_users), name);
        }

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        Group()
        {}

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of the group to use.</param>
        Group(std::string name)
            : _groupName(name)
        {
        }

        /// <summary>
        /// The name of the group (read-only).
        /// </summary>
        std::string Name()
        {
            return _groupName;
        }

        /// <summary>
        /// The names of users in this group (read-only).
        /// </summary>
        StringList Users() const
        {
            return _users;
        }

        /// <summary>
        /// Determine if the specified user is in this group.  This is a case-
        /// sensitive search.
        /// </summary>
        /// <param name="name">Name of the user to look for.</param>
        /// <returns>Return true if the user is in this group; otherwise false.</returns>
        bool ContainsUser(std::string name)
        {
            StringList::iterator foundIter = std::find(std::begin(_users), std::end(_users), name);
            return foundIter != std::end(_users);
        }

        /// <summary>
        /// Add the specified user to this group.  If the user is already in
        /// the group, the operation is ignored.
        /// </summary>
        /// <param name="name">Name of the user to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter must specify a user name.</exception>
        void AddUser(std::string name)
        {
            if (name.empty())
            {
                throw new Helpers::argumentnull_error("name",
                    "Must specify a user name to add it to the group.");
            }

            if (!ContainsUser(name))
            {
                _users.push_back(name);
            }
        }


        /// <summary>
        /// Remove a user from this group.  If the user is not in the group
        /// then the operation is ignored.
        /// </summary>
        /// <param name="name">The name of the user to remove.</param>
        void RemoveUser(std::string name)
        {
            StringList::iterator foundIter = std::find(std::begin(_users), std::end(_users), name);
            if (foundIter != std::end(_users))
            {
                _users.erase(foundIter);
            }
        }

        /// <summary>
        /// Determine if the name of the specified group matches this Group's
        /// name.
        /// </summary>
        /// <param name="group">A Group with which to compare names.</param>
        /// <returns>Return true if the names are equal (case-sensitive).</returns>
        bool Equals(const Group& group) const
        {
            return (group._groupName == _groupName);
        }

        /// <summary>
        /// Determine if the given name matches this Group's name.
        /// </summary>
        /// <param name="name">A string containing the name of the Group.</param>
        /// <returns>Return true if the names are equal (case-sensitive).</returns>
        bool Equals(const std::string& name) const
        {
            return (name == _groupName);
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a list of Groups.
    /// 
    /// This is a simple implementation using a simple list.  It is NOT thread-safe.
    /// </summary>
    class GroupList
    {
    private:
        /// <summary>
        /// The list of groups.
        /// </summary>
        std::vector<Group> _groups;

    private:
        /// <summary>
        /// Get an iterator pointing to the group with the specified name.
        /// Returns std::end(_groups) if the group was not found with that name.
        /// </summary>
        std::vector<Group>::iterator _SearchForGroup(const std::string& name)
        {
            return std::find_if(std::begin(_groups), std::end(_groups),
                [name](const Group& g)
                {
                    return g.Equals(name);
                }
            );
        }

    public:
        /// <summary>
        /// The names of all groups contained in this list (read-only).
        /// The list is always sorted.
        /// </summary>
        StringList GroupNames()
        {
            StringList groupNames;

            for (Group group : _groups)
            {
                groupNames.push_back(group.Name());
            }
            std::sort(std::begin(groupNames), std::end(groupNames),
                [](const std::string& first, const std::string& second)
                {
                    return Helpers::stricmp(first, second) < 0;
                }
            );
            return groupNames;
        }


        /// <summary>
        /// Retrieve the Group instance for the specified group name.  The found
        /// group may be altered so it must point to the one in the list.
        /// </summary>
        /// <param name="name">Group name to search for.</param>
        /// <returns">Returns pointer to a Group object if name found.  Returns null if not found.</returns>
        Group* FindGroup(std::string name)
        {
            Group* foundGroup = nullptr;
            std::vector<Group>::iterator foundIter = _SearchForGroup(name);
            if (foundIter != std::end(_groups))
            { 
                foundGroup = &(*foundIter);
            }
            return foundGroup;
        }


        /// <summary>
        /// Add a group to the list using the given group name.  Operation
        /// ignored if the group is already in the list.
        /// </summary>
        /// <param name="name">Name of the group to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The group name cannot be null or empty.</exception>
        void AddGroup(std::string name)
        {
            if (name.empty())
            {
                throw new Helpers::argumentnull_error ("name",
                    "Must specify a group name to add it to the group list.");
            }
            if (FindGroup(name) == nullptr)
            {
                _groups.push_back(Group(name));
            }
        }


        /// <summary>
        /// Remove the specified group from the list.  Operation ignored if
        /// the group is not in the list.
        /// </summary>
        /// <param name="name">Name of the group to remove.</param>
        void RemoveGroup(std::string name)
        {
            std::vector<Group>::iterator foundIter = _SearchForGroup(name);
            if (foundIter != std::end(_groups))
            {
                _groups.erase(foundIter);
            }
        }
    };

} // end namespace

#endif // __MEDIATOR_GROUP_CLASSES_H__

