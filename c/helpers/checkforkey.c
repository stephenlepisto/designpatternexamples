/// @file
/// @brief
/// Implementation of the checkforkey() function for determining if a key
/// has been pressed.

#ifdef _MSC_VER
#include <conio.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#include "checkforkey.h"

#ifndef _MSC_VER
int kbhit (void)
{
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);

    select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);

}
#endif


/// <summary>
/// Determine if a key has been pressed.
/// </summary>
/// <returns>Returns true if a key has been pressed; otherwise, returns
/// false.  Call readkey() to get the actual key.</returns>
bool checkforkey(void)
{
#ifdef _MSC_VER
    return _kbhit() != 0;
#else
    return kbhit() != 0;
#endif
}
