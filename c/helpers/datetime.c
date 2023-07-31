/// @file
/// @brief
/// Implementation of the DateTime functions, datetime_to_string() and datetime_now(),
/// to simplify getting the local time as a string.

#include "makelocaltime.h"
#include "datetime.h"

///////////////////////////////////////////////////////////////////////////////
// datetime_to_string()
///////////////////////////////////////////////////////////////////////////////
const char* datetime_to_string(time_t timestamp)
{
    static char str[128] = { '\0' };
    struct tm local_time = { 0 };
    struct tm* timestruct = makelocaltime(&timestamp, &local_time);
    if (timestruct != NULL)
    {
        strftime(str, sizeof(str), "%m/%d/%Y %r", &local_time);
    }
    return str;
}

///////////////////////////////////////////////////////////////////////////////
// datetime_now()
///////////////////////////////////////////////////////////////////////////////
time_t datetime_now(void)
{
    return time(NULL);
}
