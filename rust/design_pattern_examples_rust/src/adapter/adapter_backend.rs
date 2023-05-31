//! Contains the wrapper functions for calling into the Adapter_BackEnd DLL.
//!
//! Originally created with bindgen from Adapter_BackEnd.h.  Extensively modified
//! to remove unused components, clean up documentation, simplify names, provide
//! Rust-compatible names for the functions in the DLL, and to add #\[allow()\]
//! so as to remove compiler warnings.

#![allow(non_camel_case_types, non_upper_case_globals)]

#[link(name="Adapter_BackEnd")]
extern "C" {
    #[doc = " Name of the first block."]
    #[link_name="BLOCK_NAME_0"]
    pub static block_name_0: *const ::std::os::raw::c_char;
}
#[link(name="Adapter_BackEnd")]
extern "C" {
    #[doc = " Name of the second block."]
    #[link_name="BLOCK_NAME_1"]
    pub static block_name_1: *const ::std::os::raw::c_char;
}
#[link(name="Adapter_BackEnd")]
extern "C" {
    #[doc = " Name of the third block."]
    #[link_name="BLOCK_NAME_2"]
    pub static block_name_2: *const ::std::os::raw::c_char;
}
#[doc = "All offsets must from 0 to 1 less than this value."]
pub const DDR_MAX_OFFSET: _bindgen_ty_1 = 32;
#[doc = "Value indicating the handle is invalid"]
pub const DDR_INVALID_HANDLE: _bindgen_ty_1 = -1;
pub type _bindgen_ty_1 = ::std::os::raw::c_int;
#[doc = "Operation succeeded"]
pub const DDR_ErrorCode_Success: DDR_ErrorCode = 0;
#[doc = "Memory block is already open and cannot be opened again"]
pub const DDR_ErrorCode_Block_Already_Opened: DDR_ErrorCode = 1;
#[doc = "Memory block is closed and cannot be accessed"]
pub const DDR_ErrorCode_Block_Not_Opened: DDR_ErrorCode = 2;
#[doc = "The given name is not a recognized memory block name"]
pub const DDR_ErrorCode_Invalid_Block_Name: DDR_ErrorCode = 3;
#[doc = "The handle argument does not correspond to a valid open memory block"]
pub const DDR_ErrorCode_Invalid_Handle: DDR_ErrorCode = 4;
#[doc = "The given offset is out of bounds"]
pub const DDR_ErrorCode_Invalid_Offset: DDR_ErrorCode = 5;
#[doc = "The block name pointer or return handle pointer argument is NULL"]
pub const DDR_ErrorCode_Null_Argument: DDR_ErrorCode = 6;
#[doc = "Represents the possible errors that can be returned from the memory block\n access functions.\n "]
pub type DDR_ErrorCode = ::std::os::raw::c_int;

extern "C" {
    #[doc = "Open access to a memory block for exclusive use, given the name of the\n memory block.\n\n# Parameters\n- blockName\n\n    Name of the block to access (one of the predefined\n names, @p BLOCK_NAME_0, @p BLOCK_NAME_1, or @p BLOCK_NAME_2)\n - dataHandle\n\n    Returns a handle to be used for accessing the\n specific memory block.\n\n# Returns\n  Returns an integer code (DDR_ErrorCode_X) indicating\n success or failure."]
    #[link_name="DDR_OpenMemoryBlock"]
    pub fn ddr_open_memory_block(
        blockName: *const ::std::os::raw::c_char,
        dataHandle: *mut ::std::os::raw::c_int,
    ) -> DDR_ErrorCode;
}

extern "C" {
    #[doc = "Close access to a previously opened memory block, thus releasing it for\n others to open.\n\n# Parameters\n- dataHandle\n\n    Handle to a previously opened memory block as\n obtained from the ddr_open_memory_block() function.\n\n# Returns\n  Returns an integer code (DDR_ErrorCode_X) indicating\n success or failure."]
    #[link_name="DDR_CloseMemoryBlock"]
    pub fn ddr_close_memory_block(dataHandle: ::std::os::raw::c_int) -> DDR_ErrorCode;
}

extern "C" {
    #[doc = "Retrieve the number of chunks in the memory block indicated by the handle\n to the successfully opened memory block.\n\n# Parameters\n- dataHandle\n\n    Handle to a previously opened memory block as\n obtained from the ddr_open_memory_block() function.\n - memorySizeInChunks\n\n    Returns the number of 32-bit chunks in the\n memory block.\n\n# Returns\n  Returns an integer code (DDR_ErrorCode_X) indicating\n success or failure."]
    #[link_name="DDR_GetMemorySize"]
    pub fn ddr_get_memory_size(
        dataHandle: ::std::os::raw::c_int,
        memorySizeInChunks: *mut ::std::os::raw::c_int,
    ) -> DDR_ErrorCode;
}

extern "C" {
    #[doc = "Read a single 32-bit value at the given offset in the memory block indicated\n by the specified handle.\n\n# Parameters\n- dataHandle\n\n    Handle to a previously opened memory block as\n obtained from the ddr_open_memory_block() function.\n - chunkOffset\n\n    Offset into the memory block from which to get\n the value (range is 0 to DDR_MAX_OFFSET-1).\n - value\n\n    Returns the requested value.\n\n# Returns\n  Returns an integer code (DDR_ErrorCode_X) indicating\n success or failure."]
    #[link_name="DDR_GetDataChunk"]
    pub fn ddr_get_data_chunk(
        dataHandle: ::std::os::raw::c_int,
        chunkOffset: ::std::os::raw::c_int,
        value: *mut u32,
    ) -> DDR_ErrorCode;
}

extern "C" {
    #[doc = "Writes a single 32-bit value to the given offset in the memory block indicated\n by the specified handle.\n\n# Parameters\n- dataHandle\n\n    Handle to a previously opened memory block as\n obtained from the ddr_open_memory_block() function.\n - chunkOffset\n\n    Offset into the memory block to which to set\n the value (range is 0 to DDR_MAX_OFFSET-1).\n - value\n\n    The value to write to the memory block\n\n# Returns\n  Returns an integer code (DDR_ErrorCode_X) indicating\n success or failure."]
    #[link_name="DDR_SetDataChunk"]
    pub fn ddr_set_data_chunk(
        dataHandle: ::std::os::raw::c_int,
        chunkOffset: ::std::os::raw::c_int,
        value: u32,
    ) -> DDR_ErrorCode;
}
