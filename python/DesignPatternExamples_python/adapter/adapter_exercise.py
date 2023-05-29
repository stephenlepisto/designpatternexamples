## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.adapter.adapter_exercise.Adapter_Exercise "Adapter_Exercise"()
# function as used in the @ref adapter_pattern.

from .adapter_frontendclass import MemoryBlock, DataReaderWriter, DataReaderWriterException, DataReaderWriterInitException

## Example of using the @ref adapter_pattern.
# 
# This example adapts functions that return error codes into a class object
# that throws exceptions, which is more fitting of an object-oriented
# language.

# ! [Using Adapter in Python]
def Adapter_Exercise():
    print()
    print("Adapter Exercise")

    try:

        with DataReaderWriter(MemoryBlock.MEMORY_BLOCK_0) as dataReaderWriter:
            memoryBlockSize = dataReaderWriter.MemoryBlockByteSize
            # Create the data to be written
            dataSize = 16
            byteOffset = 41
            writeData = []
            for index in range(0, dataSize):
                writeData.append(index + 1)
                
            readData = dataReaderWriter.Read(0, memoryBlockSize)
            dataDump = dataReaderWriter.BufferToString(readData, memoryBlockSize, 2)
            print("  Initial memory block contents:")
            print(dataDump)

            # Display the data to be written
            dataDump = dataReaderWriter.BufferToString(writeData, len(writeData), 2)
            print("  Data to be written to memory block:")
            print(dataDump)

            print("  Writing data to byte offset {}...".format(byteOffset))
            # Write the data to the external component
            dataReaderWriter.Write(byteOffset, writeData, len(writeData))

            print("  Reading back the memory block...")
            # Read the data from the external component
            readData = dataReaderWriter.Read(0, memoryBlockSize)
            print()

            # Display the data read back.  Should be the same as was written.
            dataDump = dataReaderWriter.BufferToString(readData, memoryBlockSize, 2)
            print("  Current memory block contents:")
            print(dataDump)
    except DataReaderWriterInitException as ex:
        print("Error with startup or shutdown! {0}".format(ex))
    except DataReaderWriterException as ex:
        print("Error with reading or writing! {0}".format(ex))

    print("  Done.")
# ! [Using Adapter in Python]
