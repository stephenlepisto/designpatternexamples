/// @file
/// @brief
/// Implementation of the makelocaltime() function
/// to convert a time_t to a struct tm containing the local time.

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
