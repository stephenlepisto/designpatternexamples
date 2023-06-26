//! Implementation of the titlecase() function, which converts a string to a
//! lowercase string with an uppercase first character, suitable as the first
//! word in a sentence.

/// Convert the first word (or only word) in the given string to lowercase
/// then make the first letter uppercase.  It does not touch any of the
/// other words after the first.
///
/// # Parameters
/// - s
///
///   A string to work on.
///
/// # Returns
/// Returns a new string containing the modified string.
pub fn titlecase(s: &str) -> String {
    let input = String::from(s).to_lowercase();
    let uppercase = input.to_uppercase();

    let mut output = String::new();
    if uppercase.len() > 0 {
        let (_, first_character) = uppercase.char_indices().next().unwrap();
        output.push(first_character);
    }
    if input.len() > 1 {
        output.push_str(input.get(1..).unwrap());
    }
    output
}
