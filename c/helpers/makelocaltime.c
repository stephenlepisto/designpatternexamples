/// @file
/// @brief
/// Implementation of the makelocaltime() function
/// to convert a time_t to a struct tm containing the local time.

// Posix way of asking for bounds-checked versions of library functions.
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>

#include "makelocaltime.h"

//////////////////////////////////////////////////////////////////////////////
// makelocaltime function
//////////////////////////////////////////////////////////////////////////////
struct tm* makelocaltime(const time_t* time, struct tm* timestruct)
{
    struct tm* returnstruct = NULL;
    if (time != NULL && timestruct != NULL)
    {
        returnstruct = localtime(time);
        *timestruct = *returnstruct;
        returnstruct = timestruct;
    }
    return returnstruct;
}
