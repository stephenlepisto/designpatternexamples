//! # adapter
//!
//! Implementation of the adapter_exercise() function.

pub mod adapter_functions;
pub mod adapter_backend;

use adapter_functions::{
    MemoryBlockNumber, DataReaderWriter, adapter_buffer_to_string
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
pub fn adapter_exercise() -> Result<(), String> {
    println!("");
    println!("Adapter Exercise");

    let mut reader_writer = DataReaderWriter::new(MemoryBlockNumber::MemoryBlock0);

    reader_writer.open()?;

    let memory_block_size = reader_writer.memory_block_byte_size;

    let mut read_data = reader_writer.read(0, memory_block_size)?;
    let mut hex_dump = adapter_buffer_to_string(&read_data, 2)?;
    println!("  Initial memory block contents:");
    println!("{hex_dump}");

    let data_size = 16;
    let buffer_offset = 41;
    let mut write_data: Vec<u8> = vec![0;data_size];
    for index in 0..write_data.len() {
        write_data[index] = (index + 1) as u8;
    }

    hex_dump = adapter_buffer_to_string(&write_data, 2)?;
    println!("  Data to be written to memory block:");
    println!("{hex_dump}");

    println!("  Writing data to byte offset {buffer_offset}");
    let _ = reader_writer.write(buffer_offset, &write_data)?;

    println!("  Reading back the memory block...");
    read_data = reader_writer.read(0, memory_block_size)?;
    println!();

    hex_dump = adapter_buffer_to_string(&read_data, 2)?;
    println!("  Current memory block contents:");
    println!("{hex_dump}");

    reader_writer.close()?;

    println!("  Done.");
    Ok(())
}

// ! [Using Adapter in Rust]

