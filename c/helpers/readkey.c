/// @file
/// @brief
/// Implementation of the readkey() function, a blocking read for a key from
/// the keyboard.

#ifdef _MSC_VER
#include <conio.h>
#endif

#include "readkey.h"

int readkey()
{
#ifdef _MSC_VER
    int retval = _getch();
    if (retval == 0)
    {
        retval = _getch();
    }
    return retval;
#else
    return 0;
#endif
}
