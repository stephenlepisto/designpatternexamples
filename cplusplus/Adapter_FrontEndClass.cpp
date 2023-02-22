// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include "Adapter_FrontEndClass.h"
#include "Adapter_BackEndFunctions.h"


namespace DesignPatternExamples
{
    ///////////////////////////////////////////////////////////////////////////
    // DataReaderWriter::_ConstructErrorMessage method
    ///////////////////////////////////////////////////////////////////////////
    std::string DataReaderWriter::_ConstructErrorMessage(const char* operation)
    {
        std::string msg = DataReadWriteFunctions::GetLastErrorMessage();
        return std::format("{0}: {1}", operation, msg);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////////////////////////////////
    DataReaderWriter::DataReaderWriter(const char* init)
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

    ///////////////////////////////////////////////////////////////////////////
    // Destructor
    ///////////////////////////////////////////////////////////////////////////
    DataReaderWriter::~DataReaderWriter()
    {
        if (_initialized)
        {
            DataReadWriteFunctions::Shutdown(_dataHandle);
        }
    }


    ///////////////////////////////////////////////////////////////////////
    // DataReaderWriter::Read method
    ///////////////////////////////////////////////////////////////////////
    ByteArray DataReaderWriter::Read(uint32_t maxBytes)
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

        ByteArray data(availableByteCount);

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
    // DataReaderWriter::Write method
    ///////////////////////////////////////////////////////////////////////
    void DataReaderWriter::Write(const ByteArray& data, uint32_t maxBytes)
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
    // DataReaderWriter::BufferToString method
    ///////////////////////////////////////////////////////////////////////
    std::string DataReaderWriter::BufferToString(const ByteArray& data,
        uint32_t maxBytes, int indent)
    {
        std::string output;
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
                output += std::format("{}{:04x} --", indentSpaces, row);
                for (uint32_t col = 0;
                    col < bytesPerRow && (row + col) < maxBytes;
                    ++col)
                {
                    if (col > 0)
                    {
                        output += " ";
                    }
                    size_t dataIndex = static_cast<size_t>(row) + col;
                    output += std::format("{:02x}", data[dataIndex]);
                }
                output += "\n";
            }
        }
        return output;
    }

} // end namespace
