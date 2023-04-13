/// @file
/// @brief
/// Implementation of the Adapter_Exercise() function as used in the 
/// @ref adapter_pattern.

#include <stdlib.h>
#include <stdio.h>

#include "Adapter_Exercise.h"

#include "Adapter_Functions.h"

/// <summary>
/// Example of using the @ref adapter_pattern "Adapter" design pattern in C.
/// 
/// This example adapts functions that:
/// 1. Accesses memory in 32-bit chunks instead of bytes
/// 2. Returns error codes but no human-readable error messages
/// 
/// The Adapter functions translate the 32-bit chunk access into arrays of bytes.
/// The Adapter functions also provide human-readable messages for error codes.
/// </summary>
// ! [Using Adapter in C]
void Adapter_Exercise()
{
    printf("\nAdapter_Exercise\n");

    int dataHandle = -1;
    if (Adapter_OpenMemory(Memory_Block_0, &dataHandle))
    {
        uint8_t writeData[128] = { 0 };
        uint32_t dataSize = _countof(writeData);
        int bytesWritten = 0;
        int bytesRead = 0;
        // Create the data to be written
        for (uint32_t index = 0; index < dataSize; index++)
        {
            writeData[index] = (uint8_t)index;
        }

        // Display the data to be written
        const char* hexdump = Adapter_BufferToString(writeData, dataSize, 2);
        if (hexdump == NULL)
        {
            printf("  %s\n", Adapter_GetLastErrorMessage());
        }
        else
        {
            printf("  Data written:\n");
            printf("%s\n", hexdump);

            if (Adapter_WriteMemory(dataHandle, 0, writeData, dataSize, &bytesWritten))
            {
                uint8_t readData[128] = { 0 };
                if (Adapter_ReadMemory(dataHandle, 0, readData, bytesWritten, &bytesRead))
                {
                    hexdump = Adapter_BufferToString(readData, bytesRead, 2);
                    if (hexdump == NULL)
                    {
                        printf("  %s\n", Adapter_GetLastErrorMessage());
                    }
                    else
                    {
                        printf("  Data read:\n");
                        printf("%s\n", hexdump);
                    }
                }
                else
                {
                    printf("  %s\n", Adapter_GetLastErrorMessage());
                }
            }
            else
            {
                printf("  %s\n", Adapter_GetLastErrorMessage());
            }
        }

        if (!Adapter_CloseMemory(dataHandle))
        {
            printf("  %s\n", Adapter_GetLastErrorMessage());
        }
    }
    else
    {
        printf("  %s\n", Adapter_GetLastErrorMessage());
    }

    printf("  Done.\n");
}
// ! [Using Adapter in C]

