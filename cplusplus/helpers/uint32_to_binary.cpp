/// @file
/// @brief
/// Implementation of the uint32_to_binary() function, that converts a 32-bit
/// unsigned integer to a binary string.  Need this since C++ does not normally
/// provide a printf() converter to binary.

#include <sstream>
#include <vector>

#include "uint32_to_binary.h"

namespace Helpers
{

    ///////////////////////////////////////////////////////////////////////////////
    // uint32_to_binary()
    ///////////////////////////////////////////////////////////////////////////////
    std::string uint32_to_binary(uint32_t number)
    {
        int numBits = (sizeof(uint32_t) * 8);
        int maxBitIndex = numBits - 1;
        uint32_t mask = 1;
        std::vector<char> buffer;
        buffer.resize(numBits + 1);

        for (int bitIndex = maxBitIndex; bitIndex >= 0; bitIndex--)
        {
            buffer[bitIndex] = (number & mask) ? '1' : '0';
            mask <<= 1;
        }
        return std::string(&buffer[0]);
    }

} // end namespace
