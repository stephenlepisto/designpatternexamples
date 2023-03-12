## The @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DataReadWriteFunctions "DataReadWriteFunctions"
#  class used in the @ref adapter_pattern.

from enum import Enum

##  Error code returned by the Data Read/Write functions. 
#
#  The caller would consult a reference manual for these error codes or get
#  them from a header file.  These are defined here for this example to
#  make it clear error codes are being returned.  The caller can use
#  GetLastErrorMessage() to translate the error code to a human-readable
#  string.
class ErrorCodes(Enum):
    NoError = 0
    InvalidParameter = 1
    AlreadyShutDown = 2
    AlreadyStarted = 3
    InvalidDataHandle = 4


## Represents an opaque token or handle to data in the
#  @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DataReadWriteFunctions "DataReadWriteFunctions"
#  class.  Since a class is passed by reference in Python, a function such as
#  @ref DesignPatternExamples_python.adapter.adapter_backendfunctions.DataReadWriteFunctions.Startup() "Startup"()
#  can write to the handle to set its value.  Use the `value` attribute to read/write the handle.
class Handle(int):
    pass

##  A dictionary mapping a string name to a buffer of bytes.
_localData = {} # type: dict[str, bytearray]

## A dictionary mapping an integer token to a string (the name used
#  in the _localData dictionary).  The token is returned to the caller.
_handleToKey = {} # type: dict[int, str]

##  The next token to allocate.
_nextKey = 0 # type: int

##  The last error code set by a function.
_lastErrorCode = ErrorCodes.NoError


## Represents a collection of functions used for accessing some arbitrarily-
#  sized block of data.  These functions return error codes that need to
#  be adapted to exceptions by the Adapter design pattern wrapper.
class DataReadWriteFunctions:

    ##  Initialize the data reader/writer.
    #
    #  @param initData
    #         Initialization string
    #  @param dataHandle
    #         Returns the handle representing the data reader/writer
    #
    #  @returns
    #    Returns 0 if successful; otherwise, non-zero if there was an error.
    def Startup(initData : str, dataHandle : Handle) -> int:
        _lastErrorCode = ErrorCodes.InvalidParameter
        if dataHandle != None:
            _lastErrorCode = ErrorCodes.AlreadyStarted
            dataHandle.value = -1
            if not initData in _localData:
                # Generate a buffer of integers to use as the initial data
                # that in turn is associated with the initData name.
                data = bytearray(128)
                for index in range(0, len(data)):
                    # Reverse order of numbers.
                    data[index] = len(data) - index
                _localData[initData] = data

                # Now generate a token (a handle) for the initData buffer
                # and return it.
                dataHandle.value = _nextKey
                ++_nextKey
                _handleToKey[dataHandle.value] = initData
                _lastErrorCode = ErrorCodes.NoError
        return int(_lastErrorCode.value)


    ##  Shut down the data reader/writer.
    #
    #  @param dataHandle
    #         Handle to shut down
    #
    #  @returns
    #    Returns 0 if successful; otherwise, non-zero if there was an error.
    def Shutdown(dataHandle : Handle) -> int:
        _lastErrorCode = ErrorCodes.AlreadyShutDown

        if dataHandle.value in _handleToKey:
            del(_localData[_handleToKey[dataHandle.value]])
            del(_handleToKey[dataHandle.value])
            _lastErrorCode = ErrorCodes.NoError
        return int(_lastErrorCode.value)
 

    ##  Retrieve the message related to the last error reported as a string.
    #
    #  @returns
    #    A string containing the last error message.  Returns an empty string
    #    if there was no error.
    def GetLastErrorMessage() -> str:
        match _lastErrorCode:
            case ErrorCodes.NoError:
                return ""

            case ErrorCodes.InvalidParameter:
                return "Invalid parameter"

            case ErrorCodes.AlreadyShutDown:
                return "Data reader/writer already shut down."

            case ErrorCodes.AlreadyStarted:
                return "Data reader/writer already started."

            case ErrorCodes.InvalidDataHandle:
                return "Invalid data handle"

            case _:
                return "Unknown error: {}".format(_lastErrorCode)


    ##  Write a block of bytes to the target.
    #
    #  @param dataHandle
    #         Handle to data reader/writer.
    #  @param data
    #         A block of data of at least `dataLength` bytes.
    #  @param dataLength
    #         The number of bytes to write.
    #
    #  @returns
    #    Returns 0 if successful; otherwise, non-zero if there was an error.
    def WriteData(dataHandle : Handle, data: bytearray, dataLength: int) -> int:
        _lastErrorCode = ErrorCodes.InvalidParameter

        if data:
            _lastErrorCode = ErrorCodes.InvalidDataHandle
            if dataHandle.value in _handleToKey:
                localData = _localData[_handleToKey[dataHandle.value]]
                if dataLength > len(localData):
                    localData.extend(bytearray(dataLength - len(localData)))

                for index in range(0, dataLength):
                    localData[index] = data[index]
                _lastErrorCode = ErrorCodes.NoError
        return int(_lastErrorCode.value)


    ##  Read a block of bytes from the target.
    #
    #  @param dataHandle
    #         Handle to data reader/writer.
    #  @param maxDataLength
    #         The maximum number of bytes to read.
    #  @param data
    #         The buffer to store the bytes  Can be null if attempting to
    #         retrieve the amount of data available.
    #  @param availableDataLength
    #         A list by which the number of bytes available for reading is
    #         returned.  Cannot be None.
    #
    #  @returns
    #    Returns 0 if successful; otherwise, non-zero if there was an error.
    def ReadData(dataHandle : Handle, maxDataLength : int, data : bytearray,
        availableDataLength : list[int]) -> int:
        _lastErrorCode = ErrorCodes.InvalidParameter

        if availableDataLength is not None:
            if len(availableDataLength) == 0:
                availableDataLength.append(0)
            else:
                availableDataLength[0] = 0
            _lastErrorCode = ErrorCodes.InvalidDataHandle
            if dataHandle.value in _handleToKey:
                localData = _localData[_handleToKey[dataHandle.value]]
                availableDataLength[0] = len(localData)

                # Note: data parameter is allowed to be null
                _lastErrorCode = ErrorCodes.NoError
                if data is not None:
                    _lastErrorCode = ErrorCodes.InvalidParameter
                    # If buffer is large enough to contain the requested
                    # data then
                    if availableDataLength[0] >= maxDataLength:
                        # Read only up to the amount available
                        byteCount = len(localData) if maxDataLength > len(localData) else maxDataLength
                        for index in range(0, byteCount):
                            data[index] = localData[index]
                        _lastErrorCode = ErrorCodes.NoError

        return int(_lastErrorCode.value)
