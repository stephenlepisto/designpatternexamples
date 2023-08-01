/// @file
/// @brief
/// Implementation of the @ref Helpers::readkey() "readkey()" function, a
/// blocking read for a key from the keyboard.

#ifdef _MSC_VER
#include <conio.h>
#endif

#include "readkey.h"

namespace Helpers
{

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
        return 0x1b; // Dummy for now
#endif
    }

} // end namespace
