/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Mediator_Exercise "Mediator_Exercise"
/// class used in the @ref mediator_pattern.

using System;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref mediator_pattern in C#.
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
    internal class Mediator_Exercise
    {
        /// <summary>
        /// Helper method to convert a list of strings to a comma-delimited
        /// list in a single string.
        /// </summary>
        /// <param name="items">The list of strings to convert.</param>
        /// <returns>A string containing a comma-delimited format of strings.</returns>
        string _ListToString(string[] items)
        {
            StringBuilder output = new StringBuilder();
            for (int index = 0; index < items.Length; ++index)
            {
                if (index != 0)
                {
                    output.Append(", ");
                }
                output.Append(items[index]);
            }
            return output.ToString();
        }

        /// <summary>
        /// Helper method to add a number of users to the Users list.
        /// </summary>
        /// <param name="mediator">The mediator object that owns the list of users.</param>
        void Mediator_SetupUsers(UserGroupMediator mediator)
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
        void Mediator_SetupGroups(UserGroupMediator mediator)
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

        /// <summary>
        /// Executes the example for the @ref mediator_pattern in C#.
        /// </summary>
        // ! [Using Mediator in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Mediator Exercise");
            UserGroupMediator mediator = new UserGroupMediator();

            Mediator_SetupUsers(mediator);
            Mediator_SetupGroups(mediator);

            //-----------------------------------------------------------------
            // Operation 1: Determine all groups
            Console.WriteLine("  Operation 1: Show all groups");
            Console.WriteLine("    All groups: {0}", _ListToString(mediator.GetAllGroups()));

            //-----------------------------------------------------------------
            // Operation 2: Determine all users
            Console.WriteLine("  Operation 2: Show all users");
            Console.WriteLine("    All users : {0}", _ListToString(mediator.GetAllUsers()));

            //-----------------------------------------------------------------
            // Operation 3: Does a user belong to a group
            Console.WriteLine("  Operation 3: Determine if a user is a member of a specific group.");
            string userName = "Arthur";
            string groupName = "admins";
            Console.Write("    Is user '{0}' in the '{1}' group?", userName, groupName);
            Console.WriteLine("  {0}", mediator.IsUserInGroup(userName, groupName) ? "Yes" : "No");

            //-----------------------------------------------------------------
            // Operation 4: Show all users in a group
            Console.WriteLine("  Operation 4: Show all users in a specific group.");
            groupName = "Users";
            string[] userNames = mediator.GetUsersInGroup(groupName);
            Console.WriteLine("    All users in '{0}' group: {1}", groupName, _ListToString(userNames));

            //-----------------------------------------------------------------
            // Operation 5: Show all groups with a user
            Console.WriteLine("  Operation 5: Show all groups containing a specific user.");
            userName = "Marvin";
            string[] groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("    All groups with user '{0}': {1}", userName, _ListToString(groupNames));

            //-----------------------------------------------------------------
            // Operation 6: Show Remove a user from a group
            Console.WriteLine("  Operation 6: Remove a user from a group.");
            userName = "Marvin";
            groupName = "Power Users";
            mediator.RemoveUserFromGroup(userName, groupName);
            Console.WriteLine("    Removed user '{0}' from group '{1}'", userName, groupName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      All groups with user '{0}': {1}", userName, _ListToString(groupNames));

            //-----------------------------------------------------------------
            // Operation 7: Add a user to a group
            Console.WriteLine("  Operation 7: Add a user to a group.");
            groupName = "Users";
            Console.WriteLine("    Adding user '{0}' to group '{1}'.", userName, groupName);
            mediator.AddUserToGroup(userName, groupName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      All groups with user '{0}': {1}", userName, _ListToString(groupNames));

            //-----------------------------------------------------------------
            // Operation 8: Remove a user from all groups
            Console.WriteLine("  Operation 8: Remove a user from all groups.");
            userName = "Arthur";
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("    Removing user '{0}' from all groups.", userName);
            Console.WriteLine("      Start: all groups with user '{0}': {1}", userName, _ListToString(groupNames));
            Console.WriteLine("      Removing...");
            mediator.RemoveUserFromAllGroups(userName);
            groupNames = mediator.GetGroupsWithUser(userName);
            Console.WriteLine("      End: all groups with user '{0}': {1}", userName, _ListToString(groupNames));

            //-----------------------------------------------------------------
            // Operation 9: Remove a user (which also removes user from all groups)
            Console.WriteLine("  Operation 9: Remove a user (also removes the user from all groups).");
            userName = "Marvin";
            Console.WriteLine("    Removing user '{0}'.", userName);
            mediator.RemoveUser(userName);
            Console.WriteLine("      All users : {0}", _ListToString(mediator.GetAllUsers()));
            groupNames = mediator.GetAllGroups();
            foreach (string name in groupNames)
            {
                userNames = mediator.GetUsersInGroup(name);
                Console.WriteLine("      Users in group '{0}': {1}", name, _ListToString(userNames));
            }
            //-----------------------------------------------------------------

            Console.WriteLine("  Done.");
        }
        // ! [Using Mediator in C#]
    }
}
