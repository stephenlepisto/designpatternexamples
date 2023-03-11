## @package adapter
#  The @ref DesignPatternExamples_python.adapter.adapter_frontendclass.DataReaderWriter "DataReaderWriter"
#  class used in the @ref adapter_pattern "Adapter pattern".

from io import StringIO

from .adapter_backendfunctions import DataReadWriteFunctions, Handle

## Represents an error that occurred during initialization or shut down of
#  the Data reader/writer.
class DataReaderWriterInitException(Exception):
    pass


## Represents an error that occurred when reading or writing data in the
#  Data reader/writer.
class DataReaderWriterException(Exception):
    pass



## Represents a data reader/writer to a caller.
#  Wraps the DataReaderWriterFunctions.  To use:
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.py}
#  with DataReaderWriter("initialization string") as dataReaderWriter:
#      pass
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class DataReaderWriter:
    
    ## Constructor
    #  @param initstring
    #         String used for initializing the data reader/writer.
    def __init__(self, initstring: str):
        self._initialized = False
        self._initstring = initstring
        self._dataHandle = Handle()

    ## Entry function used in the `with` statement to initialize an instance
    #  of the reader/writer.
    def __enter__(self):
        errorCode = DataReadWriteFunctions.Startup(self._initstring, self._dataHandle)
        if errorCode == 0:
            self._initialized = True
        else:
            msg = self._ConstructErrorMessage("Initializing data reader/writer")
            raise DataReaderWriterInitException(msg)
        return self


    ## Exit function automatically called when used in the `with` statement.
    def __exit__(self, *args):
        if self._initialized:
            DataReadWriteFunctions.Shutdown(self._dataHandle)
            self._initialized = False


    ## Creates a formatted error message from the given operation, using
    #  the last error message from the DataReaderWriterFunctions library.
    #
    #  @param operation
    #         The operation that was in process when the error occurred.
    #
    #  @returns
    #    Returns an error message formatted as a string.
    def _ConstructErrorMessage(self, operation : str) -> str:
        msg = DataReadWriteFunctions.GetLastErrorMessage()
        return "{0}: {1}".format(operation, msg)


    ## Read a specified number of bytes.
    #
    #  @param maxBytes
    #         Number of bytes to read
    #
    #  @returns
    #    An array of bytes that were read.
    #
    #  @throws DataReaderWriterInitException Data reader/writer not initialized.
    #  @throws DataReaderWriterException Failed to read data.
    def Read(self, maxBytes : int) -> bytearray:
        if not self._initialized:
            raise DataReaderWriterInitException("Data reader/writer is not initialized.  Unable to read.");

        available_bytes = []
        errorCode = DataReadWriteFunctions.ReadData(self._dataHandle, 0, None, available_bytes)
        if errorCode != 0:
            msg = self._ConstructErrorMessage("Preparing to read data")
            raise DataReaderWriterException(msg)

        bytes_to_read = available_bytes[0]
        return_data = bytearray(bytes_to_read)
        errorCode = DataReadWriteFunctions.ReadData(self._dataHandle, bytes_to_read, return_data, available_bytes)
        if errorCode != 0:
            msg = self._ConstructErrorMessage("Reading data")
            raise DataReaderWriterException(msg)
        return return_data


    ## Write a specified number of bytes.
    #
    #  @param data
    #         Array of bytes to write.  Must be at least `maxBytes` in length.
    #  @param maxBytes
    #         Number of bytes to write
    #
    #  @throws DataReaderWriterInitException Data reader/writer not initialized.
    #  @throws DataReaderWriterException Failed to write data.
    def Write(self, data : bytearray, maxBytes: int) -> None:
        if not self._initialized:
            raise DataReaderWriterInitException("Data reader/writer is not initialized.  Unable to write.");
        errorCode = DataReadWriteFunctions.WriteData(self._dataHandle, data, maxBytes)
        if errorCode != 0:
            msg = self._ConstructErrorMessage("Writing data")
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

