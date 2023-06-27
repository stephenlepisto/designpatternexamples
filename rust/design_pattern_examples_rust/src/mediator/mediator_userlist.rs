//! Contains the User and UserList structs that manage a list of users.

/// Represents a user with a name.
pub struct User {
    /// The name of the user.
    name: String,
}

impl User {
    /// Constructor.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of a user to use to instantiate the User struct.
    pub fn new(name: &str) -> User {
        User { name: name.to_string() }
    }
}

//#############################################################################
//#############################################################################


/// Represents a list of users.
/// 
/// This is a simple implementation using a simple list.  It is NOT thread-safe.
pub struct UserList {
    /// The list of users.
    users: Vec<User>,
}


impl UserList {
    /// Constructor
    pub fn new() -> UserList {
        UserList {
            users: vec![]
        }
    }

    /// The user names contained in this list (read-only).
    /// The list is always sorted.
    pub fn user_names(&self) -> Vec<String> {
        let mut user_names: Vec<String> = vec![];
        for user in self.users.iter() {
            user_names.push(user.name.clone());
        }
        user_names.sort_by_key(|x| x.to_lowercase());
        user_names

    }

    /// Determine if the specified user exists in the user list.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the user to search for.
    ///
    /// # Returns
    /// Returns true if the user exists; otherwise, returns false.
    pub fn contains_user(&self, name: &str) -> bool {
        match self.users.iter().position(|x| x.name == name) {
            Some(_) => true,
            None => false,
        }

    }

    /// Add the specified user name as a user.  Operation ignored if user
    /// is already in the list.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the user to add.
    pub fn add_user(&mut self, name: &str) {
        match self.users.iter().position(|x| x.name == name) {
            Some(_) => (),
            None => self.users.push(User::new(name)),
        }
    }

    /// Remove the specified user name as a user.  Operation ignored if
    /// user is not in the list.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the user to remove.
    pub fn remove_user(&mut self, name: &str) {
        if let Some(index) = self.users.iter().position(|x| x.name == name) {
            self.users.remove(index);
        }
    }
}
