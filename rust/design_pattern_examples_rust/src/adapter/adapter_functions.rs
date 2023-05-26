#![allow(non_upper_case_globals)] // For DDR_ErrorCode items

use std::ffi::{CStr};

use crate::adapter::adapter_backend::*;


/// Alias representing the handle to the memory block being accessed.
pub type DataHandle = i32;

/// Represents the memory blocks that can be accessed.  Hides how memory blocks
/// are actually identified.
pub enum MemoryBlockNumber
{
    // First block
    MemoryBlock0,
    // Second block
    #[allow(dead_code)] // Not currently used
    MemoryBlock1,
    // Third block
    #[allow(dead_code)] // Not currently used
    MemoryBlock2,
}


/// Helper function to convert the MemoryBlockNumber enumeration to a string
/// that names the memory block to be opened in the back-end functions.
///
/// # Parameters
/// - block_number
///
///   A value from the MemoryBlockNumber enumeration indicating the memory
///   block to be opened.
///
/// # Returns
/// Returns the name of the memory block as a reference to a string slice.
fn _block_number_to_name<'a>(block_number: MemoryBlockNumber) -> &'a str {
    match block_number {
        MemoryBlockNumber::MemoryBlock0 => {
            let var_name = unsafe { CStr::from_ptr(block_name_0) };
            var_name.to_str().unwrap()
        },
        MemoryBlockNumber::MemoryBlock1 => {
            let var_name = unsafe { CStr::from_ptr(block_name_1) };
            var_name.to_str().unwrap()
        },
        MemoryBlockNumber::MemoryBlock2 => {
            let var_name = unsafe { CStr::from_ptr(block_name_2) };
            var_name.to_str().unwrap()
        },
    }
}

/// Helper function to convert a DDR_ErrorCode to a human-readable representation.
///
/// # Parameters
/// - error_code
///
///   A value from the DDR_ErrorCode enumeration representing the error code.
///
/// # Returns
/// Returns a string containing the human-readable representation of the given
/// error code.
fn _errorcode_to_string(error_code: DDR_ErrorCode) -> String {
    match error_code {
        DDR_ErrorCode_DDR_ErrorCode_Success => String::from("Operation succeeded"),
        DDR_ErrorCode_DDR_ErrorCode_Block_Already_Opened => String::from("Memory block is already open and cannot be opened again"),
        DDR_ErrorCode_DDR_ErrorCode_Block_Not_Opened => String::from("Memory block is closed and cannot be accessed"),
        DDR_ErrorCode_DDR_ErrorCode_Invalid_Block_Name => String::from("The given name is not a recognized memory block name"),
        DDR_ErrorCode_DDR_ErrorCode_Invalid_Handle => String::from("The handle argument does not correspond to a valid open memory block"),
        DDR_ErrorCode_DDR_ErrorCode_Invalid_Offset => String::from("The given offset is out of bounds"),
        DDR_ErrorCode_DDR_ErrorCode_Null_Argument => String::from("The block name pointer or return handle pointer argument is NULL"),
        _ => String::from("Unknown error"),
    }
}


/// Helper function to format the given message and prompt into a single error
/// message string, which is returned.
///
/// # Parameters
/// - message
///   
///    The error message to report.
/// - prompt
///    
///    A prompt that indicates the context in which the error occurred.
fn _report_error_message(message: String, prompt: &str) -> String {
    format!("Error! {prompt}: {message}.")
}


/// Create a human-readable error message for the given error code, adding a
/// prompt to provide some context to the error.  Returns the string.
///
/// # Parameters
/// - error_code
///    
///    A value from the DDR_ErrorCode enumeration indicating the error that
///    occurred.
/// - "prompt
///    
///    A prompt that indicates the context in which the error occurred.
fn _report_ddr_error(error_code: DDR_ErrorCode, prompt: &str) -> String {
    let message = _errorcode_to_string(error_code);
    _report_error_message(message, prompt)
}


