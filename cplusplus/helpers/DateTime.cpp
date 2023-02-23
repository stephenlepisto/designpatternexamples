#include <chrono>

#include "DateTime.h"
#include "makelocaltime.h"

namespace Helpers
{

    //////////////////////////////////////////////////////////////////////////////
    // ToString() method
    //////////////////////////////////////////////////////////////////////////////
    std::string DateTime::ToString()
    {
        std::string time_as_string;
        struct tm local_time { 0 };
        struct tm* retval = Helpers::makelocaltime(&timestamp, &local_time);
        if (retval != nullptr)
        {
            char str[128]{ '\0' };
            strftime(str, sizeof str, "%m/%d/%Y %r", &local_time);
            time_as_string = str;
        }

        return time_as_string;
    }

    //////////////////////////////////////////////////////////////////////////////
    // Now() method
    //////////////////////////////////////////////////////////////////////////////
    DateTime DateTime::Now()
    {
        auto now_time = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now_time);
        return DateTime(now_time_t);
    }

} // end namespace