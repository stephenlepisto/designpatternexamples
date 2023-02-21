#pragma once
#ifndef __ADAPTER_BACKENDFUNCTIONS_H__
#define __ADAPTER_BACKENDFUNCTIONS_H__

#include <string>
#include <vector>
#include <stdint.h>

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents a collection of functions used for accessing some arbitrarily-
    /// sized block of data.  These functions return error codes that need to
    /// be adapted to exceptions by the Adapter design pattern wrapper.
    /// </summary>
    namespace DataReadWriteFunctions
    {
        /// <summary>
        /// Initialize the data reader/writer.
        /// </summary>
        /// <param name="initData">Initialization string</param>
        /// <param name="dataHandle">Returns the handle representing the data
        /// reader/writer</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an
        /// error.</returns>
        int Startup(std::string initData, int* dataHandle);

        /// <summary>
        /// Shut down the data reader/writer.
        /// </summary>
        /// <param name="dataHandle">Handle to shut down</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an
        /// error.</returns>
        int Shutdown(int dataHandle);
        
        /// <summary>
        /// Retrieve the message related to the last error reported as a string.
        /// </summary>
        /// <returns>A string containing the last error message.  Returns an
        /// empty string if there was no error.</returns>
        std::string GetLastErrorMessage();
        
        /// <summary>
        /// Write a block of bytes to the target.
        /// </summary>
        /// <param name="dataHandle">Handle to data reader/writer.</param>
        /// <param name="data">A block of data of at least 'dataLength'
        /// bytes.</param>
        /// <param name="dataLength">The number of bytes to write.</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an
        /// error.</returns>
        int WriteData(int dataHandle, const uint8_t* data, uint32_t dataLength);
        
        /// <summary>
        /// Read a block of bytes from the target.
        /// </summary>
        /// <param name="dataHandle">Handle to data reader/writer.</param>
        /// <param name="maxDataLength">The maximum number of bytes to
        /// read.</param>
        /// <param name="data">The buffer to store the bytes  Can be null if
        /// attempting to retrieve the amount of data available.</param>
        /// <param name="availableDataLength">Returns the number of bytes
        /// available for reading.</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an
        /// error.</returns>
        int ReadData(int dataHandle, uint32_t maxDataLength, uint8_t* data,
            uint32_t* availableDataLength);

    } // end namespace

} // end namespace

#endif // __ADAPTER_BACKENDFUNCTIONS_H__

