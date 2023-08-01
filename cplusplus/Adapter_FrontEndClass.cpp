/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::DataReaderWriter "DataReaderWriter"
/// class used in the @ref adapter_pattern.

#include <Adapter_BackEnd.h>

#include "helpers/formatstring.h"

#include "Adapter_FrontEndClass.h"

namespace // Anonymous namespace
{
    /// <summary>
    /// Convert the given error code to a string message.
    /// </summary>
    /// <param name="errorCode">A value from the DDR_ErrorCode enumeration.</param>
    /// <returns>A constant string describing the error.</returns>
    const char* _GetErrorMessage(DDR_ErrorCode errorCode)
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
    /// Creates a formatted error message from the given operation, using
    /// the error code from the Adapter_BackEnd library.
    /// </summary>
    /// <param name="errorCode">The error code from the underlying library
    /// to be converted to a string.</param>
    /// <param name="operation">The operation that was in process when the
    /// error occurred.</param>
    /// <returns>Returns an error message formatted as a string.</returns>
    std::string _ConstructErrorMessage(DDR_ErrorCode errorCode, const char* operation)
    {
        std::string msg = _GetErrorMessage(errorCode);
        return Helpers::formatstring("%s: %s", operation, msg.c_str());
    }

} // end anonymous namespace


//#############################################################################
//#############################################################################
//#############################################################################


namespace DesignPatternExamples_cpp
{
    ///////////////////////////////////////////////////////////////////////////
    // DataReaderWriter::_GetBlockNameForBlockNumber method
    ///////////////////////////////////////////////////////////////////////////
    const char* DataReaderWriter::_GetBlockNameForBlockNumber(MemoryBlockNumber blockNumber)
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


