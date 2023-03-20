## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.mediator.mediator_group_classes.Group "Group"
#  and
#  @ref DesignPatternExamples_python.mediator.mediator_group_classes.GroupList "GroupList"
#  classes as used in the @ref mediator_pattern.

## Represents a single group.  A group has a name and zero or more users.
#  Users are tracked by name
class Group:

    ## @name Properties
    #  @{

    ## Property gettef for the name of the group: `value = o.Name`
    @property
    def Name(self) -> str:
        return self._groupName


    ## Property getter for the names of users in this group: `value = o.Users`
    @property
    def Users(self) -> list[str]:
        return self._users.copy()

    ## @}

    ## Constructor.
    #
    #  @param name
    #         Name of the group to use.
    def __init__(self, name = "") -> None:
        self._groupName = name
        self._users = []  # type list[str]

    ## @var _groupName
    #       Name of this group.
    #  @var _users
    #       The list of users in this group.

    ## Determine if the specified user is in this group.  This is a case-
    #  sensitive search.
    #
    #  @param name
    #         Name of the user to look for.
    #  @returns
    #     Return true if the user is in this group; otherwise false.
    def ContainsUser(self, name : str) -> bool:
        return name in self._users


    ## Add the specified user to this group.  If the user is already in
    #  the group, the operation is ignored.
    #
    #  @param name
    #         Name of the user to add.  Cannot be null or empty.
    #
    #  @throws ValueError
    #          Must specify a user name to add it to the group.
    def AddUser(self, name : str) -> None:
        if not name:
            raise ValueError("Must specify a user name to add it to the group.")

        if not self.ContainsUser(name):
            self._users.append(name)


    ## Remove a user from this group.  If the user is not in the group
    #  then the operation is ignored.
    #
    #  @param name
    #         The name of the user to remove.
    def RemoveUser(self, name : str) -> None:
        if self.ContainsUser(name):
            self._users.remove(name)

    ## Determine if the name or the specified group matches this Group's name.
    #
    #  @param o
    #         A
    #         @ref DesignPatternExamples_python.mediator.mediator_group_classes.Group "Group"
    #         instance or string with which to compare names.
    #
    #  @returns
    #     Return True if the names are equal (case-sensitive).
    #
    #  @throws TypeError
    #          Expecting a Group type or string to compare to.
    def __eq__(self, o) -> bool:
        if isinstance(o, Group):
            return self._groupName == o._groupName
        elif isinstance(o, str):
            return self._groupName == o
        else:
            raise TypeError("Expecting a Group type or string to compare to.")


#########################################################################
#########################################################################


## Represents a list of Groups.
#  
#  This is a simple implementation using a simple list.  It is NOT thread-safe.
class GroupList:

    ## @name Properties
    #  @{

    ## Property getter for the names of all groups contained in this list: `value = o.GroupNames`.
    #  The list is always sorted.
    #
    # @returns
    #   A list of string containing the names of all groups.
    @property
    def GroupNames(self) -> list[str]:
        groupNames = []

        for group in self._groups:
            groupNames.append(group.Name)

        # Case-insensitive sort
        groupNames.sort(key=str.lower)
        return groupNames

    ## @}

    ## Constructor
    def __init__(self) -> None:
        self._groups = [] # type list[Group]

    ## @var _groups
    #       The list of
    #       @ref DesignPatternExamples_python.mediator.mediator_group_classes.Group "Group"
    #       instances representing all known groups.


    ## Get an iterator pointing to the group with the specified name.
    #  Returns std::end(_groups) if the group was not found with that name.
    #
    # @param name
    #        Name of the group to look for
    # @returns
    #    Returns index into the list where the group was found; otherwise,
    #    returns -1, the name was not found in the group list.
    def _SearchForGroup(self, name : str) -> int:
        foundIndex = -1
        try:
            foundIndex = self._groups.index(Group(name))
        except ValueError:
            # name was not found in the list
            pass
        return foundIndex

    ## Retrieve the Group instance for the specified group name.  The found
    #  group may be altered so it must point to the one in the list.
    #
    #  @param name
    #         Group name to search for.
    #  @returns
    #      Returns pointer to a Group object if name found.  Returns None if
    #      not found.
    def FindGroup(self, name : str) -> Group:
        foundIndex = self._SearchForGroup(name)
        if foundIndex != -1:
            return self._groups[foundIndex]
        return None


    ## Add a group to the list using the given group name.  Operation
    #  ignored if the group is already in the list.
    #
    #  @param name
    #         Name of the group to add.  Cannot be null or empty.
    #
    #  @throws ValueError
    #          Must specify a group name to add it to the group list.
    def AddGroup(self, name : str) -> None:
        if not name:
            raise ValueError("Must specify a group name to add it to the group list.")

        if not self.FindGroup(name):
            self._groups.append(Group(name))


    ## Remove the specified group from the list.  Operation ignored if
    #  the group is not in the list.
    #
    #  @param name
    #         Name of the group to remove.
    def RemoveGroup(self, name : str) -> None:
        foundIndex = self._SearchForGroup(name)
        if foundIndex != -1:
            self._groups.remove(Group(name))