/// Open a memory block for access.
///
/// # Parameters
/// - block_number
///
///    A value from the MemoryBlockNumber enumeration indicating which memory
///    block to access.
///
/// # Returns
/// If successful, returns `Ok(DataHandle)` containing the handle of the opened
/// memory block; otherwise, returns `Err(String)` containing the reason for the
/// failure.
pub fn adapter_open_memory(block_number: MemoryBlockNumber) -> Result<DataHandle, String> {
    let mut data_handle: DataHandle = DDR_INVALID_HANDLE;

    let block_name = _block_number_to_name(block_number);
    let name_ptr = block_name.as_ptr() as *const ::std::os::raw::c_char;
   
    let error_code = unsafe {
        ddr_open_memory_block(name_ptr, &mut data_handle)
    };

    if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
        Ok(data_handle)
    }
    else
    {
        Err(_report_ddr_error(error_code, "Opening memory block"))
    }

}

/// Closes a memory block from access.
///
/// # Parameters
/// - data_handle
///    
///    The handle returned from adapter_open_memory() to be closed.
///
/// # Returns
/// If successful, returns `Ok()`; otherwise, returns `Err(String)` containing
/// the reason for the failure.
pub fn adapter_close_memory(data_handle: DataHandle) -> Result<(), String> {

    let error_code = unsafe { ddr_close_memory_block(data_handle) };

    if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
        Ok(())
    } else {
        Err(_report_ddr_error(error_code, "Attempting to close memory block"))
    }
}

/// Retrieve the number of bytes in the memory block associated with the
/// specified data handle
///
/// # Parameters
/// - data_handle
///    
///    The handle returned from adapter_open_memory() to access.
///
/// # Returns
/// If successful, returns `Ok(usize)` containing the number of bytes available
/// to access; otherwise, returns `Err(String)` containing the reason for the
/// failure.
#[allow(dead_code)] // Not currently used
pub fn adapter_get_memory_size(data_handle: DataHandle) -> Result<usize, String> {
    let mut memory_size: ::std::os::raw::c_int = 0;
    let error_code = unsafe { ddr_get_memory_size(data_handle, &mut memory_size) };
    let memory_chunks = memory_size as usize;
    if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
        Ok(memory_chunks * 4) // Convert from 32-bit values to 8-bit values
    }
    else {
        Err(_report_ddr_error(error_code, "Getting memory size"))
    }
}

/// Read a requested number of bytes from the memory block associated with the
/// given handle.
///
/// # Parameters
/// - data_handle
/// 
///    The handle returned from adapter_open_memory() to access.
/// - byte_offset
///   
///    Buffer to fill with bytes from the memory block.
/// - maxBytes
///
/// # Returns
/// If successful, returns `Ok(Vec<u8>)` containing the bytes that were actually
/// read; otherwise, returns `Err(String)` containing the reason for the failure.
pub fn adapter_read_memory(data_handle: DataHandle, byte_offset: i32, max_bytes: usize) -> Result<Vec<u8>, String> {
    let mut data: Vec<u8> = vec![0; max_bytes];

    let mut chunk_offset = byte_offset / 4; // 4 bytes per 32-bit chunk
    let mut value: u32 = 0;
    let mut error_code = unsafe { ddr_get_data_chunk(data_handle, chunk_offset, &mut value) };
    if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
        let mut buffer_index = 0;
        let mut byte_offset_in_chunk = byte_offset % 4;
        while buffer_index < max_bytes {
            data[buffer_index] = value as u8;
            buffer_index += 1;
            value >>= 8;
            byte_offset_in_chunk += 1;
            if byte_offset_in_chunk == 4 {
                chunk_offset += 1;
                if chunk_offset >= DDR_MAX_OFFSET {
                    break;
                }
                byte_offset_in_chunk = 0;
                error_code = unsafe { ddr_get_data_chunk(data_handle, chunk_offset, &mut value)};
                if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
                    continue;
                } else {
                    return Err(_report_ddr_error(error_code, "Reading successive memory chunk"));
                }
            }
        }

        Ok(data)
    } else {
        Err(_report_ddr_error(error_code, "Reading initial memory chunk"))
    }
}

