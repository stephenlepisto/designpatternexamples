//! Contains random(), a function that hides how a random number is generated
//! from a range of u32 values.

use std::ops::Range;
use rand::Rng;

/// Generate a random unsigned integer value from the given range.
pub fn random(range: Range<u32>) -> u32 {
    rand::thread_rng().gen_range(range)
}
