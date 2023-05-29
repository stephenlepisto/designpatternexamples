/// @file
/// @brief
/// Implementation of the Adapter_Exercise() function as used in the 
/// @ref adapter_pattern "Adapter pattern".

#include "Adapter_Exercise.h"

#include "Adapter_FrontEndClass.h"

#include <iostream>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref adapter_pattern.
    /// 
    /// This example adapts functions that return error codes into a class
    /// object that throws exceptions, which is more fitting of an object-
    /// oriented language.
    /// </summary>
    // ! [Using Adapter in C++]
    void Adapter_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Adapter Exercise" << std::endl;
        try
        {
            DataReaderWriter dataReaderWriter(DataReaderWriter::Memory_Block_0);

            uint32_t memoryBlockSize = dataReaderWriter.GetMemoryBlockByteSize();
            
            std::vector<uint8_t> readData = dataReaderWriter.Read(0, memoryBlockSize);
            std::string dataDump = 
                dataReaderWriter.BufferToString(readData, memoryBlockSize, 2);
            std::cout << "  Initial memory block contents:" << std::endl;
            std::cout << dataDump << std::endl;

            // Create the data to be written
            uint32_t dataSize = 16;
            int byteOffset = 41;
            std::vector<uint8_t> writeData(dataSize);
            for (uint32_t index = 0; index < dataSize; ++index)
            {
                writeData[index] = static_cast<uint8_t>(index+1);
            }

            // Display the data to be written
            dataDump = dataReaderWriter.BufferToString(writeData, dataSize, 2);
            std::cout << "  Data to be written to memory block:" << std::endl;
            std::cout << dataDump << std::endl;

            std::cout << "  Writing data to byte offset " << byteOffset << "..." << std::endl;
            // Write the data to the external component
            dataReaderWriter.Write(byteOffset, writeData, dataSize);

            std::cout << "  Reading back the memory block..." << std::endl;
            // Read the data from the external component
            readData = dataReaderWriter.Read(0, memoryBlockSize);
            std::cout << std::endl;

            // Display the data read back.
            dataDump = dataReaderWriter.BufferToString(readData, memoryBlockSize, 2);
            std::cout << "  Current memory block contents:" << std::endl;
            std::cout << dataDump << std::endl;
        }
        catch (DataReaderWriterInitException& e)
        {
            std::cout << "Error with startup or shutdown! " << e.what()
                << std::endl;
        }
        catch (DataReaderWriterException& e)
        {
            std::cout << "Error with reading or writing! " << e.what()
                << std::endl;
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Adapter in C++]


} // end namespace
