/// @file
/// @brief
/// Implementation of the Adapter_Exercise() function as used in the 
/// @ref adapter_pattern "Adapter pattern".

#include <stdlib.h>
#include <stdio.h>

#include "Adapter_Exercise.h"

#include "Adapter_BackEndFunctions.h"

/// <summary>
/// Example of using the @ref adapter_pattern "Adapter" design pattern.
/// 
/// This example adapts functions that return error codes into a class
/// object that throws exceptions, which is more fitting of an object-
/// oriented language.
/// </summary>
// ! [Using Adapter in C]
void Adapter_Exercise()
{
    printf("\nAdapter_Exercise\n");

    int dataHandle = -1;
    int error = DDR_Startup("my init string", &dataHandle);
    if (error == 0)
    {
        uint8_t data[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        uint32_t dataSize = sizeof(data);
        error = DDR_WriteData(dataHandle, data, dataSize);
        if (error == 0)
        {
            uint8_t newData[16] = { 0 };
            uint32_t dataSize = sizeof(newData);
            uint32_t availableDataSize = 0;
            error = DDR_ReadData(dataHandle, dataSize, newData, &availableDataSize);
            if (error == 0)
            {
                for (uint32_t index = 0; index < dataSize; index++)
                {
                    printf("0x%0x ", newData[index]);
                }
                printf("\n");
            }
            else
            {
                const char* msg = DDR_GetLastErrorMessage();
                printf("DDR_ReadData() returned code %d (%s)\n", error, msg);
            }
        }
        else
        {
            const char* msg = DDR_GetLastErrorMessage();
            printf("DDR_WriteData() returned code %d (%s)\n", error, msg);
        }
    }
    error = DDR_Shutdown(dataHandle);
    if (error != 0)
    {
        const char* msg = DDR_GetLastErrorMessage();
        printf("DDR_Shutdown() returned code %d (%s)\n", error, msg);
    }

    printf("  Done.\n");
}
// ! [Using Adapter in C++]

