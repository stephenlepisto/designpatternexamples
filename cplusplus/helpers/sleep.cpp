/// @file
/// @brief
/// Implementation of the @ref Helpers::sleep "sleep" function, for sleeping for
/// a number of milliseconds.

#include <chrono>
#include <thread>

#include "sleep.h"

namespace Helpers
{

    // Sleep for the specified number of milliseconds.
    void sleep(int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

} // end namespace
