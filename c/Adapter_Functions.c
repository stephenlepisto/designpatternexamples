/// @file
/// @brief
/// Implementation of the Adapter functions used
/// in the @ref adapter_pattern.

#include <stdio.h>
#include <string.h>

#include <Adapter_BackEnd.h>

#include "helpers/_countof.h"

#include "Adapter_Functions.h"

static char _lastError[128] = { 0 }; ///< Holds last error message
static char _hexdump[512] = { 0 }; ///< Collects hex dump as a single string. We do not expect more than about 424 bytes per hex dump.

/// <summary>
/// Given a block number, retrieve the corresponding block name.
/// </summary>
/// <param name="blockNumber">A value from the MemoryBlockNumber enumeration
/// indicating the block of memory to open.</param>
/// <returns>Returns a pointer to the block name if the block number is
/// recognized; otherwise returns NULL.</returns>
static const char* _GetBlockNameForBlockNumber(MemoryBlockNumber blockNumber)
{
    const char* blockName = NULL;

    switch (blockNumber)
    {
        case Memory_Block_0:
            blockName = BLOCK_NAME_0;
            break;

        case Memory_Block_1:
            blockName = BLOCK_NAME_1;
            break;

        case Memory_Block_2:
            blockName = BLOCK_NAME_2;
            break;

        default:
            break;
    }

    return blockName;
}

/// <summary>
/// Set the last error message to an empty string.  Call this before doing any
/// operation.
/// </summary>
static void _ResetLastError()
{
    _lastError[0] = '\0';
}

/// <summary>
/// Convert the given error code to a string message.
/// </summary>
/// <param name="errorCode">A value from the DDR_ErrorCode enumeration.</param>
/// <returns>A constant string describing the error.</returns>
static const char* _GetErrorMessage(DDR_ErrorCode errorCode)
{
    const char* message = "";

    switch (errorCode)
    {
        case DDR_ErrorCode_Success:
            message = "Operation succeeded";
            break;

        case DDR_ErrorCode_Block_Already_Opened:
            message = "Memory block is already open and cannot be opened again";
            break;

        case DDR_ErrorCode_Block_Not_Opened:
            message = "Memory block is closed and cannot be accessed";
            break;

        case DDR_ErrorCode_Invalid_Block_Name:
            message = "The given name is not a recognized memory block name";
            break;

        case DDR_ErrorCode_Invalid_Handle:
            message = "The handle argument does not correspond to a valid open memory block";
            break;

        case DDR_ErrorCode_Invalid_Offset:
            message = "The given offset is out of bounds";
            break;

        case DDR_ErrorCode_Null_Argument:
            message = "The block name pointer or return handle pointer argument is NULL";
            break;

        default:
            message = "Unrecognized error code.";
            break;
    }

    return message;
}

/// <summary>
/// Format the given message and prompt into a single error message string.
/// </summary>
/// <param name="message">The error message to report.  Cannot be NULL.</param>
/// <param name="prompt">A prompt that indicates the context in which the error
/// occurred.  Cannot be NULL.</param>
static void _ReportErrorMessage(const char* message, const char* prompt)
{
    snprintf(_lastError, _countof(_lastError), "Error! %s: %s.", prompt, message);
}


/// <summary>
/// Create a human-readable error message for the given error code, adding a
/// prompt to provide some context to the error.  Use the GetLastErrorMessage()
/// function to retrieve the string.
/// </summary>
/// <param name="errorCode">A value from the DDR_ErrorCode enumeration indicating
/// the error that occurred.</param>
/// <param name="prompt">A prompt that indicates the context in which the error
/// occurred.</param>
static void _ReportDDRError(DDR_ErrorCode errorCode, const char* prompt)
{
    const char* message = _GetErrorMessage(errorCode);

    if (prompt == NULL)
    {
        prompt = "";
    }
    _ReportErrorMessage(message, prompt);
}

