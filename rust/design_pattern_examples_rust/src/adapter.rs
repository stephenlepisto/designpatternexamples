//! # adapter
//!
//! Implementation of the adapter_exercise() function.

pub mod adapter_functions;

use adapter_functions::{MemoryBlockNumber, adapter_open_memory, adapter_close_memory, adapter_read_memory, adapter_write_memory, adapter_buffer_to_string};

/// Example of using the "Adapter" design pattern in rust.
/// 
/// This example adapts functions that:
/// 1. Accesses memory in 32-bit chunks instead of bytes
/// 2. Returns error codes but no human-readable error messages
/// 
/// The Adapter functions translate the 32-bit chunk access into arrays of bytes.
/// The Adapter functions also provide human-readable messages for error codes.
pub fn adapter_exercise() {
    println!("");
    println!("Adapter Exercise");

    let result = adapter_open_memory(MemoryBlockNumber::MemoryBlock0);
    let data_handle = match result {
        Ok(handle) => handle,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let mut write_data: Vec<u8> = vec![0;128];
    for index in 0..write_data.len() {
        write_data[index] = index as u8;
    }

    let hex_dump = match adapter_buffer_to_string(&write_data, 2) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };
    println!("  Data Written:");
    println!("{hex_dump}");

    let num_bytes_written = match adapter_write_memory(data_handle, 0, &write_data) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let read_data = match adapter_read_memory(data_handle, 0, num_bytes_written) {
        Ok(data) => data,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let hex_dump = match adapter_buffer_to_string(&read_data, 2) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };
    println!("  Data Read:");
    println!("{hex_dump}");

    match adapter_close_memory(data_handle) {
        Ok(t) => t,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    println!("  Done.");
}
