//! Contains the Group and GroupList structs that manage list of groups, where
//! each group contains a list of users belonging to that group.

//-----------------------------------------------------------------------------

use std::{rc::Rc, cell::RefCell};

//-----------------------------------------------------------------------------


/// Represents a single group.  A group has a name and zero or more users.
/// Users are tracked by name.
pub struct Group {
    /// Name of this group.
    group_name: String,
    /// The list of users in this group.
    users: Vec<String>,
}

impl Group {
    /// Constructor.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of the group to create.
    ///
    /// # Returns
    /// Returns new instance of the Group struct.
    pub fn new(group_name: &str) -> Group {
        Group {
            group_name : group_name.to_string(),
            users: vec![],
        }
    }

    /// Retrieve the names of users in this group.
    pub fn user_names(&self) -> Vec<String> {
        self.users.clone()
    }


    /// Get the index of the specified user in this group, if any.  This is a
    /// case-sensitive search.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of the user to search for
    ///
    /// # Returns
    /// Returns Some(index) if user is found; otherwise, returns None.
    fn search_for_user(&self, user_name: &str) -> Option<usize> {
        self.users.iter().position(|x| x == user_name)
    }

    /// Determine if the specified user is in this group.  This is a case-
    /// sensitive search.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of the user to search for
    ///
    /// # Returns
    /// Returns true if this group contains the specified user; otherwise,
    /// returns false.
    pub fn contains_user(&self, user_name: &str) -> bool {
        match self.search_for_user(user_name) {
            Some(_) => true,
            None => false,
        }
    }

    /// Add the specified user to this group.  If the user is already in
    /// the group, the operation is ignored.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of the user to add.
    pub fn add_user(&mut self, user_name: &str) {
        if !self.contains_user(user_name) {
            self.users.push(user_name.to_string());
        }
    }

    /// Remove a user from this group.  If the user is not in the group
    /// then the operation is ignored.
    ///
    /// # Parameters
    /// - user_name
    ///
    ///   Name of the user to remove.
    pub fn remove_user(&mut self, user_name: &str) {
        if let Some(index) = self.search_for_user(user_name) {
            self.users.remove(index);
        }
    }
}


//########################################################################
//########################################################################


/// Represents a list of Groups.
/// 
/// This is a simple implementation using a simple list.  It is NOT thread-safe.
pub struct GroupList {
    /// The list of groups.
    groups: Vec<Rc<RefCell<Group>>>,
}

impl GroupList {
    /// Constructor for an empty GroupList.
    pub fn new() -> GroupList {
        GroupList { groups: vec![] }
    }

    /// The names of all groups contained in this list.  The list is always
    /// sorted.
    pub fn group_names(&self) -> Vec<String> {
        let mut group_names: Vec<String> = vec![];
        for group in self.groups.iter() {
            group_names.push(group.borrow().group_name.clone());
        }
        group_names.sort_by_key(|x| x.to_lowercase());
        group_names
    }

    /// Retrieve the Group instance for the specified group name.  The found
    /// group may be altered so it must point to the one in the list.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of the group to find.
    ///
    /// # Returns
    /// Returns Some\<Rc\<RefCell\<Group\>\>\> if group is found; otherwise,
    /// returns None.
    pub fn find_group(&self, group_name: &str) -> Option<Rc<RefCell<Group>>> {
        match self.groups.iter().position(|x| x.borrow().group_name == group_name) {
            Some(index) => Some(self.groups[index].clone()),
            None => None,
        }
    }

    /// Add a group to the list using the given group name.  Operation
    /// ignored if the group is already in the list.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of the group to add.
    pub fn add_group(&mut self, group_name: &str) {
        match self.groups.iter().position(|x| x.borrow().group_name == group_name) {
            Some(_) => (),
            None => self.groups.push(Rc::new(RefCell::new(Group::new(group_name)))),
        }
    }

    /// Remove the specified group from the list.  Operation ignored if
    /// the group is not in the list.
    ///
    /// # Parameters
    /// - group_name
    ///
    ///   Name of the group to remove.
    pub fn _remove_group(&mut self, group_name: &str) {
        if let Some(index) = self.groups.iter().position(|x| x.borrow().group_name == group_name) {
            self.groups.remove(index);
        }
    }
}

