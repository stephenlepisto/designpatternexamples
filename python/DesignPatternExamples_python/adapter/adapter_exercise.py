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
        # Create the data to be written
        dataSize = 128
        writeData = []
        for index in range(0, dataSize):
            writeData.append(index)

        with DataReaderWriter(MemoryBlock.MEMORY_BLOCK_0) as dataReaderWriter:
            readData = dataReaderWriter.Read(0, dataSize)
            dataDump = dataReaderWriter.BufferToString(readData, dataSize, 2)
            print("  Initial data read:")
            print(dataDump)

            # Display the data to be written
            dataDump = dataReaderWriter.BufferToString(writeData, dataSize, 2)
            print("  Data to be written:")
            print(dataDump)

            # Write the data to the external component
            dataReaderWriter.Write(0, writeData, dataSize)

            # Read the data from the external component
            readData = dataReaderWriter.Read(0, dataSize)

            # Display the data read back.  Should be the same as was written.
            dataDump = dataReaderWriter.BufferToString(readData, dataSize, 2)
            print("  Data read:")
            print(dataDump)
    except DataReaderWriterInitException as ex:
        print("Error with startup or shutdown! {0}".format(ex))
    except DataReaderWriterException as ex:
        print("Error with reading or writing! {0}".format(ex))

    print("  Done.")
# ! [Using Adapter in Python]
