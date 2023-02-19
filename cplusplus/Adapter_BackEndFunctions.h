#pragma once
#ifndef __ADAPTER_BACKENDFUNCTIONS_H__
#define __ADAPTER_BACKENDFUNCTIONS_H__

#include <string>
#include <vector>
#include <stdint.h>

namespace DesignPatternExamples
{
    namespace DataReadWriteFunctions
    {
        int Startup(std::string initData, int* dataHandle);
        int Shutdown(int dataHandle);
        std::string GetLastErrorMessage();
        int WriteData(int dataHandle, const uint8_t* data, uint32_t dataLength);
        int ReadData(int dataHandle, uint32_t maxDataLength, uint8_t* data, uint32_t* availableDataLength);

    } // end namespace

} // end namespace

#endif // __ADAPTER_BACKENDFUNCTIONS_H__

