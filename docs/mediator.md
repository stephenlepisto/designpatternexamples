# Mediator Pattern {#mediator_pattern}

@image html mediator_diagram.png "Diagram of the Mediator pattern"

The Mediator pattern acts as a go-between for multiple entities that want
no knowledge of any of the other entities except at the most abstract
level.

In effect, the Mediator class is a kind of router, with sufficient
knowledge about all entities involved to facilitate communication among the
entities without the entities themselves knowing anything about the other
entities.  The Mediator class also hides the details of the individual entities
from the rest of the program (similar to the @ref facade_pattern).

The Mediator pattern requires introducing another class between the two (or
more) classes that want to talk to each other.  The intent is to model the
communication between the two (or more) classes and make that model an
object itself.  In practice, though, the mediator is not something that can
reused, although it does insulate changes in implementation of the various
entities from everyone else.

What this means is the mediator is a class that becomes the point of
contact in a system, exposing the other entities only in the most abstract
way possible, typically though numerical or string identifiers.

A classic example of the mediator pattern is Users and Groups as objects.
A User can be part of zero or more Groups and Groups can contain zero or
more Users.  There are a number of operations that can be done with this
simple relationship:

1. Determine all groups available
2. Determine all users available
3. Determine if a particular user belongs to a particular group
4. Determine all users that are in a particular group
5. Determine all groups that contain a particular user
6. Remove a particular user from a particular group
7. Add a particular user to a particular group
8. remove a particular user from all groups
9. Remove a user, which entails removing the user from all groups
10. Add a new group
11. remove a group
12. Add a user

A mediator object for the above User/Group situation would have to know where
to find the users and the groups and would provide functions for all of the above
operations.  That way, callers don't know about user and group objects
except by name; all calls go to the mediator object that in turn knows how
to find a particular user and group and how to search the groups, not to
mention managing the lists of users and groups themselves.

[Note: It can be argued that managing the user and group lists from this
mediator is too much functionality for one mediator class.  On the other
hand, it simplifies the calling interface for the application and makes the
implementation of removing a user much easier; otherwise, the mediator that
controls users would need to know about this mediator class and we're back
to two classes knowing more about each other than is strictly necessary.]

The alternative is to have the caller go directly to the users and groups
to perform the requests.

# How to Use

Links to the Mediator classes descriptions:
- @ref DesignPatternExamples_cpp::UserGroupMediator "UserGroupMediator" class (C++)
- @ref DesignPatternExamples_csharp.UserGroupMediator "UserGroupMediator" class (C#)
- @ref DesignPatternExamples_cpp::Group "Group" class (C++)
- @ref DesignPatternExamples_csharp::Group "Group" class (C#)
- @ref DesignPatternExamples_cpp::GroupList "GroupList" class (C++)
- @ref DesignPatternExamples_csharp::GroupList "GroupList" class (C#)
- @ref DesignPatternExamples_cpp::UserList "UserList" class (C++)
- @ref DesignPatternExamples_csharp::UserList "UserList" class (C#)

This example makes a further refinement by having the Users list and Groups
list be objects themselves that can handle searching, adding, and removing
entries.  This simplifies the job of the mediator class.  For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cs}
internal class User
{
    public string Name { get; }
}

internal class Group
{
    public string Name { get; }
    public bool ContainsUser(string name);
    public void AddUser(string name);
    public void RemoveUser(string name);
}

internal class UserList
{
    public User FindUser(string name);
    public void AddUser(string name);
    public void RemoveUser(string name);
}

internal class GroupList
{
    public Group FindGroup(string name);
    public void AddGroup(string name);
    public void RemoveGroup(string name);
}

public class UserGroupMediator
{
    void AddUser(string name);
    void RemoveUser(string name);
    void AddGroup(string name);
    void RemoveGroup(string name);
    void AddUserToGroup(string userName, string groupName);
    void RemoveUserFromGroup(string userName, string groupName);
    void RemoveUserFromAllGroups(string userName);
    bool IsUserInGroup(string userName, string groupName);
    string[] GetGroupsWithUser(string userName);
    string[] GetUsersInGroup(string groupName);
    string[] GetAllGroups();
    string[] GetAllUsers();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Here, the caller only sees the UserGroupMediator class object and all the
functionality exposed on that class.  The caller doesn't know how the users
and groups are handled.  In the same way, the User class has no knowledge
of the Group class and vice versa.

Without the UserGroupMediator class, the caller would need to implement all
those functions itself, with full knowledge of the User, UserList, Group,
and GroupList classes, thereby exposing the implementation details of all
those classes.  With the UserGroupMediator class, the caller only needs to
know the names of users and groups, which is generally supplied by the user
that invoked the caller.

__C++__

@snippet cplusplus/program.cpp Using Mediator in C++

__C#__

@snippet csharp/program.cs Using Mediator in C#


### See Also
- @ref mainpage "Main page"