/// Write a requested number of bytes to the memory block associated with the
/// given handle.
///
/// # Parameters
/// 
///    The handle returned from adapter_open_memory() to access.
/// - byte_offset
///    
///    Byte offset into the memory block from which to start writing.
/// -buffer
///    
///    Vector of bytes to write to the memory block.
///
/// # Returns
/// If successful, returns `Ok(i32)` containing the number of bytes actually
/// written; otherwise, returns `Err(String)` containing the reason for the
/// failure.
pub fn adapter_write_memory(data_handle: DataHandle, byte_offset: i32, bytes_to_write: &Vec<u8>) -> Result<usize, String> {
    let byte_count = bytes_to_write.len();
    let mut chunk_offset = byte_offset / 4;
    let mut value: u32 = 0;
    let mut byte_offset_in_chunk = byte_offset % 4;
    let mut buffer_index: usize = 0;
    let mut byte_mask : u32 = 0xffu32 << byte_offset_in_chunk;
    let mut error_code = DDR_ErrorCode_DDR_ErrorCode_Success;
    if byte_offset_in_chunk != 0 {
        error_code = unsafe { ddr_get_data_chunk(data_handle, chunk_offset, &mut value) };
    }
    if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
        while buffer_index < bytes_to_write.len() {
            value &= !byte_mask;
            value |= (bytes_to_write[buffer_index] as u32) << (byte_offset_in_chunk * 8);
            buffer_index += 1;
            byte_mask <<= 8;
            byte_offset_in_chunk += 1;
            if byte_offset_in_chunk == 4 {
                error_code = unsafe { ddr_set_data_chunk(data_handle, chunk_offset, value) };
                if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {
                    byte_mask = 0xffu32;
                    byte_offset_in_chunk = 0;
                    chunk_offset += 1;
                    if chunk_offset >= DDR_MAX_OFFSET {
                        break;
                    }
                } else {
                    return Err(_report_ddr_error(error_code, "Writing memory"));
                }
            }
        }
        if byte_offset_in_chunk != 0 {
            error_code = unsafe { ddr_set_data_chunk(data_handle, chunk_offset, value) };
            if let DDR_ErrorCode_DDR_ErrorCode_Success = error_code {

            } else {
                return Err(_report_ddr_error(error_code, "Writing memory"));
            }
        }
        Ok(byte_count)
    } else {
        Err(_report_ddr_error(error_code, "Reading memory in preparation to writing memory"))
    }
}

/// Convert the specified data up to the specified number of bytes into
/// a string by performing a "hex dump" on the data.
///
/// # Parameters
/// -data
///    
///    Vector bytes to process.
/// -indent
///    
///    Number of spaces to indent each line.
///
/// # Returns
/// If successful, returns `Ok(String)` containing the data in the form of a
/// hex dump, possibly multiple lines; otherwise, retursn `Err(String)` containing
/// the reason for the failure.
pub fn adapter_buffer_to_string(data: &Vec<u8>, indent: usize) -> Result<String, String> {
    let mut output = String::from("");

    let bytes_per_row = 32;

    let mut row = 0;
    while row < data.len() {
        let row_start = format!("{:>indent$}0x{row:04x} --", "");
        output.push_str(&row_start);

        let mut col = 0;
        while col < bytes_per_row && (row + col) < data.len() {
            let data_index = row + col;
            let space = if col > 0 { " " } else { "" };
            let field = format!("{space}{:02x}", data[data_index]);
            output.push_str(&field);
            col += 1;
        }
        output.push_str("\n");
        row += bytes_per_row;
    }
    Ok(output)
}
