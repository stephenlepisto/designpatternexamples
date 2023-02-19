// The Mediator pattern acts as a go-between for multiple entities that want
// no knowledge of any of the other entities except at the most abstract
// level.
//
// In effect, the Mediator class is a kind of router, with sufficient
// knowledge about all entities involved to facilitate communication among the
// entities without the entities themselves knowing anything about the other
// entities.
//
// The Mediator pattern requires introducing another class between the two (or
// more) classes that want to talk to each other.  The intent is to model the
// communication between the two (or more) classes and make that model an
// object unto itself.  In practice, though, the mediator is not something
// that can be reused, although it does insulate changes in implementation of
// the various entities from everyone else.
//
// What this means is the mediator is a class that becomes the point of
// contact in a system, exposing the other entities only in the most abstract
// way possible, typically though numerical or string identifiers.
//
// A classic example of the mediator pattern is Users and Groups as objects.
// A User can be part of zero or more Groups and Groups can contain zero or
// more Users.  There are a number of operations that can be done with this
// simple relationship:
//  1. Determine if a particular user belongs to a particular group
//  2. Determine all groups that contain a particular user
//  3. Determine all users that are in a particular group
//  4. Add a particular user to a particular group
//  5. Remove a particular user from a particular group
//  6. remove a particular user from all groups
//  7. Add a new group
//  8. remove a group
//  9. Add a user
// 10. Remove a user, which entails removing the user from all groups
// 11. Determine all groups available
// 12. Determine all users available
//
// A mediator object for this situation would have to know where to find the
// users and the groups and would provide functions for all of the above
// operations.  That way, callers don't know about user and group objects
// except by name; all calls go to the mediator object that in turn knows how
// to find a particular user and group and how to search the groups, not to
// mention managing the lists of users and groups themselves.
//
// [Note: It can be argued that managing the user and group lists from this
// mediator is too much functionality for one mediator class.  On the other
// hand, it simplifies the calling interface for the application and makes the
// implementation of removing a user much easier; otherwise, the mediator that
// controls users would need to know about this mediator class and we're back
// to two classes knowing more about each other than is strictly necessary.]
//
// The alternative is to have the caller go directly to the users and groups
// to perform the requests.
//
// A further refinement is to have the Users list and Groups list be objects
// themselves that can handle searching, adding, and removing entries.  This
// simplifies the job of the mediator class.  For example:
//
// class UserList
// {
//     public User FindUser(string name);
//     public void AddUser(string name);
//     public void RemoveUser(string name);
// }
//
// class GroupList
// {
//     public Group FindGroup(string name);
//     public void AddGroup(string name);
//     public void RemoveGroup(string name);
// }
//
// class User
// {
//     public string Name { get; }
// }
//
// class Group
// {
//     public string Name { get; }
//     public bool ContainsUser(string name);
//     public void AddUser(string name);
//     public void RemoveUser(string name);
// }
//
// class UserGroupMediator
// {
//     void AddUser(string name);
//     void RemoveUser(string name);
//     void AddGroup(string name);
//     void RemoveGroup(string name);
//     void AddUserToGroup(string userName, string groupName);
//     void RemoveUserFromGroup(string userName, string groupName);
//     void RemoveUserFromAllGroups(string userName);
//     bool IsUserInGroup(string userName, string groupName);
//     string[] GetGroupsWithUser(string userName);
//     string[] GetUsersInGroup(string groupName);
//     string[] GetAllGroups();
//     string[] GetAllUsers();
// }
//
// Here, the caller only sees the UserGroupMediator class object and all the
// functionality exposed on that class.  The caller doesn't know how the users
// and groups are handled.  In the same way, the User class has no knowledge
// of the Group class and vice versa.
//
// Without the UserGroupMediator class, the caller would need to implement all
// those functions itself, with full knowledge of the User, UserList, Group,
// and GroupList classes, thereby exposing the implementation details of all
// those classes.  With the UserGroupMediator class, the caller only needs to
// know the names of users and groups, which is generally supplied by the user
// that invoked the caller.

using System;
using System.Collections.Generic;


