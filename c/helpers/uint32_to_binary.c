/// @file
/// @brief
/// Implementation of the uint32_to_binary() function, that converts a 32-bit
/// unsigned integer to a binary string.  Need this since C does not normally
/// provide a printf() converter to binary.

#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#include "uint32_to_binary.h"

///////////////////////////////////////////////////////////////////////////////
// uint32_to_binary()
///////////////////////////////////////////////////////////////////////////////
void uint32_to_binary(uint32_t number, char* buffer, size_t bufferSize)
{
    if (buffer != NULL && bufferSize > 32)
    {
        int numBits = (sizeof(uint32_t) * 8);
        int maxBitIndex = numBits - 1;
        uint32_t mask = 1;

        memset(buffer, 0, bufferSize);
        if ((size_t)maxBitIndex >= bufferSize)
        {
            maxBitIndex = (int)(bufferSize - 1);
        }
        for (int bitIndex = maxBitIndex; bitIndex >= 0; bitIndex--)
        {
            buffer[bitIndex] = (number & mask) ? '1' : '0';
            mask <<= 1;
        }
    }
}
