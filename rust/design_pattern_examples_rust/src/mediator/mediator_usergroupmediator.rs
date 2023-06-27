//! Contains the UserGroupMediator struct, which mediates between the UserList
//! and GroupList structs.

//-----------------------------------------------------------------------------

use super::mediator_grouplist::GroupList;
use super::mediator_userlist::UserList;

//-----------------------------------------------------------------------------

/// A simple container for the user and group lists.  This represents
/// some entity external to the mediator that handles such things.
/// 
/// For this example, an instance of this class is contained in the
/// mediator rather than deal with a singleton external entity.
struct UserGroupContainer {
    /// Provides access to the list of groups.
    groups: GroupList,
    /// Provides access to the list of users.
    users: UserList,
}

impl UserGroupContainer {
    /// Constructor
    ///
    /// This is intended to at least obscure where the list of users and list
    /// of groups come from.
    fn new() -> UserGroupContainer {
        UserGroupContainer {
            groups: GroupList::new(),
            users: UserList::new(),
        }
    }
}

/// Represents the mediator between caller, users, and groups.  All users
/// and groups are identified by string name.  The names are case-sensitive.
pub struct UserGroupMediator {
    /// The container that holds the lists of users and groups.
    ///
    /// Normally this would be held somewhere else but, for this example,
    /// the mediator will be the owner.
    user_group_container: UserGroupContainer,
}

impl UserGroupMediator {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the UserGroupMediator struct.
    pub fn new() -> UserGroupMediator {
        UserGroupMediator {
            user_group_container: UserGroupContainer::new(),
        }
    }

    /// Add a user to the list of known users.  If the name is already in
    /// the list of users, the request to add is ignored.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user to add.
    pub fn add_user(&mut self, user_name: &str) {
        self.user_group_container.users.add_user(user_name);
    }

    /// Removes the specified user from the list of known users, if the
    /// user exists.  Also removes the user from all groups.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user to remove.
    pub fn remove_user(&mut self, user_name: &str) {
        self.remove_user_from_all_groups(user_name);
        self.user_group_container.users.remove_user(user_name);
    }

    /// Add a group to the list of known groups.  If the group is already
    /// in the list, the request to add is ignored.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of group to add.
    pub fn add_group(&mut self, group_name: &str) {
        self.user_group_container.groups.add_group(group_name);
    }

    /// Remove the specified group from the list of known groups if the
    /// group exists.  The request is ignored if the group does not exist.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of group to remove.
    pub fn _remove_group(&mut self, group_name: &str) {
        self.user_group_container.groups._remove_group(group_name);
    }

    /// Add the specified user to the specified group.  If the user is already
    /// in the group, do nothing.  The user must exist.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user to add to the group.
    /// - group_name
    ///
    ///   Name of group to which to add the user.
    pub fn add_user_to_group(&mut self, user_name: &str, group_name: &str) {
        // As mediator, we must verify the user exists because the group
        // has no way to do this (groups have no knowledge of how users
        // are stored, by design).
        if self.user_group_container.users.contains_user(user_name) {
            match self.user_group_container.groups.find_group(group_name) {
                Some(group) => group.borrow_mut().add_user(user_name),
                None => eprintln!("  Error! Cannot add user '{user_name}' to group '{group_name}' as that group does not exist!"),
            }
        } else {
            eprintln!("  Error! User '{user_name}' does not exist.  Cannot add to group '{group_name}'!");
        }
    }

    /// Remove the specified user from the specified group.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user to remove from the group.
    /// - group_name
    ///
    ///   Name of group from which to remove the user.
    pub fn remove_user_from_group(&mut self, user_name: &str, group_name: &str) {
        // As mediator, we must verify the user exists because the group
        // has no way to do this (groups have no knowledge of how users
        // are stored, by design).
        if self.user_group_container.users.contains_user(user_name) {
            match self.user_group_container.groups.find_group(group_name) {
                Some(group) => group.borrow_mut().remove_user(user_name),
                None => eprintln!("  Error! Cannot remove user '{user_name}' from group '{group_name}' as that group does not exist!"),
            }
        } else {
            eprintln!("  Error! User '{user_name}' does not exist.  Cannot remove from group '{group_name}'!");
        }
    }

    /// Remove the specified user from all existing groups.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user to remove from all groups.
    pub fn remove_user_from_all_groups(&mut self, user_name: &str) {
        // As mediator, we must verify the user exists because the group
        // has no way to do this (groups have no knowledge of how users
        // are stored, by design).
        if self.user_group_container.users.contains_user(user_name) {
            let group_names = self.user_group_container.groups.group_names();
            for group_name in group_names {
                if let Some(group) = self.user_group_container.groups.find_group(&group_name) {
                    group.borrow_mut().remove_user(user_name);
                }
            }
        } else {
            eprintln!("  Error! User '{user_name}' does not exist.  Cannot remove from all groups!");
        }
    }

    /// Determine if the specified user is in the specified group.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user for which to get all groups the user is in.
    /// - group_name
    ///
    ///   Name of group to look in for the user.
    ///
    /// # Returns
    /// Returns true if the user is found in the group; otherwise, returns false.
    pub fn is_user_in_group(&self, user_name: &str, group_name: &str) -> bool {
        if self.user_group_container.users.contains_user(user_name) {
            if let Some(group) = self.user_group_container.groups.find_group(&group_name) {
                group.borrow().contains_user(user_name)
            } else {
                eprintln!("  Error! Cannot determine if user '{user_name}' is in group '{group_name}' as that group does not exist!");
                false
            }
        } else {
            eprintln!("  Error! User '{user_name}' does not exist.  Cannot determine if user is in group '{group_name}'!");
            false
        }
    }

    /// Retrieve a list of all groups that contain the specified user.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of user for which to get all groups the user is in.
    ///
    /// # Returns
    /// Returns list of group names that contain the user.  Can return an empty
    /// list if no group contains the user.
    pub fn get_groups_with_user(&self, user_name: &str) -> Vec<String> {
        let mut groups: Vec<String> = vec![];
        if self.user_group_container.users.contains_user(user_name) {
            let group_names = self.user_group_container.groups.group_names();
            for group_name in group_names {
                if let Some(group) = self.user_group_container.groups.find_group(&group_name) {
                    if group.borrow().contains_user(user_name) {
                        groups.push(group_name.clone());
                    }
                }
            }
        } else {
            eprintln!("  Error! User '{user_name}' does not exist.  Cannot get groups containing user!");
        }

        groups
    }

    /// Retrieve a list of users in the specified group.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of group for which to get all users.
    ///
    /// # Returns
    /// Returns list of user names found in the group.  Can return an empty
    /// list if the group has no users.
    pub fn get_users_in_group(&self, group_name: &str) -> Vec<String> {
        if let Some(group) = self.user_group_container.groups.find_group(&group_name) {
            return group.borrow().user_names();
        } else {
            eprintln!("  Error! Cannot determine get users in group '{group_name}' as that group does not exist!");
            vec![]
        }
    }

    /// Retrieve a list of all known groups.
    pub fn get_all_groups(&self) -> Vec<String> {
        self.user_group_container.groups.group_names()
    }

    /// Retrieve a list of all known users.
    pub fn get_all_users(&self) -> Vec<String> {
        self.user_group_container.users.user_names()
    }
}
