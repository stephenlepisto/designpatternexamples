/// @file
/// @brief
/// Implementation of the @ref Helpers::makelocaltime "makelocaltime()" function
/// to convert a time_t to a struct tm containing the local time.

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
            returnstruct = localtime(time);
            *timestruct = *returnstruct;
            returnstruct = timestruct;
        }
        return returnstruct;
    }

} // end namespace
