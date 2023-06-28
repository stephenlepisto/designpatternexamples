//! The Mediator design pattern example module
//! 
//! A mediator is instantiated then populated with users and groups.
//! Users are added to some of the groups.  The users handler and the groups
//! handler are completely separate from each other; the mediator only makes it
//! look like they are working on together.
//! 
//! A series of operations are then performed through the mediator.  The output
//! shows the results of each operation.  Note that all operations are done
//! using user and group names, with no knowledge of the actual lists of users
//! and groups.  The mediator hides all the details.
//!
//! Accessed through the mediator_exercise() function.

//-----------------------------------------------------------------------------

pub mod mediator_usergroupmediator;
pub mod mediator_userlist;
pub mod mediator_grouplist;

//-----------------------------------------------------------------------------

use mediator_usergroupmediator::UserGroupMediator;

//-----------------------------------------------------------------------------

/// Helper method to convert a list of strings to a comma-delimited
/// list in a single string.
///
/// # Parameters
/// - items
///
///   The list of strings to convert.
///
/// # Returns
/// Returns a string containing a comma-delimited format of strings.
fn list_to_string(items: &Vec<String>) -> String {
    let mut output = String::new();
    for index in 0..items.len() {
        if index != 0 {
            output.push_str(", ");
        }
        output.push_str(&items[index]);
    }
    return output;
}

/// Helper method to add a number of users to the Users list.
///
/// # Parameters
/// - mediator
///
///   The mediator object that owns the list of users.
fn mediator_setup_users(mediator: &mut UserGroupMediator) {
    // Operation 12: Add a user
    mediator.add_user("Stephen");
    mediator.add_user("Gladys");
    mediator.add_user("Marvin");
    mediator.add_user("Arthur");
}


/// Helper method to add a number of groups to the Groups list and
/// then add users to the groups.  Note that everything here is done
/// with names.
///
/// # Parameters
/// - mediator
///
///   The mediator object that owns the list of groups.
fn mediator_setup_groups(mediator: &mut UserGroupMediator) {
    // Operation 10: Add a group
    mediator.add_group("admins");
    mediator.add_group("Users");
    mediator.add_group("Power Users");

    // Operation 7: Add user to a group
    mediator.add_user_to_group("Marvin", "admins");
    mediator.add_user_to_group("Arthur", "admins");
    mediator.add_user_to_group("Stephen", "Users");
    mediator.add_user_to_group("Gladys", "Users");
    mediator.add_user_to_group("Arthur", "Power Users");
    mediator.add_user_to_group("Marvin", "Power Users");
}


/// Example of using the "Mediator" design pattern.
/// 
/// A mediator is instantiated then populated with users and groups.
/// Users are added to some of the groups.  The users handler and the groups
/// handler are completely separate from each other; the mediator only makes it
/// look like they are working on together.
/// 
/// A series of operations are then performed through the mediator.  The output
/// shows the results of each operation.  Note that all operations are done
/// using user and group names, with no knowledge of the actual lists of users
/// and groups.  The mediator hides all the details.
// ! [Using Mediator in Rust]
pub fn mediator_exercise() -> Result<(), String> {
    println!("");
    println!("Mediator Exercise");

    let mut mediator = UserGroupMediator::new();
    mediator_setup_users(&mut mediator);
    mediator_setup_groups(&mut mediator);

    //-----------------------------------------------------------------
    // Operation 1: Determine all groups
    println!("  Operation 1: Show all groups");
    println!("    All groups: {}", list_to_string(&mediator.get_all_groups()));

    //-----------------------------------------------------------------
    // Operation 2: Determine all users
    println!("  Operation 2: Show all users");
    println!("    All users : {}", list_to_string(&mediator.get_all_users()));

    //-----------------------------------------------------------------
    // Operation 3: Does a user belong to a group
    println!("  Operation 3: Determine if a user is a member of a specific group.");
    let mut user_name = "Arthur";
    let mut group_name = "admins";
    let is_in_group = match mediator.is_user_in_group(user_name, group_name) {
        false => "No",
        true => "Yes",
    };
    println!("    Is user '{0}' in the '{1}' group?  {2}", user_name, group_name, is_in_group);

    //-----------------------------------------------------------------
    // Operation 4: Show all users in a group
    println!("  Operation 4: Show all users in a specific group.");
    group_name = "Users";
    let mut user_names = mediator.get_users_in_group(group_name);
    println!("    All users in '{0}' group: {1}", group_name, list_to_string(&user_names));

    //-----------------------------------------------------------------
    // Operation 5: Show all groups with a user
    println!("  Operation 5: Show all groups containing a specific user.");
    user_name = "Marvin";
    let mut group_names = mediator.get_groups_with_user(user_name);
    println!("    All groups with user '{0}': {1}", user_name, list_to_string(&group_names));

    //-----------------------------------------------------------------
    // Operation 6: Show Remove a user from a group
    println!("  Operation 6: Remove a user from a group.");
    user_name = "Marvin";
    group_name = "Power Users";
    mediator.remove_user_from_group(user_name, group_name);
    println!("    Removed user '{0}' from group '{1}'", user_name, group_name);
    group_names = mediator.get_groups_with_user(user_name);
    println!("      All groups with user '{0}': {1}", user_name, list_to_string(&group_names));

    //-----------------------------------------------------------------
    // Operation 7: Add a user to a group
    println!("  Operation 7: Add a user to a group.");
    group_name = "Users";
    println!("    Adding user '{0}' to group '{1}'.", user_name, group_name);
    mediator.add_user_to_group(user_name, group_name);
    group_names = mediator.get_groups_with_user(user_name);
    println!("      All groups with user '{0}': {1}", user_name,list_to_string(&group_names));

    //-----------------------------------------------------------------
    // Operation 8: Remove a user from all groups
    println!("  Operation 8: Remove a user from all groups.");
    user_name = "Arthur";
    group_names = mediator.get_groups_with_user(user_name);
    println!("    Removing user '{0}' from all groups.", user_name);
    println!("      Start: all groups with user '{0}': {1}", user_name, list_to_string(&group_names));
    println!("      Removing...");
    mediator.remove_user_from_all_groups(user_name);
    group_names = mediator.get_groups_with_user(user_name);
    println!("      End: all groups with user '{0}': {1}", user_name, list_to_string(&group_names));

    //-----------------------------------------------------------------
    // Operation 9: Remove a user (which also removes user from all groups)
    println!("  Operation 9: Remove a user (also removes the user from all groups).");
    user_name = "Marvin";
    println!("    Removing user '{0}'.", user_name);
    mediator.remove_user(user_name);
    println!("      All users : {0}", list_to_string(&mediator.get_all_users()));
    group_names = mediator.get_all_groups();
    for group_name in group_names.iter() {
        user_names = mediator.get_users_in_group(&group_name);
        println!("      Users in group '{0}': {1}", group_name, list_to_string(&user_names));
    }
    //-----------------------------------------------------------------

    println!("  Done.");

    Ok(())
}
// ! [Using Mediator in Rust]
