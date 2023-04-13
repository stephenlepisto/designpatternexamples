/// @file
/// @brief
/// Implementation of the memory read/write functions
/// as used in the @ref adapter_pattern.

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "Adapter_BackEndFunctions.h"

/// <summary>
/// Maximum number of 32-bit chunks in a single memory block.
/// </summary>
#define MAX_DATA_SIZE 32

/// <summary>
/// Represents a single memory block.
/// </summary>
typedef struct
{
    /// <summary>
    /// Name of a memory block so it can be addressed individually.
    /// </summary>
    const char* name;

    /// <summary>
    /// True if a caller has acquired this memory block for exclusive access;
    /// otherwise, false, memory cannot be accessed.
    /// </summary>
    bool locked;                   

    /// <summary>
    /// Data held in this memory block, stored as 32-bit values.  Least significant
    /// byte is first byte of each value.
    /// </summary>
    uint32_t data[MAX_DATA_SIZE];
} MemoryBlock;

/// <summary>
/// Predefined set of memory blocks that can be accessed by name. Data for each
/// memory block is stored as a set of 32-bit values and can only be accessed
/// as a 32-bit quantity.
/// </summary>
static MemoryBlock memory_blocks[] = {
    { BLOCK_NAME_0, false, { 0 } },
    { BLOCK_NAME_1, false, { 0 } },
    { BLOCK_NAME_2, false, { 0 } }
};


static size_t memory_block_count = _countof(memory_blocks);

/// <summary>
/// Retrieve the index of the requested memory block.
/// </summary>
/// <param name="blockName">Name of the block to find</param>
/// <returns>Returns the index to the memory block if found; otherwise, returns
/// -1, indicating the block was not found.</returns>
static int _FindBlock(const char* blockName)
{
    int foundIndex = -1;

    for (size_t index = 0; index < memory_block_count; index++)
    {
        if (strcmp(memory_blocks[index].name, blockName) == 0)
        {
            foundIndex = (int)index;
            break;
        }
    }
    return foundIndex;
}

/// <summary>
/// Convert the given data handle to an index into the memory blocks.
/// </summary>
/// <param name="dataHandle">Data handle as returned from the DDR_OpenMemoryBlock()
/// function.</param>
/// <param name="memoryIndex">Returns the index into the memory blocks if the
/// data handle is valid.</param>
/// <returns>Returns true if the data handle is valid and was converted to an
/// index; otherwise, returns false.</returns>
static bool _ConvertHandleToBlockIndex(int dataHandle, int* memoryIndex)
{
    bool isValidHandle = false;

    if (memoryIndex != NULL)
    {
        int index = dataHandle;
        if (index >= 0 && index < (int)memory_block_count)
        {
            *memoryIndex = index;
            isValidHandle = true;
        }
    }

    return isValidHandle;
}


/// <summary>
/// Determine if the given offset is valid.
/// </summary>
/// <param name="chunkOffset">Offset into a memory block to verify.</param>
/// <returns>Returns true if the offset is valid; otherwise, returns false,
/// the offset is out of bounds.</returns>
static bool _IsValidOffset(int chunkOffset)
{
    return chunkOffset >= 0 && chunkOffset < DDR_MAX_OFFSET;
}

///////////////////////////////////////////////////////////////////////////////
// DDR_OpenMemoryBlock()
///////////////////////////////////////////////////////////////////////////////
DDR_ErrorCode DDR_OpenMemoryBlock(const char* blockName, int* dataHandle)
{
    DDR_ErrorCode errorCode = DDR_ErrorCode_Null_Argument;

    if (blockName != NULL && dataHandle != NULL)
    {
        *dataHandle = DDR_INVALID_HANDLE;
        errorCode = DDR_ErrorCode_Invalid_Block_Name;
        int foundBlockIndex = _FindBlock(blockName);
        if (foundBlockIndex != -1)
        {
            errorCode = DDR_ErrorCode_Block_Already_Opened;
            if (!memory_blocks[foundBlockIndex].locked)
            {
                memory_blocks[foundBlockIndex].locked = true;
                // Note: We are using the index as the handle
                *dataHandle = foundBlockIndex;
                errorCode = DDR_ErrorCode_Success;
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// DDR_CloseMemoryBlock()
///////////////////////////////////////////////////////////////////////////////
DDR_ErrorCode DDR_CloseMemoryBlock(int dataHandle)
{
    DDR_ErrorCode errorCode = DDR_ErrorCode_Invalid_Handle;

    int memoryIndex = -1;
    if (_ConvertHandleToBlockIndex(dataHandle, &memoryIndex))
    {
        errorCode = DDR_ErrorCode_Block_Not_Opened;
        if (memory_blocks[memoryIndex].locked)
        {
            memory_blocks[memoryIndex].locked = false;
            errorCode = DDR_ErrorCode_Success;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// DDR_GetMemorySize()
///////////////////////////////////////////////////////////////////////////////
DDR_ErrorCode DDR_GetMemorySize(int dataHandle, int* memorySizeInChunks)
{
    DDR_ErrorCode errorCode = DDR_ErrorCode_Null_Argument;
    if (memorySizeInChunks != NULL)
    {
        errorCode = DDR_ErrorCode_Invalid_Handle;
        int memoryIndex = -1;
        if (_ConvertHandleToBlockIndex(dataHandle, &memoryIndex))
        {
            *memorySizeInChunks = MAX_DATA_SIZE;
            errorCode = DDR_ErrorCode_Success;
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// DDR_GetDataChunk()
///////////////////////////////////////////////////////////////////////////////
DDR_ErrorCode DDR_GetDataChunk(int dataHandle, int chunkOffset, uint32_t* value)
{
    DDR_ErrorCode errorCode = DDR_ErrorCode_Null_Argument;

    if (value != NULL)
    {
        int memoryIndex = -1;
        if (_ConvertHandleToBlockIndex(dataHandle, &memoryIndex))
        {
            errorCode = DDR_ErrorCode_Block_Not_Opened;
            if (memory_blocks[memoryIndex].locked)
            {
                errorCode = DDR_ErrorCode_Invalid_Offset;
                if (_IsValidOffset(chunkOffset))
                {
                    *value = memory_blocks[memoryIndex].data[chunkOffset];
                    errorCode = DDR_ErrorCode_Success;
                }
            }
        }
    }

    return errorCode;
}

///////////////////////////////////////////////////////////////////////////////
// DDR_SetDataChunk()
///////////////////////////////////////////////////////////////////////////////
DDR_ErrorCode DDR_SetDataChunk(int dataHandle, int chunkOffset, uint32_t value)
{
    DDR_ErrorCode errorCode = DDR_ErrorCode_Invalid_Handle;
    int memoryIndex = -1;
    if (_ConvertHandleToBlockIndex(dataHandle, &memoryIndex))
    {
        errorCode = DDR_ErrorCode_Block_Not_Opened;
        if (memory_blocks[memoryIndex].locked)
        {
            errorCode = DDR_ErrorCode_Invalid_Offset;
            if (_IsValidOffset(chunkOffset))
            {
                memory_blocks[memoryIndex].data[chunkOffset] = value;
                errorCode = DDR_ErrorCode_Success;
            }
        }
    }

    return errorCode;
}
