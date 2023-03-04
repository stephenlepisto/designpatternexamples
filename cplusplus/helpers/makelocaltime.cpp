/// @file
/// @brief
/// Implementation of the @ref Helpers::makelocaltime "makelocaltime()" function
/// to convert a time_t to a struct tm containing the local time.

// Posix way of asking for bounds-checked versions of library functions.
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <chrono>

#include "makelocaltime.h"

namespace Helpers
{

    //////////////////////////////////////////////////////////////////////////////
    // makelocaltime function
    //////////////////////////////////////////////////////////////////////////////
    struct tm* makelocaltime(const time_t* time, struct tm* timestruct)
    {
        struct tm* returnstruct = nullptr;
        if (time != nullptr && timestruct != nullptr)
        {
#ifdef _MSC_VER
            // Note reversal of the parameters from the other forms.
            errno_t err = localtime_s(timestruct, time);
            if (err == 0)
            {
                returnstruct = timestruct;
            }
#elif defined(__STDC_LIB_EXT1__)
            returnstruct = localtime_s(time, timestruct);
#else
            returnstruct = localtime_r(time, timestruct)
#endif
        }
        return returnstruct;
    }

} // end namespace
