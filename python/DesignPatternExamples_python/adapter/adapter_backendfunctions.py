## @file
#  @brief
#  The wrapper for the @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL
#  containing functions used in the @ref adapter_pattern.

import os
import os.path
import sys
from ctypes import *
from enum import Enum

## Represents the possible errors that can be returned from the memory block
#  access functions.
class DDR_ErrorCode(Enum):
    ## Operation succeeded
    DDR_ErrorCode_Success = 0
    ## Memory block is already open and cannot be opened again
    DDR_ErrorCode_Block_Already_Opened = 1
    ## Memory block is closed and cannot be accessed
    DDR_ErrorCode_Block_Not_Opened = 2
    ## The given name is not a recognized memory block name
    DDR_ErrorCode_Invalid_Block_Name = 3
    ## The handle argument does not correspond to a valid open memory block
    DDR_ErrorCode_Invalid_Handle = 4
    ## The given offset is out of bounds
    DDR_ErrorCode_Invalid_Offset = 5
    ## The block name pointer or return handle pointer argument is NULL
    DDR_ErrorCode_Null_Argument = 6


## All offsets must from 0 to 1 less than this value.
DDR_MAX_OFFSET = 32

## Name of the first block.
BLOCK_NAME_0 = "gorp"

## Name of the second block.
BLOCK_NAME_1 = "baba"

## Name of the third block.
BLOCK_NAME_2 = "yaga"


## Represents an opaque token or handle to data.  Since a class is passed by
#  reference in Python, a function can write to the handle to set its value.
#  Use the `value` attribute to read/write the handle.
class Handle:
    ## Constructor
    def __init__(self):
        self.value = -1

    ## @var value
    #       The attribute to read to get the value passed back through the
    #       Handle class instance.  The value can also be written to.


## Represents a value that can be passed into or out of a function.  Since a
#  class is passed by reference in Python, a function can write to the handle
#  to set its value.  Use the `value` attribute to read/write the handle.
class ValueHandle:
    ## Constructor
    def __init__(self):
        self.value = 0

    ## @var value
    #       The attribute to read to get the value passed back through the
    #       ValueHandle class instance.  The value can also be written to.


## Path to the @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL that will be loaded
#  by ctypes.  The DLL is located in the same directory as this file.
if sys.platform == "win32":
    dll_path = os.path.join(os.path.dirname(__file__), "Adapter_BackEnd")
else:
    dll_path = os.path.join(os.path.dirname(__file__), "libAdapter_BackEnd.so")

## Instance of a CDLL object representing the loaded @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.
adapter_backend = cdll.LoadLibrary(dll_path)


##  Open access to a memory block for exclusive use, given the name of the
#   memory block.  Use
#    @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.ddr_closememoryblock "ddr_closememoryblock"()
#    to release access to the memory block.
#
#   @param blockName
#          Name of the block to access (one of the predefined names,
#          `BLOCK_NAME_0`, `BLOCK_NAME_1`, or `BLOCK_NAME_2`)
#   @param dataHandle
#          Returns a handle to be used for accessing the specific memory block.
#   @returns
#     Returns a value from the
#     @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode "DDR_ErrorCode"
#     enumeration indicating success or failure.
def ddr_openmemoryblock(blockName, dataHandle: Handle) -> DDR_ErrorCode:
    handle = c_int()
    name = blockName.encode("UTF8")
    error_code = DDR_ErrorCode(adapter_backend.DDR_OpenMemoryBlock(name, byref(handle)))
    if error_code == DDR_ErrorCode.DDR_ErrorCode_Success:
        dataHandle.value = handle.value
    return error_code

##  Close access to a memory block previously opened by ddr_openmemoryblock(),
#   thus releasing it for others to open.
#
#   @param dataHandle
#          Handle to a previously opened memory block as obtained from the
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.ddr_openmemoryblock "ddr_openmemoryblock"() function.
#   @returns
#     Returns a value from the
#     @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode "DDR_ErrorCode"
#     enumeration indicating success or failure.
def ddr_closememoryblock(dataHandle : Handle) -> DDR_ErrorCode:
    return DDR_ErrorCode(adapter_backend.DDR_CloseMemoryBlock(dataHandle.value))

##  Retrieve the number of chunks in the memory block indicated by the handle
#   to the successfully opened memory block.
#
#   @param dataHandle
#          Handle to a previously opened memory block as obtained from the
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.ddr_openmemoryblock "ddr_openmemoryblock"() function.
#   @param memorySizeInChunks
#          Returns the number of 32-bit chunks in the memory block.
#   @returns
#     Returns a value from the
#     @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode "DDR_ErrorCode"
#     enumeration indicating success or failure.
def ddr_getmemorysize(dataHandle: Handle, memorySizeInChunks: ValueHandle) -> DDR_ErrorCode:
    chunks = c_int()
    error_code = DDR_ErrorCode(adapter_backend.DDR_GetMemorySize(dataHandle.value, byref(chunks)))
    if error_code == DDR_ErrorCode.DDR_ErrorCode_Success:
        memorySizeInChunks.value = chunks.value
    return error_code

##  Read a single 32-bit value at the given offset in the memory block indicated
#   by the specified handle.
#
#   @param dataHandle
#          Handle to a previously opened memory block as obtained from the
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.ddr_openmemoryblock "ddr_openmemoryblock"() function.
#   @param chunkOffset
#          Offset into the memory block from which to get the value (range is 0 to
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_MAX_OFFSET "DDR_MAX_OFFSET"-1).
#   @param value
#          Returns the requested value.
#   @returns
#     Returns a value from the
#     @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode "DDR_ErrorCode"
#     enumeration indicating success or failure.
def ddr_getdatachunk(dataHandle: Handle, chunkOffset: int, value: ValueHandle) -> DDR_ErrorCode:
    chunk_value = c_uint32()
    error_code = DDR_ErrorCode(adapter_backend.DDR_GetDataChunk(dataHandle.value, chunkOffset, byref(chunk_value)))
    if error_code == DDR_ErrorCode.DDR_ErrorCode_Success:
        value.value = chunk_value.value
    return error_code

##  Writes a single 32-bit value to the given offset in the memory block indicated
#   by the specified handle.
#
#   @param dataHandle
#          Handle to a previously opened memory block as obtained from the
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.ddr_openmemoryblock "ddr_openmemoryblock"() function.
#   @param chunkOffset
#          Offset into the memory block to which to set the value (range is 0 to
#          @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_MAX_OFFSET "DDR_MAX_OFFSET"-1).
#   @param value
#          The value to write to the memory block
#   @returns
#     Returns a value from the
#     @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode "DDR_ErrorCode"
#     enumeration indicating success or failure.
def ddr_setdatachunk(dataHandle: Handle, chunkOffset: int, value: int) -> DDR_ErrorCode:
    chunk_value = c_uint32(value)
    error_code = DDR_ErrorCode(adapter_backend.DDR_SetDataChunk(dataHandle.value, chunkOffset, chunk_value))
    return error_code
