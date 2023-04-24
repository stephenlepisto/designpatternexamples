/// @file
/// @brief
/// Declaration of the uint32_to_binary() function, that converts a 32-bit
/// unsigned integer to a binary string.  Need this since C does not normally
/// provide a printf() converter to binary.

#pragma once
#ifndef __UINT32_TO_BINARY_H__
#define __UINT32_TO_BINARY_H__

#include <stdint.h>

/// <summary>
/// Function to convert a 32-bit unsigned integer into a string representation
/// containing all 32 bits.
/// 
/// Need this since C does not normally provide a printf() converter to binary.
/// </summary>
/// <param name="number">The number to convert to a string representation in
/// binary.</param>
/// <param name="buffer">A buffer to store the string representation.</param>
/// <param name="bufferSize">The size of the buffer.  Should be at least 33
/// characters.</param>
void uint32_to_binary(uint32_t number, char* buffer, size_t bufferSize);

#endif //__UINT32_TO_BINARY_H__
