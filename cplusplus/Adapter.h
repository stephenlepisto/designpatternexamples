#pragma once
#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include <exception>
#include <memory>
#include <string>
#include <vector>
#include <stdint.h>

namespace DesignPatternExamples
{

    /// <summary>
    /// Represents an error that occurred during initialization or shut down of the
    /// Data reader/writer.
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
    struct DataReaderWriter
    {
        virtual ~DataReaderWriter() { }

        /// <summary>
        /// Read a specified number of bytes.
        /// </summary>
        /// <param name="maxBytes">Number of bytes to read</param>
        /// <returns>An array of bytes that were read.</returns>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to read data.</exception>
        virtual std::vector<uint8_t> Read(uint32_t maxBytes) = 0;

        /// <summary>
        /// Write a specified number of bytes.
        /// </summary>
        /// <param name="data">Array of bytes to write.  Must be at least 'maxBytes' in length.</param>
        /// <param name="maxBytes">Number of bytes to write</param>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to write data.</exception>
        virtual void Write(const std::vector<uint8_t>& data, uint32_t maxBytes) = 0;

        /// <summary>
        /// Convert the specified data up to the specified number of bytes into a
        /// string by performing a "hex dump" on the data.
        /// </summary>
        /// <param name="data">The data to process.</param>
        /// <param name="maxBytes">The number of bytes from the data to process.</param>
        /// <param name="indent">Number of spaces to indent each line.</param>
        /// <returns>A string containing the data in the form of a hex dump, possibly
        /// multiple lines.</returns>
        virtual std::string BufferToString(const std::vector<uint8_t>& data, uint32_t maxBytes, int indent) = 0;
    };

    /// <summary>
    /// Construct an instance of the DataReaderWriter interface.
    /// </summary>
    /// <param name="init">A string containing the initialization information.</param>
    /// <returns>A DataReaderWriter object</returns>
    std::unique_ptr<DataReaderWriter> CreateDataReaderWriter(const char* init);

} // end namespace

#endif // __ADAPTER_H__
