/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::DataReaderWriter "DataReaderWriter"
/// class used in the @ref adapter_pattern.

#pragma once
#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include <exception>
#include <string>
#include <vector>
#include <stdint.h>

namespace DesignPatternExamples_cpp
{

    // Represents an array of 8-bit values or bytes.
    typedef std::vector<uint8_t> ByteArray;


    /// <summary>
    /// Represents an error that occurred during initialization or shut down of
    /// the Data reader/writer.
    /// </summary>
    class DataReaderWriterInitException : public std::exception
    {
    private:
        std::string message;
    public:
        DataReaderWriterInitException(std::string msg)
            : message(msg)
        {
        }

        /// <summary>
        /// Override exception::what() to return the message we are tracking.
        /// </summary>
        const char* what()
        {
            return message.c_str();
        }
    };


    /// <summary>
    /// Represents an error that occurred when reading or writing data in the
    /// Data reader/writer.
    /// </summary>
    class DataReaderWriterException : public std::exception
    {
    private:
        std::string message;
    public:
        DataReaderWriterException(std::string msg)
            : message(msg)
        {
        }

        /// <summary>
        /// Override exception::what() to return the message we are tracking.
        /// </summary>
        const char *what()
        {
            return message.c_str();
        }
    };

    /// <summary>
    /// Represents a data reader/writer to a caller.
    /// </summary>
    /// <remarks>Wraps the Adapter_BackEnd dynamic library.</remarks>
    class DataReaderWriter
    {
    public:
        /// <summary>
        /// Represents the memory blocks that can be accessed.  Hides how memory blocks
        /// are actually identified.
        /// </summary>
        enum MemoryBlockNumber
        {
            Memory_Block_0 = 0,  ///< First block
            Memory_Block_1 = 1,  ///< Second block
            Memory_Block_2 = 2,  ///< Third block
        };

    private:
        bool _initialized;
        int _dataHandle;
        uint32_t _memoryBlockByteSize;

    private:
        /// <summary>
        /// Given a block number, retrieve the corresponding block name.
        /// </summary>
        /// <param name="blockNumber">A value from the MemoryBlockNumber enumeration
        /// indicating the block of memory to open.</param>
        /// <returns>Returns a pointer to the block name if the block number is
        /// recognized; otherwise returns NULL.</returns>
        const char* _GetBlockNameForBlockNumber(DataReaderWriter::MemoryBlockNumber blockNumber);

    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="blockNumber">A value from the MemoryBlockNumber enumeration
        /// indicating which memory block to access.</param>
        DataReaderWriter(MemoryBlockNumber blockNumber);

        /// <summary>
        /// Destructor.
        /// </summary>
        ~DataReaderWriter();

        /// <summary>
        /// Retrieve the size of the currently opened memory block in bytes.
        /// </summary>
        /// <returns>The size of memory block in bytes.</returns>
        uint32_t GetMemoryBlockByteSize();

        /// <summary>
        /// Read a specified number of bytes.
        /// </summary>
        /// <param name="byteOffset">Byte offset into the memory block from
        /// which to start reading.</param>
        /// <param name="maxBytes">Number of bytes to read</param>
        /// <returns>An array of bytes that were read.</returns>
        /// <exception cref="DataReaderWriterInitException">
        /// Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">
        /// Failed to read data.</exception>
        ByteArray Read(int byteOffset, uint32_t maxBytes);

        /// <summary>
        /// Write a specified number of bytes.
        /// </summary>
        /// <param name="byteOffset">Byte offset into the memory block to which
        /// to start writing.</param>
        /// <param name="data">Array of bytes to write.  Must be at least
        /// 'maxBytes' in length.</param>
        /// <param name="maxBytes">Number of bytes to write</param>
        /// <exception cref="DataReaderWriterInitException">
        /// Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">
        /// Failed to write data.</exception>
        void Write(int byteOffset, const ByteArray& data, uint32_t maxBytes);

        /// <summary>
        /// Convert the specified data up to the specified number of bytes into
        /// a string by performing a "hex dump" on the data.
        /// </summary>
        /// <param name="data">The data to process.</param>
        /// <param name="maxBytes">The number of bytes from the data to
        /// process.</param>
        /// <param name="indent">Number of spaces to indent each line.</param>
        /// <returns>A string containing the data in the form of a hex dump,
        /// possibly multiple lines.</returns>
        std::string BufferToString(const ByteArray& data, uint32_t maxBytes,
            int indent);
    };

} // end namespace

#endif // __ADAPTER_H__
