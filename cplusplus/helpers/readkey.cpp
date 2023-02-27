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
#endif
    }

} // end namespace
