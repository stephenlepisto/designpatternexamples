/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::DataReaderWriter "DataReaderWriter"
/// class used in the @ref adapter_pattern "Adapter pattern".

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
            , exception(message.c_str())
        {
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
            , exception(message.c_str())
        {
        }
    };


    /// <summary>
    /// Represents a data reader/writer to a caller.
    /// </summary>
    /// <remarks>Wraps the DataReaderWriterFunctions.</remarks>
    class DataReaderWriter
    {
    private:
        bool _initialized;
        int _dataHandle;

    private:
        /// <summary>
        /// Creates a formatted error message from the given operation, using
        /// the last error message from the DataReaderWriterFunctions library.
        /// </summary>
        /// <param name="operation">The operation that was in process when the
        /// error occurred.</param>
        /// <returns>Returns an error message formatted as a string.</returns>
        std::string _ConstructErrorMessage(const char* operation);

    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="init">String used for initializing the data
        /// reader/writer.</param>
        DataReaderWriter(const char* init);

        /// <summary>
        /// Destructor.
        /// </summary>
        ~DataReaderWriter();

        /// <summary>
        /// Read a specified number of bytes.
        /// </summary>
        /// <param name="maxBytes">Number of bytes to read</param>
        /// <returns>An array of bytes that were read.</returns>
        /// <exception cref="DataReaderWriterInitException">
        /// Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">
        /// Failed to read data.</exception>
        ByteArray Read(uint32_t maxBytes);

        /// <summary>
        /// Write a specified number of bytes.
        /// </summary>
        /// <param name="data">Array of bytes to write.  Must be at least
        /// 'maxBytes' in length.</param>
        /// <param name="maxBytes">Number of bytes to write</param>
        /// <exception cref="DataReaderWriterInitException">
        /// Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">
        /// Failed to write data.</exception>
        void Write(const ByteArray& data, uint32_t maxBytes);

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
