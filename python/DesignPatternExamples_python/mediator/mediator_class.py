## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.mediator.mediator_class.UserGroupsContainer "UserGroupsContainer"
# and
# @ref DesignPatternExamples_python.mediator.mediator_class.UserGroupMediator "UserGroupMediator"
# function as used in the @ref mediator_pattern.


from .mediator_user_classes import UserList
from .mediator_group_classes import GroupList


## A simple container for the user and group lists.  This represents
#  some entity external to the mediator that handles such things.
#  
#  For this example, an instance of this class is contained in the
#  mediator rather than deal with a singleton external entity.
#
class UserGroupsContainer:

    ## Constructor
    def __init__(self) -> None:
        self.Users = UserList()
        self.Groups = GroupList()

    ## @var Users
    #       List of all users
    #  @var Groups
    #       List of all groups


#########################################################################
#########################################################################


## Represents the mediator between caller, users, and groups.  All users
#  and groups are identified by string name.  The names are case-sensitive.
class UserGroupMediator:

    ## Constructor
    def __init__(self) -> None:
        self._userGroupsContainer = UserGroupsContainer()

    ## @var _userGroupsContainer
    #       Collection of all users and all groups.
    #       Normally this would be held somewhere else but for this example,
    #       the mediator will be the owner.

    
    ## Add a user to the list of known users.  If the name is already in
    #  the list of users, the request to add is ignored.
    #
    #  @param name
    #         Name of the user to add.  Must not be null or empty.
    def AddUser(self, name : str) -> None:
            self._userGroupsContainer.Users.AddUser(name)


    ## Removes the specified user from the list of known users, if the
    #  user exists.  Also removes the user from all groups.
    #
    #  @param name
    #         Name of user to remove.
    #
    #  @throws ValueError
    #          User does not exist
    def RemoveUser(self, name : str) -> None:
        self.RemoveUserFromAllGroups(name)
        self._userGroupsContainer.Users.RemoveUser(name)


    ## Add a group to the list of known groups.  If the group is already
    #  in the list, the request to add is ignored.
    #
    #  @param name
    #         Name of the user to add.  Must not be null or empty.
    def AddGroup(self, name : str) -> None:
        self._userGroupsContainer.Groups.AddGroup(name);


    ## Remove the specified group from the list of known groups if the
    #  group exists.
    #
    #  @param name
    #         Name of group to remove.
    def RemoveGroup(self, name : str) -> None:
        self._userGroupsContainer.Groups.RemoveGroup(name);


    ## Add the specified user to the specified group.  If the user is already
    #  in the group, do nothing.  The user must exist.
    #
    #  @param userName
    #         Name of user to add.  Must be an existing user.
    #  @param groupName
    #         Name of group to add user to.  Must be an existing group.
    #
    #  @throws ValueError
    #          User or group does not exist
    def AddUserToGroup(self, userName : str, groupName : str) -> None:
        # As mediator, we must verify the user exists because the group
        # has no way to do this (groups have no knowledge of how users
        # are stored, by design).
        if not self._userGroupsContainer.Users.FindUser(userName):
            message = "User '{0}' does not exist.  Cannot add to group '{1}'!".format(userName, groupName)
            raise ValueError(message)

        foundGroup = self._userGroupsContainer.Groups.FindGroup(groupName)
        if not foundGroup:
            message = "Cannot add user '{0}' to group '{1}' as that group does not exist!".format(userName, groupName)
            raise ValueError(message)

        foundGroup.AddUser(userName)


    ## Remove the specified user from the specified group.
    #
    #  @param userName
    #         Name of user to remove.  Must be an existing user.
    #  @param groupName
    #         Name of group to remove user from.  Must be an existing group.
    #
    #  @throws ValueError
    #          User or group does not exist
    def RemoveUserFromGroup(self, userName : str, groupName : str) -> None:
        # As mediator, we must verify the user exists because the group
        # has no way to do this (groups have no knowledge of how users
        # are stored, by design).
        if not self._userGroupsContainer.Users.FindUser(userName):
            message = "User '{0}' does not exist.  Cannot remove from group '{1}'!".format(userName, groupName)
            raise ValueError(message)

        foundGroup = self._userGroupsContainer.Groups.FindGroup(groupName)
        if not foundGroup:
            message = "Cannot remove user '{0}' from group '{1}' as that group does not exist!".format(userName, groupName)
            raise ValueError(message)

        foundGroup.RemoveUser(userName);


    ## Remove the specified user from all existing groups.
    #
    #  @param userName
    #         Name of user to remove.  Must be an existing user.
    #
    #  @throws ValueError
    #          User does not exist
    def RemoveUserFromAllGroups(self, userName : str) -> None:
        # As mediator, we must verify the user exists because the group
        # has no way to do this (groups have no knowledge of how users
        # are stored, by design).
        if not self._userGroupsContainer.Users.FindUser(userName):
            message = "User '{0}' does not exist.  Cannot remove from all groups'!".format(userName)
            raise ValueError(message)

        for groupName in self._userGroupsContainer.Groups.GroupNames():
            group = self._userGroupsContainer.Groups.FindGroup(groupName)
            if group:
                if group.ContainsUser(userName):
                    group.RemoveUser(userName)


    ## Determine if the specified user is in the specified group.
    #
    #  @param userName
    #         Name of user to find.  Must be an existing user.
    #  @param groupName
    #         Name of group to look in.  Must be an existing group.
    #  @returns
    #     Returns True if the user is in the group; otherwise, returns False.
    #
    #  @throws ValueError
    #          User or group does not exist
    def IsUserInGroup(self, userName : str, groupName : str) -> bool:
        userInGroup = False

        if not self._userGroupsContainer.Users.FindUser(userName):
            message = "User '{0}' does not exist.  Cannot determine if user is in group '{1}'!".format(userName, groupName)
            raise ValueError(message)

        foundGroup = self._userGroupsContainer.Groups.FindGroup(groupName)
        if not foundGroup:
            message = "Cannot determine if user '{0}' is in group '{1}' as that group does not exist!".format(userName, groupName)
            raise ValueError(message)

        userInGroup = foundGroup.ContainsUser(userName)

        return userInGroup


    ## Retrieve a list of all groups that contain the specified user.
    #
    #  @param userName
    #         Name of the user to look for.  Must be an existing user.
    #  @returns
    #     An array of group names containing the user.  Array is empty if the
    #  user is not found in any group.
    #
    #  @throws ValueError
    #          User does not exist
    def GetGroupsWithUser(self, userName : str) -> list[str]:
        if not self._userGroupsContainer.Users.FindUser(userName):
            message = "User '{0}' does not exist.  Cannot get groups container user!".format(userName)
            raise ValueError(message)

        groupNames = []
        for groupName in self._userGroupsContainer.Groups.GroupNames():
            group = self._userGroupsContainer.Groups.FindGroup(groupName)
            if group:
                if group.ContainsUser(userName):
                    groupNames.append(groupName)

        return groupNames


    ## Retrieve a list of users in the specified group.
    #
    #  @param groupName
    #         Name of the group to examine.  Must be an existing group.
    #  @returns
    #     Returns an array of user names.  The array can be empty if no users
    #  are in the group.
    #
    #  @throws ValueError
    #          Group does not exist
    def GetUsersInGroup(self, groupName : str) -> list[str]:
        foundGroup = self._userGroupsContainer.Groups.FindGroup(groupName)
        if not foundGroup:
            message = "Cannot determine get users in group '{0}' as that group does not exist!".format(groupName)
            raise ValueError(message)

        return foundGroup.Users()


    ## Retrieve a list of all known groups.
    #
    #  @returns
    #     An array of group names.
    def GetAllGroups(self) -> list[str]:
        return self._userGroupsContainer.Groups.GroupNames()


    ## Retrieve a list of all known users.
    #
    #  @returns
    #     An array of user names.
    def GetAllUsers(self) -> list[str]:
        return self._userGroupsContainer.Users.UserNames()