/// <summary>
/// Report as an error an error code returned from the C library (typically
/// through a "safe" library function).
/// </summary>
/// <param name="errorCode">An error returned by a "safe" library function.</param>
/// <param name="prompt">A prompt that indicates the context in which the error
/// occurred.</param>
static void _ReportLibraryError(errno_t errorCode, const char* prompt)
{
    char buffer[80] = { 0 };

    errno_t err = strerror_s(buffer, sizeof(buffer), errorCode);
    if (err == 0)
    {
        _ReportErrorMessage(buffer, prompt);
    }
    else
    {
        _ReportErrorMessage("Failed to get error message", prompt);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Adapter_OpenMemory()
///////////////////////////////////////////////////////////////////////////////
bool Adapter_OpenMemory(MemoryBlockNumber blockNumber, int* dataHandle)
{
    bool openOkay = false;

    _ResetLastError();

    const char* blockName = _GetBlockNameForBlockNumber(blockNumber);
    if (blockName != NULL)
    {
        DDR_ErrorCode errorCode = DDR_OpenMemoryBlock(blockName, dataHandle);
        if (errorCode == DDR_ErrorCode_Success)
        {
            openOkay = true;
        }
        else
        {
            _ReportDDRError(errorCode, "Opening memory block");
        }
    }
    else
    {
        _ReportErrorMessage("Invalid block number", "Attempting to open memory block");
    }


    return openOkay;
}

///////////////////////////////////////////////////////////////////////////////
// Adapter_CloseMemory()
///////////////////////////////////////////////////////////////////////////////
bool Adapter_CloseMemory(int dataHandle)
{
    bool closeOkay = true;

    _ResetLastError();

    DDR_ErrorCode errorCode = DDR_CloseMemoryBlock(dataHandle);
    if (errorCode != DDR_ErrorCode_Success)
    {
        _ReportDDRError(errorCode, "Attempting to close memory block");
    }
    return closeOkay;
}


///////////////////////////////////////////////////////////////////////////////
// Adapter_GetMemorySize()
///////////////////////////////////////////////////////////////////////////////
bool Adapter_GetMemorySize(int dataHandle, int* sizeInBytes)
{
    bool sizeOkay = false;

    _ResetLastError();

    if (sizeInBytes != NULL)
    {
        int chunkSize = 0;
        DDR_ErrorCode errorCode = DDR_GetMemorySize(dataHandle, &chunkSize);
        if (errorCode == DDR_ErrorCode_Success)
        {
            *sizeInBytes = chunkSize * sizeof(uint32_t);
            sizeOkay = true;
        }
        else
        {
            _ReportDDRError(errorCode, "Getting memory size");
        }
    }
    else
    {
        _ReportErrorMessage("'sizeInBytes' parameter is NULL", "Attempting to get memory size");
    }

    return sizeOkay;
}


///////////////////////////////////////////////////////////////////////////////
// Adapter_ReadMemory()
///////////////////////////////////////////////////////////////////////////////
bool Adapter_ReadMemory(int dataHandle, int byteOffset, uint8_t* buffer, int maxBytes, int* bytesRead)
{
    bool readOkay = false;

    _ResetLastError();

    if (buffer != NULL)
    {
        if (maxBytes > 0)
        {
            int chunkOffset = byteOffset / (sizeof(uint32_t));
            uint32_t value = 0;
            int bufferIndex = 0;
            DDR_ErrorCode errorCode = DDR_ErrorCode_Success;
            errorCode = DDR_GetDataChunk(dataHandle, chunkOffset, &value);
            if (errorCode == DDR_ErrorCode_Success)
            {
                int byteOffsetInChunk = byteOffset % (sizeof(uint32_t));
                while (bufferIndex < maxBytes)
                {
                    buffer[bufferIndex] = value & 0xff;
                    bufferIndex++;
                    value >>= 8;
                    byteOffsetInChunk++;
                    if (byteOffsetInChunk == sizeof(uint32_t))
                    {
                        chunkOffset++;
                        if (chunkOffset >= DDR_MAX_OFFSET)
                        {
                            break;
                        }
                        byteOffsetInChunk = 0;
                        errorCode = DDR_GetDataChunk(dataHandle, chunkOffset, &value);
                        if (errorCode != DDR_ErrorCode_Success)
                        {
                            _ReportDDRError(errorCode, "Reading memory");
                            break;
                        }
                    }
                }
                if (errorCode == DDR_ErrorCode_Success)
                {
                    if (bytesRead != NULL)
                    {
                        *bytesRead = bufferIndex;
                        readOkay = true;
                    }
                }
            }
            else
            {
                _ReportDDRError(errorCode, "Reading memory");
            }
        }
        else
        {
            readOkay = true;
        }
    }
    else
    {
        _ReportErrorMessage("'buffer' parameter is NULL", "Attempting to read memory");
    }

    return readOkay;
}


///////////////////////////////////////////////////////////////////////////////
// Adapter_WriteMemory()
///////////////////////////////////////////////////////////////////////////////
bool Adapter_WriteMemory(int dataHandle, int byteOffset, const uint8_t* buffer, int maxBytes, int* bytesWritten)
{
    bool writeOkay = false;

    _ResetLastError();

    if (buffer != NULL)
    {
        if (maxBytes > 0)
        {
            DDR_ErrorCode errorCode = DDR_ErrorCode_Success;
            int chunkOffset = byteOffset / sizeof(uint32_t);
            uint32_t value = 0;
            int byteOffsetInChunk = byteOffset % sizeof(uint32_t);
            int bufferIndex = 0;
            uint32_t byteMask = 0xff << (byteOffsetInChunk * 8);
            if (byteOffsetInChunk != 0)
            {
                errorCode = DDR_GetDataChunk(dataHandle, chunkOffset, &value);
            }
            if (errorCode == DDR_ErrorCode_Success)
            {
                while (bufferIndex < maxBytes)
                {
                    value &= ~byteMask;
                    value |= ((uint32_t)buffer[bufferIndex]) << (byteOffsetInChunk * 8);
                    bufferIndex++;
                    byteMask <<= 8;
                    byteOffsetInChunk++;
                    if (byteOffsetInChunk == sizeof(uint32_t))
                    {
                        errorCode = DDR_SetDataChunk(dataHandle, chunkOffset, value);
                        if (errorCode == DDR_ErrorCode_Success)
                        {
                            byteMask = 0xff;
                            byteOffsetInChunk = 0;
                            chunkOffset++;
                            if (chunkOffset >= DDR_MAX_OFFSET)
                            {
                                writeOkay = true;
                                break;
                            }
                            errorCode = DDR_GetDataChunk(dataHandle, chunkOffset, &value);
                            if (errorCode != DDR_ErrorCode_Success)
                            {
                                break;
                            }
                        }
                        else
                        {
                            _ReportDDRError(errorCode, "Writing memory");
                            break;
                        }
                    }
                }
                if (errorCode == DDR_ErrorCode_Success)
                {
                    if (byteOffsetInChunk != 0)
                    {
                        errorCode = DDR_SetDataChunk(dataHandle, chunkOffset, value);
                    }
                }
                if (errorCode == DDR_ErrorCode_Success)
                {
                    if (bytesWritten != NULL)
                    {
                        *bytesWritten = bufferIndex;
                    }
                    writeOkay = true;
                }
                else
                {
                    _ReportDDRError(errorCode, "Writing memory");
                }
            }
            else
            {
                _ReportDDRError(errorCode, "Reading memory in preparation to writing memory");
            }
        }
        else
        {
            writeOkay = true;
        }
    }
    else
    {
        _ReportErrorMessage("'buffer' parameter is NULL", "Attempting to write memory");
    }

    return writeOkay;
}


///////////////////////////////////////////////////////////////////////////////
// Adapter_GetLastErrorMessage()
///////////////////////////////////////////////////////////////////////////////
const char* Adapter_GetLastErrorMessage()
{
    return _lastError;
}


///////////////////////////////////////////////////////////////////////////////
// Adapter_BufferToString()
///////////////////////////////////////////////////////////////////////////////
const char* Adapter_BufferToString(const uint8_t* data, uint32_t maxBytes, int indent)
{
    char* hexdumpstring = _hexdump;
    hexdumpstring[0] = '\0';

    if (data != NULL && maxBytes > 0)
    {
        char indentation[10] = { 0 };
        if (indent > _countof(indentation) - 1)
        {
            indent = _countof(indentation) - 1;
        }
        errno_t err = strncpy_s(indentation, sizeof(indentation), "          ", indent);
        if (err != 0)
        {
            _ReportLibraryError(err, "Creating indentation for hex dump");
            hexdumpstring = NULL;
        }
        else
        {
            uint32_t bytesPerRow = 32;
            char stringBuffer[192] = { 0 };
            for (uint32_t row = 0; row < maxBytes; row += bytesPerRow)
            {
                int numCharsAdded = sprintf_s(stringBuffer, sizeof(stringBuffer), "%s%04x --", indentation, row);
                if (numCharsAdded == -1)
                {
                    _ReportLibraryError(errno, "Formatting hex dump address");
                    hexdumpstring = NULL;
                    break;
                }
                err = strcat_s(_hexdump, sizeof(_hexdump), stringBuffer);
                if (err != 0)
                {
                    _ReportLibraryError(err, "Adding address to hex dump buffer");
                    hexdumpstring = NULL;
                    break;
                }
                for (uint32_t col = 0; col < bytesPerRow && (row + col) < maxBytes; col++)
                {
                    char* prompt = col > 0 ? " %02x" : "%02x";
                    uint32_t dataIndex = row + col;
                    numCharsAdded = sprintf_s(stringBuffer, sizeof(stringBuffer), prompt, (int)data[dataIndex]);
                    if (numCharsAdded == -1)
                    {
                        _ReportLibraryError(err, "Formatting hex data");
                        hexdumpstring = NULL;
                        break;
                    }
                    err = strcat_s(_hexdump, sizeof(_hexdump), stringBuffer);
                    if (err != 0)
                    {
                        _ReportLibraryError(err, "Adding hex data to hex dump buffer");
                        hexdumpstring = NULL;
                        break;
                    }
                }
                if (err != 0)
                {
                    break;
                }
                strcat_s(_hexdump, sizeof(_hexdump), "\n");
            }
        }
    }
    return hexdumpstring;
}
