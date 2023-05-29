//! # adapter
//!
//! Implementation of the adapter_exercise() function.

pub mod adapter_functions;
pub mod adapter_backend;

use adapter_functions::{
    MemoryBlockNumber, adapter_open_memory, adapter_close_memory,
    adapter_get_memory_size, adapter_read_memory, adapter_write_memory,
    adapter_buffer_to_string
};

/// Example of using the "Adapter" design pattern in rust.
/// 
/// This example adapts functions that:
/// 1. Accesses memory in 32-bit chunks instead of bytes
/// 2. Returns error codes but no human-readable error messages
/// 
/// The Adapter functions translate the 32-bit chunk access into arrays of bytes.
/// The Adapter functions also provide human-readable messages for error codes.

// ! [Using Adapter in Rust]
pub fn adapter_exercise() {
    println!("");
    println!("Adapter Exercise");

    let data_handle = match adapter_open_memory(MemoryBlockNumber::MemoryBlock0) {
        Ok(handle) => handle,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let memory_block_size = match adapter_get_memory_size(data_handle) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let mut read_data = match adapter_read_memory(data_handle, 0, memory_block_size) {
        Ok(data) => data,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    let mut hex_dump = match adapter_buffer_to_string(&read_data, 2) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };
    println!("  Initial memory block contents:");
    println!("{hex_dump}");

    let data_size = 16;
    let buffer_offset = 41;
    let mut write_data: Vec<u8> = vec![0;data_size];
    for index in 0..write_data.len() {
        write_data[index] = (index + 1) as u8;
    }

    hex_dump = match adapter_buffer_to_string(&write_data, 2) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };
    println!("  Data to be written to memory block:");
    println!("{hex_dump}");

    println!("  Writing data to byte offset {buffer_offset}");
    let _ = match adapter_write_memory(data_handle, buffer_offset, &write_data) {
        Ok(_) => (),
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    println!("Reading back the memory block...");
    read_data = match adapter_read_memory(data_handle, 0, memory_block_size) {
        Ok(data) => data,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };

    hex_dump = match adapter_buffer_to_string(&read_data, 2) {
        Ok(value) => value,
        Err(message) => {
            eprintln!("  {message}");
            return;
        }
    };
    println!("  Current memory block contents:");
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

// ! [Using Adapter in Rust]

