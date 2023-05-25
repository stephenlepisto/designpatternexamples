/// @file
/// @brief
/// Declaration of the memory read/write functions
/// as used in the @ref adapter_pattern.

#pragma once
#ifndef __ADAPTER_BACKENDFUNCTIONS_H__
#define __ADAPTER_BACKENDFUNCTIONS_H__

#include <stdint.h>

#ifdef ADAPTERBACKEND_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif


/// Name of the first block.
DllExport extern const char* BLOCK_NAME_0;

/// Name of the second block.
DllExport extern const char* BLOCK_NAME_1;

/// Name of the third block.
DllExport extern const char* BLOCK_NAME_2;


enum {
    DDR_MAX_OFFSET = 32,      ///< All offsets must from 0 to 1 less than this value.

    DDR_INVALID_HANDLE = -1,  ///< Value indicating the handle is invalid
};

/// <summary>
/// Represents the possible errors that can be returned from the memory block
/// access functions.
/// </summary>
typedef enum
{
    DDR_ErrorCode_Success = 0,               ///< Operation succeeded
    DDR_ErrorCode_Block_Already_Opened = 1,  ///< Memory block is already open and cannot be opened again
    DDR_ErrorCode_Block_Not_Opened = 2,      ///< Memory block is closed and cannot be accessed
    DDR_ErrorCode_Invalid_Block_Name = 3,    ///< The given name is not a recognized memory block name
    DDR_ErrorCode_Invalid_Handle = 4,        ///< The handle argument does not correspond to a valid open memory block
    DDR_ErrorCode_Invalid_Offset = 5,        ///< The given offset is out of bounds
    DDR_ErrorCode_Null_Argument = 6          ///< The block name pointer or return handle pointer argument is NULL
} DDR_ErrorCode;


/// <summary>
/// Open access to a memory block for exclusive use, given the name of the
/// memory block.
/// </summary>
/// <param name="blockName">Name of the block to access (one of the predefined
/// names, @p BLOCK_NAME_0, @p BLOCK_NAME_1, or @p BLOCK_NAME_2)</param>
/// <param name="dataHandle">Returns a handle to be used for accessing the
/// specific memory block.</param>
/// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
/// success or failure.</returns>
DllExport DDR_ErrorCode DDR_OpenMemoryBlock(const char* blockName, int* dataHandle);

/// <summary>
/// Close access to a previously opened memory block, thus releasing it for
/// others to open.
/// </summary>
/// <param name="dataHandle">Handle to a previously opened memory block as
/// obtained from the DDR_OpenMemoryBlock() function.</param>
/// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
/// success or failure.</returns>
DllExport DDR_ErrorCode DDR_CloseMemoryBlock(int dataHandle);

/// <summary>
/// Retrieve the number of chunks in the memory block indicated by the handle
/// to the successfully opened memory block.
/// </summary>
/// <param name="dataHandle">Handle to a previously opened memory block as
/// obtained from the DDR_OpenMemoryBlock() function.</param>
/// <param name="memorySizeInChunks">Returns the number of 32-bit chunks in the
/// memory block.</param>
/// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
/// success or failure.</returns>
DllExport DDR_ErrorCode DDR_GetMemorySize(int dataHandle, int* memorySizeInChunks);

/// <summary>
/// Read a single 32-bit value at the given offset in the memory block indicated
/// by the specified handle.
/// </summary>
/// <param name="dataHandle">Handle to a previously opened memory block as
/// obtained from the DDR_OpenMemoryBlock() function.</param>
/// <param name="chunkOffset">Offset into the memory block from which to get
/// the value (range is 0 to DDR_MAX_OFFSET-1).</param>
/// <param name="value">Returns the requested valued.</param>
/// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
/// success or failure.</returns>
DllExport DDR_ErrorCode DDR_GetDataChunk(int dataHandle, int chunkOffset, uint32_t* value);

/// <summary>
/// Writes a single 32-bit value to the given offset in the memory block indicated
/// by the specified handle.
/// </summary>
/// <param name="dataHandle">Handle to a previously opened memory block as
/// obtained from the DDR_OpenMemoryBlock() function.</param>
/// <param name="chunkOffset">Offset into the memory block to which to set
/// the value (range is 0 to DDR_MAX_OFFSET-1).</param>
/// <param name="value">The value to write to the memory block</param>
/// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
/// success or failure.</returns>
DllExport DDR_ErrorCode DDR_SetDataChunk(int dataHandle, int chunkOffset, uint32_t value);

#endif // __ADAPTER_BACKENDFUNCTIONS_H__
