#include "Bridge_LogHelper.h"

#include <stdlib.h>
#include <stdio.h>

#include "helpers/makelocaltime.h"

/// <summary>
/// Return a regular time stamp of the current time in local time.
/// </summary>
/// <returns>A string containing the current date and time expressed in
/// local time.  Valid until the next call to this function.</returns>
static const char* _GetTimeStamp()
{
    static char str[128] = { '\0' };
    time_t now = 0;
    struct tm local_time = { 0 };
    time(&now);
    struct tm* timestruct = makelocaltime(&now, &local_time);
    if (timestruct != NULL)
    {
        strftime(str, sizeof(str), "%m/%d/%Y %r", &local_time);
    }
    return str;
}


///////////////////////////////////////////////////////////////////////////////
// LogHelper_FormatLogLine()
///////////////////////////////////////////////////////////////////////////////
bool LogHelper_FormatLogLine(const char* loglevel, const char* message, char* output, size_t maxOutputSize)
{
    bool success = false;

    if (loglevel != NULL && message != NULL && output != NULL && maxOutputSize > 0)
    {
        *output = '\0';
        const char* timestamp = _GetTimeStamp();
        int numChars = sprintf_s(output, maxOutputSize, "%s [%s] %s\n", timestamp, loglevel, message);
        if (numChars != -1)
        {
            success = true;
        }
    }
    return success;
}