namespace DesignPatternExamples
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
        public UserList Users = new UserList();
        public GroupList Groups = new GroupList();
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the mediator between caller, users, and groups.  All users
    /// and groups are identified by string name.  The names are case-sensitive.
    /// </summary>
    public class UserGroupMediator
    {
        // Normally this would be held somewhere else but for this example,
        // the mediator will be the owner.
        UserGroupsContainer _userGroupsContainer = new UserGroupsContainer();


        /// <summary>
        /// Add a user to the list of known users.  If the name is already in
        /// the list of users, the request to add is ignored.
        /// </summary>
        /// <param name="name">Name of the user to add.  Must not be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter cannot be null or empty.</exception>
        public void AddUser(string name)
        {
            _userGroupsContainer.Users.AddUser(name);
        }


        /// <summary>
        /// Removes the specified user from the list of known users, if the
        /// user exists.  Also removes the user from all groups.
        /// </summary>
        /// <param name="name">Name of user to remove.</param>
        public void RemoveUser(string name)
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
        public void AddGroup(string name)
        {
            _userGroupsContainer.Groups.AddGroup(name);
        }


        /// <summary>
        /// Remove the specified group from the list of known groups if the
        /// group exists.
        /// </summary>
        /// <param name="name">Name of group to remove.</param>
        public void RemoveGroup(string name)
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
        public void AddUserToGroup(string userName, string groupName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            User foundUser = _userGroupsContainer.Users.FindUser(userName);
            if (foundUser == null)
            {
                string message = String.Format("User '{0}' does not exist.  Cannot add to group '{1}'!", userName, groupName);
                throw new ArgumentException(message);
            }

            Group foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == null)
            {
                string message = String.Format("Cannot add user '{0}' to group '{1}' as that group does not exist!", userName, groupName);
                throw new ArgumentException(message);
            }

            foundGroup.AddUser(userName);
        }


        /// <summary>
        /// Remove the specified user from the specified group.
        /// </summary>
        /// <param name="userName">Name of user to remove.  Must be an existing user.</param>
        /// <param name="groupName">Name of group to remove user from.  Must be an existing group.</param>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        public void RemoveUserFromGroup(string userName, string groupName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            User foundUser = _userGroupsContainer.Users.FindUser(userName);
            if (foundUser == null)
            {
                string message = String.Format("User '{0}' does not exist.  Cannot remove from group '{1}'!", userName, groupName);
                throw new ArgumentException(message);
            }

            Group foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == null)
            {
                string message = String.Format("Cannot remove user '{0}' from group '{1}' as that group does not exist!", userName, groupName);
                throw new ArgumentException(message);
            }

            foundGroup.RemoveUser(userName);
        }


        /// <summary>
        /// Remove the specified user from all existing groups.
        /// </summary>
        /// <param name="userName">Name of user to remove.  Must be an existing user.</param>
        /// <exception cref="ArgumentException">User does not exist.</exception>
        public void RemoveUserFromAllGroups(string userName)
        {
            // As mediator, we must verify the user exists because the group
            // has no way to do this (groups have no knowledge of how users
            // are stored, by design).
            User foundUser = _userGroupsContainer.Users.FindUser(userName);
            if (foundUser == null)
            {
                string message = String.Format("User '{0}' does not exist.  Cannot remove from all groups'!", userName);
                throw new ArgumentException(message);
            }

            foreach (string groupName in _userGroupsContainer.Groups.GroupNames)
            {
                Group group = _userGroupsContainer.Groups.FindGroup(groupName);
                if (group != null)
                {
                    if (group.ContainsUser(userName))
                    {
                        group.RemoveUser(userName);
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
        public bool IsUserInGroup(string userName, string groupName)
        {
            bool userInGroup = false;

            User foundUser = _userGroupsContainer.Users.FindUser(userName);
            if (foundUser == null)
            {
                string message = String.Format("User '{0}' does not exist.  Cannot determine if user is in group '{1}'!", userName, groupName);
                throw new ArgumentException(message);
            }

            Group foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == null)
            {
                string message = String.Format("Cannot determine if user '{0}' is in group '{1}' as that group does not exist!", userName, groupName);
                throw new ArgumentException(message);
            }

            userInGroup = foundGroup.ContainsUser(userName);

            return userInGroup;
        }


        /// <summary>
        /// Retrieve a list of all groups that contain the specified user.
        /// </summary>
        /// <param name="userName">Name of the user to look for.  Must be an existing user.</param>
        /// <returns>An array of group names containing the user.  Array is empty if the
        /// user is not found in any group.</returns>
        /// <exception cref="ArgumentException">User or group does not exist.</exception>
        public string[] GetGroupsWithUser(string userName)
        {
            User foundUser = _userGroupsContainer.Users.FindUser(userName);
            if (foundUser == null)
            {
                string message = String.Format("User '{0}' does not exist.  Cannot get groups containiner user!", userName);
                throw new ArgumentException(message);
            }

            List<string> groupNames = new List<string>();
            foreach(string groupName in _userGroupsContainer.Groups.GroupNames)
            {
                Group group = _userGroupsContainer.Groups.FindGroup(groupName);
                if (group != null)
                {
                    if (group.ContainsUser(userName))
                    {
                        groupNames.Add(groupName);
                    }
                }
            }
            return groupNames.ToArray();
        }


        /// <summary>
        /// Retrieve a list of users in the specified group.
        /// </summary>
        /// <param name="groupName">Name of the group to examine.  Must be an existing group.</param>
        /// <returns>Returns an array of user names.  The array can be empty if no users
        /// are in the group.</returns>
        /// <exception cref="ArgumentException">Group does not exist.</exception>
        public string[] GetUsersInGroup(string groupName)
        {
            Group foundGroup = _userGroupsContainer.Groups.FindGroup(groupName);
            if (foundGroup == null)
            {
                string message = String.Format("Cannot determine get users in group '{0}' as that group does not exist!", groupName);
                throw new ArgumentException(message);
            }
            return (string[])foundGroup.Users.Clone();
        }


        /// <summary>
        /// Retrieve a list of all known groups.
        /// </summary>
        /// <returns>An array of group names.</returns>
        public string[] GetAllGroups()
        {
            return (string[])_userGroupsContainer.Groups.GroupNames.Clone();
        }


        /// <summary>
        /// Retrieve a list of all known users.
        /// </summary>
        /// <returns>An array of user names.</returns>
        public string[] GetAllUsers()
        {
            return (string[])_userGroupsContainer.Users.UserNames.Clone();
        }
    }
}
