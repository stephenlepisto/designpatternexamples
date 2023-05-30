/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Adapter_Exercise "Adapter_Exercise"
/// class used in the @ref adapter_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref adapter_pattern in C#.
    /// 
    /// This example adapts functions that:
    /// 1. Accesses memory in 32-bit chunks instead of bytes
    /// 2. Returns error codes but no human-readable error messages
    /// 
    /// The @ref DesignPatternExamples_csharp.DataReaderWriter "DataReaderWriter"
    /// class translates the 32-bit chunk access into arrays of bytes.
    /// The DataReaderWriter class also provides human-readable messages
    /// for error codes.
    /// </summary>
    internal class Adapter_Exercise
    {
        /// <summary>
        /// Executes the example for the @ref adapter_pattern in C#.
        /// </summary>
        // ! [Using Adapter in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Adapter Exercise");
            try
            {
                // Will call Dispose() automatically when exiting the using block
                using (var dataReaderWriter = new DataReaderWriter(DataReaderWriter.MemoryBlockNumber.Memory_Block_0))
                {
                    uint memoryBlockSize = dataReaderWriter.MemoryBlockByteSize;
                    byte[] readData = dataReaderWriter.Read(0, memoryBlockSize);
                    string dataDump = dataReaderWriter.BufferToString(readData, memoryBlockSize, 2);
                    Console.WriteLine("  Initial memory block contents:{0}{1}", Environment.NewLine, dataDump);

                    // Create the data to be written
                    uint dataSize = 16;
                    int byteOffset = 41;
                    byte[] writeData = new byte[dataSize];
                    for (int index = 0; index < dataSize; ++index)
                    {
                        writeData[index] = (byte)(index + 1);
                    }

                    // Display the data to be written
                    dataDump = dataReaderWriter.BufferToString(writeData, dataSize, 2);
                    Console.WriteLine("  Data to be written to memory block:{0}{1}", Environment.NewLine, dataDump);

                    Console.WriteLine("  Writing data to byte offset {0}...", byteOffset);
                    // Write the data to the external component
                    dataReaderWriter.Write(byteOffset, writeData, dataSize);

                    Console.WriteLine("  Reading back the memory block...");
                    // Read the data from the external component
                    readData = dataReaderWriter.Read(0, memoryBlockSize);
                    Console.WriteLine();

                    // Display the data read back.  Should be the same as was written.
                    dataDump = dataReaderWriter.BufferToString(readData, memoryBlockSize, 2);
                    Console.WriteLine("  Current memory block contents:{0}{1}", Environment.NewLine, dataDump);
                }

            }
            catch (DataReaderWriterInitException e)
            {
                Console.WriteLine("Error with startup or shutdown! {0}", e.Message);
            }
            catch (DataReaderWriterException e)
            {
                Console.WriteLine("Error with reading or writing! {0}", e.Message);
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Adapter in C#]
    }
}
