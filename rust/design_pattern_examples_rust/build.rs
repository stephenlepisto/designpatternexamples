//! design_pattern_examples_rust build script
//!
//! This build script sets up the link switches for linking to the
//! Adapter_BackEnd dynamic library, given a path to that library via the
//! environment variable ADAPTER_BINARY_DIR.

use std::env;
use std::path::{Path, PathBuf};

fn main() {
    // Note: the DEBUG environment variable is not in the cargo metadata so we
    // go to the environment for the value.
    let debug_config = match env::var("DEBUG") {
        Ok(var) => match var.as_str()  {
                            "true" => "debug",
                            _ => "release",
                        },
        Err(_) => ".", // No DEBUG?  Assume single-configuration build
    };

    // We expect CMake to provide the ADAPTER_BINARY_DIR variable.  However,
    // tools such as rust analyzer in Visual Studio Code can't provide that
    // variable and instead just stops working because the environment variable
    // can't be found (that is, don't just call unwrap() when trying to get the
    // variable).  If the variable cannot be found, generate a path that it
    // might have been.
    let library_path = match env::var("ADAPTER_BINARY_DIR") {
        Ok(value) => PathBuf::from(value),
        Err(_) => Path::join(&env::current_dir().unwrap(), "..").join("..").join("build").join("Adapter_BackEnd").join(format!("{debug_config}")),
    };

    // Override the CARGO_PKG_VERSION used in the program if RUST_VERSION is
    // set.  Allows CMake to override the version stored in the Cargo.toml
    // manifest file.
    if let Ok(val) = env::var("RUST_VERSION") {
        println!("cargo:rustc-env=CARGO_PKG_VERSION={}", val);
    }

    // We don't need to use cargo:rustc-link-lib here since the use of the
    // #[link()] in adapter_backend.rs automatically adds the library to the
    // link line.
    //println!("cargo:rustc-link-lib=Adapter_BackEnd");
    println!("cargo:rustc-link-search={}", library_path.display());
    // Note: The following is platform-specific but appears to be ignored on
    // Windows when building with cargo.
    println!("cargo:rustc-link-arg=-Wl,-rpath=$ORIGIN");
}
