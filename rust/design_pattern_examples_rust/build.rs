//! design_pattern_examples_rust build script
//!
//! This build script always copies the Adapter_BackEnd library files to the
//! target directory.

use std::env;
use std::fs;
use std::path::{Path, PathBuf};

fn main() {
    let profile = env::var("PROFILE").unwrap_or("debug".to_string());
    let debug_config: String;
    if profile == "debug" {
        debug_config = "Debug".to_string();
    }
    else {
        debug_config = "Release".to_string();
    }
    let library_path = Path::join(&env::current_dir().unwrap(), "..").join("..").join("lib").join("x64").join(format!("{debug_config}/"));
    println!("cargo:rustc-link-lib=Adapter_BackEnd");
    println!("cargo:rustc-link-search={}", library_path.display());

    let files_to_copy = vec!["Adapter_BackEnd.dll", "Adapter_BackEnd.pdb"];
    let input_path = library_path;
    let output_path = _get_output_path(&debug_config);

    // Make sure the output directory exists
    output_path.try_exists().unwrap();

    for file in files_to_copy {
        let src = input_path.join(file);
        let dest = output_path.join(file);
        fs::copy(src, dest).unwrap();
    }
    //let mut output = String::from("Environment variables in build environment\n");
    //for e in env::vars() {
    //    let entry = format!("  {} = {}\n", e.0, e.1);
    //    output.push_str(&entry);
    //}
    //fs::write("build_env.log", output).unwrap();
}


fn _get_output_path(build_type: &str) -> PathBuf {
    //<root or manifest path>/target/<profile>/
    let manifest_dir_string = env::var("CARGO_MANIFEST_DIR").unwrap();
    let path = Path::new(&manifest_dir_string).join("target").join(build_type);
    return PathBuf::from(path);
}
