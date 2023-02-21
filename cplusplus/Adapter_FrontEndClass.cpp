#include <sstream>
#include <iomanip>
#include "Adapter.h"
#include "Adapter_BackEndFunctions.h"

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents a concrete instance of a DataReaderWriter interface.
    /// </summary>
    class DataReaderWriterImpl : public IDataReaderWriter
    {
    private:
        bool _initialized;
        int _dataHandle;

    private:
        /// <summary>
        /// Creates a formatted error message from the given operation, using
        /// the last error message from the DataReaderWriterFunctions library.
        /// </summary>
        /// <param name="operation">The operation that was in process when the
        /// error occurred.</param>
        /// <returns>Returns an error message formatted as a string.</returns>
        std::string _ConstructErrorMessage(const char* operation)
        {
            std::ostringstream output;

            std::string msg = DataReadWriteFunctions::GetLastErrorMessage();
            output << operation << ": " << msg;

            return output.str();
        }

    public:
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="init">String used to initialize the underlying
        /// data reader/writer functions.</param>
        DataReaderWriterImpl(const char* init)
            : _initialized(false)
            , _dataHandle(0)
        {
            int errorCode = DataReadWriteFunctions::Startup(init, &_dataHandle);
            if (errorCode == 0)
            {
                _initialized = true;
            }
            else
            {
                std::string msg =
                    _ConstructErrorMessage("Initializing data reader/writer");
                throw new DataReaderWriterInitException(msg);
            }
        }


        ///////////////////////////////////////////////////////////////////////
        // IDataReaderWriter interface methods
        ///////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////////////////////////////////
        // Read a specified number of bytes.
        ///////////////////////////////////////////////////////////////////////
        std::vector<uint8_t> Read(uint32_t maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException(
                    "Data reader/writer is not initialized.  Unable to read.");
            }

            uint32_t availableByteCount = 0;
            int errorCode = DataReadWriteFunctions::ReadData(_dataHandle, 0,
                nullptr, &availableByteCount);

            if (errorCode != 0)
            {
                std::string msg = _ConstructErrorMessage("Preparing to read data");
                throw new DataReaderWriterException(msg);
            }

            std::vector<uint8_t> data(availableByteCount);

            errorCode = DataReadWriteFunctions::ReadData(_dataHandle, maxBytes,
                &data[0], &availableByteCount);
            if (errorCode != 0)
            {
                std::string msg = _ConstructErrorMessage("Reading data");
                throw new DataReaderWriterException(msg);
            }

            return data;
        }

        ///////////////////////////////////////////////////////////////////////
        // Write a specified number of bytes.
        ///////////////////////////////////////////////////////////////////////
        void Write(const std::vector<uint8_t>& data, uint32_t maxBytes)
        {
            if (!_initialized)
            {
                throw new DataReaderWriterInitException(
                    "Data reader/writer is not initialized.  Unable to write.");
            }
            int errorCode = DataReadWriteFunctions::WriteData(_dataHandle,
                &data[0], maxBytes);
            if (errorCode != 0)
            {
                std::string msg = _ConstructErrorMessage("Writing data");
                throw new DataReaderWriterException(msg);
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // Convert the specified data up to the specified number of bytes into a
        // string by performing a "hex dump" on the data.
        ///////////////////////////////////////////////////////////////////////
        std::string BufferToString(const std::vector<uint8_t>& data,
            uint32_t maxBytes, int indent)
        {
            std::ostringstream output;
            std::string indentSpaces(indent, ' ');

            if (maxBytes != 0)
            {
                size_t byteCount = maxBytes;
                if (byteCount > data.size())
                {
                    byteCount = data.size();
                }
                uint32_t bytesPerRow = 32;
                for (uint32_t row = 0; row < maxBytes; row += bytesPerRow)
                {
                    output << indentSpaces << std::hex << std::setw(4)
                           << std::setfill('0')
                           << row
                           << std::dec << "--";
                    for (uint32_t col = 0;
                        col < bytesPerRow && (row + col) < maxBytes;
                        ++col)
                    {
                        if (col > 0)
                        {
                            output << " ";
                        }
                        size_t dataIndex = static_cast<size_t>(row) + col;
                        output << std::hex << std::setw(2) << std::setfill('0')
                               << static_cast<int>(data[dataIndex]);
                    }
                    output << std::endl;
                }
            }
            return output.str();
        }
    };


    //########################################################################
    //########################################################################

    //////////////////////////////////////////////////////////////////////////
    // Class factory to generate a DataReaderWriter object.
    //////////////////////////////////////////////////////////////////////////

    std::unique_ptr<IDataReaderWriter> CreateDataReaderWriter(const char* init)
    {
        return std::make_unique<DataReaderWriterImpl>(init);
    }

} // end namespace
