## @file
#  @brief
#  Implementation of the
#  @ref DesignPatternExamples_python.mediator.mediator_user_classes.User "User"
#  and
#  @ref DesignPatternExamples_python.mediator.mediator_user_classes.UserList "UserList"
#  classes as used in the @ref mediator_pattern.

## Represents a user with a name.
class User:

    ## Constructor.
    #
    #  @param name
    #         The name of the user to assign.
    def __init__(self, name = "") -> None:
        self._name = name

    ## @var _name
    #       Name of the user

    
    ##  The name of the user.
    def Name(self) -> str:
        return self._name


    ## Determine if the name or the specified User matches this User's name.
    #
    #  @param o
    #         A
    #         @ref DesignPatternExamples_python.mediator.mediator_user_classes.User "User"
    #         instance or a string containing the name of a user.
    #  @returns
    #     Returns True if the names are equal (case-sensitive)
    #
    #  @throws TypeError
    #          Expecting a User type or string to compare to.
    def __eq__(self, o) -> bool:
        if isinstance(o, User):
            return self._name == o._name
        elif isinstance(o, str):
            return self._name == o
        else:
            raise TypeError("Expecting a User type or string to compare to.")


#########################################################################
#########################################################################


## Represents a list of users.
#  
#  This is a simple implementation using a simple list.  It is NOT thread-safe.
class UserList:

    ## Constructor
    def __init__(self) -> None:
        self._users = [] # type: list[User]

    ## @var _users
    #       List of
    #       @ref DesignPatternExamples_python.mediator.mediator_user_classes.User "User"
    #       instances representing all known users.


    ## Get an iterator pointing to the user with the specified name.
    #
    # @param name
    #        Name of the user to search for
    #
    # @returns
    #    Returns index into the list where the user was found; otherwise,
    #    returns -1, the name was not found in the user list.
    def _SearchForUser(self, name : str) -> int:
        foundIndex = -1
        try:
            foundIndex = self._users.index(User(name))
        except ValueError:
            # name was not found in the list
            pass
        return foundIndex


    ## The user names contained in this list.
    #  The list is always sorted.
    #
    # @returns
    #   A list of string containing the names of all groups.
    def UserNames(self) -> list[str]:
        userNames = []

        for user in self._users:
            userNames.append(user.Name())

        # Case-insensitive sort
        userNames.sort(key=str.lower)
        return userNames


    ## Retrieve the User instance for the specified user name.  The found
    #  user may be altered so it must point to the one in the list.
    #
    #  @param name
    #         User name to search for.
    #  @returns
    #     Returns a User object if name found.
    def  FindUser(self, name : str) -> User:
        foundIndex = self._SearchForUser(name)
        if foundIndex != -1:
            return self._users[foundIndex]
        return None


    ## Add the specified user name as a user.  Operation ignored if user
    #  is already in the list.
    #
    #  @param name
    #         Name of user to add.  Cannot be null or empty.
    #
    #  @throws ValueError
    #          Must specify a user name to add it to the user list.
    def AddUser(self, name : str) -> None:
        if not name:
            raise ValueError("Must specify a user name to add it to the user list.")

        if not self.FindUser(name):
            self._users.append(User(name))


    ## Remove the specified user name as a user.  Operation ignored if
    #  user is not in the list.
    #
    #  @param name
    #         Name of user to remove.
    def RemoveUser(self, name : str) -> None:
        foundIndex = self._SearchForUser(name)
        if foundIndex != -1:
            self._users.remove(User(name))
