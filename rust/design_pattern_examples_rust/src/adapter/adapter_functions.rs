/// Alias representing the handle to the memory block being accessed.
pub type DataHandle = i32;

/// Represents the memory blocks that can be accessed.  Hides how memory blocks
/// are actually identified.
pub enum MemoryBlockNumber
{
    // First block
    MemoryBlock0,
    // Second block
    MemoryBlock1,
    // Third block
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
/// Returns the name of the memory block as a string.
fn _block_number_to_name(block_number: MemoryBlockNumber) -> String {
    match block_number {
        MemoryBlockNumber::MemoryBlock0 => String::from("block 0"),
        MemoryBlockNumber::MemoryBlock1 => String::from("block 1"),
        MemoryBlockNumber::MemoryBlock2 => String::from("block 3"),
    }
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
    let data_handle = 0;

    let block_name = _block_number_to_name(block_number);

    Ok(data_handle)
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

    Ok(())
}

/// Retrieve the number of bytes in the memory block associated with the
/// specified data handle
///
/// # Parameters
/// - data_handle
///    
///    The handle returned from adapter_open_memory() to access.
/// - aram name="sizeInBytes">Returns the number of bytes available to access.</param>
///
/// # Returns
/// If successful, returns `Ok(usize)` containing the number of bytes available
/// to access; otherwise, returns `Err(String)` containing the reason for the
/// failure.
pub fn adapter_get_memory_size(data_handle: DataHandle) -> Result<usize, String> {
    let memory_chunks = 128;

    Ok(memory_chunks * 4) // Convert from 32-bit values to 8-bit values
    
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
    let data = vec![0; max_bytes];

    Ok(data)
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

    Ok(byte_count)
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
