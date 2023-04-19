/// @file
/// @brief
/// Implementation of the sleep() function, for sleeping for a number of milliseconds.
///
/// Copied from https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds#answer-28827188

#include <stdlib.h>

#ifdef _MSC_VER
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

#include "sleep.h"


// Sleep for the specified number of milliseconds.
void sleep(int milliseconds)
{
#ifdef _MSC_VER
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
        sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

