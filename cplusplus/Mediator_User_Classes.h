/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::User "User" and the
/// @ref DesignPatternExamples_cpp::UserList "UserList" classes
/// used in the @ref mediator_pattern.


#pragma once
#ifndef __MEDIATOR_USER_CLASSES_H__
#define __MEDIATOR_USER_CLASSES_H__

#include <algorithm>
#include <string>
#include <vector>

#include "helpers/argumentnull_error.h"
#include "helpers/stringlist.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a user with a name.
    /// </summary>
    class User
    {
    private:
        std::string _name;

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        User()
        {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">The name of the user to assign.</param>
        User(std::string name)
            : _name(name)
        {
        }


        /// <summary>
        /// The name of the user (read-only).
        /// </summary>
        std::string Name()
        {
            return _name;
        }

        /// <summary>
        /// Compare a string to this User.
        /// </summary>
        /// <param name="s">A string containing the name of a user.</param>
        /// <returns>Returns true if the names are equal (case-sensitive).</returns>
        bool Equals(const std::string& s) const
        {
            return s == _name;
        }

        /// <summary>
        /// Compare another User name to this User name.
        /// </summary>
        /// <param name="user">A User object to compare names with.</param>
        /// <returns>Return true if the names are equal (case-sensitive).</returns>
        bool Equals(const User& user) const
        {
            return user._name == _name;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a list of users.
    /// 
    /// This is a simple implementation using a simple list.  It is NOT thread-safe.
    /// </summary>
    class UserList
    {
    private:
        /// <summary>
        /// The list of users.
        /// </summary>
        std::vector<User> _users;

    private:
        /// <summary>
        /// Get an iterator pointing to the user with the specified name.
        /// Returns std::end(_users) if the user was not found with that name.
        /// </summary>
        std::vector<User>::iterator _SearchForUser(const std::string& name)
        {
            return std::find_if(std::begin(_users), std::end(_users),
                [name](const User& u)
                {
                    return u.Equals(name);
                }
            );
        }

    public:
        /// <summary>
        /// The user names contained in this list (read-only).
        /// The list is always sorted.
        /// </summary>
        StringList UserNames()
        {
            StringList  userNames;
            for (User& user : _users)
            {
                userNames.push_back(user.Name());
            }
            std::sort(std::begin(userNames), std::end(userNames));
            return userNames;
        }


        /// <summary>
        /// Retrieve the User instance for the specified user name.  The found
        /// user may be altered so it must point to the one in the list.
        /// </summary>
        /// <param name="name">User name to search for.</param>
        /// <returns>Returns a User object if name found.</returns>
        User* FindUser(std::string name)
        {
            User* foundUser = nullptr;

            std::vector<User>::iterator foundIter = _SearchForUser(name);
            if (foundIter != std::end(_users))
            {
                foundUser = &(*foundIter);
            }
            return foundUser;
        }


        /// <summary>
        /// Add the specified user name as a user.  Operation ignored if user
        /// is already in the list.
        /// </summary>
        /// <param name="name">Name of user to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter is null or empty.</exception>
        void AddUser(std::string name)
        {
            if (name.empty())
            {
                throw new Helpers::argumentnull_error("name",
                    "Must specify a user name to add it to the user list.");
            }

            if (FindUser(name) == nullptr)
            {
                _users.push_back(User(name));
            }
        }


        /// <summary>
        /// Remove the specified user name as a user.  Operation ignored if
        /// user is not in the list.
        /// </summary>
        /// <param name="name">Name of user to remove.</param>
        void RemoveUser(std::string name)
        {
            std::vector<User>::iterator foundIter = _SearchForUser(name);
            if (foundIter != std::end(_users))
            {
                _users.erase(foundIter);
            }
        }
    };

} // end namespace

#endif // __MEDIATOR_USER_CLASSES_H__

