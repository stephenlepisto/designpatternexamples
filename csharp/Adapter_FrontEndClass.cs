// The Adapter design pattern is used when code written in one way needs to
// communicate with code written in a completely different way.  For example,
// an object-oriented program needs to call into a library of functions.  A
// related example is if the library produces error codes but the main program
// uses exceptions.  The Adapter design adapts a library with one calling
// convention to another convention, hiding the details of the library.
//
// In this example, the DataReaderWriter class provides an object-oriented
// interface to a set of functions.  The functions are static and return error
// codes.  The DataReaderWriter class is the Adapter, converting primitive
// function calls into an object-oriented class, complete with exceptions.

using System;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents an error that occurred during initialization or shut down of the
    /// Data reader/writer.
    /// </summary>
    internal class DataReaderWriterInitException : Exception
    {
        public DataReaderWriterInitException(string msg)
            : base(msg)
        {
        }
    }


    /// <summary>
    /// Represents an error that occurred when reading or writing data in the
    /// Data reader/writer.
    /// </summary>
    internal class DataReaderWriterException : Exception
    {
        public DataReaderWriterException(string msg)
            : base(msg)
        {
        }
    }

    
    /// <summary>
    /// Represents a data reader/writer to a caller.
    /// </summary>
    /// <remarks>Wraps the DataReaderWriterFunctions.</remarks>
    internal class DataReaderWriter : IDisposable
    {
        private bool _disposed;
        private bool _initialized;
        private int _dataHandle;

        /// <summary>
        /// Creates a formatted error message from the given operation, using
        /// the last error message from the DataReaderWriterFunctions library.
        /// </summary>
        /// <param name="operation">The operation that was in process when the
        /// error occurred.</param>
        /// <returns>Returns an error message formatted as a string.</returns>
        private string _ConstructErrorMessage(string operation)
        {
            StringBuilder output = new StringBuilder();
            string msg = DataReadWriteFunctions.GetLastErrorMessage();
            output.AppendFormat("{0}: {1}", operation, msg);

            return output.ToString();
        }


        /// <summary>
        /// Constructor for a data reader/writer
        /// </summary>
        /// <param name="init">Initialization string.</param>
        /// <exception cref="DataReaderWriterInitException">Failed to initialize the data reader/writer.</exception>
        public DataReaderWriter(string init)
        {
            int errorCode = DataReadWriteFunctions.Startup(init, out _dataHandle);
            if (errorCode == 0)
            {
                _initialized = true;
            }
            else
            {
                string msg = _ConstructErrorMessage("Initializing data reader/writer");
                throw new DataReaderWriterInitException(msg);
            }
        }


        /// <summary>
        /// Read a specified number of bytes.
        /// </summary>
        /// <param name="maxBytes">Number of bytes to read</param>
        /// <returns>An array of bytes that were read.</returns>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to read data.</exception>
        public byte[] Read(uint maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException("Data reader/writer is not initialized.");
            }

            uint availableByteCount = 0;
            int errorCode = DataReadWriteFunctions.ReadData(_dataHandle, 0, null, out availableByteCount);

            if (errorCode != 0)
            {
                string msg = _ConstructErrorMessage("Preparing to read data");
                throw new DataReaderWriterException(msg);
            }

            byte[] data = new byte[availableByteCount];

            errorCode = DataReadWriteFunctions.ReadData(_dataHandle, maxBytes, data, out availableByteCount);
            if (errorCode != 0)
            {
                string msg = _ConstructErrorMessage("Reading data");
                throw new DataReaderWriterException(msg);
            }

            return data;
        }

        /// <summary>
        /// Write a specified number of bytes.
        /// </summary>
        /// <param name="data">Array of bytes to write.  Must be at least 'maxBytes' in length.</param>
        /// <param name="maxBytes">Number of bytes to write</param>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        /// <exception cref="DataReaderWriterException">Failed to write data.</exception>
        public void Write(byte[] data, uint maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException("Data reader/writer is not initialized.");
            }
            int errorCode = DataReadWriteFunctions.WriteData(_dataHandle, data, maxBytes);
            if (errorCode != 0)
            {
                string msg = _ConstructErrorMessage("Writing data");
                throw new DataReaderWriterException(msg);
            }
        }


        /// <summary>
        /// Convert the specified data up to the specified number of bytes into a
        /// string by performing a "hex dump" on the data.
        /// </summary>
        /// <param name="data">The data to process.</param>
        /// <param name="maxBytes">The number of bytes from the data to process.</param>
        /// <param name="indent">Number of spaces to indent each line.</param>
        /// <returns>A string containing the data in the form of a hex dump, possibly
        /// multiple lines.</returns>
        public string BufferToString(byte[] data, uint maxBytes, int indent)
        {
            StringBuilder output = new StringBuilder();
            string indentSpaces = new string(' ', indent);

            if (data != null && maxBytes != 0)
            {
                int byteCount = (int)maxBytes;
                if (byteCount > data.Length)
                {
                    byteCount = data.Length;
                }
                int bytesPerRow = 32;
                for (int row = 0; row < maxBytes; row += bytesPerRow)
                {
                    output.AppendFormat("{0}{1:x4} --", indentSpaces, row);
                    for (int col = 0; col < bytesPerRow && (row + col) < maxBytes; ++col)
                    {
                        if (col > 0)
                        {
                            output.Append(' ');
                        }
                        output.AppendFormat("{0:x2}", data[row + col]);
                    }
                    output.Append(Environment.NewLine);
                }
            }
            return output.ToString();
        }

    
#region IDisposable Members

        /// <summary>
        /// Shut down the data reader/writer and dispose of resources.
        /// </summary>
        /// <exception cref="DataReaderWriterInitException">Data reader/writer not initialized.</exception>
        public void Dispose()
        {
 	        if (!_disposed)
            {
                if (_initialized)
                {
                    _initialized = false;
                    int errorCode = DataReadWriteFunctions.Shutdown(_dataHandle);
                    _dataHandle = -1;
                    if (errorCode != 0)
                    {
                        string msg = _ConstructErrorMessage("Shutting down data reader/writer");
                        throw new DataReaderWriterInitException(msg);
                    }
                }
                _disposed = true;
            }
        }

#endregion
    }
}
