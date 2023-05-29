## @file
#  @brief
#  The @ref DesignPatternExamples_python.adapter.adapter_frontendclass.DataReaderWriter "DataReaderWriter"
#  class used in the @ref adapter_pattern.

from ctypes import sizeof, c_uint32
from io import StringIO
from enum import Enum
from math import trunc

from .adapter_backendfunctions import *

## Represents an error that occurred during initialization or shut down of
#  the Data reader/writer.
class DataReaderWriterInitException(Exception):
    pass


## Represents an error that occurred when reading or writing data in the
#  Data reader/writer.
class DataReaderWriterException(Exception):
    pass


## Represents the memory blocks that can be accessed.  Hides how memory blocks
#  are actually identified.
class MemoryBlock(Enum):
    ## Represents the first memory block.
    MEMORY_BLOCK_0 = 0,
    ## Represents the second memory block.
    MEMORY_BLOCK_1 = 1,
    ## Represents the third memory block.
    MEMORY_BLOCK_2 = 2


## Represents a data reader/writer to a caller.
#  Adapts the functions from the @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.
#  To use:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  with DataReaderWriter(MemoryBlock.MEMORY_BLOCK_0) as dataReaderWriter:
#      pass
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class DataReaderWriter:

    ## Constructor
    #  @param blockNumber
    #         A value from the
    #         @ref DesignPatternExamples_python.adapter.adapter_frontendclass.MemoryBlock "MemoryBlock"
    #         enumeration indicating the block of memory to open.
    def __init__(self, blockNumber: MemoryBlock):
        self._initialized = False
        self._blockNumber = blockNumber
        self._dataHandle = Handle()
        self._memoryBlockByteSize = 0

    ## @var _initialized
    #       True if this instance has been initialized to use the
    #       specified memory block (by a call to __enter__())
    #  @var _blockNumber
    #       The number of the memory block to use.
    #  @var _dataHandle
    #       Contains the handle to the memory block after __enter__()
    #       has returned.
    #  @var _memoryBlockByteSize
    #       Holds the number of bytes in the opened memory block

    ## Entry function used in the `with` statement to initialize an instance
    #  of the reader/writer.
    def __enter__(self):
        block_name = self._GetBlockNameForBlockNumber(self._blockNumber)
        errorCode = ddr_openmemoryblock(block_name, self._dataHandle)
        if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
            value = ValueHandle()
            errorCode = ddr_getmemorysize(self._dataHandle, value)
            if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
                self._memoryBlockByteSize = value.value * sizeof(c_uint32)
                self._initialized = True
            else:
                msg = self._ConstructErrorMessage(errorCode, "Getting size of memory block")
                raise DataReaderWriterInitException(msg)
        else:
            msg = self._ConstructErrorMessage(errorCode, "Initializing data reader/writer")
            raise DataReaderWriterInitException(msg)
        return self


    ## Exit function automatically called when used in the `with` statement.
    def __exit__(self, *args):
        if self._initialized:
            ddr_closememoryblock(self._dataHandle)
            self._initialized = False


    ## Retrieve the size of the memory block in bytes.
    #
    #  @returns
    #    Returns the number of bytes available in the currently opened memory
    #    block.
    @property
    def MemoryBlockByteSize(self):
        if not self._initialized:
            msg = self._ConstructErrorMessage(DDR_ErrorCode.DDR_ErrorCode_Block_Not_Opened,
                                             "Memory block not opened so cannot retrieve memory block size")
            raise DataReaderWriterInitException(msg)
        return self._memoryBlockByteSize


    ## Given a value from the
    #  @ref DesignPatternExamples_python.adapter.adapter_frontendclass.MemoryBlock "MemoryBlock"
    #  enumeration that specifies the number of the block, return the name of
    #  the block as required by the low-level @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.
    def _GetBlockNameForBlockNumber(self, block_number: MemoryBlock):
        block_name = "unknown"

        if block_number == MemoryBlock.MEMORY_BLOCK_0:
            block_name = BLOCK_NAME_0
        elif block_number == MemoryBlock.MEMORY_BLOCK_1:
            block_name = BLOCK_NAME_1
        elif block_number == MemoryBlock.MEMORY_BLOCK_2:
            block_name = BLOCK_NAME_2
        return block_name


    ## Convert the given error code to a string message.
    #
    #  @param errorCode
    #         A value from the
    #         @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode DDR_ErrorCode"
    #         enumeration.
    #  @returns
    #    Returns a string describing the error.
    def _GetErrorMessage(self, errorCode: DDR_ErrorCode) -> str:
        message = "";

        match errorCode:
            case DDR_ErrorCode.DDR_ErrorCode_Success:
                message = "Operation succeeded";

            case DDR_ErrorCode.DDR_ErrorCode_Block_Already_Opened:
                message = "Memory block is already open and cannot be opened again";

            case DDR_ErrorCode.DDR_ErrorCode_Block_Not_Opened:
                message = "Memory block is closed and cannot be accessed";

            case DDR_ErrorCode.DDR_ErrorCode_Invalid_Block_Name:
                message = "The given name is not a recognized memory block name";

            case DDR_ErrorCode.DDR_ErrorCode_Invalid_Handle:
                message = "The handle argument does not correspond to a valid open memory block";

            case DDR_ErrorCode.DDR_ErrorCode_Invalid_Offset:
                message = "The given offset is out of bounds";

            case DDR_ErrorCode.DDR_ErrorCode_Null_Argument:
                message = "The block name pointer or return handle pointer argument is NULL";

            case _ :
                message = f"Unrecognized error code: {errorCode}"

        return message

    ## Creates a formatted error message from the given operation, using
    #  the given error code returned from the
    #  @ref Adapter_BackEnd.h "Adapter_BackEnd" DLL.
    #
    #  @param errorCode
    #         A value from the
    #         @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DDR_ErrorCode DDR_ErrorCode"
    #         enumeration.
    #  @param operation
    #         The operation that was in process when the error occurred.
    #
    #  @returns
    #    Returns an error message formatted as a string.
    def _ConstructErrorMessage(self, errorCode: int, operation : str) -> str:
        msg = self._GetErrorMessage(errorCode)
        return "{0}: {1}".format(operation, msg)


    ## Read a specified number of bytes.
    #
    #  @param byteOffset
    #         Byte offset into the memory block to which to start reading.
    #  @param maxBytes
    #         Number of bytes to read
    #
    #  @returns
    #    An array of bytes that were read.
    #
    #  @throws DataReaderWriterInitException Data reader/writer not initialized.
    #  @throws DataReaderWriterException Failed to read data.
    def Read(self, byteOffset: int, maxBytes : int) -> bytearray:
        if not self._initialized:
            raise DataReaderWriterInitException("Data reader/writer is not initialized.  Unable to read.");

        return_data = bytearray()
        if maxBytes > 0:
            chunkOffset = byteOffset // sizeof(c_uint32)
            value = ValueHandle()
            bufferIndex = 0
            errorCode = ddr_getdatachunk(self._dataHandle, chunkOffset, value)
            if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
                byteOffsetInChunk = byteOffset % sizeof(c_uint32)
                while bufferIndex < maxBytes:
                    return_data.append(value.value & 0xff)
                    bufferIndex += 1
                    value.value >>= 8
                    byteOffsetInChunk += 1
                    if byteOffsetInChunk == sizeof(c_uint32):
                        chunkOffset += 1
                        if chunkOffset >= DDR_MAX_OFFSET:
                            break
                        byteOffsetInChunk = 0
                        errorCode = ddr_getdatachunk(self._dataHandle, chunkOffset, value)
                        if errorCode != DDR_ErrorCode.DDR_ErrorCode_Success:
                            msg = self._ConstructErrorMessage(errorCode, "Reading memory")
                            raise DataReaderWriterException(msg)
            else:
                msg = self._ConstructErrorMessage(errorCode, "Reading memory")
                raise DataReaderWriterException(msg)

        return return_data


    ## Write a specified number of bytes.
    #
    #  @param byteOffset
    #         Byte offset into the memory block to which to start writing.
    #  @param data
    #         Array of bytes to write.  Must be at least `maxBytes` in length.
    #  @param maxBytes
    #         Number of bytes to write
    #
    #  @throws DataReaderWriterInitException Data reader/writer not initialized.
    #  @throws DataReaderWriterException Failed to write data.
    def Write(self, byteOffset: int, data : bytearray, maxBytes: int) -> None:
        if not self._initialized:
            raise DataReaderWriterInitException("Data reader/writer is not initialized.  Unable to write.");
        if maxBytes > 0:
            errorCode = DDR_ErrorCode.DDR_ErrorCode_Success
            chunkOffset = byteOffset // sizeof(c_uint32)
            value = ValueHandle()
            byteOffsetInChunk = int(byteOffset % sizeof(c_uint32))
            bufferIndex = 0
            byteMask = 0xff << (byteOffsetInChunk * 8)
            if byteOffsetInChunk != 0:
                errorCode = ddr_getdatachunk(self._dataHandle, chunkOffset, value)
            if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
                while bufferIndex < maxBytes:
                    value.value = value.value & (byteMask ^ 0xffffffff)
                    value.value = value.value | (data[bufferIndex] << (byteOffsetInChunk * 8))
                    bufferIndex += 1
                    byteMask <<= 8
                    byteOffsetInChunk += 1
                    if byteOffsetInChunk == sizeof(c_uint32):
                        errorCode = ddr_setdatachunk(self._dataHandle, chunkOffset, value.value)
                        if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
                            byteMask = 0xff
                            byteOffsetInChunk = 0
                            chunkOffset += 1
                            if chunkOffset >= DDR_MAX_OFFSET:
                                break
                            errorCode = ddr_getdatachunk(self._dataHandle, chunkOffset, value)
                            if errorCode != DDR_ErrorCode.DDR_ErrorCode_Success:
                                msg = self._ConstructErrorMessage(errorCode, "Reading memory")
                                raise DataReaderWriterException(msg)
                        else:
                            msg = self._ConstructErrorMessage(errorCode, "Writing memory")
                            raise DataReaderWriterException(msg)
                if errorCode == DDR_ErrorCode.DDR_ErrorCode_Success:
                    if byteOffsetInChunk != 0:
                        errorCode = ddr_setdatachunk(self._dataHandle, chunkOffset, value.value)

                if errorCode != DDR_ErrorCode.DDR_ErrorCode_Success:
                    msg = self._ConstructErrorMessage(errorCode, "Writing memory")
                    raise DataReaderWriterException(msg)
            else:
                msg = self._ConstructErrorMessage(errorCode, "Reading memory in preparation to writing memory")
                raise DataReaderWriterException(msg)


    ## Convert the specified data up to the specified number of bytes into
    #  a string by performing a "hex dump" on the data.
    #
    #  @param data
    #         The data to process.
    #  @param maxBytes
    #         The number of bytes from the data to process
    #  @param indent
    #         Number of spaces to indent each line.
    #  
    #  @returns
    #    A string containing the data in the form of a hex dump, possibly
    #    multiple lines.
    def BufferToString(self, data: bytearray, maxBytes : int, indent: int) -> str:
        output = StringIO()
        indent_spaces = ' ' * indent

        if maxBytes != 0:
            byteCount = maxBytes
            if byteCount > len(data):
                byteCount = len(data)
            bytesPerRow = 32
            for row in range(0, maxBytes, bytesPerRow):
                output.write("{}{:04x} --".format(indent_spaces, row))
                for col in range(0, bytesPerRow):
                    if (col + row) >= maxBytes:
                        break
                    if col > 0:
                        output.write(" ")
                    dataIndex = row + col
                    output.write("{:02x}".format(data[dataIndex]))
                output.write("\n")

        return output.getvalue()

