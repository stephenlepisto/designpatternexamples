//! Contains the DataReaderWriter struct that acts as an adapter to the
//! Adapter_BackEnd DLL (via the function wrappers in adapter_backend.rs).

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

/// Represents a data reader/writer to a caller.
/// Adapts the functions from the Adapter_BackEnd DLL (as wrapped by the functions
/// in adapter_backend.rs).
pub struct DataReaderWriter {
    _data_handle: DataHandle,
    _block_number: MemoryBlockNumber,

    /// Number of bytes in the currently opened memory block.
    pub memory_block_byte_size: usize,
}

impl DataReaderWriter {
    /// Constructor for DataReaderWriter struct.
    ///
    /// # Parameters
    /// - blockNumber
    ///
    ///   A value from the MemoryBlockNumber enumeration indicating the block
    ///   of memory to open.
    pub fn new(block_number: MemoryBlockNumber) -> DataReaderWriter {
        DataReaderWriter {
            _data_handle: DDR_INVALID_HANDLE,
            _block_number: block_number,
            memory_block_byte_size: 0
        }
    }

    /// Open a memory block for access.  Which memory block to open is specified
    /// in the constructor.  If this is successful, the memory block is open for
    /// reading and writing.  Call close() to shut down access to the memory
    /// block.
    pub fn open(&mut self) -> Result<(), String> {
        let block_name = _block_number_to_name(&self._block_number);
        let name_ptr = block_name.as_ptr() as *const ::std::os::raw::c_char;
   
        let mut error_code = unsafe {
            ddr_open_memory_block(name_ptr, &mut self._data_handle)
        };

        if let DDR_ErrorCode_Success = error_code {
            let mut memory_size: ::std::os::raw::c_int = 0;
            error_code = unsafe { ddr_get_memory_size(self._data_handle, &mut memory_size) };
            if error_code == DDR_ErrorCode_Success {
                self.memory_block_byte_size = (memory_size as usize) * 4;
                Ok(())
            }
            else {
                Err(_report_ddr_error(error_code, "Opening memory block"))
            }
        }
        else
        {
            Err(_report_ddr_error(error_code, "Opening memory block"))
        }
    }


    /// Closes a memory block from access.  If this is successful, the same
    /// memory block can be opened again by a call to open().  Otherwise,
    /// instantiate the DataReaderWriter structure again to specify a different
    /// memory block.
    pub fn close(&mut self) -> Result<(), String> {
        let error_code = unsafe { ddr_close_memory_block(self._data_handle) };

        if let DDR_ErrorCode_Success = error_code {
            self._data_handle = DDR_INVALID_HANDLE;
            self.memory_block_byte_size = 0;
            Ok(())
        } else {
            Err(_report_ddr_error(error_code, "Attempting to close memory block"))
        }
    }

    /// Called by Drop::drop() to ensure the memory handle is closed.  Does
    /// nothing if the handle is already closed (or was never opened).  Ignores
    /// any errors returned from close() if the memory handle was left opened.
    fn _drop_close(&mut self) {
        if self._data_handle != DDR_INVALID_HANDLE {
            // Ignore return values
            let _ = self.close();
        }
    }

