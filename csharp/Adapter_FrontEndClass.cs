/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.DataReaderWriter "DataReaderWriter"
/// class used in the @ref adapter_pattern "Adapter pattern".

using System;
using System.Collections;
using System.Text;
using static DesignPatternExamples_csharp.DataReadWriteFunctions;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents an error that occurred during initialization or shut down of the
    /// Data reader/writer.
    /// </summary>
    internal class DataReaderWriterInitException : Exception
    {
        public DataReaderWriterInitException(string msg)
            : base(msg)
        {
        }
    }


    /// <summary>
    /// Represents an error that occurred when reading or writing data in the
    /// Data reader/writer.
    /// </summary>
    internal class DataReaderWriterException : Exception
    {
        public DataReaderWriterException(string msg)
            : base(msg)
        {
        }
    }

    
    /// <summary>
    /// Represents a data reader/writer to a caller.
    /// </summary>
    /// <remarks>Wraps the DataReaderWriterFunctions.</remarks>
    internal class DataReaderWriter : IDisposable
    {
        /// <summary>
        /// Represents the memory blocks that can be accessed.  Hides how memory blocks
        /// are actually identified.
        /// </summary>
        public enum MemoryBlockNumber
        {
            Memory_Block_0 = 0,  ///< First block
            Memory_Block_1 = 1,  ///< Second block
            Memory_Block_2 = 2,  ///< Third block
        };

        private bool _disposed;
        private bool _initialized;
        private int _dataHandle;
        private uint _memoryBlockByteSize;

        /// <summary>
        /// Retrieve the size of the memory block in bytes.
        /// </summary>
        public uint MemoryBlockByteSize
        {
            get { return _memoryBlockByteSize; }
        }

        /// <summary>
        /// Helper function to convert a value from the @ref MemoryBlockNumber
        /// enumeration, which specifies the number of a memory block, into
        /// the name of the block as required by the low-level
        /// @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.</summary>
        /// <param name="blockNumber">Value from the MemoryBlockNumber enumeration
        /// for which to get the block name.</param>
        /// <returns>Returns a string containing the name of the block.</returns>
        private string _GetBlockNameForBlockNumber(MemoryBlockNumber blockNumber)
        {
            string blockName = "";

            switch (blockNumber)
            {
                case MemoryBlockNumber.Memory_Block_0:
                    blockName = BLOCK_NAME_0;
                    break;

                case MemoryBlockNumber.Memory_Block_1:
                    blockName = BLOCK_NAME_1;
                    break;

                case MemoryBlockNumber.Memory_Block_2:
                    blockName = BLOCK_NAME_2;
                    break;

                default:
                    break;
            }

            return blockName;
        }

        /// <summary>
        /// Convert the given error code to a string message.
        /// </summary>
        /// <param name="errorCode">A value from the DDR_ErrorCode enumeration.</param>
        /// <returns>A constant string describing the error.</returns>
        string _GetErrorMessage(DDR_ErrorCode errorCode)
        {
            string message = "";

            switch (errorCode)
            {
                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Success:
                    message = "Operation succeeded";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Block_Already_Opened:
                    message = "Memory block is already open and cannot be opened again";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Block_Not_Opened:
                    message = "Memory block is closed and cannot be accessed";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Invalid_Block_Name:
                    message = "The given name is not a recognized memory block name";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Invalid_Handle:
                    message = "The handle argument does not correspond to a valid open memory block";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Invalid_Offset:
                    message = "The given offset is out of bounds";
                    break;

                case DataReadWriteFunctions.DDR_ErrorCode.DDR_ErrorCode_Null_Argument:
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
        string _ConstructErrorMessage(DDR_ErrorCode errorCode, string operation)
        {
            string msg = _GetErrorMessage(errorCode);
            return String.Format("{0}: {1}", operation, msg);
        }


        /// <summary>
        /// Constructor for a data reader/writer
        /// </summary>
        /// <param name="blockNumber">A value from the MemoryBlockNumber enumeration
        /// indicating the block of memory to open.</param>
        /// <exception cref="DataReaderWriterInitException">Failed to initialize the data reader/writer.</exception>
        public DataReaderWriter(MemoryBlockNumber blockNumber)
        {
            _initialized = false;
            _dataHandle = -1;
            string blockName = _GetBlockNameForBlockNumber(blockNumber);
            if (!String.IsNullOrEmpty(blockName))
            {
                DataReadWriteFunctions.DDR_ErrorCode errorCode =
                    DataReadWriteFunctions.DDR_OpenMemoryBlock(blockName, out _dataHandle);
                if (errorCode == DDR_ErrorCode.DDR_ErrorCode_Success)
                {
                    int memorySizeInChunks = 0;
                    errorCode = DataReadWriteFunctions.DDR_GetMemorySize(_dataHandle, out memorySizeInChunks);
                    if (errorCode != DDR_ErrorCode.DDR_ErrorCode_Success)
                    {
                        string msg = _ConstructErrorMessage(errorCode,
                            "Memory block not opened so cannot retrieve memory block size");
                        throw new DataReaderWriterInitException(msg);
                    }
                    _memoryBlockByteSize = (uint)memorySizeInChunks * sizeof(UInt32);
                    _initialized = true;
                }
                else
                {
                    string msg = _ConstructErrorMessage(errorCode, "Initializing data reader/writer");
                    throw new DataReaderWriterInitException(msg);
                }
            }
        }


        /// <summary>
        /// Read a specified number of bytes.
        /// </summary>
        /// <param name="byteOffset">Byte offset into the memory block from
        /// which to start reading.</param>
        /// <param name="maxBytes">Number of bytes to read</param>
        /// <returns>An array of bytes that were read.</returns>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to read data.</exception>
        public byte[] Read(int byteOffset, uint maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException("Data reader/writer is not initialized.");
            }

            byte[] data = new byte[maxBytes];

            if (maxBytes > 0)
            {
                int chunkOffset = byteOffset / (sizeof(UInt32));
                UInt32 value = 0;
                UInt32 bufferIndex = 0;
                DDR_ErrorCode errorCode = DDR_ErrorCode.DDR_ErrorCode_Success;
                errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, out value);
                if (errorCode == DDR_ErrorCode.DDR_ErrorCode_Success)
                {
                    int byteOffsetInChunk = byteOffset % (sizeof(UInt32));
                    while (bufferIndex < maxBytes)
                    {
                        data[bufferIndex] = (byte) (value & 0xff);
                        bufferIndex++;
                        value >>= 8;
                        byteOffsetInChunk++;
                        if (byteOffsetInChunk == sizeof(UInt32))
                        {
                            chunkOffset++;
                            if (chunkOffset >= DataReadWriteFunctions.DDR_MAX_OFFSET)
                            {
                                break;
                            }
                            byteOffsetInChunk = 0;
                            errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, out value);
                            if (errorCode != DDR_ErrorCode.DDR_ErrorCode_Success)
                            {
                                string msg = _ConstructErrorMessage(errorCode, "Reading memory");
                                throw new DataReaderWriterException(msg);
                            }
                        }
                    }
                }
                else
                {
                    string msg = _ConstructErrorMessage(errorCode, "Reading memory");
                    throw new DataReaderWriterException(msg);
                }
            }

            return data;
        }

        /// <summary>
        /// Write a specified number of bytes.
        /// </summary>
        /// <param name="byteOffset">Byte offset into the memory block to which
        /// to start writing.</param>
        /// <param name="data">Array of bytes to write.  Must be at least 'maxBytes' in length.</param>
        /// <param name="maxBytes">Number of bytes to write</param>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to write data.</exception>
        public void Write(int byteOffset, byte[] data, uint maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException("Data reader/writer is not initialized.");
            }
            DDR_ErrorCode errorCode = DDR_ErrorCode.DDR_ErrorCode_Success;
            int chunkOffset = byteOffset / sizeof(UInt32);
            UInt32 value = 0;
            int byteOffsetInChunk = byteOffset % sizeof(UInt32);
            UInt32 bufferIndex = 0;
            UInt32 byteMask = (UInt32)0xff << (byteOffsetInChunk * 8);
            if (byteOffsetInChunk != 0)
            {
                errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, out value);
            }
            if (errorCode == DDR_ErrorCode.DDR_ErrorCode_Success)
            {
                while (bufferIndex < maxBytes)
                {
                    value &= ~byteMask;
                    value |= ((UInt32)data[bufferIndex]) << (byteOffsetInChunk * 8);
                    bufferIndex++;
                    byteMask <<= 8;
                    byteOffsetInChunk++;
                    if (byteOffsetInChunk == sizeof(UInt32))
                    {
                        errorCode = DDR_SetDataChunk(_dataHandle, chunkOffset, value);
                        if (errorCode == DDR_ErrorCode.DDR_ErrorCode_Success)
                        {
                            byteMask = 0xff;
                            byteOffsetInChunk = 0;
                            chunkOffset++;
                            if (chunkOffset >= DDR_MAX_OFFSET)
                            {
                                break;
                            }
                            errorCode = DDR_GetDataChunk(_dataHandle, chunkOffset, out value);
                            if (errorCode != DDR_ErrorCode.DDR_ErrorCode_Success)
                            {
                                break;
                            }
                        }
                        else
                        {
                            string msg = _ConstructErrorMessage(errorCode, "Writing memory");
                            throw new DataReaderWriterException(msg);
                        }
                    }
                }
                if (errorCode == DDR_ErrorCode.DDR_ErrorCode_Success)
                {
                    if (byteOffsetInChunk != 0)
                    {
                        errorCode = DDR_SetDataChunk(_dataHandle, chunkOffset, value);
                    }
                }
                if (errorCode != DDR_ErrorCode.DDR_ErrorCode_Success)
                {
                    string msg = _ConstructErrorMessage(errorCode, "Writing memory");
                    throw new DataReaderWriterException(msg);
                }
            }
            else
            {
                string msg = _ConstructErrorMessage(errorCode, "Reading memory in preparation to writing memory");
                throw new DataReaderWriterException(msg);
            }
        }


        /// <summary>
        /// Convert the specified data up to the specified number of bytes into a
        /// string by performing a "hex dump" on the data.
        /// </summary>
        /// <param name="data">The data to process.</param>
        /// <param name="maxBytes">The number of bytes from the data to process.</param>
        /// <param name="indent">Number of spaces to indent each line.</param>
        /// <returns>A string containing the data in the form of a hex dump, possibly
        /// multiple lines.</returns>
        public string BufferToString(byte[] data, uint maxBytes, int indent)
        {
            StringBuilder output = new StringBuilder();
            string indentSpaces = new string(' ', indent);

            if (data != null && maxBytes != 0)
            {
                int byteCount = (int)maxBytes;
                if (byteCount > data.Length)
                {
                    byteCount = data.Length;
                }
                int bytesPerRow = 32;
                for (int row = 0; row < maxBytes; row += bytesPerRow)
                {
                    output.AppendFormat("{0}{1:x4} --", indentSpaces, row);
                    for (int col = 0; col < bytesPerRow && (row + col) < maxBytes; ++col)
                    {
                        if (col > 0)
                        {
                            output.Append(' ');
                        }
                        output.AppendFormat("{0:x2}", data[row + col]);
                    }
                    output.Append(Environment.NewLine);
                }
            }
            return output.ToString();
        }

    
#region IDisposable Members

        /// <summary>
        /// Shut down the data reader/writer and dispose of resources.
        /// </summary>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        public void Dispose()
        {
 	        if (!_disposed)
            {
                if (_initialized)
                {
                    _initialized = false;
                    DDR_ErrorCode errorCode = DataReadWriteFunctions.DDR_CloseMemoryBlock(_dataHandle);
                    _dataHandle = -1;
                    if (errorCode != 0)
                    {
                        string msg = _ConstructErrorMessage(errorCode, "Shutting down data reader/writer");
                        throw new DataReaderWriterInitException(msg);
                    }
                }
                _disposed = true;
            }
        }

#endregion
    }
}
