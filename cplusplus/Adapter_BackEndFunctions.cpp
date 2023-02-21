#include <map>
#include "Adapter_BackEndFunctions.h"

// Stuff defined in this anonymous namespace cannot be seen outside this module.
namespace // Anonymous
{
    /// <summary>
    /// Error code returned by the Data Read/Write functions. 
    /// </summary>
    /// <remarks>The caller would consult a reference manual for these
    /// error codes or get them from a header file.  These are defined here
    /// for this example to make it clear error codes are being returned.
    /// The caller can use GetLastErrorMessage() to translate the error
    /// code to a human-readable string.
    /// </remarks>
    enum ErrorCodes
    {
        NoError = 0,
        InvalidParameter = 1,
        AlreadyShutDown = 2,
        AlreadyStarted = 3,
        InvalidDataHandle = 4
    };


    /// <summary>
    /// A dictionary mapping a string name to a buffer of bytes.
    /// </summary>
    std::map<std::string, std::vector<uint8_t> > _localData;

    /// <summary>
    /// A dictionary mapping an integer token to a string (the name used
    /// in the _localData dictionary).  The token is returned to the caller.
    /// </summary>
    std::map<int, std::string> _handleToKey;

    /// <summary>
    /// The next token to allocate.
    /// </summary>
    int _nextKey = 0;

    /// <summary>
    /// The last error code set by a function.
    /// </summary>
    ErrorCodes _lastErrorCode;


} // end namespace


namespace DesignPatternExamples
{
    namespace DataReadWriteFunctions
    {
        ///////////////////////////////////////////////////////////////////////
        // Initialize the data reader/writer.
        ///////////////////////////////////////////////////////////////////////
        int Startup(std::string initData, int* dataHandle)
        {
            _lastErrorCode = ErrorCodes::InvalidParameter;
            if (dataHandle != nullptr)
            {
                _lastErrorCode = ErrorCodes::AlreadyStarted;
                *dataHandle = -1;
                if (_localData.find(initData) == std::end(_localData))
                {
                    // Generate a buffer of integers to use as the initial data
                    // that in turn is associated with the initData name.
                    std::vector<uint8_t> data(128);
                    for (size_t index = 0; index < data.size(); ++index)
                    {
                        // Reverse order of numbers.
                        data[index] = (uint8_t)(data.size() - index);
                    }
                    _localData[initData] = data;

                    // Now generate a token (a handle) for the initData buffer
                    // and return it.
                    *dataHandle = _nextKey;
                    ++_nextKey;
                    _handleToKey[*dataHandle] = initData;
                    _lastErrorCode = ErrorCodes::NoError;
                }
            }
            return (int)_lastErrorCode;
        }


        ///////////////////////////////////////////////////////////////////////
        // Shut down the data reader/writer.
        ///////////////////////////////////////////////////////////////////////
        int Shutdown(int dataHandle)
        {
            _lastErrorCode = ErrorCodes::AlreadyShutDown;

            if (_handleToKey.find(dataHandle) != std::end(_handleToKey))
            {
                _localData.erase(_handleToKey[dataHandle]);
                _handleToKey.erase(dataHandle);
                _lastErrorCode = ErrorCodes::NoError;
            }

            return (int)_lastErrorCode;
        }


        ///////////////////////////////////////////////////////////////////////
        // Retrieve the message related to the last error reported as a string.
        ///////////////////////////////////////////////////////////////////////
        std::string GetLastErrorMessage()
        {
            std::string errorMessage = "";
            switch (_lastErrorCode)
            {
            case ErrorCodes::NoError:
                break;

            case ErrorCodes::InvalidParameter:
                errorMessage = "Invalid parameter";
                break;

            case ErrorCodes::AlreadyShutDown:
                errorMessage = "Data reader/writer already shut down.";
                break;

            case ErrorCodes::AlreadyStarted:
                errorMessage = "Data reader/writer already started.";
                break;

            case ErrorCodes::InvalidDataHandle:
                errorMessage = "Invalid data handle";
                break;

            default:
                errorMessage = "Unknown error";
                break;
            }
            return errorMessage;
        }


        ///////////////////////////////////////////////////////////////////////
        // Write a block of bytes to the target.
        ///////////////////////////////////////////////////////////////////////
        int WriteData(int dataHandle, const uint8_t* data, uint32_t dataLength)
        {
            _lastErrorCode = ErrorCodes::InvalidParameter;

            if (data != nullptr)
            {
                _lastErrorCode = ErrorCodes::InvalidDataHandle;
                if (_handleToKey.find(dataHandle) != std::end(_handleToKey))
                {
                    std::vector<uint8_t>& localData =
                        _localData[_handleToKey[dataHandle]];
                    if (dataLength > localData.size())
                    {
                        localData.resize(dataLength);
                    }

                    for (uint32_t index = 0; index < dataLength; ++index)
                    {
                        localData[index] = data[index];
                    }
                    _lastErrorCode = ErrorCodes::NoError;
                }
            }

            return (int)_lastErrorCode;
        }


        ///////////////////////////////////////////////////////////////////////
        // Read a block of bytes from the target.
        ///////////////////////////////////////////////////////////////////////
        int ReadData(int dataHandle, uint32_t maxDataLength, uint8_t* data,
            uint32_t* availableDataLength)
        {
            _lastErrorCode = ErrorCodes::InvalidParameter;

            if (availableDataLength != nullptr)
            {
                *availableDataLength = 0;
                _lastErrorCode = ErrorCodes::InvalidDataHandle;
                if (_handleToKey.find(dataHandle) != std::end(_handleToKey))
                {
                    std::vector<uint8_t>& localData =
                        _localData[_handleToKey[dataHandle]];
                    *availableDataLength = (uint32_t)localData.size();

                    // Note: data parameter is allowed to be null
                    _lastErrorCode = ErrorCodes::NoError;
                    if (data != nullptr)
                    {
                        _lastErrorCode = ErrorCodes::InvalidParameter;
                        // If buffer is large enough to contain the requested
                        // data then
                        if (*availableDataLength >= maxDataLength)
                        {
                            // Read only up to the amount available
                            uint32_t byteCount = maxDataLength > localData.size()
                                ? (uint32_t)localData.size() : maxDataLength;
                            for (uint32_t index = 0; index < byteCount; ++index)
                            {
                                data[index] = localData[index];
                            }
                            _lastErrorCode = ErrorCodes::NoError;
                        }
                    }
                }
            }
            return (int)_lastErrorCode;
        }

    } // end namespace

} // end namespace
