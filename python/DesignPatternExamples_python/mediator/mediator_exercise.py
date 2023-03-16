## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.mediator.mediator_exercise.Mediator_Exercise "Mediator_Exercise"()
#  function as used in the @ref mediator_pattern.

from .mediator_class import UserGroupMediator

## Helper method to convert a list of strings to a comma-delimited
#  list in a single string.
#
#  @param items
#         The list of strings to convert.
#  @returns
#     A string containing a comma-delimited format of strings.
def _ListToString(items : list[str]) -> str:
    return ", ".join(items)

## Helper method to add a number of users to the Users list.
#
#  @param mediator
#         The mediator object that owns the list of users.
def Mediator_SetupUsers(mediator : UserGroupMediator) -> None:
    # Operation 12: Add a user
    mediator.AddUser("Stephen");
    mediator.AddUser("Gladys");
    mediator.AddUser("Marvin");
    mediator.AddUser("Arthur");


## Helper method to add a number of groups to the Groups list and
#  then add users to the groups.  Note that everything here is done
#  with names.
# 
#  @param mediator
#         The mediator object that owns the list of groups.
def Mediator_SetupGroups(mediator : UserGroupMediator) -> None:
    # Operation 10: Add a group
    mediator.AddGroup("admins");
    mediator.AddGroup("Users");
    mediator.AddGroup("Power Users");

    # Operation 7: Add user to a group
    mediator.AddUserToGroup("Marvin", "admins");
    mediator.AddUserToGroup("Arthur", "admins");
    mediator.AddUserToGroup("Stephen", "Users");
    mediator.AddUserToGroup("Gladys", "Users");
    mediator.AddUserToGroup("Arthur", "Power Users");
    mediator.AddUserToGroup("Marvin", "Power Users");


##  Example of using the @ref mediator_pattern.
#  
#  A mediator is instantiated then populated with users and groups.
#  Users are added to some of the groups.
#  
#  A series of operations are then performed through the mediator.
#  The output shows the results of each operation.  Note that all
#  operations are done using user and group names, with no knowledge
#  of the actual lists of users and groups.  The mediator hides all
#  the details.

# ! [Using Mediator in Python]
def Mediator_Exercise():
    print()
    print("Mediator Exercise")

    mediator = UserGroupMediator()

    Mediator_SetupUsers(mediator)
    Mediator_SetupGroups(mediator)

    #-----------------------------------------------------------------
    # Operation 1: Determine all groups
    print("  Operation 1: Show all groups")
    print("    All groups: {0}".format(_ListToString(mediator.GetAllGroups())))

    #-----------------------------------------------------------------
    # Operation 2: Determine all users
    print("  Operation 2: Show all users");
    print("    All users : {0}".format(_ListToString(mediator.GetAllUsers())))

    #-----------------------------------------------------------------
    # Operation 3: Does a user belong to a group
    print("  Operation 3: Determine if a user is a member of a specific group.");
    userName = "Arthur";
    groupName = "admins";
    print("    Is user '{0}' in the '{1}' group?".format(userName, groupName), end="")
    print("  {0}".format("Yes" if mediator.IsUserInGroup(userName, groupName) else "No"))

    #-----------------------------------------------------------------
    # Operation 4: Show all users in a group
    print("  Operation 4: Show all users in a specific group.");
    groupName = "Users";
    userNames = mediator.GetUsersInGroup(groupName);
    print("    All users in '{0}' group: {1}".format(groupName, _ListToString(userNames)))

    #-----------------------------------------------------------------
    # Operation 5: Show all groups with a user
    print("  Operation 5: Show all groups containing a specific user.");
    userName = "Marvin";
    groupNames = mediator.GetGroupsWithUser(userName);
    print("    All groups with user '{0}': {1}".format(userName, _ListToString(groupNames)))

    #-----------------------------------------------------------------
    # Operation 6: Show Remove a user from a group
    print("  Operation 6: Remove a user from a group.");
    userName = "Marvin";
    groupName = "Power Users";
    mediator.RemoveUserFromGroup(userName, groupName);
    print("    Removed user '{0}' from group '{1}'".format(userName, groupName))
    groupNames = mediator.GetGroupsWithUser(userName);
    print("      All groups with user '{0}': {1}".format(userName, _ListToString(groupNames)))

    #-----------------------------------------------------------------
    # Operation 7: Add a user to a group
    print("  Operation 7: Add a user to a group.");
    groupName = "Users";
    print("    Adding user '{0}' to group '{1}'.".format(userName, groupName))
    mediator.AddUserToGroup(userName, groupName);
    groupNames = mediator.GetGroupsWithUser(userName);
    print("      All groups with user '{0}': {1}".format(userName, _ListToString(groupNames)))

    #-----------------------------------------------------------------
    # Operation 8: Remove a user from all groups
    print("  Operation 8: Remove a user from all groups.");
    userName = "Arthur";
    groupNames = mediator.GetGroupsWithUser(userName);
    print("    Removing user '{0}' from all groups.".format(userName))
    print("      Start: all groups with user '{0}': {1}".format(userName, _ListToString(groupNames)))
    print("      Removing...");
    mediator.RemoveUserFromAllGroups(userName);
    groupNames = mediator.GetGroupsWithUser(userName);
    print("      End: all groups with user '{0}': {1}".format(userName, _ListToString(groupNames)))

    #-----------------------------------------------------------------
    # Operation 9: Remove a user (which also removes user from all groups)
    print("  Operation 9: Remove a user (also removes the user from all groups).");
    userName = "Marvin";
    print("    Removing user '{0}'.".format(userName))
    mediator.RemoveUser(userName);
    print("      All users : {0}".format(_ListToString(mediator.GetAllUsers())))
    groupNames = mediator.GetAllGroups();
    for name in groupNames:
        userNames = mediator.GetUsersInGroup(name);
        print("      Users in group '{0}': {1}".format(name, _ListToString(userNames)))

    #-----------------------------------------------------------------

    print("  Done.")
# ! [Using Mediator in Python]
