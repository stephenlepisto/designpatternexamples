/// @file
/// @brief
/// Declaration of the Adapter functions used
/// in the @ref adapter_pattern.

#pragma once
#ifndef __ADAPTER_FUNCTIONS_H__
#define __ADAPTER_FUNCTIONS_H__

#include <stdbool.h>
#include <stdint.h>

/// <summary>
/// Represents the memory blocks that can be accessed.  Hides how memory blocks
/// are actually identified.
/// </summary>
typedef enum
{
    Memory_Block_0 = 0,  ///< First block
    Memory_Block_1 = 1,  ///< Second block
    Memory_Block_2 = 2,  ///< Third block
} MemoryBlockNumber;

/// <summary>
/// Open a memory block for access.
/// </summary>
/// <param name="blockNumber">A value from the MemoryBlockNumber enumeration
/// indicating which memory block to access.</param>
/// <param name="dataHandle">Returns the handle to the memory block to access.</param>
/// <returns>Returns true if all went well; otherwise, returns false, use
/// AdapterGetLastErrorMessage() to get the reason for the failure.</returns>
bool Adapter_OpenMemory(MemoryBlockNumber blockNumber, int* dataHandle);

/// <summary>
/// Closes a memory block from access.
/// </summary>
/// <param name="dataHandle">The handle returned from Adapter_OpenMemory() to be
/// closed.</param>
/// <returns>Returns true if all went well; otherwise, returns false, use
/// AdapterGetLastErrorMessage() to get the reason for the failure.</returns>
bool Adapter_CloseMemory(int dataHandle);

/// <summary>
/// Retrieve the number of bytes in the memory block associated with the
/// specified data handle
/// </summary>
/// <param name="dataHandle">The handle returned from Adapter_OpenMemory() to
/// access.</param>
/// <param name="sizeInBytes">Returns the number of bytes available to access.</param>
/// <returns>Returns true if all went well; otherwise, returns false, use
/// AdapterGetLastErrorMessage() to get the reason for the failure.</returns>
bool Adapter_GetMemorySize(int dataHandle, int* sizeInBytes);

/// <summary>
/// Read a requested number of bytes from the memory block associated with the
/// given handle.
/// </summary>
/// <param name="dataHandle">The handle returned from Adapter_OpenMemory() to
/// access.</param>
/// <param name="byteOffset">Byte offset into the memory block from which to start
/// reading.</param>
/// <param name="buffer">Buffer to fill with bytes from the memory block.</param>
/// <param name="maxBytes">The number of bytes to read.</param>
/// <param name="bytesRead">if not NULL, returns the number of bytes actually
/// read.</param>
/// <returns>Returns true if all went well; otherwise, returns false, use
/// AdapterGetLastErrorMessage() to get the reason for the failure.</returns>
bool Adapter_ReadMemory(int dataHandle, int byteOffset, uint8_t* buffer, int maxBytes, int* bytesRead);

/// <summary>
/// Write a requested number of bytes to the memory block associated with the
/// given handle.
/// </summary>
/// <param name="dataHandle">The handle returned from Adapter_OpenMemory() to
/// access.</param>
/// <param name="byteOffset">Byte offset into the memory block to which to start
/// writing.</param>
/// <param name="buffer">Buffer of bytes to write to the memory block.</param>
/// <param name="maxBytes">The number of bytes to write.</param>
/// <param name="bytesWritten">If not NULL, returns the number of bytes actually
/// written.</param>
/// <returns>Returns true if all went well; otherwise, returns false, use
/// AdapterGetLastErrorMessage() to get the reason for the failure.</returns>
bool Adapter_WriteMemory(int dataHandle, int byteOffset, const uint8_t* buffer, int maxBytes, int* bytesWritten);

/// <summary>
/// Retrieve a string describing the last error that occurred in the Adapter.
/// </summary>
/// <returns>A string containing an error message.  Remains valid until the next
/// Adapter operation that is called.</returns>
const char* Adapter_GetLastErrorMessage(void);

/// <summary>
/// Convert the specified data up to the specified number of bytes into
/// a string by performing a "hex dump" on the data.
/// </summary>
/// <param name="data">The data to process.</param>
/// <param name="maxBytes">The number of bytes from the data to process.</param>
/// <param name="indent">Number of spaces to indent each line.</param>
/// <returns>A string containing the data in the form of a hex dump, possibly
/// multiple lines.</returns>
const char* Adapter_BufferToString(const uint8_t* data, uint32_t maxBytes, int indent);

#endif // __ADAPTER_FUNCTIONS_H__
