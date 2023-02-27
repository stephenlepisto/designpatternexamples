#ifdef _MSC_VER
#include <conio.h>
#endif

#include "checkforkey.h"

namespace Helpers
{

    bool checkforkey()
    {
#ifdef _MSC_VER
        return _kbhit() != 0;
#else
        return false;
#endif
    }

} // end namespace
