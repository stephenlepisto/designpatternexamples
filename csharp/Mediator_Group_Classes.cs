/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Group "Group" and the
/// @ref DesignPatternExamples_csharp.GroupList "GroupList" classes
/// used in the @ref mediator_pattern "Mediator pattern".

// The Mediator pattern acts as a go-between for multiple entities that want
// no knowledge of any of the other entities except at the most abstract
// level.
//
// The classes defined in this module are for handling groups.  These classes
// have no knowledge of the User class or the mediator class itself.
//
// This is a dead simple implementation of the concept of a group.  There is
// only a name of the group and the list of users (identified by name) being
// tracked here.
using System;
using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a single group.  A group has a name and zero or more users.
    /// Users are tracked by name.
    /// </summary>
    public class Group
    {
        /// <summary>
        /// The list of users in this group.
        /// </summary>
        private List<string> _users = new List<string>();

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of the group to use.</param>
        internal Group(string name)
        {
            Name = name;
        }

        /// <summary>
        /// The name of the group (read-only).
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// The names of users in this group (read-only).
        /// </summary>
        public string[] Users
        {
            get
            {
                return _users.ToArray();
            }
        }

        /// <summary>
        /// Determine if the specified user is in this group.  This is a case-
        /// sensitive search.
        /// </summary>
        /// <param name="name">Name of the user to look for.</param>
        /// <returns>Return true if the user is in this group; otherwise false.</returns>
        public bool ContainsUser(string name)
        {
            return _users.Contains(name);
        }

        /// <summary>
        /// Add the specified user to this group.  If the user is already in
        /// the group, the operation is ignored.
        /// </summary>
        /// <param name="name">Name of the user to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The 'name' parameter must specify a user name.</exception>
        public void AddUser(string name)
        {
            if (String.IsNullOrEmpty(name))
            {
                throw new ArgumentNullException("name", "Must specify a user name to add it to the group.");
            }

            if (!ContainsUser(name))
            {
                _users.Add(name);
            }
        }


        /// <summary>
        /// Remove a user from this group.  If the user is not in the group
        /// then the operation is ignored.
        /// </summary>
        /// <param name="name">The name of the user to remove.</param>
        public void RemoveUser(string name)
        {
            if (_users.Contains(name))
            {
                _users.Remove(name);
            }
        }

        /// <summary>
        /// Override to compare a Group or string to this Group.
        /// </summary>
        /// <param name="obj">A string or an instance of the Group class.</param>
        /// <returns>True if the names are equal (case-sensitive).</returns>
        public override bool Equals(object obj)
        {
            if (obj is Group)
            {
                return ((Group)obj).Name == Name;
            }
            if (obj is string)
            {
                return (string)obj == Name;
            }
            return false;
        }

        /// <summary>
        /// Generate a hash code for this instance.
        /// 
        /// Because we overrode Equals(), we need to override GetHashCode().
        /// </summary>
        /// <returns>Hash code of the name, since that is what uniquely
        /// identifies a Group instance.</returns>
        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a list of Groups.
    /// 
    /// This is a simple implementation using a simple list.  It is NOT thread-safe.
    /// </summary>
    public class GroupList
    {
        /// <summary>
        /// The list of groups.
        /// </summary>
        private List<Group> _groups = new List<Group>();


        /// <summary>
        /// The names of all groups contained in this list (read-only).
        /// The list is always sorted.
        /// </summary>
        public string[] GroupNames
        {
            get
            {
                List<string> groupNames = new List<string>();
                foreach (Group group in _groups)
                {
                    groupNames.Add(group.Name);
                }
                groupNames.Sort();
                return groupNames.ToArray();
            }
        }


        /// <summary>
        /// Retrieve the Group instance for the specified group name.
        /// </summary>
        /// <param name="name">Group name to search for.</param>
        /// <returns>Returns a Group object if name found.  Returns null if not found.</returns>
        public Group FindGroup(string name)
        {
            return _groups.Find(x => x.Equals(name));
        }


        /// <summary>
        /// Add a group to the list using the given group name.  Operation
        /// ignored if the group is already in the list.
        /// </summary>
        /// <param name="name">Name of the group to add.  Cannot be null or empty.</param>
        /// <exception cref="ArgumentNullException">The group name cannot be null or empty.</exception>
        public void AddGroup(string name)
        {
            if (String.IsNullOrEmpty(name))
            {
                throw new ArgumentNullException("name", "Must specify a group name to add it to the group list.");
            }

            Group newGroup = new Group(name);
            if (!_groups.Contains(newGroup))
            {
                _groups.Add(newGroup);
            }
        }


        /// <summary>
        /// Remove the specified group from the list.  Operation ignored if
        /// the group is not in the list.
        /// </summary>
        /// <param name="name">Name of the group to remove.</param>
        public void RemoveGroup(string name)
        {
            Group existingGroup = new Group(name);
            if (_groups.Contains(existingGroup))
            {
                _groups.Remove(existingGroup);
            }
        }
    }
}