    ///////////////////////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////////////////////
    DataReaderWriter::DataReaderWriter(MemoryBlockNumber blockNumber)
        : _initialized(false)
        , _dataHandle(0)
    {
        const char* blockName = _GetBlockNameForBlockNumber(blockNumber);
        if (blockName != NULL)
        {
            DDR_ErrorCode errorCode = DDR_OpenMemoryBlock(blockName, &_dataHandle);
            if (errorCode == DDR_ErrorCode_Success)
            {
                int memorySizeInChunks = 0;
                errorCode = DDR_GetMemorySize(_dataHandle, &memorySizeInChunks);
                if (errorCode != DDR_ErrorCode_Success)
                {
                    std::string msg =
                        _ConstructErrorMessage(errorCode,
                            "Memory block not opened so cannot retrieve memory block size");
                    throw new DataReaderWriterInitException(msg);
                }
                _memoryBlockByteSize = static_cast<uint32_t>(memorySizeInChunks) * sizeof(uint32_t);
                _initialized = true;
            }
            else
            {
                std::string msg =
                    _ConstructErrorMessage(errorCode, "Initializing data reader/writer");
                throw new DataReaderWriterInitException(msg);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // Destructor
    ///////////////////////////////////////////////////////////////////////////
    DataReaderWriter::~DataReaderWriter()
    {
        if (_initialized)
        {
            (void)DDR_CloseMemoryBlock(_dataHandle);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    // DataReaderWriter::GetMemoryBlockByteSize
    ///////////////////////////////////////////////////////////////////////////
    uint32_t DataReaderWriter::GetMemoryBlockByteSize()
    {
        return _initialized ? _memoryBlockByteSize : 0;
    }

    ///////////////////////////////////////////////////////////////////////
    // DataReaderWriter::Read method
    ///////////////////////////////////////////////////////////////////////
    ByteArray DataReaderWriter::Read(int byteOffset, uint32_t maxBytes)
    {
        if (!_initialized)
        {
            throw new DataReaderWriterInitException(
                "Data reader/writer is not initialized.  Unable to read.");
        }

        ByteArray data(maxBytes);

        if (maxBytes > 0)
        {
            int chunkOffset = byteOffset / (sizeof(uint32_t));
            uint32_t value = 0;
            uint32_t bufferIndex = 0;
            DDR_ErrorCode errorCode = DDR_ErrorCode_Success;
            errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, &value);
            if (errorCode == DDR_ErrorCode_Success)
            {
                int byteOffsetInChunk = byteOffset % (sizeof(uint32_t));
                while (bufferIndex < maxBytes)
                {
                    data[bufferIndex] = value & 0xff;
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
                        errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, &value);
                        if (errorCode != DDR_ErrorCode_Success)
                        {
                            std::string msg = _ConstructErrorMessage(errorCode, "Reading memory");
                            throw new DataReaderWriterException(msg);
                        }
                    }
                }
                if (errorCode == DDR_ErrorCode_Success)
                {
                    if (bufferIndex > 0) {
                        if (static_cast<uint32_t>(bufferIndex) > maxBytes) {
                            data.resize(bufferIndex);
                        }
                    }
                }
            }
            else
            {
                std::string msg = _ConstructErrorMessage(errorCode, "Reading memory");
                throw new DataReaderWriterException(msg);
            }
        }

        return data;
    }

    ///////////////////////////////////////////////////////////////////////
    // DataReaderWriter::Write method
    ///////////////////////////////////////////////////////////////////////
    void DataReaderWriter::Write(int byteOffset, const ByteArray& data, uint32_t maxBytes)
    {
        if (!_initialized)
        {
            throw new DataReaderWriterInitException(
                "Data reader/writer is not initialized.  Unable to write.");
        }
        if (maxBytes > 0)
        {
            DDR_ErrorCode errorCode = DDR_ErrorCode_Success;
            int chunkOffset = byteOffset / sizeof(uint32_t);
            uint32_t value = 0;
            int byteOffsetInChunk = byteOffset % sizeof(uint32_t);
            uint32_t bufferIndex = 0;
            uint32_t byteMask = 0xff << (byteOffsetInChunk * 8);
            if (byteOffsetInChunk != 0)
            {
                errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, &value);
            }
            if (errorCode == DDR_ErrorCode_Success)
            {
                while (bufferIndex < maxBytes)
                {
                    value &= ~byteMask;
                    value |= ((uint32_t)data[bufferIndex]) << (byteOffsetInChunk * 8);
                    bufferIndex++;
                    byteMask <<= 8;
                    byteOffsetInChunk++;
                    if (byteOffsetInChunk == sizeof(uint32_t))
                    {
                        errorCode = DDR_SetDataChunk(_dataHandle, chunkOffset, value);
                        if (errorCode == DDR_ErrorCode_Success)
                        {
                            byteMask = 0xff;
                            byteOffsetInChunk = 0;
                            chunkOffset++;
                            if (chunkOffset >= DDR_MAX_OFFSET)
                            {
                                break;
                            }
                            errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, &value);
                            if (errorCode != DDR_ErrorCode_Success)
                            {
                                break;
                            }
                        }
                        else
                        {
                            std::string msg = _ConstructErrorMessage(errorCode, "Writing memory");
                            throw new DataReaderWriterException(msg);
                        }
                    }
                }
                if (errorCode == DDR_ErrorCode_Success)
                {
                    if (byteOffsetInChunk != 0)
                    {
                        errorCode = DDR_SetDataChunk(_dataHandle, chunkOffset, value);
                    }
                }
                if (errorCode != DDR_ErrorCode_Success)
                {
                    std::string msg = _ConstructErrorMessage(errorCode, "Writing memory");
                    throw new DataReaderWriterException(msg);
                }
            }
            else
            {
                std::string msg = _ConstructErrorMessage(errorCode, "Reading memory in preparation to writing memory");
                throw new DataReaderWriterException(msg);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    // DataReaderWriter::BufferToString method
    ///////////////////////////////////////////////////////////////////////
    std::string DataReaderWriter::BufferToString(const ByteArray& data,
        uint32_t maxBytes, int indent)
    {
        std::string output;
        std::string indentSpaces(indent, ' ');

        if (maxBytes != 0)
        {
            size_t byteCount = maxBytes;
            if (byteCount > data.size())
            {
                byteCount = data.size();
            }
            uint32_t bytesPerRow = 32;
            for (uint32_t row = 0; row < maxBytes; row += bytesPerRow)
            {
                output += Helpers::formatstring("%s%04x --", indentSpaces.c_str(), row);
                for (uint32_t col = 0;
                    col < bytesPerRow && (row + col) < maxBytes;
                    ++col)
                {
                    if (col > 0)
                    {
                        output += " ";
                    }
                    size_t dataIndex = static_cast<size_t>(row) + col;
                    output += Helpers::formatstring("%02x", data[dataIndex]);
                }
                output += "\n";
            }
        }
        return output;
    }

} // end namespace
