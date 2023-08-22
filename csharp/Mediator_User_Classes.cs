/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.User "User" and the
/// @ref DesignPatternExamples_csharp.UserList "UserList" classes
/// used in the @ref mediator_pattern "Mediator pattern".

// The Mediator pattern acts as a go-between for multiple entities that want
// no knowledge of any of the other entities except at the most abstract
// level.
//
// The classes defined in this module are for handling users.  These classes
// have no knowledge of groups or the mediator class itself.
//
// This is a dead simple implementation of the concept of a user.  There is
// only a name being tracked here.

using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a user with a name.
    /// </summary>
    public class User
    {
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">The name of the user to assign.</param>
        public User(string name)
        {
            Name = name;
        }


        /// <summary>
        /// The name of the user (read-only).
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// Override to compare a User or string to this User.
        /// </summary>
        /// <param name="obj">A string or an instance of the User class.</param>
        /// <returns>True if the names are equal (case-sensitive).</returns>
        public override bool Equals(object? obj)
        {
            if (obj != null)
            {
                if (obj is User)
                {
                    return ((User)obj).Name == Name;
                }
                if (obj is string)
                {
                    return (string)obj == Name;
                }
            }
            return false;
        }


        /// <summary>
        /// Generate a hash code for this instance.
        /// 
        /// Because we overrode Equals(), we need to override GetHashCode().
        /// </summary>
        /// <returns>Hash code of the name, since that is what uniquely
        /// identifies a User instance.</returns>
        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a list of users.
    /// 
    /// This is a simple implementation using a simple list.  It is NOT thread-safe.
    /// </summary>
    public class UserList
    {
        /// <summary>
        /// The list of users.
        /// </summary>
        List<User> _users = new List<User>();

        /// <summary>
        /// The user names contained in this list (read-only).
        /// The list is always sorted.
        /// </summary>
        public string[] UserNames
        {
            get
            {
                List<string> userNames = new List<string>();
                foreach (User user in _users)
                {
                    userNames.Add(user.Name);
                }
                userNames.Sort();
                return userNames.ToArray();
            }
        }


        /// <summary>
        /// Retrieve the User instance for the specified user name.
        /// </summary>
        /// <param name="name">User name to search for.</param>
        /// <returns>Returns a User object if name found.  Returns null if not found.</returns>
        public User? FindUser(string name)
        {
            return _users.Find(x => x.Equals(new User(name)));
        }


        /// <summary>
        /// Add the specified user name as a user.  Operation ignored if user
        /// is already in the list.
        /// </summary>
        /// <param name="name">Name of user to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter is null or empty.</exception>
        public void AddUser(string name)
        {
            if (String.IsNullOrEmpty(name))
            {
                throw new ArgumentNullException("name", "Must specify a user name to add it to the user list.");
            }

            User newUser = new User(name);
            if (!_users.Contains(newUser))
            {
                _users.Add(newUser);
            }
        }


        /// <summary>
        /// Remove the specified user name as a user.  Operation ignored if
        /// user is not in the list.
        /// </summary>
        /// <param name="name">Name of user to remove.</param>
        public void RemoveUser(string name)
        {
            User existingUser = new User(name);
            if (_users.Contains(existingUser))
            {
                _users.Remove(existingUser);
            }
        }
    }
}
