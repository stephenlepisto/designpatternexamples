//! design_pattern_examples_rust build script
//!
//! This build script always copies the Adapter_BackEnd library files to the
//! target directory.

use std::env;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;
use serde_json;

fn main() {
    // Note: the DEBUG environment variable is not in the cargo metadata so we
    // go to the environment for the value.
    let debug_config = match env::var("DEBUG").unwrap().as_str() {
        "true" => "debug",
        _ => "release",
    };
    let library_path = Path::join(&env::current_dir().unwrap(), "..").join("..").join("lib").join("x64").join(format!("{debug_config}/"));
    println!("cargo:rustc-link-lib=Adapter_BackEnd");
    println!("cargo:rustc-link-search={}", library_path.display());

    let files_to_copy = vec!["Adapter_BackEnd.dll", "Adapter_BackEnd.pdb"];
    let input_path = library_path;
    let output_path = _get_output_path(&debug_config);

    println!("cargo:warning=output_path = {}", output_path.display());
    // Make sure the output directory exists
    output_path.try_exists().unwrap();

    println!("cargo:warning=Copying Adapter_BackEnd files to {}", output_path.display());
    for file in files_to_copy {
        let src = input_path.join(file);
        let dest = output_path.join(file);
        if src.exists() {
            fs::copy(src, dest).unwrap();
        }
    }
}


/// Retrieve the path to where all output files are being written.  Need to get
/// this from the metadata provided by cargo.
///
/// # Parameters
/// - build_type
///
///   The build configuration type (typically "debug" or "release") that becomes
///   a sub-directory under the target_directory where the files go.  This was
///   determined empirically because this information is not in the cargo
///   metadata.
///
/// # Returns
/// Returns a PathBuf object containing the output path to use.  PathBuf is
/// usually required for file-oriented functions.
fn _get_output_path(build_type: &str) -> PathBuf {
    let metadata = _read_cargo_metadata();

    // This converts the JSON-formatted string into a map of strings to values.
    let json_map : serde_json::Map<String, serde_json::Value> = serde_json::from_str(&metadata).unwrap();

    // get() returns a double quote-delimited value for some reason so be sure
    // to strip the double quotes.  Note that trim_matches() returns a string
    // slice, but I also needed to call replace() and that returns a string so
    // that's all good.
    let target_dir = match json_map.get("target_directory") {
        Some(v) => v.to_string().trim_matches('"').replace("\\\\", "\\"),
        None => String::new(),
    };
    PathBuf::from(target_dir).join(build_type)
}

/// Read all the cargo metadata into a string and return it.  Basically, run
/// the cargo metadata command return the output as a string.
///
/// # Returns
/// Returns a string containing the cargo metadata, presumably formatted in
/// JSON.  It's up to the caller to parse the data correctly.
fn _read_cargo_metadata() -> String {
    let output = Command::new("cargo").arg("metadata").arg("--format-version").arg("1").output().expect("Failed to run cargo metadata");
    String::from_utf8_lossy(&output.stdout).to_string()
}