    /// Read a requested number of bytes from the currently opened memory block.
    ///
    /// # Parameters
    /// - byte_offset
    ///   
    ///   Offset into the memory block to start reading from.
    /// - maxBytes
    ///
    ///   The number of bytes to read.
    ///
    /// # Returns
    /// If successful, returns `Ok(Vec<u8>)` containing the bytes that were actually
    /// read; otherwise, returns `Err(String)` containing the reason for the failure.
    pub fn read(&self, byte_offset: i32, max_bytes: usize) -> Result<Vec<u8>, String> {
        let mut data: Vec<u8> = vec![0; max_bytes];

        let mut chunk_offset = byte_offset / 4; // 4 bytes per 32-bit chunk
        let mut value: u32 = 0;
        let mut error_code = unsafe { ddr_get_data_chunk(self._data_handle, chunk_offset, &mut value) };
        if let DDR_ErrorCode_Success = error_code {
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
                    error_code = unsafe { ddr_get_data_chunk(self._data_handle, chunk_offset, &mut value)};
                    if let DDR_ErrorCode_Success = error_code {
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

    /// Write a requested number of bytes to the currently opened memory block.
    ///
    /// # Parameters
    /// 
    /// - byte_offset
    ///    
    ///   Byte offset into the memory block indicating where to start writing.
    /// - bytes_to_write
    ///    
    ///   Vector of bytes to write to the memory block.  All of the bytes will
    ///   be written -- up to the end of the memory block.
    ///
    /// # Returns
    /// If successful, returns `Ok(i32)` containing the number of bytes actually
    /// written; otherwise, returns `Err(String)` containing the reason for the
    /// failure.
    pub fn write(&self, byte_offset: i32, bytes_to_write: &Vec<u8>) -> Result<usize, String> {
        let mut chunk_offset = byte_offset / 4;
        let mut value: u32 = 0;
        let mut byte_offset_in_chunk = byte_offset % 4;
        let mut buffer_index: usize = 0;
        let mut byte_mask : u32 = 0xffu32 << (byte_offset_in_chunk * 8);
        let mut error_code = DDR_ErrorCode_Success;
        if byte_offset_in_chunk != 0 {
            error_code = unsafe { ddr_get_data_chunk(self._data_handle, chunk_offset, &mut value) };
        }
        if let DDR_ErrorCode_Success = error_code {
            while buffer_index < bytes_to_write.len() {
                value &= !byte_mask;
                value |= (bytes_to_write[buffer_index] as u32) << (byte_offset_in_chunk * 8);
                buffer_index += 1;
                byte_mask <<= 8;
                byte_offset_in_chunk += 1;
                if byte_offset_in_chunk == 4 {
                    error_code = unsafe { ddr_set_data_chunk(self._data_handle, chunk_offset, value) };
                    if let DDR_ErrorCode_Success = error_code {
                        byte_mask = 0xffu32;
                        byte_offset_in_chunk = 0;
                        chunk_offset += 1;
                        if chunk_offset >= DDR_MAX_OFFSET {
                            break;
                        }
                        error_code = unsafe { ddr_get_data_chunk(self._data_handle, chunk_offset, &mut value) };
                        if let DDR_ErrorCode_Success = error_code {

                        } else {
                            return Err(_report_ddr_error(error_code, "Reading memory in preparation to writing memory"));
                        }
                    
                    } else {
                        return Err(_report_ddr_error(error_code, "Writing memory"));
                    }
                }
            }
            if byte_offset_in_chunk != 0 {
                error_code = unsafe { ddr_set_data_chunk(self._data_handle, chunk_offset, value) };
                if let DDR_ErrorCode_Success = error_code {

                } else {
                    return Err(_report_ddr_error(error_code, "Writing memory"));
                }
            }
            Ok(buffer_index)
        } else {
            Err(_report_ddr_error(error_code, "Reading memory in preparation to writing memory"))
        }
    }
}

impl Drop for DataReaderWriter {
    /// Makes sure the current memory block is closed in the event that an error
    /// caused an early return from the function that owned the DataReaderWriter
    /// instance.
    fn drop(&mut self) {
        self._drop_close();
    }
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
fn _block_number_to_name<'a>(block_number: &MemoryBlockNumber) -> &'a str {
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
        DDR_ErrorCode_Success => String::from("Operation succeeded"),
        DDR_ErrorCode_Block_Already_Opened => String::from("Memory block is already open and cannot be opened again"),
        DDR_ErrorCode_Block_Not_Opened => String::from("Memory block is closed and cannot be accessed"),
        DDR_ErrorCode_Invalid_Block_Name => String::from("The given name is not a recognized memory block name"),
        DDR_ErrorCode_Invalid_Handle => String::from("The handle argument does not correspond to a valid open memory block"),
        DDR_ErrorCode_Invalid_Offset => String::from("The given offset is out of bounds"),
        DDR_ErrorCode_Null_Argument => String::from("The block name pointer or return handle pointer argument is NULL"),
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


/// Helper function to create a human-readable error message for the given
/// error code, adding a prompt to provide some context to the error.  Returns
/// the string.
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
