// The Adapter design pattern is used when code written in one way needs to
// communicate with code written in a completely different way.
//
// For this example, the DataReadWriteFunctions class represents a library of
// functions that use error codes for reporting errors.  In a real C# program,
// the static methods on this class might actually be calls into an external
// DLL.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents some example functions for accessing a target to read/write data.
    /// </summary>
    internal static class DataReadWriteFunctions
    {
        /// <summary>
        /// A dictionary mapping a string name to a buffer of bytes.
        /// </summary>
        private static Dictionary<string, byte[]> _localData = new Dictionary<string, byte[]>();
        /// <summary>

        /// A dictionary mapping an integer token to a string (the name used
        /// in the _localData dictionary).  The token is returned to the caller.
        /// </summary>
        private static Dictionary<int, string> _handleToKey = new Dictionary<int, string>();

        /// <summary>
        /// The next token to allocate.
        /// </summary>
        private static int _nextKey = 0;

        /// <summary>
        /// The last error code set by a function.
        /// </summary>
        private static int _lastErrorCode;


        /// <summary>
        /// Initialize the data reader/writer.
        /// </summary>
        /// <param name="initData">Initialization string</param>
        /// <param name="dataHandle">Returns the handle representing the data reader/writer</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an error.</returns>
        public static int Startup(string initData, out int dataHandle)
        {
            _lastErrorCode = 3;
            dataHandle = -1;
            if (!_localData.ContainsKey(initData))
            {
                // Generate a buffer of integers to use as the initial data that
                // in turn is associated with the initData name.
                byte[] data = new byte[128];
                for (int index = 0; index < data.Length; ++index)
                {
                    // Reverse order of numbers.
                    data[index] = (byte)(data.Length - index);
                }
                _localData[initData] = data;

                // Now generate a token (a handle) for the initData buffer
                // and return it.
                dataHandle = _nextKey;
                ++_nextKey;
                _handleToKey[dataHandle] = initData;
                _lastErrorCode = 0;
            }

            return _lastErrorCode;
        }


        /// <summary>
        /// Shut down the data reader/writer.
        /// </summary>
        /// <param name="dataHandle">Handle to shut down</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an error.</returns>
        public static int Shutdown(int dataHandle)
        {
            _lastErrorCode = 2;

            if (_handleToKey.ContainsKey(dataHandle))
            {
                _localData.Remove(_handleToKey[dataHandle]);
                _handleToKey.Remove(dataHandle);
                _lastErrorCode = 0;
            }

            return _lastErrorCode;
        }


        /// <summary>
        /// Retrieve the message related to the last error reported as a string.
        /// </summary>
        /// <returns>A string containing the last error message.  Returns an empty string
        /// if there was no error.</returns>
        public static string GetLastErrorMessage()
        {
            string errorMessage = "";
            switch(_lastErrorCode)
            {
                case 0:
                    break;

                case 1:
                    errorMessage = "Invalid parameter";
                    break;
                
                case 2:
                    errorMessage = "Data reader/writer already shut down.";
                    break;

                case 3:
                    errorMessage = "Data reader/writer already started.";
                    break;

                case 4:
                    errorMessage = "Invalid data handle";
                    break;

                default:
                    errorMessage = "Unknown error";
                    break;
            }
            return errorMessage;
        }


        /// <summary>
        /// Write a block of bytes to the target.
        /// </summary>
        /// <param name="dataHandle">Handle to data reader/writer.</param>
        /// <param name="data">A block of data of at least 'dataLength' bytes.</param>
        /// <param name="dataLength">The number of bytes to write.</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an error.</returns>
        public static int WriteData(int dataHandle, byte[] data, uint dataLength)
        {
            _lastErrorCode = 1;

            if (data != null && data.Length <= dataLength)
            {
                _lastErrorCode = 4;
                if (_handleToKey.ContainsKey(dataHandle))
                {
                    byte[] localData = _localData[_handleToKey[dataHandle]];
                    if (dataLength > localData.Length)
                    {
                        localData = new byte[dataLength];
                    }

                    for (uint index = 0; index < dataLength; ++index)
                    {
                        localData[index] = data[index];
                    }
                    _lastErrorCode = 0;
                }
            }

            return _lastErrorCode;
        }


        /// <summary>
        /// Read a block of bytes from the target.
        /// </summary>
        /// <param name="dataHandle">Handle to data reader/writer.</param>
        /// <param name="maxDataLength">The maximum number of bytes to read.</param>
        /// <param name="data">The buffer to store the bytes.</param>
        /// <returns>0 if successful; otherwise, non-zero if there was an error.</returns>
        public static int ReadData(int dataHandle, uint maxDataLength, byte[] data, out uint availableDataLength)
        {
            _lastErrorCode = 4;

            availableDataLength = 0;
            if (_handleToKey.ContainsKey(dataHandle))
            {
                byte[] localData = _localData[_handleToKey[dataHandle]];
                availableDataLength = (uint)localData.Length;

                _lastErrorCode = 0;
                if (data != null)
                {
                    _lastErrorCode = 1;
                    // If buffer is large enough to contain the requested data then
                    if (data.Length >= maxDataLength)
                    {
                        // Read only up to the amount available
                        uint byteCount = maxDataLength > localData.Length ? (uint)localData.Length : maxDataLength;
                        for (uint index = 0; index < byteCount; ++index)
                        {
                            data[index] = localData[index];
                        }
                        _lastErrorCode = 0;
                    }
                }
            }

            return _lastErrorCode;
        }
    }
}
